#!/usr/bin/env python3
"""Extract the BDAT tables of the base game from its bf2.arh / bf2.ard archive.

Usage: extract_bdat.py <bf2.arh> <bf2.ard> <output dir>

The game keeps its data in bf2.ard, indexed by bf2.arh (format "arh1"): a table of
files (offset, sizes, id) and a path trie that maps a path to a file id. This walks
the trie, writes every `/bdat/**.bdat` file below the output directory with the
same relative path, and checks the archive on the way: the trie and the file table
must agree on every file id, every extracted file must have its recorded size and a
valid BDAT header, and the number of files must be the one of the 1.0.0 base game.
Any mismatch is an error.
"""

import os
import struct
import sys
import zlib

# 1.0.0 base game: common.bdat, common_gmk.bdat, lookat.bdat and, per language
# (fr, gb, ge, it, sp), 3468 message files.
EXPECTED_FILES = 3 + 5 * 3468

XBC1_HEADER = 0x30


class ArhError(Exception):
    pass


def words(data, offset, size, key):
    """A section of the arh is stored as 32-bit words xored with a key from the header."""
    count = size // 4
    values = struct.unpack_from(f"<{count}I", data, offset)
    return struct.pack(f"<{count}I", *(v ^ key for v in values))


def read_arh(arh):
    magic, _, _, str_ptr, str_size, dict_ptr, dict_size, file_ptr, file_count, key = struct.unpack_from("<4s9I", arh, 0)
    if magic != b"arh1":
        raise ArhError("not an arh1 file")
    key = (key ^ 0xF3F35353) & 0xFFFFFFFF
    strings = words(arh, str_ptr, str_size, key)
    nodes = list(struct.iter_unpack("<ii", words(arh, dict_ptr, dict_size, key)))
    files = [struct.unpack_from("<QIIII", arh, file_ptr + 24 * i) for i in range(file_count)]
    return strings, nodes, files


def paths(strings, nodes):
    """Every path of the trie with its file id.

    A node with a non-negative `next` fans out to the nodes `next ^ c`, one per next
    character c, and owns them when their `prev` is the node. Character 0 ends a path
    that is also the prefix of another: that node's `next` is the file id. A node with
    a negative `next` is a leaf: -next points at the rest of the path in the string
    table, followed by the file id.
    """
    result = {}
    stack = [(0, b"")]
    while stack:
        node, prefix = stack.pop()
        nxt = nodes[node][0]
        if nxt < 0:
            end = strings.index(b"\0", -nxt)
            result[(prefix + strings[-nxt:end]).decode()] = struct.unpack_from("<I", strings, end + 1)[0]
            continue
        for c in range(128):
            child = nxt ^ c
            if child >= len(nodes) or child == node or nodes[child][1] != node:
                continue
            if c == 0:
                result[prefix.decode()] = nodes[child][0]
            else:
                stack.append((child, prefix + bytes([c])))
    return result


def stored_size(compressed, size):
    """The file table gives the size of the zlib stream; an xbc1 container adds its header."""
    return compressed + (XBC1_HEADER if size else 0)


def unpack(data, compressed, size):
    """Files with a nonzero uncompressed size are xbc1 containers (type 1 is zlib)."""
    if size == 0:
        return data
    if data[:4] != b"xbc1":
        raise ArhError("compressed file without xbc1 header")
    kind, expected, stream = struct.unpack_from("<III", data, 4)
    if kind != 1 or expected != size or stream != compressed:
        raise ArhError(f"unexpected xbc1 header (type {kind}, size {expected} != {size}, stream {stream} != {compressed})")
    return zlib.decompress(data[XBC1_HEADER:])


def check_bdat(name, data):
    """File header: table count, file size, table offsets; every table starts with BDAT."""
    if len(data) < 12:
        raise ArhError(f"{name}: too short for a BDAT file")
    count, length = struct.unpack_from("<II", data, 0)
    if length != len(data):
        raise ArhError(f"{name}: header says {length} bytes, file has {len(data)}")
    for i in range(count):
        offset = struct.unpack_from("<I", data, 8 + 4 * i)[0]
        if data[offset:offset + 4] != b"BDAT":
            raise ArhError(f"{name}: table {i} has no BDAT magic")


def main():
    if len(sys.argv) != 4:
        sys.exit(__doc__)
    arh_path, ard_path, out = sys.argv[1:]
    with open(arh_path, "rb") as f:
        strings, nodes, files = read_arh(f.read())
    index = paths(strings, nodes)
    if sorted(index.values()) != list(range(len(files))):
        raise ArhError(f"path trie holds {len(index)} paths for {len(files)} files, ids do not match")
    for path, fid in index.items():
        if files[fid][4] != fid:
            raise ArhError(f"{path}: file table entry {fid} has id {files[fid][4]}")

    bdats = sorted(p for p in index if p.startswith("/bdat/") and p.endswith(".bdat"))
    if len(bdats) != EXPECTED_FILES:
        raise ArhError(f"found {len(bdats)} BDAT files, the 1.0.0 base game has {EXPECTED_FILES}")

    total = 0
    with open(ard_path, "rb") as ard:
        for path in bdats:
            offset, compressed, size, _, _ = files[index[path]]
            ard.seek(offset)
            raw = ard.read(stored_size(compressed, size))
            if len(raw) != stored_size(compressed, size):
                raise ArhError(f"{path}: archive ends inside the file")
            data = unpack(raw, compressed, size)
            if size and len(data) != size:
                raise ArhError(f"{path}: unpacked {len(data)} bytes, expected {size}")
            check_bdat(path, data)
            dest = os.path.join(out, path.lstrip("/"))
            os.makedirs(os.path.dirname(dest), exist_ok=True)
            with open(dest, "wb") as f:
                f.write(data)
            total += len(data)
    languages = sorted({p.split("/")[2] for p in bdats if p.count("/") == 3})
    print(f"{len(bdats)} BDAT files ({total} bytes) of {len(files)} archive files, languages {' '.join(languages)}")


if __name__ == "__main__":
    try:
        main()
    except (ArhError, OSError, zlib.error, struct.error, ValueError) as e:
        sys.exit(f"extract_bdat: {e}")
