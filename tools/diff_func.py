#!/usr/bin/env python3
"""Compile sources and compare functions against the original game binary.

Usage:
  diff-func                                   check every function defined in src/
  diff-func <symbol>                          diff one function, its source file is found automatically
  diff-func <symbol> <source.cpp> [flags...]  diff one function from a given file

<symbol> is either a mangled name or a demangled one, with or without its
signature: gf::GfDataBlade::setHikariCurrent or 'gf::GfDataBlade::setHikariCurrent(bool)'.
"""
import difflib
import glob
import os
import re
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
    "-fPIC",
    "-g",
    "-I" + os.path.join(ROOT, "include"),
    "-I" + os.path.join(ROOT, "src", "application", "BF2"),
]

FUNC_HEADER = re.compile(r"^[0-9a-f]+ <(\S+)>:$")
INSN = re.compile(r"^\s*[0-9a-f]+:\s+(.*)$")
RELOC = re.compile(r"^\s*[0-9a-f]+:\s+(R_AARCH64_\w+)\s+(\S+)")
BRANCH_TARGET = re.compile(r"0x[0-9a-f]+ <([^>+]+)(\+0x[0-9a-f]+)?>")

color = sys.stdout.isatty() and "NO_COLOR" not in os.environ


def paint(text, code):
    return f"\033[{code}m{text}\033[0m" if color and text.strip() else text


def run(args, **kwargs):
    return subprocess.run(args, check=True, capture_output=True, text=True, **kwargs).stdout


def demangle(names):
    return dict(zip(names, run(["llvm-cxxfilt"], input="\n".join(names)).splitlines()))


def objdump(path, symbols, relocs):
    args = ["llvm-objdump", "-d", "--no-show-raw-insn", *(f"--disassemble-symbols={s}" for s in symbols), path]
    if relocs:
        args.insert(2, "-r")
    funcs = {}
    lines = None
    for line in run(args).splitlines():
        header = FUNC_HEADER.match(line)
        if header:
            lines = funcs.setdefault(header.group(1), [])
            continue
        if lines is None:
            continue
        reloc = RELOC.match(line)
        if reloc and lines:
            op = lines[-1].split("\t")[0]
            lines[-1] = f"{op}\t<{reloc.group(2)}>"
            continue
        insn = INSN.match(line)
        if insn:
            text = insn.group(1).split("//")[0].rstrip()
            text = BRANCH_TARGET.sub(lambda m: f"<{m.group(1)}>", text)
            lines.append(text)
    return funcs


def target_symbols():
    return set(run(["llvm-nm", "--defined-only", "--format=just-symbols", TARGET_ELF]).split())


def resolve_symbol(name, known):
    if name.startswith("_Z"):
        return name
    names = sorted(known)
    demangled = demangle(names)
    exact = [m for m in names if demangled[m] == name]
    if exact:
        return exact[0]
    candidates = [m for m in names if demangled[m].split("(")[0] == name]
    if len(candidates) == 1:
        return candidates[0]
    if not candidates:
        sys.exit(f"no function named {name} in the game binary")
    sys.exit(f"{name} is ambiguous, pass the full signature:\n" + "\n".join(f"  {demangled[m]}" for m in candidates))


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


def compile_all(tmp):
    sources = sorted(glob.glob(os.path.join(SRC_DIR, "**", "*.cpp"), recursive=True))
    with ThreadPoolExecutor() as pool:
        results = list(pool.map(lambda s: (s, *compile_source(s, tmp)), sources))
    failed = False
    for source, obj, err in results:
        if err:
            failed = True
            print(paint(f"compile error: {os.path.relpath(source, ROOT)}", "1;31"), file=sys.stderr)
            print(err, file=sys.stderr)
    return [(source, obj) for source, obj, _ in results if obj], failed


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


def diff_one(name, source, extra):
    known = target_symbols()
    symbol = resolve_symbol(name, known)
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
        mine = objdump(obj, [symbol], relocs=True).get(symbol)
    if not mine:
        sys.exit(f"{symbol} not found in compiled object (check the mangled name with llvm-nm)")
    target = objdump(TARGET_ELF, [symbol], relocs=False)[symbol]
    return print_diff(target, mine)


def check_all():
    known = target_symbols()
    rows = []
    with tempfile.TemporaryDirectory() as tmp:
        objects, failed = compile_all(tmp)
        per_object = [(source, obj, [f for f in defined_functions(obj) if f in known]) for source, obj in objects]
        all_funcs = [f for _, _, funcs in per_object for f in funcs]
        if not all_funcs:
            sys.exit("no game function defined under src/")
        targets = objdump(TARGET_ELF, all_funcs, relocs=False)
        for source, obj, funcs in per_object:
            mine = objdump(obj, funcs, relocs=True) if funcs else {}
            for f in funcs:
                rows.append((f, os.path.relpath(source, ROOT), mine.get(f) == targets.get(f), len(targets.get(f, []))))

    names = demangle([f for f, *_ in rows])
    width = max(len(names[f]) for f, *_ in rows)
    for f, source, ok, size in sorted(rows, key=lambda r: (r[2], r[1], names[r[0]])):
        status = paint("MATCH   ", "32") if ok else paint("NO MATCH", "31")
        print(f"{status}  {names[f]:<{width}}  {size:>4} insns  {source}")
    matched = sum(ok for _, _, ok, _ in rows)
    summary = f"\n{matched}/{len(rows)} functions match"
    print(paint(summary, "1;32" if matched == len(rows) and not failed else "1;31"))
    return matched == len(rows) and not failed


def main():
    args = sys.argv[1:]
    if args and args[0] in ("-h", "--help"):
        print(__doc__)
        return
    if not args:
        ok = check_all()
    else:
        ok = diff_one(args[0], args[1] if len(args) > 1 else None, args[2:])
    sys.exit(0 if ok else 1)


if __name__ == "__main__":
    main()
