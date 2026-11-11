#!/usr/bin/env python3
"""Build work/status.json: one record per named game function, with its state and the zone it belongs to.

Usage (from the nix develop shell, the game binary is needed):
  python3 tools/status.py              write work/status.json and print the totals per zone
  python3 tools/status.py --quiet      write work/status.json only
  python3 tools/status.py --zone gf    also list the zone's functions that are not done yet, biggest first
  python3 tools/status.py --areas      also write progress/areas.json (see below)

It reuses what check.py computes (compiled objects, per-function comparison and their caches), so a run after
check costs a few seconds. The file holds game data (names, addresses, sizes, source paths): it stays in work/ and
is never committed. Only the aggregate numbers printed here may be published.

progress/areas.json is the one tracked output: the matching and total code bytes per zone, named after the
directories of our public src/ tree, for the area map of decompilati.onl. Zones with no matching code are folded
into one "Not started" area. It holds no function names, addresses or game-only directory names.

A record:
  name         mangled name of the game symbol (for a local function: the mangled name in our source)
  demangled    demangled name with its signature
  address      game address, "0x71..." (a hex string)
  size         size in bytes (a local function: four bytes per instruction)
  namespace    first component of the qualified name ("" for a global function); a class of the global namespace
               appears as its own name
  scope        qualified scope of the name with its template arguments ("gf::GfFoo"); method: the last component
  zone         top source directory: src/application/BF2/<dir> or src/libs/<lib> of the source file defining it; for
               a function not written yet, the directory of its game source file, else the zone most of the
               functions of its namespace have, else "unknown"
  src_file     our source file defining the function, or null
  game_file    the game's source file of the function as found in assertion strings of its code, or null
  state        match (bytes equal the game's), nonmatch (we define it, bytes differ), todo (not defined under src/),
               local (a function local to its source file that check finds through the callers that match: it has
               no game symbol; "matching" tells whether its bytes equal the game's)
"""
import argparse
import bisect
import collections
import datetime
import json
import os
import re
import sys
import tempfile

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import check  # noqa: E402  (needs XC2_SYSROOT from the nix develop shell)

ROOT = check.ROOT
STATUS_PATH = os.path.join(ROOT, "work", "status.json")
AREAS_PATH = os.path.join(ROOT, "progress", "areas.json")
STATES = ("match", "nonmatch", "todo", "local")
GAME_SOURCE = re.compile(rb"(?<=\x00)[\x20-\x7e]{4,400}\.(?:cpp|h|inl|c)\x00")
# The game's source tree: <prefix>/application/BF2/<dir>/... and <prefix>/libs/<lib>/...
GAME_LIBS = re.compile(r"/libs/([^/]+)/")
GAME_APP = re.compile(r"application/BF2/+([^/]+)/")
WRAPPERS = ("non-virtual thunk to ", "virtual thunk to ", "covariant return thunk to ")


def split_top(text, separator):
    """Split text on separator where no <...> or (...) is open."""
    parts, depth, start = [], 0, 0
    for i, ch in enumerate(text):
        if ch in "<(":
            depth += 1
        elif ch in ">)":
            depth -= 1
        elif depth == 0 and text.startswith(separator, i):
            parts.append(text[start:i])
            start = i + len(separator)
    parts.append(text[start:])
    return parts


def parse_name(demangled):
    """(scope, method) of a demangled function name: ('gf::GfFoo', 'bar') for 'gf::GfFoo::bar(int)'. Template
    arguments stay in the scope ('mm::Vector<mm::Vec3>'), not in the method."""
    text = demangled.replace("(anonymous namespace)", "anonymous")
    for prefix in WRAPPERS:
        if text.startswith(prefix):
            text = text[len(prefix):]
    operator = re.search(r"(?:^|::)operator\b", text)
    if operator:
        return text[:operator.start()], "operator"
    depth, end = 0, len(text)
    for i, ch in enumerate(text):
        if ch == "<":
            depth += 1
        elif ch == ">":
            depth -= 1
        elif ch == "(" and depth == 0:
            end = i
            break
    head = split_top(text[:end], " ")[-1]
    parts = [p for p in split_top(head, "::") if p]
    method = re.sub(r"<.*", "", parts[-1]) if parts else ""
    return "::".join(parts[:-1]), method


def name_fields(demangled):
    scope, method = parse_name(demangled)
    return {"namespace": re.sub(r"<.*", "", split_top(scope, "::")[0]), "scope": scope, "method": method}


def src_zone(path):
    """Zone of one of our source files: its directory under src/application/BF2 or src/libs."""
    parts = path.replace("\\", "/").split("/")
    if parts[:4] == ["src", "application", "BF2", "libs"] and len(parts) > 5:
        return parts[4].lower()
    if parts[:3] == ["src", "application", "BF2"] and len(parts) > 4:
        return parts[3].lower()
    if parts[:2] == ["src", "libs"] and len(parts) > 3:
        return parts[2].lower()
    return parts[1].lower() if len(parts) > 2 else "unknown"


def game_zone(path):
    """Zone of a game source path, in the same naming as src_zone."""
    path = path.replace("\\", "/")
    lib = GAME_LIBS.search(path)
    if lib:
        return lib.group(1).lower()
    app = GAME_APP.search(path)
    return app.group(1).lower() if app else "unknown"


def source_strings(game):
    """Address of every source path string in the game's data -> the path."""
    found = {}
    for section in game.image.sections:
        if section.addr and section.type != check.SHT_NOBITS and not section.flags & check.SHF_EXECINSTR:
            data = game.image.data[section.offset:section.offset + section.size]
            for match in GAME_SOURCE.finditer(data):
                found[section.addr + match.start()] = match.group(0)[:-1].decode("latin1")
    return found


def scan_game_files(game):
    """Sorted list of (code address, source path) for each source path string the code loads (adrp + add)."""
    strings = source_strings(game)
    text = next(s for s in game.image.sections if s.name == ".text")
    words = memoryview(game.image.data)[text.offset:text.offset + text.size].cast("I")
    hits, pages = [], {}
    for i, word in enumerate(words):
        if word & 0x9F000000 == 0x90000000:
            pc = text.addr + 4 * i
            pages[word & 31] = (check.get_field(word, check.PAGE, pc), i)
        elif word & 0xFFC00000 == 0x91000000:
            seen = pages.get((word >> 5) & 31)
            if seen and i - seen[1] <= 24:
                path = strings.get(seen[0] + ((word >> 10) & 0xFFF))
                if path:
                    hits.append((text.addr + 4 * i, path))
    return hits


def game_files(game):
    """Function address -> the game source path its code refers to most: a .cpp before a header, then the most used."""
    hits = check.cached(os.path.join(check.CACHE_DIR, "target.sources"), check.target_key(), lambda: scan_game_files(game))
    per_function = collections.defaultdict(collections.Counter)
    starts = [e for e in game.entries if e[2] in "TtWw"]
    keys = [e[0] for e in starts]
    for address, path in hits:
        i = bisect.bisect_right(keys, address) - 1
        if i >= 0 and address < starts[i][0] + starts[i][1]:
            per_function[starts[i][0]][path] += 1
    chosen = {}
    for address, counter in per_function.items():
        ranked = sorted(counter.items(), key=lambda kv: (not kv[0].endswith(".cpp"), -kv[1], kv[0]))
        chosen[address] = ranked[0][0]
    return chosen


def check_results(demangled):
    """(rows, errors): the (symbol, game address, match, instructions, local, source, defining source) of every
    function our sources define, as check computes them."""
    with tempfile.TemporaryDirectory() as tmp:
        objects, errors = check.compile_all(tmp)
    per_object = [(source, obj, [f for f in check.defined_functions(obj) if f in demangled]) for source, obj in objects]
    per_object = [entry for entry in per_object if entry[2]]
    rows = []
    results = check.check_objects([(obj, funcs) for _, obj, funcs in per_object])
    for (source, obj, _), found in zip(per_object, results):
        for symbol, address, ok, count, local, _ in found["rows"]:
            defining = source if local else check.defining_file(demangled[symbol], source)
            rows.append((symbol, address, ok, count, local, os.path.relpath(source, ROOT), os.path.relpath(defining, ROOT)))
    # The same rule as check: a function defined in several objects is a weak copy, it matches when one copy does.
    rows = check.merge_copies(rows, lambda row: row[0], lambda row: row[2], lambda row: row[4])
    return rows, errors


def build():
    game = check.target_game()
    demangled = check.cached(os.path.join(check.CACHE_DIR, "target.demangled"), check.target_key(),
                             lambda: check.demangle(sorted(check.target_symbols())))
    rows, errors = check_results(demangled)
    matched_addresses = {r[1] for r in rows if r[2] and not r[4]}
    defined = {}
    for symbol, address, ok, count, local, source, defining in rows:
        if not local:
            defined.setdefault(symbol, defining)
    files = game_files(game)

    records = []
    for name, spans in game.functions.items():
        if name not in demangled:
            continue
        for address, size in spans:
            if address in matched_addresses:
                state = "match"
            elif name in defined:
                state = "nonmatch"
            else:
                state = "todo"
            src = defined.get(name)
            records.append({
                "name": name, "demangled": demangled[name], "address": f"{address:#x}", "size": size,
                **name_fields(demangled[name]), "zone": None,
                "src_file": src, "game_file": files.get(address), "state": state,
            })
    local_names = check.demangle(sorted({r[0] for r in rows if r[4]})) if any(r[4] for r in rows) else {}
    for symbol, address, ok, count, local, source, defining in rows:
        if local:
            records.append({
                "name": symbol, "demangled": local_names[symbol], "address": f"{address:#x}", "size": 4 * count,
                **name_fields(local_names[symbol]), "zone": src_zone(source),
                "src_file": source, "game_file": files.get(address), "state": "local", "matching": ok,
            })

    # Zone: our source directory, else the game source directory, else what most functions of the namespace have.
    # A header of a shared library only shows that the code inlines it (its assertion strings sit in every caller):
    # it says nothing of the zone, so it counts only when the namespace gives no vote.
    def weak_hint(path):
        return bool(path) and not path.endswith(".cpp") and bool(GAME_LIBS.search(path.replace("\\", "/")))

    votes = collections.defaultdict(collections.Counter)
    for record in records:
        if record["src_file"]:
            record["zone"] = record["zone"] or src_zone(record["src_file"])
        elif record["game_file"] and not weak_hint(record["game_file"]):
            record["zone"] = game_zone(record["game_file"])
        if record["zone"] and record["zone"] != "unknown":
            votes[record["namespace"]][record["zone"]] += 1
    for record in records:
        if not record["zone"] or record["zone"] == "unknown":
            counter = votes.get(record["namespace"])
            if counter:
                record["zone"] = counter.most_common(1)[0][0]
            else:
                record["zone"] = game_zone(record["game_file"]) if record["game_file"] else "unknown"
    records.sort(key=lambda r: (int(r["address"], 16), r["name"]))
    return records, errors


def totals(records):
    """Functions and bytes per state, counted once per address (C1 and C2 constructors share a body)."""
    seen, out = set(), {state: [0, 0] for state in STATES[:3]}
    for record in records:
        if record["state"] == "local" or record["address"] in seen:
            continue
        seen.add(record["address"])
        out[record["state"]][0] += 1
        out[record["state"]][1] += record["size"]
    return out


def zone_table(records):
    zones = collections.defaultdict(lambda: {state: [0, 0] for state in STATES[:3]})
    seen = set()
    for record in records:
        if record["state"] == "local" or record["address"] in seen:
            continue
        seen.add(record["address"])
        cell = zones[record["zone"]][record["state"]]
        cell[0] += 1
        cell[1] += record["size"]
    return zones


def public_zones():
    """Lowercase zone name -> the name of our src/ directory that defines it."""
    names = {}
    for base in ("src/application/BF2", "src/application/BF2/libs", "src/libs"):
        path = os.path.join(ROOT, base)
        for entry in sorted(os.listdir(path)):
            if os.path.isdir(os.path.join(path, entry)) and not (base.endswith("BF2") and entry == "libs"):
                names[entry.lower()] = entry
    return names


def areas(records):
    """Code bytes per zone as decompilati.onl areas. The total of all areas is the total of the game's code."""
    public = public_zones()
    out, rest = [], {"total": 0, "matching": 0, "non_matching": 0}
    for name, cells in zone_table(records).items():
        matching = cells["match"][1]
        total = sum(c[1] for c in cells.values())
        if matching == 0:
            rest["total"] += total
        elif name in public:
            out.append({"name": public[name], "code": {"total": total, "matching": matching, "non_matching": 0}})
        else:
            raise ValueError(f"zone {name!r} has matching code but is not a directory of src/")
    out.sort(key=lambda a: (-a["code"]["matching"], a["name"]))
    if rest["total"]:
        out.append({"name": "Not started", "code": rest})
    return out


def print_summary(records, zone=None):
    table = zone_table(records)
    rows = []
    for name, cells in table.items():
        done = cells["match"][1]
        total = sum(c[1] for c in cells.values())
        rows.append((total - done, name, cells, done, total))
    rows.sort(reverse=True)
    print(f"{'zone':<14}{'match':>8}{'nonmatch':>9}{'todo':>8}{'bytes done':>13}{'bytes total':>13}{'%':>7}")
    for _, name, cells, done, total in rows:
        print(f"{name:<14}{cells['match'][0]:>8}{cells['nonmatch'][0]:>9}{cells['todo'][0]:>8}"
              f"{done:>13,}{total:>13,}{done / total:>7.1%}")
    overall = totals(records)
    funcs = sum(c[0] for c in overall.values())
    size = sum(c[1] for c in overall.values())
    print(f"total: {overall['match'][0]:,} / {funcs:,} functions ({overall['match'][0] / funcs:.3%}), "
          f"{overall['match'][1]:,} / {size:,} bytes of code ({overall['match'][1] / size:.3%}), "
          f"{overall['nonmatch'][0]} nonmatch, {sum(1 for r in records if r['state'] == 'local')} local")
    if zone:
        todo = sorted((r for r in records if r["zone"] == zone and r["state"] != "match" and r["state"] != "local"),
                      key=lambda r: -r["size"])
        for record in todo[:40]:
            print(f"  {record['state']:<8}{record['size']:>7}  {record['demangled']}")


def main():
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("--quiet", action="store_true")
    parser.add_argument("--areas", action="store_true", help="also write progress/areas.json")
    parser.add_argument("--zone")
    parser.add_argument("--output", default=STATUS_PATH)
    args = parser.parse_args()
    records, errors = build()
    document = {
        "generated": datetime.datetime.now().astimezone().isoformat(timespec="seconds"),
        "compile_errors": len(errors),
        "functions": records,
    }
    partial = f"{args.output}.{os.getpid()}"
    with open(partial, "w") as f:
        json.dump(document, f, separators=(",", ":"))
    os.replace(partial, args.output)
    if args.areas:
        os.makedirs(os.path.dirname(AREAS_PATH), exist_ok=True)
        with open(AREAS_PATH, "w") as f:
            json.dump(areas(records), f, indent=2)
            f.write("\n")
    if errors:
        check.print_compile_errors(errors[:3])
        print(f"status: {len(errors)} files failed to compile, their functions count as todo", file=sys.stderr)
    if not args.quiet:
        print_summary(records, args.zone)


if __name__ == "__main__":
    main()
