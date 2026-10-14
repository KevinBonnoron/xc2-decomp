#!/usr/bin/env python3
"""Generate the BDAT accessor sources (gf_bdat_*.cpp/.h) from the game's own code.

Usage: gen_bdat.py <namespace tag> <class> <file stem>
       gen_bdat.py bbt GfBdatBtl gf_bdat_btl

The game's BDAT accessors are generated code: for each column, a `_gfbXX::initColumn`
stores a member pointer in a static variable, and `_gfbXX::getColumn` reads the
column through it. The `GfBdatXxx` class repeats every getter on its own tables.
This script reads those functions back from work/main_100.elf and writes the
equivalent C++.
"""

import os
import re
import struct
import subprocess
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
ELF = os.path.join(ROOT, "work", "main_100.elf")
BASE = 0x7100000000

INSN = re.compile(r"^\s*([0-9a-f]+):\s+(\S+)\s*(.*)$")
FUNC = re.compile(r"^([0-9a-f]+) <(\S+)>:$")

TYPES = {
    "and #0xffff": ("u32", "valueU16"),
    "and #0xff": ("u32", "valueU8"),
    "sxth": ("s32", "valueS16"),
    "sxtb": ("s32", "valueS8"),
    "none": ("u32", "valueU32"),
    "pointer": ("const char *", "valueString"),
    "float": ("f32", "valueF32"),
}


def run(args):
    return subprocess.run(args, check=True, capture_output=True, text=True).stdout


def symbols():
    result = []
    for line in run(["llvm-nm", "--defined-only", "-S", ELF]).splitlines():
        parts = line.split()
        if len(parts) == 4 and parts[2] in "Tt":
            result.append((int(parts[0], 16), int(parts[1], 16), parts[3]))
    return result


class Elf:
    def __init__(self):
        self.data = open(ELF, "rb").read()
        shoff = struct.unpack_from("<Q", self.data, 0x28)[0]
        size, count = struct.unpack_from("<HH", self.data, 0x3A)
        self.sections = [struct.unpack_from("<IIQQQQIIQQ", self.data, shoff + i * size) for i in range(count)]

    def string(self, addr):
        for _, typ, _, start, offset, length, *_ in self.sections:
            if typ != 8 and start and start <= addr < start + length:
                pos = offset + addr - start
                return self.data[pos:self.data.index(b"\0", pos)].decode()
        raise ValueError(hex(addr))


def disassemble(names):
    out = run(["llvm-objdump", "-d", "--no-show-raw-insn", *(f"--disassemble-symbols={n}" for n in names), ELF])
    funcs, current = {}, None
    for line in out.splitlines():
        header = FUNC.match(line)
        if header:
            current = funcs.setdefault(header.group(2), [])
            continue
        insn = INSN.match(line)
        if insn and current is not None:
            current.append((insn.group(2), insn.group(3).split("//")[0].strip()))
    return funcs


def imm(text):
    return int(text.strip().lstrip("#"), 0)


def addresses(insns):
    """Follow adrp/add/ldr/str to the absolute addresses each instruction touches."""
    regs, touched = {}, []
    for op, args in insns:
        parts = [a.strip() for a in re.split(r",(?![^\[]*\])", args)]
        if op == "adrp":
            regs[parts[0][1:]] = int(parts[1].split()[0], 16)
        elif op == "add" and len(parts) == 3 and parts[1][1:] in regs and parts[2].startswith("#"):
            regs[parts[0][1:]] = regs[parts[1][1:]] + imm(parts[2])
        elif op == "ldp" and len(parts) == 3:
            mem = re.match(r"\[(\w+)(?:, #(-?0x[0-9a-f]+|\d+))?\]", parts[2])
            if mem and mem.group(1)[1:] in regs:
                base = regs[mem.group(1)[1:]] + (imm(mem.group(2)) if mem.group(2) else 0)
                touched.append(("ldr", parts[0], base))
                touched.append(("ldr", parts[1], base + 8))
        elif op in ("ldr", "str") and len(parts) == 2:
            mem = re.match(r"\[(\w+)(?:, #(-?0x[0-9a-f]+|\d+))?\]", parts[1])
            if mem and mem.group(1)[1:] in regs:
                touched.append((op, parts[0], regs[mem.group(1)[1:]] + (imm(mem.group(2)) if mem.group(2) else 0)))
                if op == "ldr":
                    regs.pop(parts[0][1:], None)
    return regs, touched


def parse_init(insns, elf):
    strings, stores, regs = [], [], {}
    for op, args in insns:
        parts = [a.strip() for a in re.split(r",(?![^\[]*\])", args)]
        if op == "adrp":
            regs[parts[0]] = int(parts[1].split()[0], 16)
        elif op == "add" and len(parts) == 3 and parts[1] in regs and parts[2].startswith("#"):
            regs[parts[0]] = regs[parts[1]] + imm(parts[2])
            if parts[0] == "x1":
                strings.append(elf.string(regs["x1"]))
        elif op == "str" and parts[0] == "x0":
            mem = re.match(r"\[(\w+)(?:, #(-?0x[0-9a-f]+|\d+))?\]", parts[1])
            stores.append(regs[mem.group(1)] + (imm(mem.group(2)) if mem.group(2) else 0))
    return list(zip(stores, strings))


def parse_getter(insns):
    _, touched = addresses(insns)
    statics = []
    for op, reg, addr in touched:
        if op == "ldr" and reg.startswith("x") and addr not in statics:
            statics.append(addr)
    call = next((a for o, a in insns if o == "bl" and ("getValCheck" in a or "getFlagVal" in a)), "")
    if "getFlagVal" in call:
        return {"kind": "flag", "statics": statics[:2]}
    code = next(imm(a.split(",")[-1]) for o, a in insns if o in ("orr", "mov") and a.startswith("w3,"))
    after = [o + " " + a for o, a in insns[[i for i, (o, a) in enumerate(insns) if o == "bl" and "getValCheck" in a][0] + 1:]]
    if any(o == "mov" and a == "x0, xzr" for o, a in insns):
        kind = "pointer"
    elif any(o == "fmov" and a.startswith("s8, w0") for o, a in insns):
        kind = "float"
    elif after and after[0].startswith("and w0, w0, #0xffff"):
        kind = "and #0xffff"
    elif after and after[0].startswith("and w0, w0, #0xff"):
        kind = "and #0xff"
    elif after and after[0].startswith("sxth"):
        kind = "sxth"
    elif after and after[0].startswith("sxtb"):
        kind = "sxtb"
    else:
        kind = "none"
    return {"kind": kind, "statics": statics[:1], "code": code}


def demangled_name(mangled):
    m = re.match(r"_ZN2gf\d+_gfb\w\w(\d+)", mangled)
    n = int(m.group(1))
    return mangled[m.end():m.end() + n]


def main():
    tag, cls, stem = sys.argv[1:]
    ns = f"_gf{tag}"
    syms = symbols()
    prefix = f"_ZN2gf6{ns}"
    funcs = sorted((s for s in syms if s[2].startswith(prefix)), key=lambda s: s[0])
    class_prefix = f"_ZNK2gf{len(cls)}{cls}"
    methods = sorted((s for s in syms if s[2].startswith(class_prefix)), key=lambda s: s[0])
    code = disassemble([f[2] for f in funcs] + [m[2] for m in methods])
    elf = Elf()

    statics = {}
    entries = []
    for addr, size, mangled in funcs:
        name = demangled_name(mangled)
        insns = code[mangled]
        if name.startswith("init"):
            column = name[len("init"):]
            stored = parse_init(insns, elf)
            for i, (static, member) in enumerate(stored):
                statics[static] = (column if i == 0 else column + "Flag", member)
            entries.append(("init", name, column, [s for s, _ in stored], mangled, [m for _, m in stored]))
        else:
            try:
                info = parse_getter(insns)
            except (StopIteration, IndexError):
                print(f"skipped {name}", file=sys.stderr)
                continue
            entries.append(("get", name, info, mangled))

    tables = {}
    for addr, size, mangled in methods:
        insns = code.get(mangled, [])
        load = next((a for o, a in insns if o == "ldr" and re.match(r"x\d+, \[x0, #0x[0-9a-f]+\]", a)), None)
        if load:
            tables[mangled] = imm(load.split("#")[1].rstrip("]"))

    direct = {s for e in entries if e[0] == "init" and len(code[e[4]]) <= 10 for s in e[3]}
    write(cls, ns, stem, statics, entries, methods, tables, code, direct)


def static_name(statics, addr):
    if len(statics[addr]) == 3:
        return f"s_{statics[addr][0]}"
    return f"s_members[{statics[addr][0]}]"


def write(cls, ns, stem, statics, entries, methods, tables, code, direct):
    out = []
    w = out.append
    w(f'#include "gf/data/{stem}.h"')
    w('#include "bdat.h"')
    w("")
    w("namespace gf {")
    w(f"namespace {ns} {{")
    w("")
    first = min(statics)
    separate = [a for a in sorted(statics) if a in direct and a != first]
    for addr in separate:
        statics[addr] = (statics[addr][0], statics[addr][1], True)
    w("enum {")
    for addr in sorted(statics):
        if addr in separate:
            continue
        w(f"  {statics[addr][0]},")
    w("  MEMBER_COUNT,")
    w("};")
    w("")
    w("static u8 *s_members[MEMBER_COUNT];")
    for addr in separate:
        w(f"static u8 *s_{statics[addr][0]};")
    w("")
    getters = {}
    for entry in entries:
        if entry[0] == "init":
            _, name, column, stores, _, members = entry
            w(f"void {name}(const CBdatWrapper &wrapper) {{")
            for static, member in zip(stores, members):
                w(f'  {static_name(statics, static)} = Bdat::getMember(wrapper.data, "{member}");')
            w("}")
            w("")
            continue
        _, name, info, mangled = entry
        getters[name] = info
        if info["kind"] == "flag":
            member, flag = (static_name(statics, a) for a in info["statics"])
            w(f"bool {name}(const CBdatWrapper &wrapper, u32 id) {{")
            w(f"  if ({member} == nullptr || {flag} == nullptr || id < Bdat::getIdTop(wrapper.data) ||")
            w("      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {")
            w("    return false;")
            w("  }")
            w("")
            w(f"  return wrapper.getFlagVal({member}, id, {flag}) != 0;")
            w("}")
            w("")
            continue
        ret, field = TYPES[info["kind"]]
        member = static_name(statics, info["statics"][0])
        zero = "nullptr" if info["kind"] == "pointer" else "0"
        w(f"{ret} {name}(const CBdatWrapper &wrapper, u32 id) {{")
        if info["kind"] == "float":
            w("  f32 value = 0.0f;")
            w(f"  if ({member} != nullptr && id >= Bdat::getIdTop(wrapper.data) && id < Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {{")
            w(f"    value = wrapper.getValCheck({member}, id, {info['code']}).{field};")
            w("  }")
            w("")
            w("  return value;")
        else:
            w(f"  if ({member} == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {{")
            w(f"    return {zero};")
            w("  }")
            w("")
            w(f"  return wrapper.getValCheck({member}, id, {info['code']}).{field};")
        w("}")
        w("")
    w(f"}} // namespace {ns}")
    w("")

    table_names = {}
    for mangled, offset in tables.items():
        table_names.setdefault(offset, []).append(re.sub(r"^(get|is)", "", demangled(mangled)))
    member_names = {offset: "m" + common_prefix(names) for offset, names in table_names.items()}

    declarations = []
    for addr, size, mangled in methods:
        name = demangled(mangled)
        args = mangled[len(f"_ZNK2gf{len(cls)}{cls}{len(name)}{name}"):]
        if name.endswith("Start") and args == "Ev" and mangled in tables:
            table = member_names[tables[mangled]]
            declarations.append(f"  u32 {name}() const;")
            w(f"u32 {cls}::{name}() const {{ return Bdat::getIdTop({table}->data); }}")
            w("")
        elif name.endswith("End") and args == "Ev" and mangled in tables:
            table = member_names[tables[mangled]]
            declarations.append(f"  u32 {name}() const;")
            w(f"u32 {cls}::{name}() const {{ return Bdat::getIdTop({table}->data) + Bdat::getIdCount({table}->data); }}")
            w("")
        elif args == "Ej" and name in getters and mangled in tables:
            info = getters[name]
            ret = "bool" if info["kind"] == "flag" else TYPES[info["kind"]][0]
            table = member_names[tables[mangled]]
            declarations.append(f"  {ret} {name}(u32 id) const;")
            w(f"{ret} {cls}::{name}(u32 id) const {{ return {ns}::{name}(*{table}, id); }}")
            w("")
    w("} // namespace gf")
    open(os.path.join(ROOT, "src", "application", "BF2", "gf", "data", stem + ".cpp"), "w").write("\n".join(out) + "\n")

    header = [
        "#pragma once",
        '#include "gf/data/gf_bdat_wrapper.h"',
        '#include "mm_mtl/singleton.h"',
        '#include "types.h"',
        "",
        "namespace gf {",
        "",
        f"class {cls} : public mm::mtl::PtrSingleton<{cls}>, public GfBdatRefresh {{",
        "public:",
        *declarations,
        "",
        "private:",
    ]
    end = 0x10
    for offset in sorted(member_names):
        if offset > end:
            header.append(f"  CBdatWrapper *_{end:02x}[{(offset - end) // 8}];")
        header.append(f"  CBdatWrapper *{member_names[offset]};")
        end = offset + 8
    header += ["};", "", "} // namespace gf", ""]
    path = os.path.join(ROOT, "src", "application", "BF2", "gf", "data", stem + ".h")
    if os.path.exists(path):
        generated = {(re.search(r"(\w+)\(", d).group(1), d.count(",")) for d in declarations}
        kept = []
        for line in open(path).read().splitlines():
            decl = re.match(r"  (?:static )?[\w:<>, *&]+?[ *&](\w+)\((.*)\)( const)?;$", line)
            if decl and (decl.group(1), decl.group(2).count(",")) not in generated:
                kept.append(line)
        if kept:
            index = header.index("") if False else header.index("private:") - 1
            header[index:index] = [""] + kept
    open(path, "w").write("\n".join(header))


def demangled(mangled):
    m = re.match(r"_ZNK2gf\d+\w+?(\d+)([A-Za-z_]\w*)", mangled)
    rest = mangled[len(re.match(r"_ZNK2gf(\d+)", mangled).group(0)):]
    cls_len = int(re.match(r"_ZNK2gf(\d+)", mangled).group(1))
    rest = rest[cls_len:]
    n = int(re.match(r"\d+", rest).group(0))
    start = len(str(n))
    return rest[start:start + n]


def common_prefix(names):
    prefix = os.path.commonprefix(names)
    return prefix if prefix else names[0]


if __name__ == "__main__":
    main()
