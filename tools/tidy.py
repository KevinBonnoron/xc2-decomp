#!/usr/bin/env python3
"""clang-tidy on the lines a change adds, for the match-forcing code the quality gate's patterns cannot see.

Usage: tidy.py [--github] [BASE [HEAD]]

Runs a small list of objective checks over the sources and headers that changed between BASE and HEAD (defaults:
main and HEAD, the tree being checked out), and keeps only the findings on the added lines:
  clang-analyzer-deadcode.DeadStores         a value stored and never read
  clang-analyzer-core.uninitialized.*        a value read before it is set
  bugprone-branch-clone                      branches with identical bodies
  bugprone-suspicious-semicolon              a stray empty statement after if, for or while
  misc-redundant-expression                  identical operands, always true or false conditions
  -Wself-assign, -Wself-assign-field         x = x
The analysis is clang 21's, not the game's compiler: the sources are parsed with the game's language flags and
headers, which is enough for these checks. --github prints the findings as workflow annotations. Exit status 1 when
there is a finding or when a file cannot be analyzed.
"""
import json
import os
import re
import subprocess
import sys
from collections import defaultdict
from concurrent.futures import ThreadPoolExecutor

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from check import CXXFLAGS, HEADER_FLAGS, ROOT, included_sources, root_sources  # noqa: E402

CHECKS = ["-*", "clang-analyzer-deadcode.DeadStores", "clang-analyzer-core.uninitialized.*", "bugprone-branch-clone",
          "bugprone-suspicious-semicolon", "misc-redundant-expression", "clang-diagnostic-self-assign*"]
WARNINGS = ["-Wself-assign", "-Wself-assign-field"]
# The language and the headers of the game; what the code generation needs is not for the analysis.
FLAGS = [flag for flag in CXXFLAGS if flag.startswith(("--target", "-std", "-fno-exceptions", "-fno-rtti", "-D", "-I", "-isystem", "-idirafter"))]
HUNK = re.compile(r"^@@ -\S+ \+(\d+)(?:,(\d+))? @@")
FINDING = re.compile(r"^(.+?):(\d+):(\d+): (warning|error): (.*)$")


def git(*args):
    return subprocess.run(["git", *args], capture_output=True, text=True, check=True).stdout


def added_lines(base, head):
    """path -> [first, last] ranges of the lines the change adds to a source or header."""
    found = defaultdict(list)
    path = None
    for line in git("diff", "-U0", "--no-color", "--diff-filter=ACMR", base, head, "--", "src", "include").splitlines():
        if line.startswith("+++ "):
            path = line[6:] if line.startswith("+++ b/") else None
        elif path and path.endswith((".cpp", ".h")):
            hunk = HUNK.match(line)
            if hunk:
                start, count = int(hunk.group(1)), int(hunk.group(2) or 1)
                if count:
                    found[path].append([start, start + count - 1])
    return found


def translation_units(paths):
    """The sources that compile the changed files: a root source itself, the roots that include a part, and a header
    by itself."""
    roots = {os.path.relpath(r, ROOT): r for r in root_sources()}
    owners = defaultdict(set)
    for relative, root in roots.items():
        for part in included_sources(root):
            owners[os.path.relpath(part, ROOT)].add(relative)
    units = {}
    for path in paths:
        if path.endswith(".h"):
            units[path] = list(HEADER_FLAGS)
        elif path in roots:
            units[path] = []
        else:
            for owner in owners.get(path, ()):
                units[owner] = []
    return units


def analyze(unit, extra, ranges):
    filters = [{"name": p, "lines": r} for p, r in ranges.items()]
    args = ["clang-tidy-unwrapped", "-quiet", "-checks=" + ",".join(CHECKS), "-warnings-as-errors=",
            "-line-filter=" + json.dumps(filters), unit, "--", *FLAGS, *extra, *WARNINGS]
    proc = subprocess.run(args, capture_output=True, text=True, cwd=ROOT)
    return unit, proc.stdout, proc.stderr, proc.returncode


def main():
    args = [a for a in sys.argv[1:] if a != "--github"]
    github = "--github" in sys.argv[1:]
    base = args[0] if args else "main"
    head = args[1] if len(args) > 1 else "HEAD"
    ranges = added_lines(base, head)
    units = translation_units(sorted(ranges))
    # Each file is judged on its own added lines, wherever the translation unit that reaches it is.
    with ThreadPoolExecutor() as pool:
        results = list(pool.map(lambda item: analyze(item[0], item[1], ranges), sorted(units.items())))
    findings, failures = set(), []
    for unit, out, err, code in results:
        for line in out.splitlines():
            found = FINDING.match(line)
            if not found:
                continue
            path = os.path.relpath(found.group(1), ROOT)
            if found.group(4) == "error":
                failures.append(f"{unit}: {line}")
            elif path in ranges and any(a <= int(found.group(2)) <= b for a, b in ranges[path]):
                findings.add((path, int(found.group(2)), int(found.group(3)), found.group(5)))
        if code and not any(f.startswith(unit + ":") for f in failures):
            failures.append(f"{unit}: clang-tidy exited with {code}: {err.strip().splitlines()[-1] if err.strip() else ''}")
    for path, line, column, message in sorted(findings):
        if github:
            print(f"::warning file={path},line={line},col={column}::{message}")
        else:
            print(f"{path}:{line}:{column}: {message}")
    for failure in failures:
        print(f"tidy: cannot analyze {failure}", file=sys.stderr)
    print(f"tidy: {len(units)} files analyzed, {len(findings)} findings on added lines, {len(failures)} failures",
          file=sys.stderr)
    return 1 if findings or failures else 0


if __name__ == "__main__":
    sys.exit(main())
