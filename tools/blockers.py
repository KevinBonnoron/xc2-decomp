#!/usr/bin/env python3
"""Structured list of the reasons game functions are not matched yet: work/blockers.json.

Agents record a function they gave up on with `add` instead of editing a free text skip list.

Usage:
  blockers.py add FUNCTION... -c CATEGORY -d DETAIL [--zone Z] [--source RUN] [--all]
  blockers.py list [--zone Z] [--category C] [--function TEXT] [--source RUN] [--json]
  blockers.py stats [--zone Z]
  blockers.py retire [FUNCTION... [--reason TEXT]] [--dry-run]
  blockers.py refresh [--dry-run]                 re-read the zone of every record from work/status.json
  blockers.py import-skip FILE... [--dry-run]     one-off migration of the free text skip lists

FUNCTION is a mangled name, a demangled name with its signature, or a qualified name without one
(GfFoo::bar or gf::GfFoo::bar). A name shared by several overloads needs --all, or the exact signature.
The function must be a game function of work/status.json (python3 tools/status.py, in the nix develop shell).

CATEGORY is one of:
  registers                 same instructions, different registers
  scheduling                same instructions, different order or block layout
  store-merge               stores merged, split or reordered
  shared-type:<Type>        needs the layout or a change of a type other code uses
  missing-class:<Class>     needs a class that is not declared yet
  missing-helper:<addr>     needs a game function without a symbol (address 0x71...)
  container:<Cont::method>  a container method (FixedVector::resize, Map::find...) compiles differently
  reinline-forbidden        only matches with a function body written out again (forbidden)
  uninit-forbidden          only matches with an uninitialized value (forbidden)
  ui-human                  ui code reserved for a human
  btl-reserved              battle code reserved
  vtable-emission           the class vtable or its key function is emitted with the function
  other                     anything else: say what in the detail

Records live in work/blockers.json (never committed): function, mangled, zone, category, detail, date, source.
Run it from your own worktree or by the main checkout path: a worktree without work/blockers.json of its own
should use the tools/blockers.py of the main checkout so all agents write the same file.
`retire` drops the records of the functions that now match according to work/status.json and keeps them,
with the date, under "retired".
"""
import argparse
import collections
import contextlib
import datetime
import difflib
import fcntl
import json
import os
import re
import subprocess
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
WORK = os.path.join(ROOT, "work")
BLOCKERS_PATH = os.path.join(WORK, "blockers.json")
STATUS_PATH = os.path.join(WORK, "status.json")
UNMIGRATED_PATH = os.path.join(WORK, "blockers-unmigrated.txt")

PLAIN = ("registers", "scheduling", "store-merge", "reinline-forbidden", "uninit-forbidden", "ui-human",
         "btl-reserved", "vtable-emission", "other")
PARAMETERIZED = {
    "shared-type": re.compile(r"[A-Za-z_][\w:<>, *&]*"),
    "missing-class": re.compile(r"[A-Za-z_][\w:<>, *&]*"),
    "missing-helper": re.compile(r"0x[0-9a-f]{6,}"),
    "container": re.compile(r"[A-Za-z_][\w:<>, ]*::[~A-Za-z_]\w*"),
}


def today():
    return datetime.date.today().isoformat()


def die(message):
    sys.exit(f"blockers: {message}")


def valid_category(text):
    """The category written canonically, or an error naming the valid ones."""
    text = text.strip()
    if text in PLAIN:
        return text
    kind, _, argument = text.partition(":")
    if kind in PARAMETERIZED and PARAMETERIZED[kind].fullmatch(argument):
        return f"{kind}:{argument.lower() if kind == 'missing-helper' else argument}"
    if kind in PARAMETERIZED:
        die(f"category {text!r}: {kind} needs an argument, e.g. {kind}:<{'addr 0x71...' if kind == 'missing-helper' else 'name'}>"
            + (" in the form Container::method" if kind == "container" else ""))
    die(f"unknown category {text!r}, one of: " + ", ".join(list(PLAIN[:3]) + [f"{k}:<..>" for k in PARAMETERIZED] + list(PLAIN[3:])))


def load_status():
    try:
        with open(STATUS_PATH) as f:
            return json.load(f)
    except FileNotFoundError:
        die(f"{STATUS_PATH} does not exist: run `nix develop -c python3 tools/status.py` in the main checkout")


def status_by_name(status):
    return {r["name"]: r for r in status["functions"] if r["state"] != "local"}


def load_blockers():
    try:
        with open(BLOCKERS_PATH) as f:
            return json.load(f)
    except FileNotFoundError:
        return {"version": 1, "blockers": [], "retired": []}


@contextlib.contextmanager
def locked(write=True):
    """Exclusive access to blockers.json for a read-modify-write; the document is replaced atomically."""
    os.makedirs(WORK, exist_ok=True)
    with open(BLOCKERS_PATH + ".lock", "w") as lock:
        fcntl.flock(lock, fcntl.LOCK_EX)
        document = load_blockers()
        yield document
        if not write:
            return
        partial = f"{BLOCKERS_PATH}.{os.getpid()}"
        with open(partial, "w") as f:
            json.dump(document, f, indent=1)
            f.write("\n")
        os.replace(partial, BLOCKERS_PATH)


def current_run():
    if os.environ.get("BLOCKER_RUN"):
        return os.environ["BLOCKER_RUN"]
    try:
        out = subprocess.run(["git", "branch", "--show-current"], capture_output=True, text=True, check=True).stdout
    except (OSError, subprocess.CalledProcessError):
        return "unknown"
    return out.strip() or "unknown"


def one_per_address(records):
    """Aliases (the C1 and C2 constructors) share one body: keep one record per address."""
    seen, out = set(), []
    for record in sorted(records, key=lambda r: r["name"]):
        if record["address"] not in seen:
            seen.add(record["address"])
            out.append(record)
    return out


def strip_signature(demangled):
    depth = 0
    for i, ch in enumerate(demangled):
        if ch == "<":
            depth += 1
        elif ch == ">":
            depth -= 1
        elif ch == "(" and depth == 0:
            return demangled[:i]
    return demangled


def resolve(text, status):
    """Game functions (one record per address) a user supplied name stands for."""
    text = text.strip()
    functions = [r for r in status["functions"] if r["state"] != "local"]
    found = [r for r in functions if r["name"] == text]
    if not found:
        normal = re.sub(r"\s+", " ", text)
        found = [r for r in functions if r["demangled"] == normal]
    if not found:
        bare = normal.rstrip()
        found = [r for r in functions if strip_signature(r["demangled"]) == bare]
    if not found:
        found = [r for r in functions if strip_signature(r["demangled"]).endswith("::" + bare) or r["demangled"].endswith("::" + normal)]
    return one_per_address(found)


def suggestions(text, status):
    names = {strip_signature(r["demangled"]) for r in status["functions"] if r["state"] != "local"}
    return difflib.get_close_matches(strip_signature(text), sorted(names), n=5, cutoff=0.6)


def record_for(function, category, detail, source, date=None):
    return {"function": function["demangled"], "mangled": function["name"], "zone": function["zone"],
            "category": category, "detail": detail, "date": date or today(), "source": source}


def store(document, new):
    """Add a record; the same function and category again replaces the older record. The generic `other` records
    of a function give way to a specific one."""
    mine = [b for b in document["blockers"] if b["mangled"] == new["mangled"]]
    for old in mine:
        if old["category"] == new["category"] or (old["category"] == "other" and new["category"] != "other"):
            document["blockers"].remove(old)
        elif new["category"] == "other":
            return False
    document["blockers"].append(new)
    return True


def cmd_add(args):
    category = valid_category(args.category)
    if not args.detail.strip():
        die("a detail is required (-d)")
    status = load_status()
    chosen = []
    for name in args.function:
        found = resolve(name, status)
        if not found:
            close = suggestions(name, status)
            die(f"no game function named {name!r}" + (f"; close names: {', '.join(close)}" if close else ""))
        if len(found) > 1 and not args.all:
            die(f"{name!r} is {len(found)} functions (overloads); give the signature or pass --all:\n  "
                + "\n  ".join(r["demangled"] for r in found[:10]))
        chosen += found
    source = args.source or current_run()
    with locked() as document:
        for function in chosen:
            if function["state"] == "match":
                print(f"skipped {function['demangled']}: it already matches")
                continue
            store(document, record_for(function, category, args.detail.strip(), source))
            print(f"recorded {function['demangled']}  [{category}]")


def selected(document, args):
    out = []
    for b in document["blockers"]:
        if args.zone and b["zone"] != args.zone:
            continue
        if getattr(args, "category", None) and not (b["category"] == args.category or b["category"].startswith(args.category + ":")):
            continue
        if getattr(args, "function", None) and args.function.lower() not in b["function"].lower():
            continue
        if getattr(args, "source", None) and b["source"] != args.source:
            continue
        out.append(b)
    return out


def cmd_list(args):
    rows = selected(load_blockers(), args)
    if args.json:
        json.dump(rows, sys.stdout, indent=1)
        print()
        return
    for b in sorted(rows, key=lambda b: (b["zone"], b["category"], b["function"])):
        detail = b["detail"] if len(b["detail"]) <= 90 else b["detail"][:87] + "..."
        print(f"{b['zone']:<10} {b['category']:<28} {b['function'][:70]:<70}  {detail}")
    print(f"{len(rows)} blocker(s)")


def sizes_of(status):
    return {r["name"]: r["size"] for r in status["functions"] if r["state"] != "local"}


def categories_of(rows, key=lambda b: b["category"]):
    """Group blockers by a key: {key: {mangled: blocker}}."""
    groups = collections.defaultdict(dict)
    for b in rows:
        groups[key(b)][b["mangled"]] = b
    return groups


def cmd_stats(args):
    document = load_blockers()
    sizes = sizes_of(load_status())
    rows = selected(document, args)
    total = {b["mangled"] for b in rows}
    print(f"{'category':<34}{'functions':>10}{'bytes':>10}")
    groups = categories_of(rows, key=lambda b: b["category"].split(":")[0])
    for kind, group in sorted(groups.items(), key=lambda kv: -sum(sizes.get(m, 0) for m in kv[1])):
        print(f"{kind:<34}{len(group):>10}{sum(sizes.get(m, 0) for m in group):>10,}")
    print(f"{'all (a function counted once)':<34}{len(total):>10}{sum(sizes.get(m, 0) for m in total):>10,}")
    zones = categories_of(rows, key=lambda b: b["zone"])
    print(f"\n{'zone':<34}{'functions':>10}{'bytes':>10}")
    for zone, group in sorted(zones.items(), key=lambda kv: -sum(sizes.get(m, 0) for m in kv[1])):
        print(f"{zone:<34}{len(group):>10}{sum(sizes.get(m, 0) for m in group):>10,}")
    print(f"\n{len(document['blockers'])} record(s), {len(document['retired'])} retired")


def cmd_retire(args):
    status = load_status()
    by_name = status_by_name(status)
    with locked(write=not args.dry_run) as document:
        if args.function:
            names = {r["name"] for text in args.function for r in resolve(text, status)}
            doomed = [b for b in document["blockers"] if b["mangled"] in names]
            if not doomed:
                die("no blocker recorded for " + ", ".join(args.function))
            reason = args.reason or "retired by hand"
        else:
            addresses = {r["address"] for r in status["functions"] if r["state"] == "match"}
            doomed = [b for b in document["blockers"] if b["mangled"] in by_name and by_name[b["mangled"]]["address"] in addresses]
            reason = "function matches"
        for b in doomed:
            print(f"retire {b['function']}  [{b['category']}]  ({reason})")
        if args.dry_run:
            return
        for b in doomed:
            document["blockers"].remove(b)
            document["retired"].append({**b, "retired": today(), "reason": reason})
        print(f"{len(doomed)} retired, {len(document['blockers'])} left (status of {status['generated']})")


def cmd_refresh(args):
    """The zone is stored when a record is made; status.py has since changed how it assigns zones."""
    status = load_status()
    by_name = status_by_name(status)
    with locked(write=not args.dry_run) as document:
        moved = collections.Counter()
        gone = 0
        for b in document["blockers"]:
            function = by_name.get(b["mangled"])
            if not function:
                gone += 1
            elif function["zone"] != b["zone"]:
                moved[(b["zone"], function["zone"])] += 1
                b["zone"] = function["zone"]
        for (old, new), count in sorted(moved.items(), key=lambda kv: -kv[1]):
            print(f"{count:>6}  {old} -> {new}")
        print(f"{sum(moved.values())} zone(s) changed, {gone} record(s) name a function no longer in work/status.json "
              f"(status of {status['generated']})")


# Migration of the free text skip lists ----------------------------------------------------------------------

HEADER = re.compile(r"^(?P<head>[^:]*\b(?:tried|pass)\b[^:]*):\s*(?P<rest>.*)$")
CUT_WORDS = re.compile(r"\b(?:needs?|needing|wait(?:s|ing)? on|whose|breaks)\b")
STOP = {"Already", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth"}
CTOR = ("ctor", "ctors", "constructor", "constructors")
DTOR = ("dtor", "dtors", "destructor", "destructors")
TOO_BROAD = 150

LAYOUT_WORDS = {"the", "a", "an", "block", "stack", "frame", "table", "padding", "member", "struct"}


def strip_templates(text):
    previous = None
    while previous != text:
        previous, text = text, re.sub(r"<[^<>]*>", "", text)
    return text


def classify(text):
    """The category of a skip-list note, by the words it uses; None when no word tells."""
    helper = re.search(r"\b(0x71[0-9a-f]{6,})\b", text)
    if helper and re.search(r"helper|unsymbol|no symbol", text):
        return f"missing-helper:{helper.group(1)}"
    container = re.search(r"\b((?:Fixed(?:Vector|Queue|List|Array|Stack)|Vector|FixStr|Map|IntrusivePtr|UniquePtr)(?:<[^>]*>)?)::(~?\w+)", text)
    if container and re.search(r"\b(?:inlin|never|out of line|layout|size|erase|insert|resize|back|find|operator|assert|load)", text):
        return f"container:{strip_templates(container.group(1))}::{container.group(2)}"
    missing = (re.search(r"\b([A-Z][\w:*]*)\s+(?:is\s+)?(?:missing|undeclared)\b", text)
               or re.search(r"\b(?:undeclared|missing)\s+(?:class\s+)?([A-Z][\w:*]*)", text))
    if missing:
        return f"missing-class:{missing.group(1)}"
    layout = re.search(r"\blayout of (?:the )?([A-Z][\w:<>]*)", text) or re.search(r"\b([A-Z][\w:<>]*) layout\b", text)
    if layout and layout.group(1).lower() not in LAYOUT_WORDS:
        return f"shared-type:{layout.group(1)}"
    if re.search(r"btl.*reserved|reserved.*btl", text):
        return "btl-reserved"
    if re.search(r"\bui\b.*reserved|user decision|reserved for contributors", text):
        return "ui-human"
    if re.search(r"re-?inlin|hand-inlin|\binlin(?:es|ed|ing)\b", text):
        return "reinline-forbidden"
    if re.search(r"uninit|junk[ -]|undefined this", text):
        return "uninit-forbidden"
    if re.search(r"vtable|key function", text):
        return "vtable-emission"
    if re.search(r"store[ -]?(?:merg|order|schedul)|merged .{0,20}stores?|(?:zero|u16|byte|float|halfword) stores?|stores? merg|stp vs|memset merge|zero-?store", text):
        return "store-merge"
    if re.search(r"\bregisters?\b|\bregs\b|callee-saved|\bx\d+/x\d+|\bw\d+ vs w\d+|\bswap\b", text):
        return "registers"
    if re.search(r"schedul|block (?:order|layout|placement)|test order|compare order|hoist|\border\b", text):
        return "scheduling"
    return None


def tokens(text):
    """The chains of identifiers of a text: [(identifier, template arguments or None)...]. An identifier directly
    followed by '*' keeps it (a wildcard: Bgm*)."""
    out, i, n = [], 0, len(text)
    ident = re.compile(r"[A-Za-z_~][A-Za-z0-9_]*\*?")
    while i < n:
        m = ident.match(text, i)
        if not m or (i > 0 and (text[i - 1].isalnum() or text[i - 1] == "_")):
            i += 1
            continue
        parts = []
        while True:
            i, args = m.end(), None
            if i < n and text[i] == "<":
                depth, j = 0, i
                while j < n:
                    depth += text[j] == "<"
                    depth -= text[j] == ">"
                    if depth == 0:
                        break
                    j += 1
                if j < n:
                    args, i = text[i + 1:j], j + 1
            parts.append((m.group(0), args))
            m2 = ident.match(text, i + 2) if text.startswith("::", i) else None
            if not m2:
                break
            m = m2
        out.append(parts)
    return out


def split_outside(text, separators):
    """Split at the characters of separators that sit outside parentheses and angle brackets."""
    parts, depth, start = [], 0, 0
    for i, ch in enumerate(text):
        if ch in "(<":
            depth += 1
        elif ch in ")>":
            depth = max(0, depth - 1)
        elif depth == 0 and ch in separators:
            parts.append(text[start:i])
            start = i + 1
    parts.append(text[start:])
    return [p.strip() for p in parts if p.strip()]


def without_parentheses(text):
    previous = None
    while previous != text:
        previous, text = text, re.sub(r"\([^()]*\)", " ", text)
    return text


def is_candidate(ident):
    return len(ident) >= 4 and re.search(r"[A-Z]", ident) is not None and ident not in STOP


class Index:
    """The game functions by class and by method name. A class is the last component of the scope of a name, so a
    namespace (a lower case scope) is one too."""

    def __init__(self, status):
        self.by_class = collections.defaultdict(list)
        self.by_method = collections.defaultdict(list)
        self.namespaces = set()
        for r in status["functions"]:
            if r["state"] == "local":
                continue
            scope = strip_templates(r["scope"])
            path = scope.split("::") if scope else []
            r = dict(r, cls=path[-1] if path else "", path=path)
            self.by_class[r["cls"]].append(r)
            self.by_method[r["method"]].append(r)
            self.namespaces.update(p for p in path if p == p.lower())

    @staticmethod
    def fit(records, args=None, ns=None):
        """The records whose scope has the template arguments and the namespace, or all when none has."""
        fitting = [r for r in records if args is None or all(word in r["scope"] for word in re.findall(r"\w+", args))]
        inside = [r for r in fitting if ns is None or ns in r["path"]]
        return inside or fitting if ns else fitting

    def methods_of(self, cls, name, args=None, ns=None):
        return self.fit([r for r in self.by_class.get(cls, []) if r["method"] == name], args, ns)

    def class_functions(self, cls, args=None, ns=None):
        return self.fit(self.by_class.get(cls, []), args, ns)

    def qualified(self, parts):
        """Functions named by a chain with '::': the last part is the method, the others its scope."""
        names = [p[0] for p in parts]
        scope = names[:-1]
        return self.fit([r for r in self.by_class.get(names[-2], [])
                         if r["method"] == names[-1] and r["path"][-len(scope):] == scope], parts[-2][1])

    def prefixed_classes(self, prefix, scope=()):
        """The classes whose name starts with prefix inside the scope's namespaces."""
        return [c for c, records in self.by_class.items()
                if c and c != c.lower() and c.startswith(prefix) and any(all(s in r["path"] for s in scope) for r in records)]


def subjects(index, text, state):
    """(functions, identifier-like words, how many of them resolved, too broad) a skip-list note is about. state
    carries the class and namespace last named from one note to the next: 'Class a, b, c' names three methods."""
    found, candidates, resolved, broad = [], 0, 0, False
    mentions = []  # [class, template arguments, named a method, namespace]

    def method_hit(records, mention=None):
        found.extend(records)
        if mention:
            mention[2] = True

    for parts in tokens(text):
        name, args = parts[-1]
        bare = name.rstrip("*")
        candidate = is_candidate(bare)
        candidates += candidate
        ns = state.get("ns")
        context = state.get("context")
        last = mentions[-1] if mentions and context and mentions[-1][0] == context[0] else None
        done = False
        if len(parts) == 1 and not name.endswith("*") and bare in index.namespaces and not candidate:
            state["ns"] = bare
            continue
        if len(parts) > 1:
            outer = parts[-2][0]
            if outer.endswith("*"):
                classes = index.prefixed_classes(outer[:-1], [p[0] for p in parts[:-2]])
                records = [r for c in classes for r in index.by_class[c] if r["method"] == bare]
                if records:
                    method_hit(records)
                    done = True
            else:
                records = index.qualified(parts)
                if records:
                    method_hit(records)
                    state["context"] = outer, parts[-2][1]
                    mentions.append([outer, parts[-2][1], True, None])
                    done = True
                elif bare in index.by_class:
                    mentions.append([bare, args, False, ns])
                    state["context"] = bare, args
                    done = True
        elif name.endswith("*"):
            classes = index.prefixed_classes(bare)
            for cls in classes:
                mentions.append([cls, None, False, ns])
            done = bool(classes)
        else:
            if context:
                cls, cargs = context
                lowered = name.lower()
                records = (index.methods_of(cls, cls, cargs, ns) if lowered in CTOR else
                           index.methods_of(cls, "~" + cls, cargs, ns) if lowered in DTOR else
                           index.methods_of(cls, name, cargs, ns))
                if records and name != cls:
                    method_hit(records, last)
                    done = True
            if not done and name in index.by_class and name != name.lower():
                mentions.append([name, args, False, ns])
                state["context"] = name, args
                done = True
            if not done and candidate and len(name) >= 5:
                records = index.fit(index.by_method.get(name, []), None, ns)
                classes = {r["cls"] for r in records}
                if records and len(classes) == 1:
                    method_hit(records)
                    state["context"] = records[0]["cls"], None
                    mentions.append([records[0]["cls"], None, True, None])
                    done = True
        resolved += done and candidate
    for cls, args, got, ns in mentions:
        if not got:
            records = index.class_functions(cls, args, ns)
            if len(records) > TOO_BROAD:
                broad = True
            else:
                found.extend(records)
    return found, candidates, resolved, broad


def note_parts(line):
    """The (subject text, reason text, header) of each separate note of a skip-list line."""
    line = line.strip()
    if line.startswith("- "):
        line = line[2:]
    header = HEADER.match(line)
    if header:
        return [(header.group("rest").rstrip("."), "", header.group("head"))]
    out = []
    for part in split_outside(line, ";"):
        if ":" in re.sub(r"::", "", part):
            subject, _, reason = re.sub(r"::", "\x00", part).partition(":")
            out.append((subject.replace("\x00", "::").strip(), reason.replace("\x00", "::").strip(), None))
        else:
            out.append((part, "", None))
    return out


def clip(text, width=600):
    return text if len(text) <= width else text[:width - 3] + "..."


def migrate_file(path, index, document, source, date, unmigrated, dry_run):
    """Records for each note of a skip list; returns the coverage counters."""
    cover = collections.Counter()
    with open(path) as f:
        lines = f.read().splitlines()
    for number, line in enumerate(lines, 1):
        if not line.strip():
            continue
        cover["lines"] += 1
        line_records = 0
        for subject, reason, head in note_parts(line):
            pieces = split_outside(subject, ",")
            analysed, state = [], {}
            for piece in pieces:
                head_text = CUT_WORDS.split(piece)[0]
                before = dict(state)
                functions, candidates, resolved, broad = subjects(index, without_parentheses(head_text), state)
                if not functions and not resolved and candidates:
                    # the functions may be named only in a parenthesis
                    state = before
                    functions2, c2, r2, broad2 = subjects(index, re.sub(r"[()]", " ", head_text), state)
                    if functions2:
                        functions, candidates, resolved, broad = functions2, c2, r2, broad2
                analysed.append((piece, functions, candidates, resolved, broad, classify(piece)))
            kinds = {a[5] for a in analysed if a[5]}
            reason_kind = classify(reason) if reason else None
            whole_kind = classify(subject + " " + reason)
            for piece, functions, candidates, resolved, broad, kind in analysed:
                cover["pieces"] += 1
                cover["candidates"] += candidates
                cover["resolved"] += resolved
                kind = kind or reason_kind or (whole_kind if len(kinds) <= 1 else None) or "other"
                if head:
                    detail = f"{head}: {piece}"
                else:
                    detail = f"{piece}: {reason}" if reason else piece
                detail = clip(detail)
                todo = one_per_address([r for r in functions if r["state"] != "match"])
                if broad:
                    cover["too_broad"] += 1
                if not todo:
                    cover["already_matching" if functions else "pieces_unresolved"] += 1
                    if not functions:
                        unmigrated.append(f"{os.path.basename(path)}:{number}: {piece}" + ("  [class too broad]" if broad else ""))
                    continue
                cover["pieces_resolved"] += 1
                line_records += 1
                for function in todo:
                    stored = store(document, record_for(function, kind, detail, source, date))
                    cover["records"] += stored
                    cover["by_category:" + kind.split(":")[0]] += stored
                    cover["functions:" + function["name"]] += 1
        cover["lines_with_records"] += bool(line_records)
    return cover


def cmd_import(args):
    status = load_status()
    index = Index(status)
    total = collections.Counter()
    unmigrated = []
    with locked(write=not args.dry_run) as document:
        for path in args.file:
            date = datetime.date.fromtimestamp(os.path.getmtime(path)).isoformat()
            source = os.path.splitext(os.path.basename(path))[0]
            cover = migrate_file(path, index, document, source, date, unmigrated, args.dry_run)
            total.update(cover)
            print(f"{os.path.basename(path)}: {cover['lines']} lines, {cover['lines_with_records']} with records, "
                  f"{cover['pieces_resolved']}/{cover['pieces']} notes resolved, {cover['records']} records")
    functions = sum(1 for k in total if k.startswith("functions:"))
    print(f"\nlines: {total['lines_with_records']}/{total['lines']} ({total['lines_with_records'] / max(1, total['lines']):.0%}) produced records")
    print(f"notes (comma separated items): {total['pieces_resolved']}/{total['pieces']} resolved to functions, "
          f"{total['already_matching']} name only functions that match now, {total['pieces_unresolved']} unresolved, "
          f"{total['too_broad']} naming a class too large to attribute")
    print(f"identifier-like words: {total['resolved']}/{total['candidates']} resolved ({total['resolved'] / max(1, total['candidates']):.0%})")
    print(f"records: {total['records']} for {functions} functions")
    print("by category: " + ", ".join(f"{k.split(':', 1)[1]} {v}" for k, v in sorted(total.items(), key=lambda kv: -kv[1]) if k.startswith("by_category:")))
    if not args.dry_run:
        with open(UNMIGRATED_PATH, "w") as f:
            f.write("\n".join(unmigrated) + "\n")
        print(f"{len(unmigrated)} unresolved notes written to {UNMIGRATED_PATH}")


def main():
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    sub = parser.add_subparsers(dest="command", required=True)
    add = sub.add_parser("add", help="record a blocker")
    add.add_argument("function", nargs="+")
    add.add_argument("-c", "--category", required=True)
    add.add_argument("-d", "--detail", required=True)
    add.add_argument("--source", help="run name, default: the current git branch")
    add.add_argument("--all", action="store_true", help="every overload of a name")
    add.set_defaults(run=cmd_add)
    lst = sub.add_parser("list", help="list blockers")
    lst.add_argument("--zone")
    lst.add_argument("--category", help="a category or its kind (container)")
    lst.add_argument("--function", help="substring of the function name")
    lst.add_argument("--source")
    lst.add_argument("--json", action="store_true")
    lst.set_defaults(run=cmd_list)
    stats = sub.add_parser("stats", help="count blockers by category and zone")
    stats.add_argument("--zone")
    stats.set_defaults(run=cmd_stats)
    retire = sub.add_parser("retire", help="drop the blockers of functions that match now (or of the given ones)")
    retire.add_argument("function", nargs="*")
    retire.add_argument("--reason")
    retire.add_argument("--dry-run", action="store_true")
    retire.set_defaults(run=cmd_retire)
    refresh = sub.add_parser("refresh", help="re-read the zone of every record from work/status.json")
    refresh.add_argument("--dry-run", action="store_true")
    refresh.set_defaults(run=cmd_refresh)
    imp = sub.add_parser("import-skip", help="migrate free text skip lists")
    imp.add_argument("file", nargs="+")
    imp.add_argument("--dry-run", action="store_true")
    imp.set_defaults(run=cmd_import)
    args = parser.parse_args()
    args.run(args)


if __name__ == "__main__":
    main()
