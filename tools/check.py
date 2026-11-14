#!/usr/bin/env python3
"""Compile sources and compare functions against the original game binary.

Usage:
  check                                   check every function defined in src/ and show the game progress,
                                          listing only the functions that do not match
  check -v                                same, and list every function
  check --readme                          same, and update the progress section of README.md
  check --strict-data                     same, and fail on a problem of the data report below that tools/data_baseline.txt
                                          does not list (the pre-commit hook runs it)
  check --write-data-baseline             full check only: rewrite tools/data_baseline.txt from the data report
  check --compile                         only compile every source and header of src/ and include/ with the game's
                                          flags and look for absolute includes; needs no game executable, so it
                                          runs in the continuous integration
  check <scope>                           check every function of a class or namespace, list the missing ones
  check <symbol>                          diff one function, its source file is found automatically
  check <symbol> <source.cpp> [flags...]  diff one function from a given file
  check <address> <source.cpp> <name> [flags...]
                                          diff a function the game has no symbol for

<scope> is a class or namespace: gf::GfDataManager.
<symbol> is either a mangled name or a demangled one, with or without its
signature: gf::GfDataBlade::setHikariCurrent or 'gf::GfDataBlade::setHikariCurrent(bool)'.

A function matches when its bytes, placed at the game address with every
relocation resolved, equal the game's bytes. Only source locations may differ:
the directory of a __FILE__ path, the __LINE__ passed to an assertion or to
operator new, and the spaces of an assertion text. Data local to your file has
no symbol in the game: read-only data must hold the game's bytes, writable data
must be at one game address wherever the function uses it.

A global function you define that the game has no symbol for is listed as NOT IN
GAME, with the game functions of the same name: usually a wrong namespace or
parameter type in its signature.

Functions local to their source file (static, anonymous namespace) have no
symbol in the game. A full check finds the game address of each one where the
callers that match call it, and checks it too. To diff one by hand, pass its
game address and its name in your file (mangled, qualified or not), e.g.
  check 0x710028c7ec src/application/BF2/gf/data/gf_data_obj.cpp unknown001
The game side ends at the next named function or at the next address some bl
calls, whichever comes first; your function is compared over its own size.

A full check ends with a report of what the function check does not compare. It
is only printed and counted (data: N problems, duplicate definitions: N, local
prefix matches: N) and never fails the check, until --strict-data turns it into
a failure. It lists, as DATA, a global data object (a table, a vtable) whose size,
bytes or pointers differ from the game's symbol of that name, a writable data
object local to your file that a matching function places on a game symbol, and
two local objects placed over each other; as DUPLICATE, a global function (not a
weak inline or template one) defined by several sources; and as PREFIX, a local
function that matches only the start of the game's code at its address.

tools/data_baseline.txt lists the problems accepted for now, one per line as
`KIND SYMBOL WHERE  # reason` (the key holds no address of your objects, so it
survives code moving around). --strict-data fails only on a problem the file does
not list or lists without a reason, and prints `fixed:` for a listed problem the
check no longer reports. --write-data-baseline rewrites the file from the report,
keeping the reasons: give each new line its reason, which is reviewed like code.
"""
import bisect
import difflib
import glob
import hashlib
import multiprocessing
import os
import pickle
import re
import struct
import subprocess
import sys
import tempfile
import threading
from collections import defaultdict, namedtuple
from concurrent.futures import ProcessPoolExecutor, ThreadPoolExecutor
from functools import lru_cache
from types import SimpleNamespace

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
TARGET_ELF = os.path.join(ROOT, "work", "main_100.elf")
SRC_DIR = os.path.join(ROOT, "src")
CACHE_DIR = os.path.join(ROOT, "work", "check_cache")

CXX = "clang++-3.9.1"
SYSROOT = os.environ.get("XC2_SYSROOT") or sys.exit("check: XC2_SYSROOT is not set, run it from the nix develop shell")

CXXFLAGS = [
    "--target=aarch64-none-elf",
    "-mcpu=cortex-a57+fp+simd+crypto+crc",
    "-O3",
    "-std=c++14",
    "-fno-exceptions",
    "-fno-rtti",
    "-fno-strict-aliasing",
    "-fno-slp-vectorize",
    "-mno-implicit-float",
    "-fPIC",
    "-g",
    "-D_GNU_SOURCE",
    # Only the headers of the sysroot: a host with /usr/include (any non-Nix Linux, as the CI runners) must not
    # provide its own libc headers before the musl ones. It changes no code generation.
    "-nostdlibinc",
    # Diagnostics only, no code generation: clang 3.9.1's spelling correction ("did you mean") can allocate without
    # bound on an undeclared identifier (20+ GB in seconds on a dr unit) instead of reporting the error.
    "-fno-spell-checking",
    "-I" + os.path.join(ROOT, "include"),
    "-I" + os.path.join(ROOT, "src", "application", "BF2"),
    "-I" + os.path.join(ROOT, "src", "libs", "monolib_mm", "source"),
    "-isystem" + os.path.join(SYSROOT, "include", "c++", "v1"),
    "-idirafter" + os.path.join(SYSROOT, "include"),
]
INCLUDE_DIRS = [flag[2:] for flag in CXXFLAGS if flag.startswith("-I")]

SOURCE_PATH = re.compile(r".*[/\\]([^/\\]+\.(?:cpp|h|inl|c))")
# Calls that receive __LINE__ (argument register) and an assertion text (x0): neither is game logic.
SOURCE_LOCATION_CALLS = {
    "_ZN2mm9MMStdBase8mmAssertEPKcS2_j": (2, True),
    "_ZnwmPN2gf11GfAllocatorEPKcmi": (3, False),
}
# Bytes before a source-location call in which its __LINE__ and assertion text are set up.
SOURCE_LOCATION_WINDOW = 64
# Complete and base constructors and destructors are aliases at the same address: either name finds it.
STRUCTOR = re.compile(r"(_ZN\w*?[0-9][A-Za-z_][A-Za-z0-9_]*)(C|D)([12])(E.*)")
MANGLED = re.compile(r"_Z\w+")
INCLUDE_CPP = re.compile(r'^#include "([^"]+\.cpp)"', re.M)
# The last operand of a pc-relative instruction as llvm-mc prints it: an offset from the instruction.
PC_RELATIVE_OPERAND = re.compile(r"#-?(?:0x[0-9a-f]+|\d+)$")
SHT_SYMTAB, SHT_RELA, SHT_NOBITS = 2, 4, 8
SHF_WRITE, SHF_EXECINSTR, SHF_MERGE, SHF_STRINGS = 0x1, 0x4, 0x10, 0x20
STT_OBJECT, STT_FUNC, STT_SECTION = 1, 2, 3
STB_LOCAL, STB_GLOBAL = 0, 1
SHN_LORESERVE = 0xFF00
# AArch64 relocations of code, by the instruction field they fill: the page of an address (adrp), its low 12 bits
# scaled by the access size (add, ldr, str), or a branch offset of the given width.
PAGE = ("page",)
RELOCATION_FIELDS = {
    275: PAGE, 276: PAGE, 311: PAGE,  # ADR_PREL_PG_HI21(_NC), ADR_GOT_PAGE
    277: ("lo12", 0), 278: ("lo12", 0), 284: ("lo12", 1), 285: ("lo12", 2), 286: ("lo12", 3), 299: ("lo12", 4),
    312: ("lo12", 3),  # ADD_ABS_LO12_NC, LDST8/16/32/64/128_ABS_LO12_NC, LD64_GOT_LO12_NC
    279: ("branch", 14), 280: ("branch", 19), 282: ("branch", 26), 283: ("branch", 26),  # TSTBR14, CONDBR19, JUMP26, CALL26
}
GOT_RELOCATIONS = {311, 312}
R_ABS64, R_ABS32, R_PREL64, R_PREL32 = 257, 258, 260, 261
# What fills the end of a function span without being code: zero words and nops.
PADDING_WORDS = {0, 0xD503201F}
# The SDK runtime links __cxa_atexit (a no-op) and __dso_handle statically, without a symbol.
UNNAMED_RUNTIME = {0x710000019C: "__cxa_atexit", 0x7101171000: "__dso_handle"}
README_START = "<!-- progress -->"
README_END = "<!-- /progress -->"

color = sys.stdout.isatty() and "NO_COLOR" not in os.environ


def paint(text, code):
    return f"\033[{code}m{text}\033[0m" if color and text.strip() else text


def run(args, **kwargs):
    return subprocess.run(args, check=True, capture_output=True, text=True, **kwargs).stdout


def demangle(names):
    return dict(zip(names, run(["llvm-cxxfilt"], input="\n".join(names)).splitlines()))


@lru_cache(maxsize=None)
def tool_key():
    """Anything that changes how sources compile or how functions are compared invalidates every cache entry."""
    digest = hashlib.sha1(open(os.path.abspath(__file__), "rb").read())
    digest.update("\0".join([os.environ.get("XC2_CXX", CXX), *CXXFLAGS]).encode())
    return digest.hexdigest()


@lru_cache(maxsize=None)
def file_digest(path, stamp=None):
    return hashlib.sha1(open(path, "rb").read()).hexdigest()


def current_digest(path):
    info = os.stat(path)
    return file_digest(path, (info.st_mtime_ns, info.st_size))


@lru_cache(maxsize=None)
def target_key():
    info = os.stat(TARGET_ELF)
    return f"{tool_key()}:{info.st_size}:{info.st_mtime_ns}"


def load_cached(path, key):
    try:
        with open(path, "rb") as f:
            stored, value = pickle.load(f)
    except (OSError, EOFError, ValueError, pickle.UnpicklingError):
        return None
    return value if stored == key else None


def save_cached(path, key, value):
    os.makedirs(os.path.dirname(path), exist_ok=True)
    partial = f"{path}.{os.getpid()}.{threading.get_ident()}"
    with open(partial, "wb") as f:
        pickle.dump((key, value), f, protocol=pickle.HIGHEST_PROTOCOL)
    os.replace(partial, path)


def cached(path, key, compute):
    value = load_cached(path, key)
    if value is None:
        value = compute()
        save_cached(path, key, value)
    return value


@lru_cache(maxsize=None)
def defined_symbols(path, sizes=False):
    args = ["llvm-nm", "--defined-only", *(["-S"] if sizes else []), path]
    if path == TARGET_ELF:
        return cached(os.path.join(CACHE_DIR, f"target{'.sizes' if sizes else ''}.nm"), target_key(), lambda: run(args))
    return cached(path + ".nm", (tool_key(), current_digest(path)), lambda: run(args))


@lru_cache(maxsize=None)
def read_source(path):
    return open(path).read()


Section = namedtuple("Section", "name type flags addr offset size link info align entsize")
Symbol = namedtuple("Symbol", "name type bind shndx value size")


class Elf:
    def __init__(self, path):
        self.data = data = open(path, "rb").read()
        shoff = struct.unpack_from("<Q", data, 0x28)[0]
        shentsize, shnum, shstrndx = struct.unpack_from("<HHH", data, 0x3A)
        headers = [struct.unpack_from("<IIQQQQIIQQ", data, shoff + i * shentsize) for i in range(shnum)]
        names = headers[shstrndx][4]
        self.sections = [Section(self.string(names + header[0]), *header[1:]) for header in headers]

    def string(self, pos):
        return self.data[pos:self.data.index(b"\0", pos)].decode()


class ObjectFile(Elf):
    """A compiled object: its sections, symbols and relocations."""

    def __init__(self, path):
        super().__init__(path)
        symtab = next(s for s in self.sections if s.type == SHT_SYMTAB)
        strtab = self.sections[symtab.link].offset
        self.symbols = [Symbol(self.string(strtab + name) if name else "", info & 0xF, info >> 4, shndx, value, size)
                        for name, info, _, shndx, value, size
                        in struct.iter_unpack("<IBBHQQ", self.data[symtab.offset:symtab.offset + symtab.size])]
        self.functions = {}
        self.function_at = {}
        for symbol in self.symbols:
            if symbol.type == STT_FUNC and 0 < symbol.shndx < SHN_LORESERVE:
                self.functions.setdefault(symbol.name, symbol)
                self.function_at.setdefault((symbol.shndx, symbol.value), symbol.name)
        self.relocation_lists = {}
        self.starts = None

    def strong_functions(self):
        """The functions this object defines with global binding: a weak one (an inline or template function) may
        be defined by several objects, a global one by one only."""
        return sorted({s.name for s in self.symbols
                       if s.type == STT_FUNC and s.bind == STB_GLOBAL and 0 < s.shndx < SHN_LORESERVE})

    def bytes(self, index, offset, size):
        section = self.sections[index]
        if section.type == SHT_NOBITS:
            return bytes(size)
        return self.data[section.offset + offset:section.offset + min(offset + size, section.size)]

    def c_string(self, index, offset):
        raw = self.bytes(index, offset, self.sections[index].size - offset)
        end = raw.find(b"\0")
        return raw if end < 0 else raw[:end]

    def relocations(self, index):
        """(offset, type, symbol index, addend) of every relocation applied to a section, sorted, with their offsets."""
        if index not in self.relocation_lists:
            found = sorted((offset, info & 0xFFFFFFFF, info >> 32, addend)
                           for s in self.sections if s.type == SHT_RELA and s.info == index
                           for offset, info, addend in struct.iter_unpack("<QQq", self.data[s.offset:s.offset + s.size]))
            self.relocation_lists[index] = (found, [r[0] for r in found])
        return self.relocation_lists[index]

    def relocations_in(self, index, start, end):
        found, offsets = self.relocations(index)
        return found[bisect.bisect_left(offsets, start):bisect.bisect_left(offsets, end)]

    def covering(self, index, offset):
        found = None
        for symbol in self.symbols:
            if (symbol.shndx == index and symbol.type != STT_SECTION and symbol.size
                    and symbol.value <= offset < symbol.value + symbol.size):
                found = symbol
        return found

    def next_start(self, index, offset):
        """Where anonymous data at offset ends: the next named object, or the next offset a relocation refers to."""
        if self.starts is None:
            starts = defaultdict(set)
            for symbol in self.symbols:
                if symbol.type != STT_SECTION and symbol.name and 0 < symbol.shndx < SHN_LORESERVE:
                    starts[symbol.shndx].add(symbol.value)
            for target in {s.info for s in self.sections if s.type == SHT_RELA}:
                if not self.sections[target].name.startswith(".debug"):
                    for _, _, symbol_index, addend in self.relocations(target)[0]:
                        symbol = self.symbols[symbol_index]
                        if 0 < symbol.shndx < SHN_LORESERVE:
                            starts[symbol.shndx].add(symbol.value + addend)
            self.starts = {index: sorted(offsets) for index, offsets in starts.items()}
        starts = self.starts.get(index, [])
        i = bisect.bisect_right(starts, offset)
        return starts[i] if i < len(starts) else self.sections[index].size


class Game:
    """The game executable: its bytes by address and its symbols."""

    def __init__(self):
        self.image = Elf(TARGET_ELF)
        entries = []
        for line in defined_symbols(TARGET_ELF, sizes=True).splitlines():
            parts = line.split()
            if len(parts) == 4:
                entries.append((int(parts[0], 16), int(parts[1], 16), parts[2], parts[3]))
        self.index_symbols(entries)
        stubs, self.calls = cached(os.path.join(CACHE_DIR, "target.code"), target_key(), self.scan_code)
        self.unnamed = {**UNNAMED_RUNTIME, **stubs}
        for addr, name in self.unnamed.items():
            self.addresses.setdefault(name, [addr])

    def index_symbols(self, entries):
        """Index the (address, size, kind, name) symbols: by address, by name, functions and data objects apart."""
        entries.sort()
        self.entries = entries
        self.starts = [e[0] for e in entries]
        self.addresses = {}
        self.functions = {}
        self.objects = {}
        for addr, size, kind, name in entries:
            self.addresses.setdefault(name, []).append(addr)
            (self.functions if kind in "TtWw" else self.objects).setdefault(name, []).append((addr, size))
        self.got_imports = {addr: name[len("__got_"):] for addr, _, _, name in entries if name.startswith("__got_")}

    def scan_code(self):
        """The import stubs (adrp x16; ldr x17, [x16, #slot]; add x16; br x17), named after the import they jump to,
        and every address a bl calls."""
        text = next(s for s in self.image.sections if s.name == ".text")
        words = memoryview(self.image.data)[text.offset:text.offset + text.size].cast("I")
        imports = {addr: name[len("__imp_"):] for addr, _, _, name in self.entries if name.startswith("__imp_")}
        stubs, calls = {}, set()
        for i, word in enumerate(words):
            if word & 0xFC000000 == 0x94000000:
                calls.add(text.addr + 4 * (i + signed(word & 0x3FFFFFF, 26)))
            elif word == 0xD61F0220 and i >= 3:
                adrp, ldr = words[i - 3], words[i - 2]
                if adrp & 0x9F00001F == 0x90000010 and ldr & 0xFFC003FF == 0xF9400211:
                    pc = text.addr + 4 * (i - 3)
                    slot = get_field(adrp, PAGE, pc) + ((ldr >> 10) & 0xFFF) * 8
                    if slot in imports:
                        stubs[pc] = imports[slot]
        return stubs, sorted(calls)

    def read(self, addr, size):
        for s in self.image.sections:
            if s.addr and s.type != SHT_NOBITS and s.addr <= addr < s.addr + s.size:
                pos = s.offset + addr - s.addr
                return self.image.data[pos:s.offset + min(addr - s.addr + size, s.size)]
        return b""

    def read_data(self, addr, size):
        """The bytes of a data object at addr: what read gives, zeros in .bss."""
        for s in self.image.sections:
            if s.addr and s.addr <= addr < s.addr + s.size:
                if s.type == SHT_NOBITS:
                    return bytes(min(size, s.addr + s.size - addr))
                return self.read(addr, size)
        return b""

    def c_string(self, addr):
        raw = b""
        while b"\0" not in raw:
            chunk = self.read(addr + len(raw), 256)
            if not chunk:
                break
            raw += chunk
        return raw.split(b"\0")[0]

    def pointer(self, addr):
        raw = self.read(addr, 8)
        return struct.unpack("<Q", raw)[0] if len(raw) == 8 else None

    def covering(self, addr):
        i = bisect.bisect_right(self.starts, addr) - 1
        if i < 0:
            return None
        start, size, _, name = self.entries[i]
        if addr == start or addr < start + size:
            return name, addr - start
        return None

    def symbol_in(self, addr, size):
        """The name of a game symbol that overlaps [addr, addr + size), or None."""
        found = self.covering(addr)
        if found:
            return found[0]
        i = bisect.bisect_right(self.starts, addr)
        return self.entries[i][3] if i < len(self.entries) and self.starts[i] < addr + size else None

    def name_at(self, addr):
        if addr in self.unnamed:
            return self.unnamed[addr]
        found = self.covering(addr)
        if found:
            return found[0] + (f"+{found[1]:#x}" if found[1] else "")
        return f"{addr:#x}"

    def symbol_addresses(self, name):
        found = self.addresses.get(name)
        structor = STRUCTOR.fullmatch(name) if found is None else None
        if structor:
            found = self.addresses.get(f"{structor[1]}{structor[2]}{3 - int(structor[3])}{structor[4]}")
        return found or []

    def unnamed_end(self, addr):
        """End of the unnamed function at addr: the next symbol, or the next address some bl calls."""
        if self.covering(addr):
            return None
        end = self.starts[bisect.bisect_right(self.starts, addr)]
        i = bisect.bisect_right(self.calls, addr)
        return min(end, self.calls[i]) if i < len(self.calls) else end


@lru_cache(maxsize=None)
def target_game():
    return Game()


def signed(value, bits):
    return (value ^ (1 << (bits - 1))) - (1 << (bits - 1))


def branch_bits(word):
    """Width of the offset field of a pc-relative branch, else None."""
    if word & 0x7C000000 == 0x14000000:  # b, bl
        return 26
    if word & 0xFF000010 == 0x54000000 or word & 0x7E000000 == 0x34000000:  # b.cond, cbz, cbnz
        return 19
    if word & 0x7E000000 == 0x36000000:  # tbz, tbnz
        return 14
    return None


def fits(word, field):
    """The instruction has the field a relocation fills."""
    if field is PAGE:
        return word & 0x9F000000 == 0x90000000
    if field[0] == "lo12":
        return word & 0x7F800000 == 0x11000000 or word & 0x3B000000 == 0x39000000  # add, ldr/str immediate
    return branch_bits(word) == field[1]


def get_field(word, field, pc):
    """The address an instruction field reaches from pc: a page, the low 12 bits, or a branch target."""
    if field is PAGE:
        return (pc & ~0xFFF) + (signed(((word >> 5) & 0x7FFFF) << 2 | (word >> 29) & 3, 21) << 12)
    if field[0] == "lo12":
        return ((word >> 10) & 0xFFF) << field[1]
    bits = field[1]
    shift = 0 if bits == 26 else 5
    return pc + signed((word >> shift) & ((1 << bits) - 1), bits) * 4


def set_field(word, field, value, pc):
    if field is PAGE:
        page = ((value & ~0xFFF) - (pc & ~0xFFF)) >> 12 & 0x1FFFFF
        return word & ~0x60FFFFE0 | (page & 3) << 29 | (page >> 2) << 5
    if field[0] == "lo12":
        return word & ~0x3FFC00 | ((value & 0xFFF) >> field[1]) << 10
    bits = field[1]
    shift = 0 if bits == 26 else 5
    mask = (1 << bits) - 1
    return word & ~(mask << shift) | ((value - pc) >> 2 & mask) << shift


def word_at(raw, offset):
    return int.from_bytes(raw[offset:offset + 4], "little")


def code_length(raw):
    """Length of raw code without its trailing padding: zero words and nops."""
    end = len(raw) & ~3
    while end >= 4 and word_at(raw, end - 4) in PADDING_WORDS:
        end -= 4
    return end


def is_mov_immediate(word):
    return word & 0x7F800000 in (0x52800000, 0x12800000) or word & 0x7F800000 == 0x32000000 and (word >> 5) & 31 == 31


def reference(game, obj, symbol, addend, got):
    """What a relocation reaches, as a key shared by every instruction that reaches it."""
    if got:
        return ("got", symbol.name)
    if symbol.type != STT_SECTION and symbol.name and game.symbol_addresses(symbol.name):
        return ("symbol", symbol.name, addend)
    if 0 < symbol.shndx < SHN_LORESERVE:
        return local_reference(game, obj, symbol.shndx, symbol.value + addend)
    return ("missing", symbol.name, addend)


def local_reference(game, obj, index, offset):
    name = obj.function_at.get((index, offset))
    if name and game.symbol_addresses(name):
        return ("symbol", name, 0)
    return ("local", index, offset)


def describe(obj, key):
    if key[0] == "local":
        return obj.function_at.get(key[1:]) or f"{obj.sections[key[1]].name}+{key[2]:#x}"
    if key[0] == "got":
        return "got:" + key[1]
    return key[1] + (f"+{key[2]:#x}" if key[2] else "")


def string_label(raw):
    text = raw.decode("utf-8", "backslashreplace")
    path = SOURCE_PATH.fullmatch(text)
    if path:
        return f'"…/{path.group(1)}"'
    return '"' + text.replace("\n", "\\n").replace("\t", "\\t") + '"'


def literal_label(raw):
    if len(raw) == 4:
        return f"{struct.unpack('<f', raw)[0]:.9g} ({struct.unpack('<I', raw)[0]:#010x})"
    if len(raw) == 8:
        return f"{struct.unpack('<d', raw)[0]:.17g} ({struct.unpack('<Q', raw)[0]:#018x})"
    return raw.hex()


def same_source_file(mine, theirs):
    """Two __FILE__ paths that differ only by their directory."""
    paths = [SOURCE_PATH.fullmatch(raw.decode("latin1")) for raw in (mine, theirs)]
    return all(paths) and paths[0].group(1) == paths[1].group(1)


def compare_read_only(game, obj, index, offset, address, function, assert_text):
    """Your read-only data at (index, offset) against the game's at address: (game label, your label, problem)."""
    section = obj.sections[index]
    if section.flags & SHF_STRINGS:
        mine, theirs = obj.c_string(index, offset), game.c_string(address)
        if mine == theirs or same_source_file(mine, theirs) or (
                assert_text and mine.replace(b" ", b"") == theirs.replace(b" ", b"")):
            return string_label(theirs), string_label(theirs), None
        return (string_label(theirs), string_label(mine),
                f"the string is {string_label(mine)}, the game's {string_label(theirs)}")
    literal = bool(section.flags & SHF_MERGE and section.entsize)
    if literal:
        start, size = offset, section.entsize
    else:
        symbol = obj.covering(index, offset)
        start, size = (symbol.value, symbol.size) if symbol else (offset, obj.next_start(index, offset) - offset)
    size = min(size, 0x10000)
    if not literal and not symbol:
        # Data without a symbol that holds relocations is a run of jump tables. next_start also counts the alignment
        # padding between the last table of the unit and the next symbol: zeros in the object, other data in the game
        # (the tables of a unit need not end on the boundary the next symbol is aligned to). The window stops after
        # its last relocation; it is never widened, and data without relocations is compared as before.
        ends = [r_offset + (8 if rtype in (R_ABS64, R_PREL64) else 4) - start
                for r_offset, rtype, _, _ in obj.relocations_in(index, start, start + size)]
        if ends:
            size = min(size, max(ends))
    base = address - (offset - start)
    mine = bytearray(obj.bytes(index, start, size))
    masked = set()
    function_index, function_start, function_size, function_address = function
    for r_offset, rtype, symbol_index, addend in obj.relocations_in(index, start, start + size):
        at = r_offset - start
        symbol = obj.symbols[symbol_index]
        target = None
        if symbol.shndx == function_index:
            if function_start <= symbol.value + addend < function_start + function_size:  # jump table entry
                target = function_address + symbol.value + addend - function_start
        elif symbol.type != STT_SECTION and symbol.name:
            found = game.symbol_addresses(symbol.name)
            if len(found) == 1:
                target = found[0] + addend
        width = 8 if rtype in (R_ABS64, R_PREL64) else 4
        if target is None or rtype not in (R_PREL32, R_ABS64, R_ABS32):
            masked.update(range(at, at + width))
        elif rtype == R_PREL32:
            struct.pack_into("<i", mine, at, target - (base + at))
        elif rtype == R_ABS64:
            struct.pack_into("<Q", mine, at, target)
        else:
            struct.pack_into("<I", mine, at, target & 0xFFFFFFFF)
    theirs = game.read(base, size)
    labels = (literal_label(theirs), literal_label(bytes(mine))) if literal and len(theirs) == size else (None, None)
    if len(theirs) != size:
        return (*labels, f"{section.name}+{offset:#x} is at {base:#x} in the game, which holds no data")
    differ = [i for i in range(size) if i not in masked and mine[i] != theirs[i]]
    if not differ:
        return labels[0], labels[0], None
    if literal:
        return (*labels, f"the literal at {address:#x} is {labels[1]}, the game's {labels[0]}")
    i = differ[0]
    return (*labels, f"the data at {base + i:#x} ({section.name}+{start + i:#x}) is {bytes(mine[i:i + 8]).hex()}, "
                     f"the game's {theirs[i:i + 8].hex()}")


def verify(game, obj, symbol, address, size=None):
    """Place your function at the game address, resolve its relocations and compare its bytes with the game's.

    size is the game function's size; None for a function the game has no symbol for, compared over your size
    within the game span (up to the next symbol or bl target)."""
    function = obj.functions[symbol]
    index, start, length = function.shndx, function.value, function.size
    ours = bytearray(obj.bytes(index, start, length))
    problems = []
    if size is None:
        span = game.unnamed_end(address) - address
        compared = min(length, span)
        if length > span:
            problems.append((span, f"the game's code at {address:#x} ends after {span // 4} instructions"))
    else:
        span = compared = size
        if length != size:
            problems.append((min(length, size), f"the game function has {size // 4} instructions, yours {length // 4}"))
    theirs = game.read(address, span)
    game_length = size if size is not None else code_length(theirs)
    if len(theirs) < span:
        problems.append((len(theirs), f"the game has no code at {address + len(theirs):#x}"))

    sites = []  # (offset, field, key)
    writable = {}  # (section index, offset) of your writable data -> the game address the instructions reach
    relocated = set()
    for offset, rtype, symbol_index, addend in obj.relocations_in(index, start, start + length):
        offset -= start
        relocated.add(offset)
        field = RELOCATION_FIELDS.get(rtype)
        if field is None:
            problems.append((offset, f"relocation type {rtype} in code"))
        else:
            sites.append((offset, field, reference(game, obj, obj.symbols[symbol_index], addend, rtype in GOT_RELOCATIONS)))
    for offset in range(0, length, 4):
        if offset in relocated:
            continue
        word = word_at(ours, offset)
        bits = branch_bits(word)
        if bits:
            target = get_field(word, ("branch", bits), offset)
            if not 0 <= target < length:  # a call the assembler resolved: a function of the same section
                sites.append((offset, ("branch", bits), local_reference(game, obj, index, start + target)))
        elif word & 0x1F000000 == 0x10000000 or word & 0x3B000000 == 0x18000000:
            problems.append((offset, "adr or ldr literal without relocation"))

    windows = [(max(0, offset - SOURCE_LOCATION_WINDOW), offset, *SOURCE_LOCATION_CALLS[key[1]])
               for offset, field, key in sites if key[0] == "symbol" and key[1] in SOURCE_LOCATION_CALLS]
    assert_texts = {key for offset, field, key in sites if field[0] != "branch" and word_at(ours, offset) & 31 == 0
                    and any(text and low <= offset < call for low, call, _, text in windows)}

    # The address the game uses for each key, from the game instructions at your relocation sites.
    found = defaultdict(lambda: defaultdict(set))
    first_site = {}
    for offset, field, key in sites:
        first_site.setdefault(key, offset)
        if offset + 4 <= compared:
            word = word_at(theirs, offset)
            if fits(word, field):
                found[key][field[0]].add(get_field(word, field, address + offset))
    values, labels, calls = {}, {}, {}
    for key, offset in first_site.items():
        kinds = found.get(key, {})
        theirs_value = None
        if all(len(v) == 1 for v in kinds.values()):
            one = {kind: min(v) for kind, v in kinds.items()}
            if "branch" in one:
                theirs_value = one["branch"] if len(one) == 1 else None
            elif "page" in one and "lo12" in one:
                theirs_value = one["page"] | one["lo12"]
        if key[0] == "symbol":
            candidates = game.symbol_addresses(key[1])
            if theirs_value is not None and theirs_value - key[2] in candidates:
                values[key] = theirs_value
            else:
                values[key] = candidates[0] + key[2]
            labels[key] = (theirs_value is not None and game.name_at(theirs_value), game.name_at(values[key]))
        elif key[0] == "missing":
            problems.append((offset, f"yours refers to {key[1]}, which the game has no symbol for"))
            labels[key] = (theirs_value is not None and game.name_at(theirs_value), key[1])
        elif theirs_value is None:
            continue
        elif key[0] == "got":
            values[key] = theirs_value
            pointer = game.pointer(theirs_value)
            held = game.got_imports.get(theirs_value) or (game.name_at(pointer) if pointer is not None else "nothing")
            if key[1] and (game.got_imports.get(theirs_value) == key[1] or pointer in game.symbol_addresses(key[1])):
                labels[key] = ("got:" + held, "got:" + held)
            else:
                labels[key] = ("got:" + held, "got:" + key[1])
                problems.append((offset, f"yours loads the address of {key[1] or 'an unnamed symbol'}, the game {held}"))
        else:
            values[key] = theirs_value
            section = obj.sections[key[1]]
            if section.flags & SHF_EXECINSTR:
                if game.covering(theirs_value):
                    problems.append((offset, f"yours calls {describe(obj, key)}, local to your file, "
                                             f"the game {game.name_at(theirs_value)}"))
                elif key[1:] in obj.function_at:
                    calls.setdefault(obj.function_at[key[1:]], theirs_value)
            elif not section.flags & SHF_WRITE and section.type != SHT_NOBITS:
                game_label, your_label, problem = compare_read_only(
                    game, obj, key[1], key[2], theirs_value, (index, start, length, address), key in assert_texts)
                labels[key] = (game_label, your_label)
                if problem:
                    problems.append((offset, problem))
            else:
                writable[key[1:]] = theirs_value

    for offset, field, key in sites:
        if key in values:
            ours[offset:offset + 4] = set_field(word_at(ours, offset), field, values[key], address + offset).to_bytes(4, "little")

    diffs, lines = [], set()
    end = min(compared, length, len(theirs))
    if ours[:end] != theirs[:end]:
        for offset in range(0, end, 4):
            mine, game_word = word_at(ours, offset), word_at(theirs, offset)
            if mine == game_word:
                continue
            if offset not in relocated and is_line_number(ours, offset, mine, game_word, windows):
                lines.add(offset)
            else:
                diffs.append(offset)
    differing = set(diffs)
    for key, offset in first_site.items():
        if key not in values and key[0] != "missing" and not any(o in differing for o, _, k in sites if k == key):
            problems.append((offset, f"the game instructions give no single address for {describe(obj, key)}"))

    our_labels, game_labels = {}, {}
    for offset, field, key in sites:
        game_label, your_label = labels.get(key, (None, None))
        if field[0] == "branch":
            if key not in values:
                our_labels[offset] = f"<{describe(obj, key)}>"
            continue
        if your_label:
            our_labels[offset] = your_label
        if game_label and offset + 4 <= len(theirs) and fits(word_at(theirs, offset), field):
            game_labels[offset] = game_label
    return SimpleNamespace(ok=not diffs and not problems, address=address, count=compared // 4, game_count=game_length // 4,
                           ours=bytes(ours), theirs=theirs, diffs=diffs, problems=sorted(problems), lines=lines,
                           our_labels=our_labels, game_labels=game_labels, calls=calls, writable=writable)


def is_line_number(ours, offset, mine, theirs, windows):
    """Both words set the register a source-location call takes __LINE__ in, directly or through a register."""
    if not (is_mov_immediate(mine) and is_mov_immediate(theirs) and mine & 0x8000001F == theirs & 0x8000001F):
        return False
    register = mine & 31
    for low, call, line_register, _ in windows:
        if low <= offset < call and register == line_register:
            return True
        for at in range(max(low, offset + 4), call, 4):  # mov wLine, wRegister
            word = word_at(ours, at)
            if word & 0x7FE0FFE0 == 0x2A0003E0 and word & 31 == line_register and (word >> 16) & 31 == register:
                return True
    return False


def verify_named(game, obj, symbol):
    verdicts = []
    for address, size in game.functions[symbol]:
        verdict = verify(game, obj, symbol, address, size)
        if verdict.ok:
            return verdict
        verdicts.append(verdict)
    return verdicts[0]


# What a relocation in data fills, by type: its width in bytes and whether it is relative to the place it fills.
DATA_RELOCATIONS = {R_ABS64: (8, False), R_ABS32: (4, False), R_PREL64: (8, True), R_PREL32: (4, True)}


def pointer_problem(game, obj, rtype, symbol, addend, theirs, at, base):
    """Why the pointer at offset at of the game's data (which starts at base) is not what your relocation resolves
    to, or None. Your symbol must be the one the game's pointer reaches: the game's symbol of that name, or the
    same bytes for what is local to your file."""
    width, relative = DATA_RELOCATIONS[rtype]
    held = int.from_bytes(theirs[at:at + width], "little", signed=relative)
    target = held + base + at if relative else held
    mask = (1 << 8 * width) - 1
    key = reference(game, obj, symbol, addend, False)
    if key[0] == "symbol":
        if any((address + key[2]) & mask == target & mask for address in game.symbol_addresses(key[1])):
            return None
        return f"points to {describe(obj, key)}, the game's {game.name_at(target)}"
    if key[0] == "missing":
        if game.got_imports.get(base + at) == key[1]:  # an import: the game holds no address there, only its slot
            return None
        return f"refers to {key[1]}, which the game has no symbol for"
    section = obj.sections[key[1]]
    if section.flags & SHF_EXECINSTR:
        if game.covering(target):
            return f"points to {describe(obj, key)}, local to your file, the game's {game.name_at(target)}"
    elif not section.flags & SHF_WRITE and section.type != SHT_NOBITS:
        problem = compare_read_only(game, obj, key[1], key[2], target, (-1, 0, 0, 0), False)[2]
        if problem:
            return f"points to {describe(obj, key)}: {problem}"
    elif game.covering(target):
        return f"points to {describe(obj, key)}, local writable data, the game's {game.name_at(target)}"
    return None


def global_data_problem(game, obj, symbol, address, game_size):
    """Why your global data object differs from the game's at address, or None: its size, then its bytes, with each
    pointer in it compared by what it resolves to."""
    size = symbol.size
    if size != game_size:
        return f"its size is {size}, the game's {game_size}"
    theirs = game.read_data(address, size)
    if len(theirs) != size:
        return f"the game holds no data at {address:#x}"
    mine = bytearray(obj.bytes(symbol.shndx, symbol.value, size))
    problems = []  # (offset, text)
    for r_offset, rtype, symbol_index, addend in obj.relocations_in(symbol.shndx, symbol.value, symbol.value + size):
        at = r_offset - symbol.value
        if rtype not in DATA_RELOCATIONS:
            problems.append((at, f"relocation type {rtype} in data"))
            continue
        width = DATA_RELOCATIONS[rtype][0]
        mine[at:at + width] = theirs[at:at + width]  # compared through what it resolves to
        problem = pointer_problem(game, obj, rtype, obj.symbols[symbol_index], addend, theirs, at, address)
        if problem:
            problems.append((at, problem))
    if mine != theirs:
        at = next(i for i in range(size) if mine[i] != theirs[i])
        problems.append((at, f"holds {bytes(mine[at:at + 8]).hex()}, the game's {theirs[at:at + 8].hex()}"))
    if not problems:
        return None
    at, problem = min(problems)
    return f"at +{at:#x} (game {address + at:#x}) {problem}"


def global_data_problems(game, obj):
    """(name, problem) of each global data object your object defines that the game has too and that differs from
    it: a table, a vtable, a static member. Local data has no symbol in the game and is compared where code uses it."""
    found = []
    for symbol in obj.symbols:
        if (symbol.type != STT_OBJECT or symbol.bind == STB_LOCAL or not 0 < symbol.shndx < SHN_LORESERVE
                or obj.sections[symbol.shndx].flags & SHF_EXECINSTR):
            continue
        problems = [global_data_problem(game, obj, symbol, address, size) for address, size in game.objects.get(symbol.name, [])]
        if problems and None not in problems:
            found.append((symbol.name, problems[0]))
    return found


def writable_objects(obj, mapped):
    """The writable data objects of your file that matching functions reach, from {(section index, offset): (game
    address, function)}: {(section index, start): (name, game address of the start, size, function, shared)}, shared
    being true for an object with global or weak binding (a variable local to an inline function), which every object
    using it defines and the linker keeps once."""
    found = {}
    for (index, offset), (address, function) in mapped.items():
        symbol = obj.covering(index, offset)
        start, size = (symbol.value, symbol.size) if symbol else (offset, 1)
        name = symbol.name if symbol and symbol.name else f"{obj.sections[index].name}+{start:#x}"
        shared = bool(symbol and symbol.name and symbol.bind != STB_LOCAL)
        found.setdefault((index, start), (name, address - (offset - start), size, function, shared))
    return found


def writable_problems(game, objects):
    """(name, problem) of each writable data object of your file that the game places over a symbol of its own: local
    data has no symbol in the game."""
    found = []
    for name, base, size, function, _ in objects.values():
        named = game.symbol_in(base, size)
        if named:
            found.append((name, f"is writable data local to your file, used by {function}, at {base:#x} in the game, "
                                f"which is {named}"))
    return found


def overlapping_objects(objects):
    """The pairs of (name, game address, size, source, shared) local data objects that overlap in the game: two
    distinct objects cannot share an address. The same shared object seen from two sources is one object."""
    found, previous = [], None
    for current in sorted(objects, key=lambda o: (o[1], o[2], o[0], o[3])):
        if previous and current[1] < previous[1] + previous[2] and not (
                previous[4] and current[4] and previous[:3] == current[:3]):
            found.append((previous, current))
        if not previous or current[1] + current[2] > previous[1] + previous[2]:
            previous = current
    return found


def strong_duplicates(definitions):
    """{function: sources} of every function defined with global binding by several sources, from (source, names of
    its global functions). A weak function (inline, template) is defined by every object that uses it: not one."""
    by_name = defaultdict(list)
    for source, names in definitions:
        for name in names:
            by_name[name].append(source)
    return {name: sources for name, sources in sorted(by_name.items()) if len(sources) > 1}


def merge_copies(rows, symbol, ok, local):
    """Drop the copies of a function that do not match when another copy does. A function defined in several objects
    is a weak copy (an inline or template function): the linker keeps one of them, so the function matches when one
    copy is the game's. A global function defined twice is reported apart (strong_duplicates). symbol, ok and local
    read these fields of a row; local rows are never copies."""
    matched = {symbol(row) for row in rows if ok(row) and not local(row)}
    return [row for row in rows if ok(row) or local(row) or symbol(row) not in matched]


def end_local_spans(rows):
    """rows with the game count of each local function cut at the start of the next local function of the object: the
    game names only the symbol after them, so the span of an unnamed function includes the unnamed ones that follow."""
    starts = sorted({row[1] for row in rows if row[4]})
    ended = []
    for name, address, ok, count, local, game_count in rows:
        i = bisect.bisect_right(starts, address)
        if local and i < len(starts):
            game_count = min(game_count, (starts[i] - address) // 4)
        ended.append((name, address, ok, count, local, game_count))
    return ended


def check_object(entry):
    """The result of one object: (symbol, game address, match, instructions, instructions of the game's code,
    local) of each function, then of the local functions the matching ones call; the global functions it defines;
    and what the function check does not compare: (name, problem) of its data, and (name, game address, size) of its
    local data objects."""
    path, symbols = entry
    game = target_game()
    obj = ObjectFile(path)
    rows, calls, mapped = [], {}, {}

    def add(name, verdict, local):
        rows.append((name, verdict.address, verdict.ok, verdict.count, local, verdict.game_count))
        if verdict.ok:
            for callee, address in verdict.calls.items():
                calls.setdefault(callee, address)
            for key, address in verdict.writable.items():
                mapped.setdefault(key, (address, name))

    for symbol in symbols:
        add(symbol, verify_named(game, obj, symbol), False)
    done = set()
    while len(done) < len(calls):
        for name in [n for n in calls if n not in done]:
            done.add(name)
            add(name, verify(game, obj, name, calls[name]), True)
    objects = writable_objects(obj, mapped)
    return {"rows": end_local_spans(rows), "strong": obj.strong_functions(),
            "data": global_data_problems(game, obj) + writable_problems(game, objects),
            "locals": [(name, base, size, shared) for name, base, size, _, shared in objects.values()]}


def check_objects(entries):
    """check_object for each (object, symbols), kept in the cache until the object or the game changes."""
    keys = [(target_key(), current_digest(path), tuple(symbols)) for path, symbols in entries]
    results = [load_cached(path + ".check", key) for (path, _), key in zip(entries, keys)]
    todo = [i for i, rows in enumerate(results) if rows is None]
    if todo:
        target_game()  # read once, before the workers fork
        with ProcessPoolExecutor(mp_context=multiprocessing.get_context("fork")) as pool:
            for i, rows in zip(todo, pool.map(check_object, [entries[i] for i in todo], chunksize=4)):
                save_cached(entries[i][0] + ".check", keys[i], rows)
                results[i] = rows
    return results


def disassemble(word_lists):
    """Instruction texts of each list of words, through one llvm-mc run."""
    words = [word for words in word_lists for word in words]
    proc = subprocess.run(["llvm-mc", "--disassemble", "-triple=aarch64", "-mattr=+crypto,+crc,+fp-armv8,+neon"],
                          input="\n".join(" ".join(f"{b:#04x}" for b in struct.pack("<I", w)) for w in words),
                          capture_output=True, text=True)
    invalid = {int(n) - 1 for n in re.findall(r"<stdin>:(\d+):\d+: warning: invalid instruction encoding", proc.stderr)}
    texts = iter(line.strip() for line in proc.stdout.splitlines() if line.strip() and not line.strip().startswith("."))
    lines = [f".word\t{word:#010x}" if i in invalid else next(texts) for i, word in enumerate(words)]
    out = []
    for words in word_lists:
        out.append(lines[:len(words)])
        lines = lines[len(words):]
    return out


def render(game, texts, raw, verdict, labels):
    """The instructions of one side, pc-relative operands written as the address they reach."""
    start, end = verdict.address, verdict.address + len(raw)
    lines = []
    for i, text in enumerate(texts):
        offset = i * 4
        word = word_at(raw, offset)
        pc = start + offset
        label = labels.get(offset)
        bits = branch_bits(word)
        if bits:
            if label is None:
                target = get_field(word, ("branch", bits), pc)
                label = f"+{target - start:#x}" if start <= target < end else f"<{game.name_at(target)}>"
            text = PC_RELATIVE_OPERAND.sub(lambda _: label, text)
        else:
            if word & 0x9F000000 == 0x90000000:  # adrp
                target = get_field(word, PAGE, pc)
            elif word & 0x9F000000 == 0x10000000:  # adr
                target = pc + signed(((word >> 5) & 0x7FFFF) << 2 | (word >> 29) & 3, 21)
            elif word & 0x3B000000 == 0x18000000:  # ldr literal
                target = pc + signed((word >> 5) & 0x7FFFF, 19) * 4
            else:
                target = None
            if target is not None:
                text = PC_RELATIVE_OPERAND.sub(lambda _: f"{target:#x}", text)
            if label:
                text += f" <{label}>"
        if offset in verdict.lines:
            text = re.sub(r"#[^,]*$", "<line>", text)
        lines.append(text)
    return lines


def show(game, verdict):
    """Print MATCH, or the side by side diff and where the bytes first differ."""
    if verdict.ok:
        print(paint(f"MATCH ({verdict.count} instructions)", "1;32"))
        return True
    texts = disassemble([[word_at(raw, o) for o in range(0, len(raw) - 3, 4)] for raw in (verdict.theirs, verdict.ours)])
    target = render(game, texts[0], verdict.theirs, verdict, verdict.game_labels)
    mine = render(game, texts[1], verdict.ours, verdict, verdict.our_labels)
    print_diff(target, mine)
    first = min([*verdict.diffs, *(offset for offset, _ in verdict.problems)])
    print(paint(f"\nfirst difference at +{first:#x} ({verdict.address + first:#x})", "1"))
    print(f"  target  {target[first // 4].expandtabs(8) if first // 4 < len(target) else '(end)'}")
    print(f"  yours   {mine[first // 4].expandtabs(8) if first // 4 < len(mine) else '(end)'}")
    for offset, problem in verdict.problems:
        print(f"  +{offset:#x}: {problem}")
    print(paint(f"\nNO MATCH: target {len(target)} instructions, yours {len(mine)}", "1;31"))
    return False


def print_diff(target, mine):
    width = max(len(l.expandtabs(8)) for l in target + ["target"]) + 2
    print(paint(f"{'target':<{width}}   yours", "1"))
    for tag, i1, i2, j1, j2 in difflib.SequenceMatcher(a=target, b=mine, autojunk=False).get_opcodes():
        for k in range(max(i2 - i1, j2 - j1)):
            left = (target[i1 + k] if i1 + k < i2 else "").expandtabs(8)
            right = (mine[j1 + k] if j1 + k < j2 else "").expandtabs(8)
            if tag == "equal":
                print(f"{left:<{width}}   {right}")
                continue
            code = "33" if tag == "replace" and left and right else ("31" if left else "32")
            print(f"{paint(f'{left:<{width}}', code)} {paint('|', code)} {paint(right, code)}")


def target_symbols():
    return set(defined_functions(TARGET_ELF))


def resolve_symbol(name, demangled):
    if name.startswith("_Z"):
        return name
    exact = [m for m in demangled if demangled[m] == name]
    if exact:
        return exact[0]
    candidates = [m for m in demangled if demangled[m].split("(")[0] == name]
    if len(candidates) > 1:
        sys.exit(f"{name} is ambiguous, pass the full signature:\n" + "\n".join(f"  {demangled[m]}" for m in candidates))
    return candidates[0] if candidates else None


def in_scope(demangled_name, scope):
    return scope is None or demangled_name.startswith(scope + "::")


def dependency_key(deps_file, extra):
    """Digest of every file the last compilation read, from the depfile clang wrote; None if one is gone."""
    try:
        text = open(deps_file).read()
    except OSError:
        return None
    digest = hashlib.sha1("\0".join([tool_key(), *extra]).encode())
    for path in text.partition(":")[2].replace("\\\n", " ").split():
        if not os.path.exists(path):
            return None
        digest.update(path.encode() + current_digest(path).encode())
    return digest.hexdigest()


def compile_source(source, tmp, extra=()):
    """Compile into the cache, or reuse the object when neither the source nor anything it includes changed."""
    name = hashlib.sha1("\0".join([os.path.relpath(source, ROOT), *extra]).encode()).hexdigest()
    base = os.path.join(CACHE_DIR, "obj", name)
    obj, deps_file, key_file = base + ".o", base + ".d", base + ".key"
    key = dependency_key(deps_file, extra)
    try:
        if key and os.path.exists(obj) and open(key_file).read() == key:
            return obj, None
    except OSError:
        pass
    os.makedirs(os.path.dirname(base), exist_ok=True)
    if os.path.exists(key_file):
        os.remove(key_file)
    proc = subprocess.run([os.environ.get("XC2_CXX", CXX), *CXXFLAGS, *extra, "-MD", "-MF", deps_file, "-c", source,
                           "-o", obj], capture_output=True, text=True)
    if proc.returncode:
        return None, proc.stderr
    open(key_file, "w").write(dependency_key(deps_file, extra) or "")
    return obj, None


def defined_functions(obj):
    out = defined_symbols(obj)
    return [parts[2] for parts in (l.split() for l in out.splitlines()) if len(parts) == 3 and parts[1] in "TtWw"]


@lru_cache(maxsize=None)
def included_sources(source):
    found = []
    for name in INCLUDE_CPP.findall(read_source(source)):
        for base in (os.path.dirname(source), os.path.join(ROOT, "src", "application", "BF2"), os.path.join(ROOT, "include")):
            path = os.path.normpath(os.path.join(base, name))
            if os.path.exists(path):
                found.append(path)
                break
    return found


def root_sources():
    sources = sorted(glob.glob(os.path.join(SRC_DIR, "**", "*.cpp"), recursive=True))
    included = {path for source in sources for path in included_sources(source)}
    return [source for source in sources if source not in included]


def header_sources():
    return sorted(glob.glob(os.path.join(SRC_DIR, "**", "*.h"), recursive=True) +
                  glob.glob(os.path.join(ROOT, "include", "**", "*.h"), recursive=True))


HEADER_FLAGS = ("-x", "c++", "-Wno-pragma-once-outside-header")


def compile_headers(tmp):
    """Compile every header on its own: it must build without relying on what its includer included before."""
    with ThreadPoolExecutor() as pool:
        results = list(pool.map(lambda h: (h, compile_source(h, tmp, HEADER_FLAGS)[1]), header_sources()))
    return [(os.path.relpath(header, ROOT), err) for header, err in results if err]


ABSOLUTE_INCLUDE = re.compile(r'^\s*#\s*include\s*[<"](/[^>"]*)[>"]', re.M)


def absolute_includes():
    """An include by absolute path builds only in one checkout, and may pull a second copy of a header elsewhere."""
    found = []
    for path in sorted(glob.glob(os.path.join(SRC_DIR, "**", "*.cpp"), recursive=True)) + header_sources():
        for target in ABSOLUTE_INCLUDE.findall(read_source(path)):
            found.append((os.path.relpath(path, ROOT), f"includes {target} by absolute path, use a path relative to an include directory\n"))
    return found


def qualified_needle(demangled_name):
    return "::".join(demangled_name.split("(")[0].split("::")[-2:]) + "("


def defining_file(demangled_name, root):
    needle = qualified_needle(demangled_name)
    for path in included_sources(root) + [root]:
        if needle in read_source(path):
            return path
    return root


def compile_all(tmp, sources=None):
    sources = root_sources() if sources is None else sources
    with ThreadPoolExecutor() as pool:
        results = list(pool.map(lambda s: (s, *compile_source(s, tmp)), sources))
    errors = [(os.path.relpath(source, ROOT), err) for source, _, err in results if err]
    return [(source, obj) for source, obj, _ in results if obj], errors


def unknown_functions(objects, demangled, scope):
    """Global functions your objects define that the game has no symbol for, with game functions of the same name."""
    defined = sorted({parts[2] for _, obj in objects for parts in (l.split() for l in defined_symbols(obj).splitlines())
                      if len(parts) == 3 and parts[1] == "T" and parts[2] not in demangled})
    names = demangle(defined) if defined else {}
    by_name = {}
    for game_name in demangled.values():
        by_name.setdefault(game_name.split("(")[0].split("::")[-1], []).append(game_name)
    found = []
    for symbol in defined:
        name = names[symbol]
        if in_scope(name, scope):
            short = name.split("(")[0].split("::")[-1]
            found.append((name, [g for g in by_name.get(short, []) if g.split("(")[0] == name.split("(")[0]] or
                          by_name.get(short, [])[:3]))
    return found


def print_unknown_functions(unknown):
    for name, candidates in unknown:
        print(f"{paint('NOT IN GAME', '33')}  {name}")
        for candidate in candidates:
            print(f"             the game has {candidate}")


def print_compile_errors(errors):
    for source, err in errors:
        print(paint(f"compile error: {source}", "1;31"), file=sys.stderr)
        print(err, file=sys.stderr)


def diff_one(symbol, source, extra):
    with tempfile.TemporaryDirectory() as tmp:
        if source:
            obj, err = compile_source(source, tmp, extra)
            if err:
                sys.exit(err)
        else:
            needle = qualified_needle(demangle([symbol])[symbol])
            likely = [root for root in root_sources()
                      if any(needle in read_source(path) for path in included_sources(root) + [root])]
            obj = None
            for sources in (likely, None):
                objects, errors = compile_all(tmp, sources)
                obj = next((o for _, o in objects if symbol in defined_functions(o)), None)
                if obj:
                    break
            if errors:
                print_compile_errors(errors)
            if obj is None:
                sys.exit(f"{demangle([symbol])[symbol]} is not defined in any file under src/" +
                         (" that compiles" if errors else ""))
    obj = ObjectFile(obj)
    if symbol not in obj.functions:
        sys.exit(f"{symbol} not found in compiled object (check the mangled name with llvm-nm)")
    game = target_game()
    return show(game, verify_named(game, obj, symbol))


def diff_unnamed(address, source, name, extra):
    with tempfile.TemporaryDirectory() as tmp:
        obj, err = compile_source(source, tmp, extra)
        if err:
            sys.exit(err)
    defined = defined_functions(obj)
    demangled = demangle(defined)
    matches = [f for f in defined if name in (f, demangled[f], demangled[f].split("(")[0],
                                              demangled[f].split("(")[0].split("::")[-1])]
    if len(matches) != 1:
        sys.exit(f"{len(matches)} functions named {name} in {source}" +
                 "".join(f"\n  {demangled[m]}" for m in matches))
    game = target_game()
    if game.covering(address):
        sys.exit(f"{address:#x} is inside {game.covering(address)[0]}, check it by name")
    return show(game, verify(game, ObjectFile(obj), matches[0], address))


def compile_everything():
    """Compile every root source and every header, and look for absolute includes: (source, object) pairs and the
    (file, error) pairs that failed."""
    with tempfile.TemporaryDirectory() as tmp:
        with ThreadPoolExecutor(max_workers=2) as pool:
            pending_headers = pool.submit(compile_headers, tmp)
            objects, errors = compile_all(tmp)
            errors += pending_headers.result() + absolute_includes()
    return objects, errors


def compile_only():
    """check --compile: everything builds, no game executable involved."""
    objects, errors = compile_everything()
    print_compile_errors(errors)
    if errors:
        print(paint(f"\n{len(errors)} {'file' if len(errors) == 1 else 'files'} failed to compile", "1;31"))
        return False
    headers = len(header_sources())
    print(paint(f"\n{len(objects)} {'source' if len(objects) == 1 else 'sources'} and "
                f"{headers} {'header' if headers == 1 else 'headers'} compile", "1;32"))
    return True


def data_report(per_object, results, prefixes):
    """What the function check does not compare, over every object: the global data that differs from the game's and
    the local data that sits on a symbol of the game or over another object ((name, problem, source)), the global
    functions defined by several sources ({function: sources}), and the local functions that match a prefix of the
    game's code ((function, address, instructions, game instructions, source)), as given by check_all."""
    problems, seen, local_objects = [], set(), []
    for (source, _, _), found in zip(per_object, results):
        source = os.path.relpath(source, ROOT)
        for name, problem in found["data"]:
            if (name, problem) not in seen:  # a vtable or an inline variable is defined by every object using it
                seen.add((name, problem))
                problems.append((name, problem, source))
        local_objects += [(name, base, size, source, shared) for name, base, size, shared in found["locals"]]
    for first, second in overlapping_objects(local_objects):
        problems.append((first[0], f"is at {first[1]:#x} in the game, over {second[0]} of {second[3]}", first[3]))
    duplicates = strong_duplicates([(os.path.relpath(source, ROOT), found["strong"])
                                    for (source, _, _), found in zip(per_object, results)])
    return SimpleNamespace(problems=problems, duplicates=duplicates, prefixes=prefixes)


def data_summary(report):
    return (f"data: {len(report.problems)} problems, duplicate definitions: {len(report.duplicates)}, "
            f"local prefix matches: {len(report.prefixes)}")


def print_data_report(report, new=None):
    """The section of the controls that only report for now, and its one line summary. With new (the part of the
    report that tools/data_baseline.txt does not list), only that part is listed."""
    shown = report if new is None else new
    if shown.problems or shown.duplicates or shown.prefixes:
        tokens = {token for _, problem, _ in shown.problems for token in MANGLED.findall(problem)}
        tokens |= {name for name, *_ in shown.problems} | set(shown.duplicates)
        tokens |= {symbol for symbol, *_ in shown.prefixes}
        mangled = sorted(t for t in tokens if t.startswith("_Z"))
        names = demangle(mangled) if mangled else {}

        def readable(text):
            return MANGLED.sub(lambda m: names.get(m[0], m[0]), text)

        if new is None:
            print(paint("\nNot compared by the function check (reported only, --strict-data makes them fail):", "1"))
        else:
            print(paint("\nNEW problems, not compared by the function check and not in tools/data_baseline.txt "
                        "(fix them; a justified one is added with `check --write-data-baseline` and a reason):", "1;31"))
        for name, problem, source in shown.problems:
            print(f"{paint('DATA     ', '33')}  {names.get(name, name)}  {readable(problem)}  {source}")
        for name, sources in shown.duplicates.items():
            print(f"{paint('DUPLICATE', '33')}  {names.get(name, name)}  defined by {', '.join(sources)}")
        for symbol, address, count, game_count, source in shown.prefixes:
            print(f"{paint('PREFIX   ', '33')}  {names.get(symbol, symbol)} (local, {address:#x})  "
                  f"{count} of the game's {game_count} instructions  {source}")
    print(paint("\n" + data_summary(report), "1"))


DATA_BASELINE = os.path.join(ROOT, "tools", "data_baseline.txt")
# The kinds of a line and how many words (KIND SYMBOL WHERE) of it there are at least: a duplicate has no place.
DATA_BASELINE_KINDS = {"DATA": 3, "DUPLICATE": 2, "PREFIX": 3}
DATA_BASELINE_HEADER = """\
# The data problems that `check` accepts for now: what its data report lists (DATA, DUPLICATE, PREFIX).
# `check --strict-data`, run by the pre-commit hook, fails on a problem that is not listed here (or listed without a
# reason) and prints `fixed:` for a listed problem the check no longer reports.
#
# One problem per line: KIND SYMBOL WHERE  # reason. SYMBOL is the mangled name; WHERE is the offset in the object
# (+0x20), `size`, or a game address (@0x...), and a DUPLICATE has none. No address of our own objects is part of a
# line, so it survives code moving.
# `check --write-data-baseline` rewrites this file from the report: it drops the fixed lines, adds the new ones with
# an empty reason and keeps the other reasons. Every line needs a reason, reviewed like a code change."""
# What the name of a local object without a symbol of its own looks like: its section and its offset in it.
ANONYMOUS_OBJECT = re.compile(r"(\.[\w.]+)\+0x[0-9a-f]+")
GAME_ADDRESS_OF_OBJECT = re.compile(r" at (0x[0-9a-f]+) in the game")


def problem_key(name, problem):
    """The line of tools/data_baseline.txt that stands for a DATA problem, without the text that moves with our code:
    the symbol and where in it (the offset, the size, or the address the game gives a local object), never the bytes
    or the address of an object of ours."""
    name = ANONYMOUS_OBJECT.sub(r"\1", name)
    at = re.match(r"at \+(0x[0-9a-f]+) ", problem)
    if at:
        return f"DATA {name} +{at[1]}"
    if problem.startswith("its size is"):
        return f"DATA {name} size"
    in_game = GAME_ADDRESS_OF_OBJECT.search(problem)
    if in_game:
        return f"DATA {name} @{in_game[1]}"
    return f"DATA {name} {' '.join(problem.split())}"


def duplicate_key(name):
    return f"DUPLICATE {name}"


def prefix_key(symbol, address):
    return f"PREFIX {symbol} @{address:#x}"


def data_keys(report):
    """The baseline line of every problem of the data report."""
    return ({problem_key(name, problem) for name, problem, _ in report.problems}
            | {duplicate_key(name) for name in report.duplicates}
            | {prefix_key(symbol, address) for symbol, address, *_ in report.prefixes})


def without_known(report, known):
    """The part of the data report whose baseline line is not in known."""
    return SimpleNamespace(
        problems=[p for p in report.problems if problem_key(p[0], p[1]) not in known],
        duplicates={name: sources for name, sources in report.duplicates.items() if duplicate_key(name) not in known},
        prefixes=[p for p in report.prefixes if prefix_key(p[0], p[1]) not in known])


def read_data_baseline(path=DATA_BASELINE):
    """({line: reason}, [errors]) of the baseline file: a missing file lists nothing, a line is KIND SYMBOL WHERE
    followed by # and its reason (empty when there is none), and every other line is blank or a comment."""
    entries, errors = {}, []
    if not os.path.exists(path):
        return entries, errors
    with open(path) as f:
        for number, text in enumerate(f, 1):
            body, _, reason = text.partition("#")
            tokens = body.split()
            if not tokens:
                continue
            where = f"{os.path.relpath(path, ROOT)}:{number}"
            if tokens[0] not in DATA_BASELINE_KINDS or len(tokens) < DATA_BASELINE_KINDS[tokens[0]]:
                errors.append(f"{where}: expected KIND SYMBOL WHERE  # reason with KIND one of "
                              f"{', '.join(DATA_BASELINE_KINDS)}, got {text.strip()!r}")
                continue
            line = " ".join(tokens)
            if line in entries:
                errors.append(f"{where}: {line} is listed twice")
            entries[line] = reason.strip()
    return entries, errors


def write_data_baseline(report, path=DATA_BASELINE):
    """Rewrite the baseline file from the data report, keeping the reason of every line that stays: the lines that
    the report no longer has are dropped, the new ones are written with an empty reason. Returns the lines that
    have no reason."""
    old, _ = read_data_baseline(path)
    lines = sorted(data_keys(report), key=lambda line: (list(DATA_BASELINE_KINDS).index(line.split()[0]), line))
    with open(path, "w") as f:
        f.write(DATA_BASELINE_HEADER + "\n\n")
        for line in lines:
            f.write(f"{line}  # {old.get(line, '')}".rstrip() + "\n")
    return [line for line in lines if not old.get(line)]


def check_against_baseline(report, path=DATA_BASELINE, incomplete=False):
    """Print what the data report holds beyond tools/data_baseline.txt, and which listed problems are gone. True when
    the check fails: a problem that is not listed, a listed one without a reason, or an unreadable file. An incomplete
    report (a file failed to compile or a function does not match: its data and prefixes are not collected) cannot
    tell that a listed problem is gone, so no problem is called fixed."""
    baseline, errors = read_data_baseline(path)
    new = without_known(report, baseline)
    found = data_keys(report)
    fixed = [] if incomplete else sorted(line for line in baseline if line not in found)
    unexplained = sorted(line for line, reason in baseline.items() if not reason)
    for error in errors:
        print(paint(f"BASELINE  {error}", "31"))
    print_data_report(report, new)
    for line in unexplained:
        print(f"{paint('NO REASON', '31')}  {line}  (every line of tools/data_baseline.txt needs a reason after #)")
    for line in fixed:
        print(f"{paint('fixed:   ', '32')}  {line}  (no longer reported: remove it from tools/data_baseline.txt "
              f"with `check --write-data-baseline`)")
    print(paint(f"data baseline: {len(found) - len(data_keys(new))} known, {len(data_keys(new))} new, "
                + ("report incomplete, fixed entries not evaluated" if incomplete else f"{len(fixed)} fixed"), "1"))
    return bool(errors or unexplained or new.problems or new.duplicates or new.prefixes)


def write_data_baseline_if_complete(report, incomplete, path=DATA_BASELINE):
    """Rewrite the baseline file from the report and say so, unless the report is incomplete (a file failed to
    compile or a function does not match: its writable data and prefix matches are not collected, so the file would
    lose their lines and reasons). True when the file was written."""
    if incomplete:
        print(paint("data baseline not written: a file failed to compile or a function does not match, "
                    "so the report is incomplete", "1;31"))
        return False
    unexplained = write_data_baseline(report, path)
    print(paint(f"wrote {os.path.relpath(path, ROOT)}: {len(data_keys(report))} problems, "
                f"{len(unexplained)} without a reason yet (write one after the # of each)", "1"))
    return True


def check_all(demangled, scope=None, verbose=True, strict_data=False, write_baseline=False):
    objects, errors = compile_everything()
    per_object = [(source, obj, [f for f in defined_functions(obj) if f in demangled and in_scope(demangled[f], scope)])
                  for source, obj in objects]
    # A full check also reads the objects that define no game function: they may define data.
    per_object = [entry for entry in per_object if entry[2] or not scope]
    unknown = unknown_functions(objects, demangled, scope)
    all_funcs = {f for _, _, funcs in per_object for f in funcs}
    # A game name sharing its address with a defined one (a C1/D1 alias of a C2/D2 body) is not left to decompile.
    addresses = {}
    if scope:
        for line in defined_symbols(TARGET_ELF).splitlines():
            parts = line.split()
            if len(parts) == 3:
                addresses[parts[2]] = parts[0]
    defined_addresses = {addresses[f] for f in all_funcs if f in addresses}

    def is_defined_alias(name, funcs):
        return name in addresses and addresses[name] in defined_addresses

    missing = sorted({demangled[m] for m in demangled if in_scope(demangled[m], scope) and m not in all_funcs and not is_defined_alias(m, all_funcs)}) if scope else []
    if not all_funcs and not scope:
        sys.exit("no game function defined under src/")
    rows, prefixes = [], []
    results = check_objects([(obj, funcs) for _, obj, funcs in per_object])
    for (source, obj, _), found in zip(per_object, results):
        for symbol, address, ok, count, local, game_count in found["rows"]:
            if local:
                rows.append((f"local:{address:#x}:{symbol}", os.path.relpath(source, ROOT), ok, count, obj, symbol, address))
                if ok and count < game_count:
                    prefixes.append((symbol, address, count, game_count, os.path.relpath(source, ROOT)))
            else:
                rows.append((symbol, os.path.relpath(defining_file(demangled[symbol], source), ROOT), ok, count, obj, symbol, None))
    rows = merge_copies(rows, lambda row: row[5], lambda row: row[2], lambda row: row[6] is not None)
    names = dict(demangled)
    locals_ = [row for row in rows if row[6] is not None]
    readable = demangle(sorted({row[5] for row in locals_})) if locals_ else {}
    for key, _, _, _, _, symbol, address in locals_:
        names[key] = f"{readable[symbol]} (local, {address:#x})"

    rows.sort(key=lambda r: (not r[2], r[1], names[r[0]]))
    mismatches = [r for r in rows if not r[2]]
    width = max((len(n) for n in [names[r[0]] for r in rows] + missing), default=0)
    for key, source, ok, count, *_ in rows if verbose else mismatches:
        status = paint("MATCH   ", "32") if ok else paint("NO MATCH", "31")
        print(f"{status}  {names[key]:<{width}}  {count:>4} insns  {source}")
    for m in missing:
        print(f"{paint('TODO    ', '2')}  {m}")

    print_unknown_functions(unknown)
    if mismatches:
        game = target_game()
        files = {}
        for key, source, _, _, obj, symbol, address in mismatches:
            obj = files.get(obj) or files.setdefault(obj, ObjectFile(obj))
            print(paint(f"\n=== {names[key]}  ({source})", "1"))
            show(game, verify(game, obj, symbol, address) if address is not None else verify_named(game, obj, symbol))
    sys.stdout.flush()
    print_compile_errors(errors)
    report = None if scope else data_report(per_object, results, prefixes)
    data_failed = False
    if report and strict_data:
        data_failed = check_against_baseline(report, incomplete=bool(errors or mismatches))
    elif report:
        print_data_report(report)
        if write_baseline:
            write_data_baseline_if_complete(report, bool(errors or mismatches))
    failed = bool(errors or unknown or data_failed)
    matched = len(rows) - len(mismatches)
    local_count = len(locals_)
    summary = f"\n{matched}/{len(rows)} functions match"
    if local_count:
        summary += f" ({local_count} of them local)"
    if scope:
        summary += f", {len(missing)} left to decompile in {scope}"
    if errors:
        summary += f", {len(errors)} {'file' if len(errors) == 1 else 'files'} failed to compile"
    if unknown:
        summary += f", {len(unknown)} not in the game"
    print(paint(summary, "1;32" if matched == len(rows) and not failed else "1;31"))
    return matched == len(rows) and not failed, [r[0] for r in rows if r[2] and r[6] is None]


def game_progress(matched):
    sizes = {}
    names = {}
    for line in defined_symbols(TARGET_ELF, sizes=True).splitlines():
        parts = line.split()
        if len(parts) == 4 and parts[2] in "TtWw":
            addr = int(parts[0], 16)
            sizes[addr] = int(parts[1], 16)
            names[parts[3]] = addr
    done = {names[f] for f in matched if f in names}
    return len(done), len(sizes), sum(sizes[a] for a in done), sum(sizes.values())


def progress_text(matched):
    funcs, total_funcs, size, total_size = game_progress(matched)
    return (f"{funcs:,} / {total_funcs:,} functions ({funcs / total_funcs:.3%}), "
            f"{size:,} / {total_size:,} bytes of code ({size / total_size:.3%})")


def update_readme(text):
    path = os.path.join(ROOT, "README.md")
    readme = open(path).read()
    block = f"{README_START}\n{text}\n{README_END}"
    updated = re.sub(re.escape(README_START) + ".*?" + re.escape(README_END), lambda _: block, readme, flags=re.S)
    if updated == readme and block not in readme:
        sys.exit(f"README.md has no {README_START} ... {README_END} section")
    open(path, "w").write(updated)


def main():
    args = sys.argv[1:]
    if args and args[0] in ("-h", "--help"):
        print(__doc__)
        return
    readme = "--readme" in args
    verbose = any(a in ("-v", "--verbose") for a in args)
    strict_data = "--strict-data" in args
    write_baseline = "--write-data-baseline" in args
    args = [a for a in args if a not in ("--readme", "-v", "--verbose", "--strict-data", "--write-data-baseline")]
    if "--compile" in args:
        if args != ["--compile"] or readme or verbose or strict_data or write_baseline:
            sys.exit("usage: check --compile")
        sys.exit(0 if compile_only() else 1)
    if (strict_data or write_baseline) and args:
        sys.exit("usage: check [-v] [--readme] [--strict-data]\n       check --write-data-baseline")
    if write_baseline and (strict_data or readme):
        sys.exit("usage: check --write-data-baseline")
    demangled = cached(os.path.join(CACHE_DIR, "target.demangled"), target_key(),
                       lambda: demangle(sorted(target_symbols())))
    if not args:
        ok, matched = check_all(demangled, verbose=verbose, strict_data=strict_data, write_baseline=write_baseline)
        text = progress_text(matched)
        print(paint(f"Game progress: {text}", "1"))
        if readme and ok:
            update_readme(text)
    else:
        name = args[0]
        symbol = resolve_symbol(name, demangled)
        if re.fullmatch(r"0x[0-9a-fA-F]+", name):
            if len(args) < 3:
                sys.exit("usage: check <address> <source.cpp> <name> [flags...]")
            ok = diff_unnamed(int(name, 16), args[1], args[2], args[3:])
        elif symbol:
            ok = diff_one(symbol, args[1] if len(args) > 1 else None, args[2:])
        elif any(in_scope(d, name) for d in demangled.values()):
            ok, _ = check_all(demangled, name)
        else:
            sys.exit(f"no function, class or namespace named {name} in the game binary")
    sys.exit(0 if ok else 1)


if __name__ == "__main__":
    main()
