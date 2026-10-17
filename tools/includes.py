#!/usr/bin/env python3
"""Keep the includes of src/ and include/ to what each file uses.

Usage:
  includes            list the includes to add, remove or replace by a forward declaration
  includes --fix      apply them
  includes <file>...  only these files

Every source and header goes through include-what-you-use: a file includes the
header of each name it uses, and a header forward-declares what it only needs
by pointer or reference instead of including it.
"""
import os
import re
import subprocess
import sys
from concurrent.futures import ThreadPoolExecutor

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from check import CXXFLAGS, HEADER_FLAGS, INCLUDE_DIRS, ROOT, header_sources, included_sources, root_sources  # noqa: E402

IWYU_FLAGS = [flag for flag in CXXFLAGS if flag.startswith(("--target", "-std", "-fno-exceptions", "-fno-rtti", "-D", "-I", "-isystem", "-idirafter"))]
IWYU_OPTIONS = ["-Xiwyu", "--max_line_length=200", "-Xiwyu", "--mapping_file=" + os.path.join(ROOT, "tools", "iwyu.imp")]


def sources():
    """Each source, and each header that is not the associated header of a source (analyzed along with it)."""
    parts = {part for root in root_sources() for part in included_sources(root)}
    cpps = root_sources() + sorted(parts)
    associated = {os.path.splitext(cpp)[0] + ".h" for cpp in cpps}
    return cpps + [header for header in header_sources() if header not in associated]


def analyze(path):
    extra = list(HEADER_FLAGS) if path.endswith(".h") else []
    proc = subprocess.run(["include-what-you-use", *IWYU_FLAGS, "-w", *extra, *IWYU_OPTIONS, path],
                          capture_output=True, text=True, cwd=ROOT)
    return path, proc.stderr


TEMPLATE_DEFINITION = re.compile(r"^template\s*<[^;{]*>\s*(?:class|struct)\s+(\w+)\s*(?:final\s*)?[:{]", re.M)
TEMPLATE_FORWARD = re.compile(r"^namespace .*\btemplate\s*<.*>\s*(?:class|struct)\s+(\w+);")


def template_headers():
    """Header of each class template: IWYU forward-declares templates even where they are needed whole."""
    found = {}
    for header in header_sources():
        for name in TEMPLATE_DEFINITION.findall(open(header).read()):
            root = next(directory for directory in INCLUDE_DIRS if header.startswith(directory + os.sep))
            found.setdefault(name, os.path.relpath(header, root))
    return found


def include_templates(block, headers):
    """Include the header of a template instead of forward-declaring it, and keep that include if IWYU drops it."""
    kept = set()
    lines = []
    for line in block.splitlines(keepends=True):
        forward = TEMPLATE_FORWARD.match(line)
        if forward and forward.group(1) in headers:
            include = f'#include "{headers[forward.group(1)]}"\n'
            kept.add(include.strip())
            if include not in lines:
                lines.append(include)
            continue
        lines.append(line)
    return "".join(line for line in lines
                   if not (line.startswith("- #include") and line[2:].split("  //")[0].strip() in kept))


def blocks(report):
    """Split an IWYU report into one block per file, keeping only the files that need a change."""
    blocks = [re.sub(r"^\(.* has correct #includes/fwd-decls\)\n+", "", block, flags=re.M) for block in report.split("---\n")]
    return [block + "---\n" for block in blocks if "should add these lines" in block]


def main():
    args = sys.argv[1:]
    fix = "--fix" in args
    files = [os.path.abspath(a) for a in args if a != "--fix"] or sources()
    with ThreadPoolExecutor() as pool:
        reports = list(pool.map(analyze, files))
    failed = [(path, report) for path, report in reports if "error:" in report]
    for path, report in failed:
        print(f"cannot analyze {os.path.relpath(path, ROOT)}:\n{report}", file=sys.stderr)
    headers = template_headers()
    changes = [include_templates(block, headers) for path, report in reports if "error:" not in report
               for block in blocks(report)]
    changes = [block for block in changes if has_change(block)]
    output = "".join(changes)
    if fix:
        subprocess.run(["fix_includes.py", "--nosafe_headers", "--nocomments", "--noreorder"],
                       input=output, text=True, cwd=ROOT, stdout=subprocess.DEVNULL)
    else:
        print(output, end="")
    print(f"{len(changes)} files {'fixed' if fix else 'to fix'}, {len(failed)} could not be analyzed", file=sys.stderr)
    sys.exit(1 if failed or (changes and not fix) else 0)


def has_change(block):
    """Whether a block still adds or removes something once the template forward declarations are includes."""
    add = block.split("should add these lines:\n", 1)[1].split("\n\n", 1)[0].strip()
    remove = block.split("should remove these lines:\n", 1)[1].split("The full include-list", 1)[0] if "should remove" in block else ""
    remove = [line for line in remove.splitlines() if line.startswith("- ")]
    current = set()
    path = block.split(" should add these lines:")[0].strip().splitlines()[-1]
    try:
        current = {line.strip() for line in open(os.path.join(ROOT, path) if not os.path.isabs(path) else path)}
    except OSError:
        pass
    added = [line for line in add.splitlines() if line.strip() and line.strip() not in current]
    return bool(added or remove)


if __name__ == "__main__":
    main()
