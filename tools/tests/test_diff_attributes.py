"""A .gitattributes file of the change must not hide added lines from the quality gate or from tidy.

python3 -m unittest discover -s tools/tests"""
import os
import subprocess
import sys
import tempfile
import unittest

TOOLS = os.path.join(os.path.dirname(os.path.abspath(__file__)), "..")
# tidy imports check.py, which wants the sysroot of the dev shell; the tests never compile.
os.environ.setdefault("XC2_SYSROOT", tempfile.gettempdir())
sys.path.insert(0, TOOLS)
import tidy  # noqa: E402


def git(root, *args):
    return subprocess.run(["git", "-C", root, *args], check=True, capture_output=True, text=True).stdout


class DiffAttributesTest(unittest.TestCase):
    def setUp(self):
        self.tmp = tempfile.TemporaryDirectory()
        self.addCleanup(self.tmp.cleanup)
        self.root = self.tmp.name
        git(self.root, "init", "-q", "-b", "main")
        git(self.root, "config", "user.email", "ci@example.com")
        git(self.root, "config", "user.name", "ci")
        self.write("src/a.cpp", "int a;\n")
        self.commit("base")

    def write(self, path, content):
        full = os.path.join(self.root, path)
        os.makedirs(os.path.dirname(full), exist_ok=True)
        with open(full, "w") as f:
            f.write(content)

    def commit(self, message):
        git(self.root, "add", "-A")
        git(self.root, "commit", "-q", "-m", message)

    def add_hidden_code(self):
        self.write(".gitattributes", "src/** -diff\n")
        self.write("src/new.cpp", "void f() {\n  goto end;\nend:;\n}\n")
        self.commit("change")

    def test_quality_gate_sees_added_lines_of_a_file_marked_binary(self):
        self.add_hidden_code()
        proc = subprocess.run([sys.executable, "-I", os.path.join(TOOLS, "quality_gate.py"), "HEAD~1", "HEAD"],
                              cwd=self.root, capture_output=True, text=True)
        self.assertEqual(proc.returncode, 1, proc.stdout + proc.stderr)
        self.assertIn("goto", proc.stdout)

    def test_tidy_sees_added_lines_of_a_file_marked_binary(self):
        self.add_hidden_code()
        cwd = os.getcwd()
        os.chdir(self.root)
        try:
            self.assertEqual(dict(tidy.added_lines("HEAD~1", "HEAD")), {"src/new.cpp": [[1, 4]]})
        finally:
            os.chdir(cwd)

    def test_tidy_reads_names_with_spaces_and_non_ascii_characters(self):
        self.write("src/with space.cpp", "int a;\n")
        self.write("src/\u00e9.cpp", "int b;\n")
        self.commit("change")
        cwd = os.getcwd()
        os.chdir(self.root)
        try:
            self.assertEqual(sorted(tidy.added_lines("HEAD~1", "HEAD")), ["src/with space.cpp", "src/\u00e9.cpp"])
        finally:
            os.chdir(cwd)


if __name__ == "__main__":
    unittest.main()
