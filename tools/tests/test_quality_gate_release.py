"""The duplicate check of the quality gate ignores the release idiom `if (p != nullptr) { delete p; p = nullptr; }`
and judges every other statement as before.

python3 -m unittest discover -s tools/tests"""
import os
import subprocess
import sys
import tempfile
import unittest

TOOLS = os.path.join(os.path.dirname(os.path.abspath(__file__)), "..")
DUPLICATES = "functions share a block of statements"

RELEASE = ["if (unknown70 != nullptr) {", "  delete unknown70;", "  unknown70 = nullptr;", "}"]
# Four statements, each longer than the gate's triviality limit, so that three copies are reported.
BLOCK = [
    "m_state = computeState(m_owner, 1);",
    "m_result = combineResults(m_state, m_extra);",
    "notifyOwner(m_owner, m_result);",
    "m_flags = finishFlags(m_result, m_state);",
]


def git(root, *args):
    return subprocess.run(["git", "-C", root, *args], check=True, capture_output=True, text=True).stdout


class ReleaseIdiomTest(unittest.TestCase):
    def setUp(self):
        self.tmp = tempfile.TemporaryDirectory()
        self.addCleanup(self.tmp.cleanup)
        self.root = self.tmp.name
        git(self.root, "init", "-q", "-b", "main")
        git(self.root, "config", "user.email", "ci@example.com")
        git(self.root, "config", "user.name", "ci")
        # the gate greps the tree for destructor definitions and fails when there is none
        self.write("src/base.cpp", "Base::~Base() {}\n")
        git(self.root, "add", "-A")
        git(self.root, "commit", "-q", "-m", "base")
        self.base = git(self.root, "rev-parse", "HEAD").strip()

    def write(self, path, content):
        full = os.path.join(self.root, path)
        os.makedirs(os.path.dirname(full), exist_ok=True)
        with open(full, "w") as f:
            f.write(content)

    def gate(self, bodies):
        """Add one function per body (a list of lines) and return the output of the gate on that change."""
        text = "".join(f"void Class{i}::method() {{\n" + "".join(f"  {line}\n" for line in body) + "}\n\n"
                       for i, body in enumerate(bodies))
        self.write("src/new.cpp", text)
        git(self.root, "add", "-A")
        git(self.root, "commit", "-q", "-m", "change")
        proc = subprocess.run([sys.executable, "-I", os.path.join(TOOLS, "quality_gate.py"), "HEAD~1", "HEAD"],
                              cwd=self.root, capture_output=True, text=True)
        self.assertEqual(proc.stderr, "")
        self.assertIn("problem(s)", proc.stdout)
        return proc.stdout

    def test_the_idiom_repeated_in_six_functions_is_not_a_duplicate(self):
        out = self.gate([RELEASE] * 6)
        self.assertNotIn(DUPLICATES, out)
        self.assertIn("0 problem(s)", out)

    def test_the_forms_of_the_idiom_are_not_duplicates(self):
        forms = [
            ["if (unknown70 != nullptr) {", "  delete[] unknown70;", "  unknown70 = nullptr;", "}"],
            ["if (unknown70 != 0) {", "  delete unknown70;", "  unknown70 = nullptr;", "}"],
            ["if (unknown70) {", "  delete unknown70;", "  unknown70 = nullptr;", "}"],
            ["if (unknown70 != nullptr) {", "  delete unknown70;", "}", "unknown70 = nullptr;"],
            ["if (this->unknown70) { delete this->unknown70; this->unknown70 = nullptr; }"],
        ]
        for form in forms:
            with self.subTest(form=form):
                self.assertNotIn(DUPLICATES, self.gate_fresh([form] * 6))

    def gate_fresh(self, bodies):
        git(self.root, "reset", "-q", "--hard", self.base)
        return self.gate(bodies)

    def test_a_block_that_only_looks_like_the_idiom_is_still_reported(self):
        others = [
            ["if (unknown70 != nullptr) {", "  delete unknown71;", "  unknown71 = nullptr;", "}"],  # another pointer
            ["if (unknown70 != nullptr) {", "  delete unknown70;", "  unknown70 = unknown72;", "}"],  # not nulled
            ["if (unknown70 != nullptr) {", "  delete unknown70;", "  unknown70 = nullptr;", "  m_count = 0;", "}"],  # more
        ]
        for body in others:
            with self.subTest(body=body):
                self.assertIn(DUPLICATES, self.gate_fresh([body] * 6))

    def test_a_genuinely_duplicated_block_is_still_reported(self):
        out = self.gate([BLOCK] * 3)
        self.assertIn("3 functions share a block of statements", out)
        self.assertIn("1 problem(s)", out)

    def test_other_statements_next_to_the_idiom_are_judged_as_before(self):
        # The four statements repeated in three functions are reported, and the idiom is not part of the block.
        out = self.gate([RELEASE + BLOCK] * 3)
        self.assertIn("3 functions share a block of statements", out)
        self.assertNotIn("delete", out)
        self.assertNotIn("nullptr", out)

    def test_the_idiom_does_not_complete_a_block_of_other_statements(self):
        # Three other statements in three functions are not reported on their own (4 in 3 functions, 3 in 5 are);
        # the idiom before them must not make them a run of four.
        out = self.gate([RELEASE + BLOCK[:3]] * 3)
        self.assertNotIn(DUPLICATES, out)
        out = self.gate_fresh([BLOCK[:3] + RELEASE] * 3)
        self.assertNotIn(DUPLICATES, out)

    def test_three_other_statements_in_five_functions_are_still_reported_without_the_idiom(self):
        out = self.gate([RELEASE + BLOCK[:3]] * 5)
        self.assertIn("5 functions share a block of statements", out)
        self.assertNotIn("delete", out)

    def test_the_idiom_between_two_halves_of_a_block_splits_it(self):
        out = self.gate([BLOCK[:2] + RELEASE + BLOCK[2:]] * 3)
        self.assertNotIn(DUPLICATES, out)


if __name__ == "__main__":
    unittest.main()
