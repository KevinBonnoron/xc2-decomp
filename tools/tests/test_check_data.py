"""The controls of check that report what the function check does not compare: global data against the game's, writable
local data placed on a game symbol or over another object, functions defined with global binding by several objects,
and local functions matched over a prefix of the game's code.

The objects and the game are built here byte by byte, so the tests need neither the compiler nor the game.

python3 -m unittest discover -s tools/tests"""
import contextlib
import io
import os
import struct
import sys
import tempfile
import unittest
from types import SimpleNamespace
from unittest import mock

TOOLS = os.path.join(os.path.dirname(os.path.abspath(__file__)), "..")
# check.py wants the sysroot of the dev shell; the tests never compile.
os.environ.setdefault("XC2_SYSROOT", tempfile.gettempdir())
sys.path.insert(0, TOOLS)
import check  # noqa: E402

SHT_PROGBITS, SHT_STRTAB, SHT_RELA = 1, 3, 4
WRITE_ALLOC, EXEC_ALLOC = 0x3, 0x6
STB_WEAK = 2
STT_OBJECT, STT_FUNC = 1, 2
R_ABS64 = 257
R_ADR_PREL_PG_HI21, R_ADD_ABS_LO12_NC = 275, 277

MOV_W0_1, MOV_W0_2, RET, NOP = 0x52800020, 0x52800040, 0xD65F03C0, 0xD503201F
ADRP_X0, ADD_X0 = 0x90000000, 0x91000000
ADRP_X0_TWO_PAGES = 0xD0000000  # adrp x0, <the page two pages after the one of the instruction>

TEXT, DATA, BSS = 0x1000, 0x2000, 0x3000


def words(*values):
    return struct.pack(f"<{len(values)}I", *values)


def build_object(sections, symbols, relocations=()):
    """A relocatable AArch64 object. sections: (name, type, flags, content or size of a NOBITS section); symbols:
    (name, type, bind, section name or None, value, size); relocations: (section, offset, type, symbol, addend)."""
    names = [section[0] for section in sections]
    section_index = {name: i + 1 for i, name in enumerate(names)}
    symbol_index = {symbol[0]: i + 1 for i, symbol in enumerate(symbols)}
    strtab = b"\0"
    symtab = bytes(24)
    for name, kind, bind, section, value, size in symbols:
        symtab += struct.pack("<IBBHQQ", len(strtab), bind << 4 | kind, 0, section_index[section] if section else 0,
                              value, size)
        strtab += name.encode() + b"\0"
    headers = [("", 0, 0, 0, b"", 0, 0, 0, 0)]  # name, type, flags, size, content, link, info, align, entsize
    for name, kind, flags, content in sections:
        if kind == check.SHT_NOBITS:
            headers.append((name, kind, flags, content, b"", 0, 0, 16, 0))
        else:
            headers.append((name, kind, flags, len(content), content, 0, 0, 16, 0))
    symtab_at = len(headers) + len({r[0] for r in relocations})
    for section in dict.fromkeys(r[0] for r in relocations):
        rela = b"".join(struct.pack("<QQq", offset, symbol_index[symbol] << 32 | rtype, addend)
                        for target, offset, rtype, symbol, addend in relocations if target == section)
        headers.append((".rela" + section, SHT_RELA, 0x40, len(rela), rela, symtab_at, section_index[section], 8, 24))
    headers.append((".symtab", check.SHT_SYMTAB, 0, len(symtab), symtab, symtab_at + 1, 0, 8, 24))
    headers.append((".strtab", SHT_STRTAB, 0, len(strtab), strtab, 0, 0, 1, 0))
    shstrtab = b"\0"
    name_at = {}
    for header in headers + [(".shstrtab",)]:
        name_at[header[0]] = len(shstrtab)
        shstrtab += header[0].encode() + b"\0"
    headers.append((".shstrtab", SHT_STRTAB, 0, len(shstrtab), shstrtab, 0, 0, 1, 0))
    blob, table = bytes(64), b""
    for name, kind, flags, size, content, link, info, align, entsize in headers:
        offset = len(blob)
        blob += content
        table += struct.pack("<IIQQQQIIQQ", name_at[name], kind, flags, 0, offset, size, link, info, align, entsize)
    header = struct.pack("<16sHHIQQQIHHHHHH", b"\x7fELF\x02\x01\x01" + bytes(9), 1, 183, 1, 0, 0, len(blob), 0, 64, 0, 0,
                         64, len(headers), len(headers) - 1)
    return header + blob[64:] + table


def make_game(sections, symbols, calls=()):
    """A Game with the given (name, type, flags, address, content or size of a NOBITS section) sections and
    (address, size, kind, name) symbols."""
    blob, found = b"", [check.Section("", 0, 0, 0, 0, 0, 0, 0, 0, 0)]
    for name, kind, flags, address, content in sections:
        if kind == check.SHT_NOBITS:
            found.append(check.Section(name, kind, flags, address, len(blob), content, 0, 0, 16, 0))
        else:
            found.append(check.Section(name, kind, flags, address, len(blob), len(content), 0, 0, 16, 0))
            blob += content
    game = check.Game.__new__(check.Game)
    game.image = SimpleNamespace(sections=found, data=blob)
    game.index_symbols(list(symbols))
    game.calls = list(calls)
    game.unnamed = {}
    return game


class ObjectTest(unittest.TestCase):
    def setUp(self):
        self.tmp = tempfile.TemporaryDirectory()
        self.addCleanup(self.tmp.cleanup)
        self.count = 0

    def object(self, sections, symbols, relocations=()):
        self.count += 1
        path = os.path.join(self.tmp.name, f"{self.count}.o")
        with open(path, "wb") as f:
            f.write(build_object(sections, symbols, relocations))
        obj = check.ObjectFile(path)
        obj.path = path
        return obj


class GlobalDataTest(ObjectTest):
    """A table of one pointer and one value, defined in the object and in the game."""

    def setUp(self):
        super().setUp()
        self.game = make_game(
            [(".text", SHT_PROGBITS, EXEC_ALLOC, TEXT, words(MOV_W0_1, RET, MOV_W0_2, RET)),
             (".data", SHT_PROGBITS, WRITE_ALLOC, DATA, struct.pack("<QQ", TEXT, 5))],
            [(TEXT, 8, "T", "_Z3foov"), (TEXT + 8, 8, "T", "_Z3barv"), (DATA, 16, "D", "_ZN2gf5tableE")])

    def table(self, value=5, target="_Z3foov", size=16, bind=1):
        return self.object(
            [(".text", SHT_PROGBITS, EXEC_ALLOC, words(MOV_W0_1, RET, MOV_W0_2, RET)),
             (".data.rel.ro", SHT_PROGBITS, WRITE_ALLOC, struct.pack("<QQ", 0, value))],
            [("_Z3foov", STT_FUNC, 1, ".text", 0, 8), ("_Z3barv", STT_FUNC, 1, ".text", 8, 8),
             ("_ZN2gf5tableE", STT_OBJECT, bind, ".data.rel.ro", 0, size)],
            [(".data.rel.ro", 0, R_ABS64, target, 0)])

    def test_a_correct_table_has_no_problem(self):
        self.assertEqual(check.global_data_problems(self.game, self.table()), [])

    def test_a_wrong_value_is_reported(self):
        (name, problem), = check.global_data_problems(self.game, self.table(value=6))
        self.assertEqual(name, "_ZN2gf5tableE")
        self.assertIn("at +0x8 (game 0x2008) holds 0600000000000000, the game's 0500000000000000", problem)

    def test_a_pointer_to_the_wrong_symbol_is_reported(self):
        (name, problem), = check.global_data_problems(self.game, self.table(target="_Z3barv"))
        self.assertEqual(name, "_ZN2gf5tableE")
        self.assertIn("at +0x0 (game 0x2000) points to _Z3barv, the game's _Z3foov", problem)

    def test_a_pointer_to_a_symbol_the_game_lacks_is_reported(self):
        obj = self.object(
            [(".data.rel.ro", SHT_PROGBITS, WRITE_ALLOC, bytes(16))],
            [("_ZN2gf5tableE", STT_OBJECT, 1, ".data.rel.ro", 0, 16), ("_Z7unknownv", 0, 1, None, 0, 0)],
            [(".data.rel.ro", 0, R_ABS64, "_Z7unknownv", 0)])
        (_, problem), = check.global_data_problems(self.game, obj)
        self.assertIn("refers to _Z7unknownv, which the game has no symbol for", problem)

    def test_a_different_size_is_reported(self):
        (_, problem), = check.global_data_problems(self.game, self.table(size=24))
        self.assertEqual(problem, "its size is 24, the game's 16")

    def test_a_weak_table_the_game_has_is_compared_too(self):
        (name, _), = check.global_data_problems(self.game, self.table(value=6, bind=STB_WEAK))
        self.assertEqual(name, "_ZN2gf5tableE")

    def test_data_the_game_has_no_symbol_for_is_left_to_the_function_check(self):
        obj = self.object([(".data", SHT_PROGBITS, WRITE_ALLOC, bytes(8))],
                          [("_ZN2gf5otherE", STT_OBJECT, 1, ".data", 0, 8), ("_ZL5local", STT_OBJECT, 0, ".data", 0, 8)])
        self.assertEqual(check.global_data_problems(self.game, obj), [])

    def test_a_pointer_to_a_slot_of_the_game_imports_is_the_same_import(self):
        game = make_game([(".data", SHT_PROGBITS, WRITE_ALLOC, DATA, bytes(16))],
                         [(DATA, 16, "D", "_ZN2gf5tableE"), (DATA + 8, 8, "D", "__got___cxa_pure_virtual")])
        obj = self.object(
            [(".data.rel.ro", SHT_PROGBITS, WRITE_ALLOC, bytes(16))],
            [("_ZN2gf5tableE", STT_OBJECT, 1, ".data.rel.ro", 0, 16), ("__cxa_pure_virtual", 0, 1, None, 0, 0)],
            [(".data.rel.ro", 8, R_ABS64, "__cxa_pure_virtual", 0)])
        self.assertEqual(check.global_data_problems(game, obj), [])
        wrong = self.object(
            [(".data.rel.ro", SHT_PROGBITS, WRITE_ALLOC, bytes(16))],
            [("_ZN2gf5tableE", STT_OBJECT, 1, ".data.rel.ro", 0, 16), ("__cxa_pure_virtual", 0, 1, None, 0, 0)],
            [(".data.rel.ro", 0, R_ABS64, "__cxa_pure_virtual", 0)])
        self.assertEqual(len(check.global_data_problems(game, wrong)), 1)

    def test_check_object_reports_the_table_with_the_rows(self):
        obj = self.table(value=6)
        with mock.patch.object(check, "target_game", lambda: self.game):
            result = check.check_object((obj.path, ["_Z3foov"]))
        self.assertEqual([row[:5] for row in result["rows"]], [("_Z3foov", TEXT, True, 2, False)])
        self.assertEqual([name for name, _ in result["data"]], ["_ZN2gf5tableE"])
        self.assertEqual(result["strong"], ["_Z3barv", "_Z3foov"])


class DuplicateDefinitionTest(ObjectTest):
    def defining(self, bind):
        return self.object([(".text", SHT_PROGBITS, EXEC_ALLOC, words(MOV_W0_1, RET))],
                           [("_Z3foov", STT_FUNC, bind, ".text", 0, 8)])

    def duplicates(self, bind):
        return check.strong_duplicates([(f"{name}.cpp", self.defining(bind).strong_functions()) for name in "ab"])

    def test_a_global_function_defined_twice_is_reported(self):
        self.assertEqual(self.duplicates(1), {"_Z3foov": ["a.cpp", "b.cpp"]})

    def test_a_weak_function_defined_twice_is_not(self):
        self.assertEqual(self.duplicates(STB_WEAK), {})

    def test_a_global_function_defined_once_is_not(self):
        self.assertEqual(check.strong_duplicates([("a.cpp", ["_Z3foov"]), ("b.cpp", ["_Z3barv"])]), {})

    def test_a_local_function_is_not_a_global_definition(self):
        self.assertEqual(self.duplicates(0), {})

    def test_copies_are_merged_as_before(self):
        rows = [("f", True, False), ("f", False, False), ("g", False, False), ("g", False, False), ("h", False, True),
                ("h", True, False)]
        kept = check.merge_copies(rows, lambda r: r[0], lambda r: r[1], lambda r: r[2])
        self.assertEqual(kept, [("f", True, False), ("g", False, False), ("g", False, False), ("h", False, True),
                                ("h", True, False)])


class LocalFunctionTest(ObjectTest):
    """A local function of three instructions that uses a local variable, at an address the game has no symbol for."""

    def local_function(self):
        return self.object(
            [(".text", SHT_PROGBITS, EXEC_ALLOC, words(ADRP_X0, ADD_X0, RET)), (".bss", check.SHT_NOBITS, WRITE_ALLOC, 8)],
            [("_ZL5localv", STT_FUNC, 0, ".text", 0, 12), ("_ZL5count", STT_OBJECT, 0, ".bss", 0, 8)],
            [(".text", 0, R_ADR_PREL_PG_HI21, "_ZL5count", 0), (".text", 4, R_ADD_ABS_LO12_NC, "_ZL5count", 0)])

    def game(self, fourth, bss_symbols=()):
        code = words(MOV_W0_1, RET, MOV_W0_2, RET, ADRP_X0_TWO_PAGES, ADD_X0, RET, fourth)
        return make_game([(".text", SHT_PROGBITS, EXEC_ALLOC, TEXT, code), (".bss", check.SHT_NOBITS, WRITE_ALLOC, BSS, 0x100)],
                         [(TEXT, 8, "T", "_Z3foov"), (TEXT + 8, 8, "T", "_Z3barv"), (TEXT + 0x20, 4, "T", "_Z3bazv"),
                          *bss_symbols])

    def test_a_local_function_shorter_than_the_game_code_is_a_prefix_match(self):
        verdict = check.verify(self.game(MOV_W0_2), self.local_function(), "_ZL5localv", TEXT + 0x10)
        self.assertTrue(verdict.ok)
        self.assertEqual((verdict.count, verdict.game_count), (3, 4))

    def test_trailing_padding_of_the_game_is_not_code(self):
        for padding in (NOP, 0):
            verdict = check.verify(self.game(padding), self.local_function(), "_ZL5localv", TEXT + 0x10)
            self.assertTrue(verdict.ok)
            self.assertEqual((verdict.count, verdict.game_count), (3, 3), hex(padding))

    def test_a_named_function_is_never_a_prefix(self):
        game = self.game(MOV_W0_2, [(TEXT + 0x10, 12, "T", "_ZL5localv")])
        verdict = check.verify(game, self.local_function(), "_ZL5localv", TEXT + 0x10, 12)
        self.assertEqual((verdict.count, verdict.game_count), (3, 3))

    def test_the_writable_data_a_function_reaches_is_mapped_to_a_game_address(self):
        obj = self.local_function()
        verdict = check.verify(self.game(NOP), obj, "_ZL5localv", TEXT + 0x10)
        self.assertTrue(verdict.ok)
        bss = next(i for i, section in enumerate(obj.sections) if section.name == ".bss")
        self.assertEqual(verdict.writable, {(bss, 0): BSS})

    def writable(self, game):
        obj = self.local_function()
        verdict = check.verify(game, obj, "_ZL5localv", TEXT + 0x10)
        mapped = {key: (address, "_ZL5localv") for key, address in verdict.writable.items()}
        return check.writable_objects(obj, mapped)

    def test_local_data_the_game_does_not_name_is_fine(self):
        self.assertEqual(check.writable_problems(self.game(NOP), self.writable(self.game(NOP))), [])

    def test_local_data_placed_on_a_game_symbol_is_reported(self):
        game = self.game(NOP, [(BSS, 8, "B", "_ZN2gf7counterE")])
        (name, problem), = check.writable_problems(game, self.writable(game))
        self.assertEqual(name, "_ZL5count")
        self.assertIn("at 0x3000 in the game, which is _ZN2gf7counterE", problem)

    def test_local_data_placed_over_the_start_of_a_game_symbol_is_reported(self):
        game = self.game(NOP, [(BSS + 4, 8, "B", "_ZN2gf7counterE")])
        self.assertEqual(len(check.writable_problems(game, self.writable(game))), 1)

    def test_a_game_symbol_ending_before_the_data_is_not_in_the_way(self):
        game = self.game(NOP, [(BSS - 8, 8, "B", "_ZN2gf7counterE")])
        self.assertEqual(check.writable_problems(game, self.writable(game)), [])


class OverlappingObjectTest(unittest.TestCase):
    def test_two_objects_at_one_address_are_reported(self):
        found = check.overlapping_objects([("a", BSS, 8, "x.cpp", False), ("b", BSS, 4, "y.cpp", False)])
        self.assertEqual([(first[0], second[0]) for first, second in found], [("b", "a")])

    def test_objects_that_only_touch_are_not(self):
        self.assertEqual(check.overlapping_objects([("a", BSS, 8, "x.cpp", False), ("b", BSS + 8, 8, "y.cpp", False)]), [])

    def test_an_object_inside_a_larger_one_is_reported(self):
        found = check.overlapping_objects([("big", BSS, 32, "x.cpp", False), ("a", BSS + 8, 4, "y.cpp", False),
                                           ("b", BSS + 16, 4, "z.cpp", False)])
        self.assertEqual([(first[0], second[0]) for first, second in found], [("big", "a"), ("big", "b")])

    def test_a_shared_object_seen_from_two_sources_is_one_object(self):
        shared = [("guard", BSS, 8, "x.cpp", True), ("guard", BSS, 8, "y.cpp", True)]
        self.assertEqual(check.overlapping_objects(shared), [])
        distinct = [("guard", BSS, 8, "x.cpp", False), ("guard", BSS, 8, "y.cpp", False)]
        self.assertEqual(len(check.overlapping_objects(distinct)), 1)


class ReportTest(unittest.TestCase):
    def test_the_report_gathers_the_three_controls_over_every_object(self):
        per_object = [(os.path.join(check.ROOT, "src", f"{name}.cpp"), None, []) for name in "ab"]
        results = [{"rows": [], "strong": ["_Z3foov"], "data": [("table", "its size is 24, the game's 16")],
                    "locals": [("count", BSS, 8, False)]},
                   {"rows": [], "strong": ["_Z3foov"], "data": [("table", "its size is 24, the game's 16")],
                    "locals": [("other", BSS, 8, False)]}]
        report = check.data_report(per_object, results, [("_ZL5localv", TEXT, 3, 4, "src/a.cpp")])
        self.assertEqual([name for name, _, _ in report.problems], ["table", "count"])
        self.assertEqual(report.duplicates, {"_Z3foov": [os.path.join("src", "a.cpp"), os.path.join("src", "b.cpp")]})
        self.assertEqual(check.data_summary(report), "data: 2 problems, duplicate definitions: 1, local prefix matches: 1")

    def test_the_report_is_printed_before_its_summary(self):
        report = SimpleNamespace(problems=[("table", "its size is 24, the game's 16", "src/a.cpp")],
                                 duplicates={"foo": ["src/a.cpp", "src/b.cpp"]},
                                 prefixes=[("local", TEXT, 3, 4, "src/c.cpp")])
        out = io.StringIO()
        with mock.patch.object(check, "color", False), contextlib.redirect_stdout(out):
            check.print_data_report(report)
        self.assertEqual(out.getvalue().splitlines()[1:], [
            "Not compared by the function check (reported only, --strict-data makes them fail):",
            "DATA       table  its size is 24, the game's 16  src/a.cpp",
            "DUPLICATE  foo  defined by src/a.cpp, src/b.cpp",
            "PREFIX     local (local, 0x1000)  3 of the game's 4 instructions  src/c.cpp",
            "",
            "data: 1 problems, duplicate definitions: 1, local prefix matches: 1"])

    def test_a_clean_report_is_one_line(self):
        out = io.StringIO()
        with mock.patch.object(check, "color", False), contextlib.redirect_stdout(out):
            check.print_data_report(SimpleNamespace(problems=[], duplicates={}, prefixes=[]))
        self.assertEqual(out.getvalue().strip(), "data: 0 problems, duplicate definitions: 0, local prefix matches: 0")


if __name__ == "__main__":
    unittest.main()
