#!/usr/bin/env python3
"""Load an uncompressed NSO and dump its dynamic symbols as `addr size type name`."""
import struct
import sys


def load_nso(path):
    data = open(path, "rb").read()
    assert data[:4] == b"NSO0", "not an NSO"
    flags = struct.unpack_from("<I", data, 0xC)[0]
    assert flags & 7 == 0, "NSO is compressed, run hactool --uncompressed first"
    segs = []
    for i in range(3):
        foff, moff, size, extra = struct.unpack_from("<4I", data, 0x10 + i * 0x10)
        segs.append((foff, moff, size, extra))
    bss = segs[2][3]
    end = segs[2][1] + segs[2][2] + bss
    image = bytearray(end)
    for foff, moff, size, _ in segs:
        image[moff:moff + size] = data[foff:foff + size]
    ro_moff = segs[1][1]
    dynstr = struct.unpack_from("<II", data, 0x90)
    dynsym = struct.unpack_from("<II", data, 0x98)
    return image, segs, ro_moff, dynstr, dynsym


def symbols(image, ro_moff, dynstr, dynsym):
    str_base = ro_moff + dynstr[0]
    sym_base = ro_moff + dynsym[0]
    for off in range(sym_base, sym_base + dynsym[1], 24):
        name_off, info, other, shndx, value, size = struct.unpack_from("<IBBHQQ", image, off)
        end = image.index(0, str_base + name_off)
        name = image[str_base + name_off:end].decode("utf-8", "replace")
        yield value, size, info & 0xF, shndx, name


def main():
    image, segs, ro_moff, dynstr, dynsym = load_nso(sys.argv[1])
    types = {0: "NOTYPE", 1: "OBJECT", 2: "FUNC"}
    for value, size, typ, shndx, name in symbols(image, ro_moff, dynstr, dynsym):
        if name:
            print(f"{value:08x} {size:6x} {types.get(typ, typ):6} {'U' if shndx == 0 else 'D'} {name}")


if __name__ == "__main__":
    main()
