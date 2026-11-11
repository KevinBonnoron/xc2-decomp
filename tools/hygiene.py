#!/usr/bin/env python3
"""Repository hygiene of a pull request: things that must never be committed, or only by the hook on main.

Usage: hygiene.py [BASE [HEAD]]   (BASE = 4b825dc642cb6eb9a060e54bf8d69288fbee4904, the empty tree, audits a whole tree)

Looks at the files added or modified between the merge base of BASE and HEAD and HEAD (defaults: main and HEAD).
In the continuous integration HEAD is the merge of the pull request into main and BASE its first parent. Fails, one
line per violation, when a changed file:
  - lives under work/, which holds the local state (game executable, caches, dumps) and is never committed;
  - is a binary file, a game or SDK artefact (by extension or by magic number: ELF, NSO, NRO, PFS0, HFS0, NCA, XCI),
    or a submodule;
  - is larger than 1 MiB;
  - is progress/areas.json (changed or deleted), or changes the <!-- progress --> block of README.md: only the
    pre-commit hook writes them, on main;
  - adds a line holding the absolute path of a user's home directory (a Linux, macOS or Windows one).
It needs nothing but git and Python 3, so it runs without the game and without Nix.
"""
import os
import re
import subprocess
import sys

MAX_SIZE = 1 << 20
ARTEFACT_EXTENSIONS = {
    # Switch executables, containers and keys
    ".nso", ".nro", ".nrr", ".nca", ".nsp", ".xci", ".xcz", ".nsz", ".keys", ".tik", ".cert",
    # Xenoblade resource formats
    ".bdat", ".wismt", ".wimdo", ".wilay", ".wifnt", ".wiefnt", ".arc", ".ard", ".sar", ".mot",
    # binaries and what comes out of Ghidra or the compiler
    ".elf", ".o", ".obj", ".a", ".so", ".dll", ".dylib", ".exe", ".ghidra", ".gzf", ".gpr", ".rep",
}
# (offset, magic, what): a file starting with one of these is a game or SDK artefact whatever its name.
MAGICS = [
    (0, b"\x7fELF", "an ELF executable"),
    (0, b"NSO0", "a Switch NSO executable"),
    (0x10, b"NRO0", "a Switch NRO executable"),
    (0, b"PFS0", "a Switch PFS0 container"),
    (0, b"HFS0", "a Switch HFS0 container"),
    (0x100, b"HEAD", "a Switch XCI cartridge image"),
    (0x200, b"NCA2", "a Switch NCA archive"),
    (0x200, b"NCA3", "a Switch NCA archive"),
    (0, b"xbc1", "a Xenoblade compressed resource"),
]
HEAD_BYTES = 0x204
GITLINK = "160000"
HUNK = re.compile(r"^@@ -\S+ \+(\d+)")
README_BLOCK = re.compile(r"<!-- progress -->.*?<!-- /progress -->", re.S)
# Spelled with character classes so that this file does not match its own rule.
HOME_PATH = re.compile(r"(?<![\w.~$])/(?:hom[e]|User[s])/(?!(?:user|username|you|example|name|runner)\b|[<{$])[^\s\"'`)>]+|"
                       r"[A-Za-z]:[/\\]+User[s][/\\]+(?!(?:user|username|you|example|name)\b|[<{%])[^\s\"'`)>]+")
PLACEHOLDER_NOTE = "use a placeholder such as /home/user, or a path relative to the repository"
RESTORE_NOTE = ("restore them with `git checkout origin/main -- README.md progress/areas.json` "
                "(or put back only the progress block of README.md)")


def git(*args):
    return subprocess.run(["git", "--literal-pathspecs", *args], capture_output=True, check=True).stdout


def changed_files(base, head):
    """The merge base, and (status, new mode, path) of every file added, copied, modified, renamed (to this path),
    type-changed or deleted since."""
    try:
        base = git("merge-base", base, head).decode().strip() or base
    except subprocess.CalledProcessError:
        pass
    fields = git("diff", "-z", "--raw", "--no-abbrev", "--diff-filter=ACMRTD", "-M", base, head).decode().split("\0")
    found = []
    i = 0
    while i + 1 < len(fields) and fields[i]:
        meta = fields[i].lstrip(":").split()
        status = meta[4][0]
        step = 3 if status in "RC" else 2
        found.append((status, meta[1], fields[i + step - 1]))
        i += step
    return base, found


def blob_size(rev, path):
    return int(git("cat-file", "-s", f"{rev}:{path}").decode())


def blob_head(rev, path, count):
    """The first count bytes of a blob, without reading a large one whole."""
    with subprocess.Popen(["git", "cat-file", "blob", f"{rev}:{path}"], stdout=subprocess.PIPE) as proc:
        data = proc.stdout.read(count)
        proc.kill()
    return data


def blob(rev, path):
    return git("cat-file", "blob", f"{rev}:{path}")


def progress_block(text):
    found = README_BLOCK.search(text)
    return found.group(0) if found else None


def added_lines(base, head, path):
    """(line number, text) of the lines the change adds to a text file."""
    diff = git("-c", "core.quotePath=false", "diff", "-U0", "--text", "--no-ext-diff", "--no-color", base, head, "--",
               path).decode("utf-8", "replace")
    found, at, in_hunk = [], 0, False
    for line in diff.splitlines():
        hunk = HUNK.match(line)
        if hunk:
            at, in_hunk = int(hunk.group(1)), True
        elif in_hunk and line.startswith("+"):
            found.append((at, line[1:]))
            at += 1
    return found


def check_file(base, head, status, mode, path):
    """The violations of one changed file."""
    if status == "D":
        return ["is deleted, and only the pre-commit hook on main writes it: " + RESTORE_NOTE] \
            if path == "progress/areas.json" else []
    problems = []
    if path.startswith("work/"):
        problems.append("lives under work/, which is local state and never committed")
    if mode == GITLINK:
        return problems + ["is a submodule, which is not allowed"]
    extension = os.path.splitext(path)[1].lower()
    if extension in ARTEFACT_EXTENSIONS:
        problems.append(f"is a game, SDK or build artefact by its extension ({extension})")
    size = blob_size(head, path)
    if size > MAX_SIZE:
        problems.append(f"is {size} bytes, the limit is {MAX_SIZE} bytes (1 MiB)")
    data = blob(head, path) if size <= MAX_SIZE else blob_head(head, path, HEAD_BYTES)
    binary = b"\0" in data[:8000]
    for offset, magic, what in MAGICS:
        # A magic at an offset also happens in text by chance: it only counts in a binary file.
        if data[offset:offset + len(magic)] == magic and (offset == 0 or binary):
            problems.append(f"is {what} (magic number {magic!r})")
    if binary and not any("magic number" in p for p in problems):
        problems.append("is a binary file")
    if path == "progress/areas.json":
        problems.append("is written only by the pre-commit hook on main, do not change it in a pull request: " + RESTORE_NOTE)
    if path == "README.md" and size <= MAX_SIZE:
        try:
            before = progress_block(blob(base, path).decode("utf-8", "replace"))
        except subprocess.CalledProcessError:
            before = None
        if progress_block(data.decode("utf-8", "replace")) != before:
            problems.append("changes the <!-- progress --> block, which only the pre-commit hook writes, on main: " + RESTORE_NOTE)
    if not binary and size <= MAX_SIZE:
        for number, line in added_lines(base, head, path):
            found = HOME_PATH.search(line)
            if found:
                problems.append(f"line {number} holds an absolute home path ({found.group(0)}), {PLACEHOLDER_NOTE}")
                break
    return problems


def main():
    args = sys.argv[1:]
    if len(args) > 2 or any(a in ("-h", "--help") for a in args):
        print(__doc__)
        return 0 if args and args[0] in ("-h", "--help") else 2
    base = args[0] if args else "main"
    head = args[1] if len(args) > 1 else "HEAD"
    base, files = changed_files(base, head)
    violations = 0
    for status, mode, path in files:
        for problem in check_file(base, head, status, mode, path):
            print(f"hygiene: {path}: {problem}")
            violations += 1
    print(f"hygiene: {len(files)} changed {'file' if len(files) == 1 else 'files'} checked, "
          f"{violations} {'violation' if violations == 1 else 'violations'}")
    return 1 if violations else 0


if __name__ == "__main__":
    sys.exit(main())
