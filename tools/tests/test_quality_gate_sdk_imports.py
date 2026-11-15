"""The destructor check of the quality gate does not flag a destructor declared under include/nn or include/nvn
(imports from the Nintendo SDK, defined there and called through the import table) and still flags any other.

python3 -m unittest discover -s tools/tests"""
import os
import subprocess
import sys
import tempfile
import unittest

TOOLS = os.path.join(os.path.dirname(os.path.abspath(__file__)), "..")
UNDEFINED = "has no definition"


def git(root, *args):
    return subprocess.run(["git", "-C", root, *args], check=True, capture_output=True, text=True).stdout


class SdkImportDestructorTest(unittest.TestCase):
    def setUp(self):
        self.tmp = tempfile.TemporaryDirectory()
        self.addCleanup(self.tmp.cleanup)
        self.root = self.tmp.name
        git(self.root, "init", "-q", "-b", "main")
        git(self.root, "config", "user.email", "ci@example.com")
        git(self.root, "config", "user.name", "ci")
        self.write("src/base.cpp", "Base::~Base() {}\n")
        git(self.root, "add", "-A")
        git(self.root, "commit", "-q", "-m", "base")

    def write(self, path, content):
        full = os.path.join(self.root, path)
        os.makedirs(os.path.dirname(full), exist_ok=True)
        with open(full, "w") as f:
            f.write(content)

    def gate(self, header, name):
        """Declare `~name();` in a class of `header` and return the output of the gate on that change."""
        self.write(header, f"class {name} {{\npublic:\n    ~{name}();\n}};\n")
        git(self.root, "add", "-A")
        git(self.root, "commit", "-q", "-m", "change")
        proc = subprocess.run([sys.executable, "-I", os.path.join(TOOLS, "quality_gate.py"), "HEAD~1", "HEAD"],
                              cwd=self.root, capture_output=True, text=True)
        self.assertEqual(proc.stderr, "")
        self.assertIn("problem(s)", proc.stdout)
        return proc.stdout

    def test_a_destructor_declared_under_include_nn_is_not_flagged(self):
        out = self.gate("include/nn/hid.h", "VibrationPlayer")
        self.assertNotIn(UNDEFINED, out)
        self.assertIn("0 problem(s)", out)

    def test_a_destructor_declared_under_include_nvn_is_not_flagged(self):
        out = self.gate("include/nvn/nvn.h", "Texture")
        self.assertNotIn(UNDEFINED, out)
        self.assertIn("0 problem(s)", out)

    def test_a_destructor_declared_elsewhere_is_still_flagged(self):
        out = self.gate("include/gf/gf_thing.h", "GfThing")
        self.assertIn("include/gf/gf_thing.h:3: ~GfThing() has no definition", out)
        self.assertIn("1 problem(s)", out)

    def test_a_directory_that_only_starts_like_nn_is_still_flagged(self):
        out = self.gate("include/nnx/thing.h", "Thing")
        self.assertIn("~Thing() has no definition", out)


if __name__ == "__main__":
    unittest.main()
