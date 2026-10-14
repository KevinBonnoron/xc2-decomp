#!/usr/bin/env python3
"""Compile sources and compare functions against the original game binary.

Usage:
  check                                   check every function defined in src/ and show the game progress
  check --readme                          same, and update the progress section of README.md
  check <scope>                           check every function of a class or namespace, list the missing ones
  check <symbol>                          diff one function, its source file is found automatically
  check <symbol> <source.cpp> [flags...]  diff one function from a given file
  check <address> <source.cpp> <name> [flags...]
                                          diff a function the game has no symbol for

<scope> is a class or namespace: gf::GfDataManager.
<symbol> is either a mangled name or a demangled one, with or without its
signature: gf::GfDataBlade::setHikariCurrent or 'gf::GfDataBlade::setHikariCurrent(bool)'.

Functions local to their source file (static, anonymous namespace) have no
symbol in the game. A call to one of them reads <local> on both sides: in the
game, a branch to an address outside every named function; in your object, a
branch to a function it defines that is local or unknown to the game. Any local
function matches any other, so check the local function itself by address: pass
its game address and its name in your file (mangled, qualified or not), e.g.
  check 0x710028c7ec src/application/BF2/gf/data/gf_data_obj.cpp unknown001
The game side ends at the next named function or at the next address some bl
calls, whichever comes first.
"""
import bisect
import difflib
import glob
import os
import re
import struct
import subprocess
import sys
import tempfile
from concurrent.futures import ThreadPoolExecutor

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
TARGET_ELF = os.path.join(ROOT, "work", "main_100.elf")
SRC_DIR = os.path.join(ROOT, "src")

CXX = "clang++-3.9.1"

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
    "-I" + os.path.join(ROOT, "include"),
    "-I" + os.path.join(ROOT, "src", "application", "BF2"),
]

FUNC_HEADER = re.compile(r"^[0-9a-f]+ <(\S+)>:$")
INSN = re.compile(r"^\s*[0-9a-f]+:\s+(.*)$")
RELOC = re.compile(r"^\s*[0-9a-f]+:\s+(R_AARCH64_\w+)\s+(\S+)")
BRANCH_TARGET = re.compile(r"0x[0-9a-f]+ <([^>+]+)(\+0x[0-9a-f]+)?>")
SOURCE_PATH = re.compile(r".*[/\\]([^/\\]+\.(?:cpp|h|inl|c))")
# Calls that receive __LINE__ (argument register) and an assertion text (x0): neither is game logic.
SOURCE_LOCATION_CALLS = {
    "_ZN2mm9MMStdBase8mmAssertEPKcS2_j": (2, True),
    "_ZnwmPN2gf11GfAllocatorEPKcmi": (3, False),
}
# Complete and base constructors and destructors are aliases at the same address: compare them as one.
STRUCTOR_VARIANT = re.compile(r"(<_ZN\w*?[0-9][A-Za-z_][A-Za-z0-9_]*)(C|D)2(E)")
INCLUDE_CPP = re.compile(r'^#include "([^"]+\.cpp)"', re.M)
MEM_OPERAND = re.compile(r"\[(\w+)(?:, #(-?0x[0-9a-f]+))?\]")
SHT_NOBITS = 8
README_START = "<!-- progress -->"
README_END = "<!-- /progress -->"

color = sys.stdout.isatty() and "NO_COLOR" not in os.environ


def paint(text, code):
    return f"\033[{code}m{text}\033[0m" if color and text.strip() else text


def run(args, **kwargs):
    return subprocess.run(args, check=True, capture_output=True, text=True, **kwargs).stdout


def demangle(names):
    return dict(zip(names, run(["llvm-cxxfilt"], input="\n".join(names)).splitlines()))


class Image:
    def __init__(self, path):
        self.data = open(path, "rb").read()
        shoff = struct.unpack_from("<Q", self.data, 0x28)[0]
        shentsize, shnum, shstrndx = struct.unpack_from("<HHH", self.data, 0x3A)
        headers = [struct.unpack_from("<IIQQQQIIQQ", self.data, shoff + i * shentsize) for i in range(shnum)]
        names = headers[shstrndx][4]
        self.sections = []
        for name, typ, _, addr, offset, size, *_ in headers:
            end = self.data.index(b"\0", names + name)
            self.sections.append((self.data[names + name:end].decode(), typ, addr, offset, size))

    def read(self, addr, size, section=None):
        for name, typ, start, offset, length in self.sections:
            if typ == SHT_NOBITS:
                continue
            base = start if section is None else 0
            if (section is None and start or name == section) and base <= addr < base + length:
                pos = offset + addr - base
                return self.data[pos:offset + min(addr - base + size, length)]
        return b""

    def section_name(self, addr):
        return next((name for name, _, start, _, length in self.sections if start and start <= addr < start + length), "")


def writable(section):
    return section.startswith((".data", ".bss"))


class TargetSymbols:
    def __init__(self):
        entries = []
        for line in run(["llvm-nm", "--defined-only", "-S", TARGET_ELF]).splitlines():
            parts = line.split()
            if len(parts) == 4:
                entries.append((int(parts[0], 16), int(parts[1], 16), parts[3]))
        entries.sort()
        self.starts = [e[0] for e in entries]
        self.entries = entries
        self.exact = {}
        for addr, _, name in entries:
            self.exact.setdefault(addr, name)
        self.stubs = {}

    def find_import_stubs(self, image):
        """Name the PLT stubs (adrp x16; ldr x17, [x16, #off]; add x16; br x17) after the import they jump to."""
        slots = {addr: name[len("__imp_"):] for addr, _, name in self.entries if name.startswith("__imp_")}
        for name, typ, start, offset, length in image.sections:
            if name != ".text":
                continue
            text = image.data[offset:offset + length]
            for pos in range(0, len(text) - 12, 4):
                adrp, ldr, add, br = struct.unpack_from("<IIII", text, pos)
                if adrp & 0x9F00001F != 0x90000010 or ldr & 0xFFC003FF != 0xF9400211 or br != 0xD61F0220:
                    continue
                pc = start + pos
                page = (pc & ~0xFFF) + (((((adrp >> 29) & 3) | (((adrp >> 5) & 0x7FFFF) << 2)) ^ 0x100000) - 0x100000 << 12)
                slot = page + ((ldr >> 10) & 0xFFF) * 8
                if slot in slots:
                    self.stubs[pc] = slots[slot]

    def unnamed_end(self, addr, image):
        """End of the unnamed function at addr: the next symbol, or the next address some bl calls."""
        if self.covering(addr):
            return None
        end = self.starts[bisect.bisect_right(self.starts, addr)]
        for name, _, start, offset, length in image.sections:
            if name != ".text" or not start <= addr < start + length:
                continue
            words = struct.unpack_from(f"<{length // 4}I", image.data, offset)
            for index, word in enumerate(words):
                if word & 0xFC000000 == 0x94000000:
                    callee = start + index * 4 + (((word & 0x3FFFFFF) ^ 0x2000000) - 0x2000000) * 4
                    if addr < callee < end:
                        end = callee
        return end

    def covering(self, addr):
        i = bisect.bisect_right(self.starts, addr) - 1
        if i < 0:
            return None
        start, size, name = self.entries[i]
        if addr == start or addr < start + size:
            return name, addr - start
        return None


def data_label(raw):
    end = raw.find(b"\0")
    try:
        text = raw[:end].decode("utf-8")
    except UnicodeDecodeError:
        return "data"
    if end > 0 and text.replace("\t", " ").replace("\n", " ").isprintable():
        source = SOURCE_PATH.fullmatch(text)
        return f'"…/{source.group(1)}"' if source else '"' + text + '"'
    return "data"


def target_label(addr, load64, image, syms):
    found = syms.covering(addr)
    if found:
        name, offset = found
        if name.startswith("__got_"):
            return "got:" + name[len("__got_"):]
        return name + (f"+{offset:#x}" if offset else "")
    if load64:
        pointer = image.read(addr, 8)
        if len(pointer) == 8 and struct.unpack("<Q", pointer)[0] in syms.exact:
            return "got:" + syms.exact[struct.unpack("<Q", pointer)[0]]
    if writable(image.section_name(addr)):
        return "data"
    return data_label(image.read(addr, 1024))


def object_label(rtype, target, image):
    if "GOT" in rtype:
        return "got:" + target
    match = re.fullmatch(r"(.+?)([+-]0x[0-9a-f]+)?", target)
    sym, addend = match.group(1), int(match.group(2) or "0", 16)
    if writable(sym):
        return "data"
    if sym.startswith("."):
        return data_label(image.read(addend, 1024, section=sym))
    return sym + (f"+{addend:#x}" if addend else "")


def with_label(text, label):
    op, _, args = text.partition("\t")
    if op in ("adrp", "adr"):
        return f"{op}\t{args.split(',')[0]}, <{label}>"
    if "[" in args:
        return MEM_OPERAND.sub(lambda m: f"[{m.group(1)}, <{label}>]", text, count=1)
    if op == "add":
        return re.sub(r", #0x[0-9a-f]+$", lambda _: f", <{label}>", text)
    return f"{op}\t<{label}>"


def objdump(path, symbols, relocs, local_functions=(), address=None):
    """Disassemble symbols, or with address the unnamed game function there, keyed by hex address."""
    image = Image(path)
    syms = None if relocs else TargetSymbols()
    if address is None:
        selection = [f"--disassemble-symbols={s}" for s in symbols]
    else:
        end = syms.unnamed_end(address, image)
        if end is None:
            sys.exit(f"{address:#x} is inside {syms.covering(address)[0]}, check it by name")
        selection = [f"--start-address={address:#x}", f"--stop-address={end:#x}"]
    args = ["llvm-objdump", "-d", "--no-show-raw-insn", *selection, path]
    if relocs:
        args.insert(2, "-r")
    if syms:
        syms.find_import_stubs(image)
    funcs = {}
    lines = funcs.setdefault(f"{address:#x}", []) if address is not None else None
    for line in run(args).splitlines():
        header = FUNC_HEADER.match(line)
        if header and address is None:
            lines = funcs.setdefault(header.group(1), [])
            continue
        if lines is None:
            continue
        reloc = RELOC.match(line)
        if reloc and lines:
            lines[-1] = with_label(lines[-1], object_label(reloc.group(1), reloc.group(2), image))
            continue
        insn = INSN.match(line)
        if insn:
            lines.append(insn.group(1).split("//")[0].rstrip())
    sizes = {} if relocs else {name: size for _, size, name in syms.entries}
    for name, lines in funcs.items():
        if not relocs:
            del lines[sizes.get(name, len(lines) * 4) // 4:]
            resolve_pages(lines, image, syms)
        funcs[name] = ignore_source_locations([STRUCTOR_VARIANT.sub(r"\1\g<2>1\3", label_branch(l, syms, local_functions))
                                               for l in lines])
    return funcs


def is_branch(op):
    return op in ("b", "bl", "cbz", "cbnz", "tbz", "tbnz") or op.startswith("b.")


def label_branch(text, syms, local_functions):
    """Name a branch target; a function the game has no symbol for, or local to your file, is <local>."""
    branch = is_branch(text.partition("\t")[0])

    def target(match):
        name = match.group(1)
        if syms:
            addr = int(match.group(0).split()[0], 16)
            if addr in syms.stubs:
                return f"<{syms.stubs[addr]}>"
            if branch and not syms.covering(addr):
                return "<local>"
        return "<local>" if branch and name in local_functions else f"<{name}>"

    return BRANCH_TARGET.sub(target, text)


def ignore_source_locations(lines):
    for i, text in enumerate(lines):
        op, _, target = text.partition("\t")
        if op not in ("bl", "b") or target.strip("<>") not in SOURCE_LOCATION_CALLS:
            continue
        line_reg, has_text = SOURCE_LOCATION_CALLS[target.strip("<>")]
        for j in range(i - 1, max(i - 16, -1), -1):
            prev_op, _, args = lines[j].partition("\t")
            if prev_op in ("bl", "b", "br", "ret") or prev_op.startswith("b."):
                break
            regs = [a.strip() for a in args.split(",")]
            if prev_op in ("mov", "orr") and regs[0] in (f"w{line_reg}", f"x{line_reg}") and regs[-1].startswith("#"):
                lines[j] = f"mov\t{regs[0]}, <line>"
            elif prev_op == "mov" and regs[0] in (f"w{line_reg}", f"x{line_reg}") and re.fullmatch(r"[wx]\d+", regs[1]):
                hoisted = regs[1][1:]
                for k in range(j - 1, -1, -1):
                    hoisted_op, _, hoisted_args = lines[k].partition("\t")
                    hoisted_regs = [a.strip() for a in hoisted_args.split(",")]
                    if hoisted_op in ("mov", "orr") and hoisted_regs[0] in (f"w{hoisted}", f"x{hoisted}") and hoisted_regs[-1].startswith("#"):
                        lines[k] = f"mov\t{hoisted_regs[0]}, <line>"
                        break
            elif has_text and prev_op in ("adrp", "add") and regs[0] == "x0" and '<"' in args:
                lines[j] = re.sub(r'<"(.*)">', lambda m: '<"' + m.group(1).replace(" ", "") + '">', lines[j])
    return lines


def resolve_pages(lines, image, syms):
    pages = {}
    labeled = set()
    for i, text in enumerate(lines):
        op, _, args = text.partition("\t")
        regs = [a.strip() for a in args.split(",")]
        if op == "adrp":
            pages[regs[0]] = (i, int(regs[1].split()[0], 16))
            continue
        mem = MEM_OPERAND.search(args)
        if mem and mem.group(1) in pages:
            base, imm = mem.group(1), int(mem.group(2) or "0", 16)
        elif op == "add" and len(regs) == 3 and regs[1] in pages and regs[2].startswith("#0x"):
            base, imm = regs[1], int(regs[2][1:], 16)
        else:
            for r in regs[:1]:
                pages.pop(r, None)
            continue
        adrp_index, page = pages[base]
        label = target_label(page + imm, op == "ldr" and regs[0].startswith("x"), image, syms)
        if adrp_index not in labeled:
            lines[adrp_index] = with_label(lines[adrp_index], label)
            labeled.add(adrp_index)
        lines[i] = with_label(text, label)
        if op != "str":
            pages.pop(regs[0], None)


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


def compile_source(source, tmp, extra=()):
    obj = os.path.join(tmp, os.path.relpath(source, ROOT).replace(os.sep, "_") + ".o")
    proc = subprocess.run([os.environ.get("XC2_CXX", CXX), *CXXFLAGS, *extra, "-c", source, "-o", obj],
                          capture_output=True, text=True)
    if proc.returncode:
        return None, proc.stderr
    return obj, None


def defined_functions(obj):
    out = run(["llvm-nm", "--defined-only", obj])
    return [parts[2] for parts in (l.split() for l in out.splitlines()) if len(parts) == 3 and parts[1] in "TtWw"]


def local_functions(obj, known):
    out = run(["llvm-nm", "--defined-only", obj])
    return {parts[2] for parts in (l.split() for l in out.splitlines())
            if len(parts) == 3 and (parts[1] == "t" or parts[1] in "TWw" and parts[2] not in known)}


def included_sources(source):
    found = []
    for name in INCLUDE_CPP.findall(open(source).read()):
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


def defining_file(demangled_name, root):
    qualified = demangled_name.split("(")[0].split("::")
    needle = "::".join(qualified[-2:]) + "("
    for path in included_sources(root) + [root]:
        if needle in open(path).read():
            return path
    return root


def compile_all(tmp):
    sources = root_sources()
    with ThreadPoolExecutor() as pool:
        results = list(pool.map(lambda s: (s, *compile_source(s, tmp)), sources))
    errors = [(os.path.relpath(source, ROOT), err) for source, _, err in results if err]
    return [(source, obj) for source, obj, _ in results if obj], errors


def print_compile_errors(errors):
    for source, err in errors:
        print(paint(f"compile error: {source}", "1;31"), file=sys.stderr)
        print(err, file=sys.stderr)


def print_diff(target, mine):
    if mine == target:
        print(paint(f"MATCH ({len(target)} instructions)", "1;32"))
        return True
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
    print(paint(f"\nNO MATCH: target {len(target)} instructions, yours {len(mine)}", "1;31"))
    return False


def diff_one(symbol, source, extra, known):
    with tempfile.TemporaryDirectory() as tmp:
        if source:
            obj, err = compile_source(source, tmp, extra)
            if err:
                sys.exit(err)
        else:
            objects, _ = compile_all(tmp)
            obj = next((o for _, o in objects if symbol in defined_functions(o)), None)
            if obj is None:
                sys.exit(f"{demangle([symbol])[symbol]} is not defined in any file under src/")
        mine = objdump(obj, [symbol], relocs=True, local_functions=local_functions(obj, known)).get(symbol)
    if not mine:
        sys.exit(f"{symbol} not found in compiled object (check the mangled name with llvm-nm)")
    target = objdump(TARGET_ELF, [symbol], relocs=False)[symbol]
    return print_diff(target, mine)


def diff_unnamed(address, source, name, extra, known):
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
        mine = objdump(obj, matches, relocs=True, local_functions=local_functions(obj, known))[matches[0]]
    target = objdump(TARGET_ELF, [], relocs=False, address=address)[f"{address:#x}"]
    return print_diff(target, mine)


def check_all(demangled, scope=None):
    rows = []
    with tempfile.TemporaryDirectory() as tmp:
        objects, errors = compile_all(tmp)
        per_object = [(source, obj, [f for f in defined_functions(obj) if f in demangled and in_scope(demangled[f], scope)])
                      for source, obj in objects]
        all_funcs = [f for _, _, funcs in per_object for f in funcs]
        missing = sorted({demangled[m] for m in demangled if in_scope(demangled[m], scope) and m not in all_funcs}) if scope else []
        if not all_funcs and not scope:
            sys.exit("no game function defined under src/")
        targets = objdump(TARGET_ELF, all_funcs, relocs=False)
        for source, obj, funcs in per_object:
            mine = objdump(obj, funcs, relocs=True, local_functions=local_functions(obj, demangled)) if funcs else {}
            for f in funcs:
                rows.append((f, os.path.relpath(defining_file(demangled[f], source), ROOT), targets.get(f, []), mine.get(f, [])))

    rows.sort(key=lambda r: (r[2] != r[3], r[1], demangled[r[0]]))
    mismatches = [r for r in rows if r[2] != r[3]]
    width = max((len(n) for n in [demangled[f] for f, *_ in rows] + missing), default=0)
    for f, source, target, mine in rows:
        status = paint("MATCH   ", "32") if target == mine else paint("NO MATCH", "31")
        print(f"{status}  {demangled[f]:<{width}}  {len(target):>4} insns  {source}")
    for m in missing:
        print(f"{paint('TODO    ', '2')}  {m}")

    for f, source, target, mine in mismatches:
        print(paint(f"\n=== {demangled[f]}  ({source})", "1"))
        print_diff(target, mine)
    sys.stdout.flush()
    print_compile_errors(errors)
    failed = bool(errors)
    matched = len(rows) - len(mismatches)
    summary = f"\n{matched}/{len(rows)} functions match"
    if scope:
        summary += f", {len(missing)} left to decompile in {scope}"
    if failed:
        summary += f", {len(errors)} {'file' if len(errors) == 1 else 'files'} failed to compile"
    print(paint(summary, "1;32" if matched == len(rows) and not failed else "1;31"))
    return matched == len(rows) and not failed, [f for f, _, target, mine in rows if target == mine]


def game_progress(matched):
    sizes = {}
    names = {}
    for line in run(["llvm-nm", "--defined-only", "-S", TARGET_ELF]).splitlines():
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
    args = [a for a in args if a != "--readme"]
    known = sorted(target_symbols())
    demangled = demangle(known)
    if not args:
        ok, matched = check_all(demangled)
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
            ok = diff_unnamed(int(name, 16), args[1], args[2], args[3:], demangled)
        elif symbol:
            ok = diff_one(symbol, args[1] if len(args) > 1 else None, args[2:], demangled)
        elif any(in_scope(d, name) for d in demangled.values()):
            ok, _ = check_all(demangled, name)
        else:
            sys.exit(f"no function, class or namespace named {name} in the game binary")
    sys.exit(0 if ok else 1)


if __name__ == "__main__":
    main()
