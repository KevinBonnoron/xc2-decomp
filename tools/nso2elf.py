#!/usr/bin/env python3
"""Convert an uncompressed NSO into an AArch64 ELF with relocations applied and a full symtab."""
import struct
import sys

from nso_syms import load_nso, symbols

BASE = 0x7100000000
PAGE = 0x1000

R_AARCH64_ABS64 = 257
R_AARCH64_GLOB_DAT = 1025
R_AARCH64_JUMP_SLOT = 1026
R_AARCH64_RELATIVE = 1027


def align(x, a):
    return (x + a - 1) & ~(a - 1)


def parse_dynamic(image):
    mod0 = struct.unpack_from("<I", image, 4)[0]
    assert image[mod0:mod0 + 4] == b"MOD0"
    dyn = mod0 + struct.unpack_from("<i", image, mod0 + 4)[0]
    tags = {}
    off = dyn
    while True:
        tag, val = struct.unpack_from("<qQ", image, off)
        off += 16
        if tag == 0:
            break
        tags[tag] = val
    return tags


def apply_relocs(image, tags, syms):
    relocs = []
    if 7 in tags:
        relocs.append((tags[7], tags[8]))
    if 23 in tags:
        relocs.append((tags[23], tags[2]))
    imports = []
    for start, size in relocs:
        for off in range(start, start + size, 24):
            r_off, r_info, addend = struct.unpack_from("<QQq", image, off)
            rtype, sym = r_info & 0xFFFFFFFF, r_info >> 32
            if rtype == R_AARCH64_RELATIVE:
                struct.pack_into("<Q", image, r_off, BASE + addend)
            elif rtype in (R_AARCH64_ABS64, R_AARCH64_GLOB_DAT, R_AARCH64_JUMP_SLOT):
                value, _, _, shndx, name = syms[sym]
                if shndx != 0:
                    struct.pack_into("<Q", image, r_off, BASE + value + addend)
                elif name:
                    imports.append((r_off, name, rtype == R_AARCH64_JUMP_SLOT))
    return imports


def main():
    src, dst = sys.argv[1], sys.argv[2]
    image, segs, ro_moff, dynstr, dynsym = load_nso(src)
    syms = list(symbols(image, ro_moff, dynstr, dynsym))
    imports = apply_relocs(image, parse_dynamic(image), syms)

    (t_off, t_mem, t_size, _), (r_off, r_mem, r_size, _), (d_off, d_mem, d_size, bss) = segs
    sections = [
        (".text", 1, 0x6, t_mem, t_size),
        (".rodata", 1, 0x2, r_mem, r_size),
        (".data", 1, 0x3, d_mem, d_size),
        (".bss", 8, 0x3, d_mem + d_size, bss),
    ]

    def section_of(addr):
        for i, (_, _, _, mem, size) in enumerate(sections):
            if mem <= addr < mem + size:
                return i + 1
        return 0xFFF1

    strtab = bytearray(b"\0")
    symtab = bytearray(24)
    entries = []
    for value, size, typ, shndx, name in syms:
        if shndx != 0 and name:
            entries.append((name, BASE + value, size, typ, section_of(value)))
    for r_off_, name, is_plt in imports:
        prefix = "__imp_" if is_plt else "__got_"
        entries.append((prefix + name, BASE + r_off_, 8, 1, section_of(r_off_)))
    for name, value, size, typ, shndx in entries:
        name_off = len(strtab)
        strtab += name.encode() + b"\0"
        symtab += struct.pack("<IBBHQQ", name_off, 0x10 | typ, 0, shndx, value, size)

    shstrtab = bytearray(b"\0")
    sh_names = {}
    for n in [s[0] for s in sections] + [".symtab", ".strtab", ".shstrtab"]:
        sh_names[n] = len(shstrtab)
        shstrtab += n.encode() + b"\0"

    phnum = 3
    out = bytearray(align(64 + 56 * phnum, PAGE))
    file_offs = []
    for _, mem, size in ((t_off, t_mem, t_size), (r_off, r_mem, r_size), (d_off, d_mem, d_size)):
        out += bytes(align(len(out), PAGE) - len(out))
        file_offs.append(len(out))
        out += image[mem:mem + size]

    def blob(b):
        nonlocal out
        out += bytes(align(len(out), 8) - len(out))
        off = len(out)
        out += b
        return off

    symtab_off = blob(symtab)
    strtab_off = blob(strtab)
    shstrtab_off = blob(shstrtab)
    out += bytes(align(len(out), 8) - len(out))
    shoff = len(out)

    shdrs = [bytes(64)]
    for i, (name, typ, flags, mem, size) in enumerate(sections):
        foff = file_offs[i] if typ == 1 else file_offs[2] + d_size
        shdrs.append(struct.pack("<IIQQQQIIQQ", sh_names[name], typ, flags, BASE + mem, foff, size, 0, 0, 16, 0))
    shdrs.append(struct.pack("<IIQQQQIIQQ", sh_names[".symtab"], 2, 0, 0, symtab_off, len(symtab), 6, 1, 8, 24))
    shdrs.append(struct.pack("<IIQQQQIIQQ", sh_names[".strtab"], 3, 0, 0, strtab_off, len(strtab), 0, 0, 1, 0))
    shdrs.append(struct.pack("<IIQQQQIIQQ", sh_names[".shstrtab"], 3, 0, 0, shstrtab_off, len(shstrtab), 0, 0, 1, 0))
    for s in shdrs:
        out += s

    ident = b"\x7fELF" + bytes([2, 1, 1, 0]) + bytes(8)
    struct.pack_into("<16sHHIQQQIHHHHHH", out, 0, ident, 2, 183, 1, BASE, 64, shoff, 0, 64, 56, phnum, 64, len(shdrs), len(shdrs) - 1)
    phdrs = [
        (5, file_offs[0], t_mem, t_size, t_size),
        (4, file_offs[1], r_mem, r_size, r_size),
        (6, file_offs[2], d_mem, d_size, d_size + bss),
    ]
    for i, (flags, foff, mem, filesz, memsz) in enumerate(phdrs):
        struct.pack_into("<IIQQQQQQ", out, 64 + 56 * i, 1, flags, foff, BASE + mem, BASE + mem, filesz, memsz, PAGE)

    open(dst, "wb").write(out)
    print(f"{dst}: {len(entries)} symbols ({len(imports)} imports), base {BASE:#x}")


if __name__ == "__main__":
    main()
