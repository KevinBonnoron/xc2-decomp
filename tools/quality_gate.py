#!/usr/bin/env python3
"""Quality gate for decompiled code added between two revisions.

Run from the repository root: python3 -I tools/quality_gate.py [base] [head]
(defaults: main and HEAD). Reports, for the lines added in src/ and include/:
- forbidden match-forcing patterns (goto, noinline, volatile, asm, raw offsets on this or void pointers,
  type punning through u64 pointers);
- destructors declared in the added code without a definition anywhere;
- duplicated code: a changed function that shares a run of statements with another function (an existing
  helper copied inline, or the same body pasted into several new functions).
Exits 1 when it finds anything.
"""
import re
import subprocess
import sys
from collections import defaultdict

BASE = sys.argv[1] if len(sys.argv) > 1 else "main"
HEAD = sys.argv[2] if len(sys.argv) > 2 else "HEAD"
PATHS = ["src", "include"]
# (block size, functions): a run of statements repeated in that many functions is reported.
RULES = [(4, 3), (3, 5)]

FORBIDDEN = [
    ("goto", re.compile(r"\bgoto\b")),
    ("noinline or other attribute", re.compile(r"__attribute__")),
    ("volatile", re.compile(r"\bvolatile\b")),
    ("inline asm", re.compile(r"\b(asm|__asm__)\b")),
    ("raw offset on this", re.compile(r"reinterpret_cast<[^>]*>\(\s*this\s*\)\s*\+|\(\s*u8\s*\*\s*\)\s*this")),
    ("raw offset on a pointer", re.compile(r"_cast<(const )?(u8|char|s8|void) \*>\(.*\)\s*\+\s*0x|\(\s*(const )?(u8|char) \*\s*\)\s*\w+\s*\+\s*0x")),
    ("type punning through a u64 pointer", re.compile(r"reinterpret_cast<(const )?u64 \*>")),
    ("packed float constant", re.compile(r"0x3f800000[0-9a-f]{8}|0x[0-9a-f]{8}3f800000", re.I)),
]

TRIVIAL = re.compile(r"^(\{|\}|\};|\} else \{|else|return;|return \w+;|return (true|false|nullptr|0|-1);|break;|continue;|default:|)$")
IDENT = re.compile(r"(?<![\w:.>])([A-Za-z_]\w*)(?!\s*[\w(:<])")
KEYWORDS = {"if", "else", "for", "while", "return", "const", "nullptr", "true", "false", "switch", "case", "do",
            "static_cast", "reinterpret_cast", "const_cast", "sizeof", "auto", "int", "u8", "u16", "u32", "u64",
            "s8", "s16", "s32", "s64", "f32", "f64", "bool", "void", "char", "this", "break", "continue"}


def git(*args):
    return subprocess.run(["git", *args], capture_output=True, text=True, check=True).stdout


def added_lines():
    """file -> set of added line numbers in HEAD, and the added line texts."""
    out = git("diff", "-U0", f"{BASE}..{HEAD}", "--", *PATHS)
    lines, texts, path, at = defaultdict(set), [], None, 0
    for line in out.splitlines():
        if line.startswith("+++ "):
            path = line[6:] if line != "+++ /dev/null" else None
        elif line.startswith("@@"):
            at = int(re.match(r"@@ -\S+ \+(\d+)", line).group(1))
        elif line.startswith("+") and path:
            lines[path].add(at)
            texts.append((path, at, line[1:]))
            at += 1
    return lines, texts


def strip_comments(text):
    text = re.sub(r"/\*.*?\*/", lambda m: "\n" * m.group(0).count("\n"), text, flags=re.S)
    text = re.sub(r"//[^\n]*", "", text)
    return re.sub(r'"(\\.|[^"\\])*"', '""', text)


def functions(path, text):
    """Top-level function definitions (column 0) of a file: (name, first line, last line, body lines)."""
    found = []
    lines = strip_comments(text).split("\n")
    i = 0
    while i < len(lines):
        line = lines[i]
        if line and not line[0].isspace() and "(" in line and not line.startswith(("#", "}", "namespace", "class ", "struct ", "static_assert", "using", "typedef", "extern")):
            start, sig = i, line
            while not sig.rstrip().endswith("{") and ";" not in sig and i + 1 < len(lines) and i - start < 6:
                i += 1
                sig += " " + lines[i].strip()
            if sig.rstrip().endswith("{") and ";" not in sig.split("{")[0]:
                depth, body = sig.count("{") - sig.count("}"), []
                j = i
                while depth > 0 and j + 1 < len(lines):
                    j += 1
                    depth += lines[j].count("{") - lines[j].count("}")
                    body.append((j + 1, lines[j]))
                name = re.search(r"([\w:~]+(?:operator\W+)?)\s*\(", sig)
                found.append((name.group(1) if name else sig[:40], start + 1, j + 1, body))
                i = j
            elif sig.rstrip().endswith("}"):
                found.append((re.search(r"([\w:~]+)\s*\(", sig).group(1) if re.search(r"([\w:~]+)\s*\(", sig) else sig[:40], start + 1, i + 1, [(start + 1, sig[sig.index("{") + 1:sig.rindex("}")])]))
        i += 1
    return found


def skeleton(line):
    """A statement with every plain identifier (locals, members) replaced, keeping calls and constants."""
    s = line.strip()
    if TRIVIAL.match(s):
        return None
    s = re.sub(r"^(const )?[\w:<>]+ \*?&?(\w+) = ", r"\2 = ", s)  # a declaration reads like an assignment
    def name(m):
        word = m.group(1)
        if word in KEYWORDS or re.fullmatch(r"unknown[0-9a-f_]+|m_\w+|_[0-9a-f]+", word):
            return word
        return "C" if re.fullmatch(r"[A-Z][A-Z0-9_]+", word) else "V"
    return IDENT.sub(name, s)


def main():
    added, texts = added_lines()
    problems = 0

    print(f"== Forbidden patterns ({BASE}..{HEAD})")
    for path, at, text in texts:
        code = re.sub(r"//.*", "", text)
        for label, pattern in FORBIDDEN:
            if pattern.search(code):
                print(f"{path}:{at}: {label}: {text.strip()[:140]}")
                problems += 1

    print("\n== Destructors declared but never defined")
    sources = git("grep", "-h", "-E", r"~\w+\(\)", HEAD, "--", *PATHS)
    for path, at, text in texts:
        m = re.search(r"^\s*(virtual )?~(\w+)\(\)( override)?;", text)
        if m and not re.search(rf"(::|\b){m.group(2)}::~{m.group(2)}\(\)|~{m.group(2)}\(\)[^;]*\{{|~{m.group(2)}\(\) = default", sources):
            print(f"{path}:{at}: ~{m.group(2)}() has no definition")
            problems += 1

    print("\n== Duplicated code")
    files = [f for f in git("ls-tree", "-r", "--name-only", HEAD, "--", *PATHS).splitlines() if f.endswith((".cpp", ".h"))]
    bodies, changed, where = {}, set(), {}
    for path in files:
        text = git("show", f"{HEAD}:{path}")
        for name, first, last, body in functions(path, text):
            key = (path, name, first)
            where[key] = f"{path}:{first} {name}"
            if any(first <= n <= last for n in added.get(path, ())):
                changed.add(key)
            bodies[key] = [sk for _, l in body for sk in [skeleton(l)] if sk]

    # (A) a changed function holds the whole body of another function: it should call it.
    def contains(outer, inner):
        n = len(inner)
        return any(outer[k:k + n] == inner for k in range(len(outer) - n + 1))
    def callable_from(helper, key):
        """A helper the changed function could call: same class, a free function, or an inline header helper."""
        hname, kname = helper[1], key[1]
        short = hname.split("::")[-1]
        if short.startswith("~") or (len(hname.split("::")) > 1 and hname.split("::")[-2] == short):
            return False
        return hname.rsplit("::", 1)[0] == kname.rsplit("::", 1)[0] or "::" not in hname or helper[0].endswith(".h")
    helpers = {k: b for k, b in bodies.items() if len(b) >= 3 and len(" ".join(b)) > 60}
    by_first = defaultdict(list)
    for k, b in helpers.items():
        by_first[b[0]].append(k)
    for key in sorted(changed, key=lambda k: where[k]):
        body = bodies[key]
        seen = set()
        for sk in set(body):
            for helper in by_first.get(sk, ()):
                if helper not in changed and helper != key and helper[1].split("::")[-1] != key[1].split("::")[-1] and helper not in seen and callable_from(helper, key) and contains(body, helpers[helper]):
                    seen.add(helper)
                    print(f"{where[key]}: contains the body of {where[helper]}; call it instead")
                    problems += 1

    # (B) the same block of statements in several functions: an inline helper written out each time.
    groups = defaultdict(set)
    for size, copies in RULES:
        runs = defaultdict(set)
        for key, body in bodies.items():
            for k in range(len(body) - size + 1):
                run = tuple(body[k:k + size])
                if sum(len(sk) > 14 for sk in run) >= 3 and len(" ".join(run)) > 20 * size:
                    runs[run].add(key)
        for run, keys in runs.items():
            if len(keys) >= copies and keys & changed:
                groups[frozenset(keys)].add(run)
    for keys in [k for k in groups if any(k < other for other in groups)]:
        del groups[keys]
    for keys, found in sorted(groups.items(), key=lambda g: -len(g[0])):
        print(f"{len(keys)} functions share a block of statements, e.g. " + " | ".join(max(found, key=len)))
        for key in sorted(keys, key=lambda k: where[k])[:8]:
            print(f"    {where[key]}{'' if key in changed else '  (existing)'}")
        if len(keys) > 8:
            print(f"    ... and {len(keys) - 8} more")
        problems += 1

    # (C) the same block several times inside one function: an unrolled loop written out by hand.
    for key in sorted(changed, key=lambda k: where[k]):
        body = [re.sub(r"\b(0x[0-9a-f]+|\d+)\b", "N", sk) for sk in bodies[key]]
        for size in (4, 3):
            counts = defaultdict(int)
            for k in range(len(body) - size + 1):
                run = tuple(body[k:k + size])
                if sum(len(sk) > 14 for sk in run) >= 2 and not any(sk.startswith("case ") for sk in run):
                    counts[run] += 1
            repeated = [run for run, n in counts.items() if n >= 3]
            if repeated:
                print(f"{where[key]}: the same block repeats {counts[repeated[0]]} times, e.g. " + " | ".join(repeated[0]))
                problems += 1
                break

    print(f"\n{problems} problem(s)")
    return 1 if problems else 0


if __name__ == "__main__":
    sys.exit(main())
