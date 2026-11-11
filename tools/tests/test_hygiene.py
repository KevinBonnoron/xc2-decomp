"""Unit tests of tools/hygiene.py, on throwaway git repositories: python3 -m unittest discover -s tools/tests"""
import os
import subprocess
import sys
import tempfile
import unittest

sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), ".."))
import hygiene  # noqa: E402

README = "# Title\n\n<!-- progress -->\n1 / 2 functions\n<!-- /progress -->\n\ntext\n"
HOME = "/hom" + "e/someone/project"
WINDOWS_HOME = "C:/Us" + "ers/someone/project"


class Repo:
    def __init__(self, root):
        self.root = root
        self.git("init", "-q", "-b", "main")
        self.git("config", "user.email", "ci@example.com")
        self.git("config", "user.name", "ci")
        self.write("README.md", README)
        self.write("progress/areas.json", "{}\n")
        self.write("src/a.cpp", "int a;\n")
        self.commit("base")

    def git(self, *args):
        return subprocess.run(["git", "-C", self.root, *args], check=True, capture_output=True, text=True).stdout

    def write(self, path, content):
        full = os.path.join(self.root, path)
        os.makedirs(os.path.dirname(full), exist_ok=True)
        with open(full, "wb") as f:
            f.write(content if isinstance(content, bytes) else content.encode())

    def commit(self, message):
        self.git("add", "-f", "-A")
        self.git("commit", "-q", "-m", message)

    def violations(self):
        cwd = os.getcwd()
        os.chdir(self.root)
        try:
            base, files = hygiene.changed_files("HEAD~1", "HEAD")
            return {path: problems for status, mode, path in files
                    if (problems := hygiene.check_file(base, "HEAD", status, mode, path))}
        finally:
            os.chdir(cwd)


class HygieneTest(unittest.TestCase):
    def setUp(self):
        self.tmp = tempfile.TemporaryDirectory()
        self.addCleanup(self.tmp.cleanup)
        self.repo = Repo(self.tmp.name)

    def violations_of(self, **files):
        for path, content in files.items():
            self.repo.write(path.replace("__", "/").replace("_dot_", "."), content)
        self.repo.commit("change")
        return self.repo.violations()

    def test_clean_change_passes(self):
        self.repo.write("src/a.cpp", "int a = 1;\n")
        self.repo.write("README.md", README.replace("text", "other text"))
        self.repo.commit("change")
        self.assertEqual(self.repo.violations(), {})

    def test_work_directory(self):
        found = self.violations_of(work__notes_dot_txt="x\n")
        self.assertIn("work/notes.txt", found)
        self.assertIn("work/", found["work/notes.txt"][0])

    def test_artefact_extensions(self):
        for name in ("game.nso", "dump.xci", "prod.keys", "table.bdat", "libx.so", "x.o", "c.gzf"):
            self.repo.write(f"src/{name}", "plain text\n")
        self.repo.commit("change")
        found = self.repo.violations()
        self.assertEqual(len(found), 7)
        self.assertTrue(all("by its extension" in problems[0] for problems in found.values()))

    def test_magic_numbers_whatever_the_name(self):
        self.repo.write("src/a.txt", b"\x7fELF" + bytes(64))
        self.repo.write("src/b.txt", b"NSO0" + bytes(64))
        self.repo.write("src/c.txt", b"PFS0" + bytes(64))
        self.repo.write("src/d.txt", b"HFS0" + bytes(64))
        self.repo.write("src/e.txt", bytes(16) + b"NRO0" + bytes(64))
        self.repo.commit("change")
        found = self.repo.violations()
        self.assertEqual(sorted(found), ["src/a.txt", "src/b.txt", "src/c.txt", "src/d.txt", "src/e.txt"])
        self.assertTrue(all("magic number" in problems[0] for problems in found.values()))

    def test_binary_file(self):
        found = self.violations_of(src__data_dot_txt=b"abc\0def")
        self.assertEqual(found["src/data.txt"], ["is a binary file"])

    def test_large_file(self):
        found = self.violations_of(docs__big_dot_txt="x" * (1 << 20) + "\n")
        self.assertIn("1048577 bytes", found["docs/big.txt"][0])
        self.assertEqual(self.violations_of(docs__edge_dot_txt="x" * ((1 << 20) - 1) + "\n").get("docs/edge.txt"), None)

    def test_progress_files(self):
        found = self.violations_of(progress__areas_dot_json="{\"a\": 1}\n")
        self.assertIn("pre-commit hook", found["progress/areas.json"][0])

    def test_readme_progress_block_changed(self):
        self.assertEqual(self.violations_of(README_dot_md=README.replace("1 / 2", "5 / 9")).keys(), {"README.md"})

    def test_readme_progress_block_removed(self):
        self.assertEqual(self.violations_of(README_dot_md="# Title\n").keys(), {"README.md"})

    def test_readme_outside_block_is_fine(self):
        self.assertEqual(self.violations_of(README_dot_md=README.replace("text", "more text")), {})

    def test_home_paths(self):
        found = self.violations_of(docs__a_dot_md=f"see {HOME}\n", docs__b_dot_md=f"see {WINDOWS_HOME}\n")
        self.assertIn("line 1", found["docs/a.md"][0])
        self.assertIn("line 1", found["docs/b.md"][0])

    def test_home_path_placeholders_and_relative_paths(self):
        text = "/hom" + "e/user/x, /hom" + "e/<you>/x, C:/Us" + "ers/user/x, ~/x, src/hom" + "e/x, ./hom" + "e/x\n"
        self.assertEqual(self.violations_of(docs__c_dot_md=text), {})

    def test_deleted_files_are_ignored(self):
        self.repo.git("rm", "-q", "src/a.cpp")
        self.repo.commit("delete")
        self.assertEqual(self.repo.violations(), {})

    def test_deleting_the_progress_snapshot_is_refused(self):
        self.repo.git("rm", "-q", "progress/areas.json")
        self.repo.commit("delete")
        found = self.repo.violations()
        self.assertIn("git checkout origin/main", found["progress/areas.json"][0])

    def test_home_path_of_macos(self):
        found = self.violations_of(docs__m_dot_md="see /Us" + "ers/someone/project\n")
        self.assertIn("line 1", found["docs/m.md"][0])

    def test_only_added_lines_are_scanned_for_home_paths(self):
        self.repo.write("docs/old.md", f"old {HOME}\n")
        self.repo.commit("seed")
        self.assertEqual(self.violations_of(docs__old_dot_md=f"old {HOME}\nnew line\n"), {})
        found = self.violations_of(docs__old_dot_md=f"old {HOME}\nnew line\nnew {HOME}\n")
        self.assertIn("line 3", found["docs/old.md"][0])

    def test_type_change_to_a_symlink(self):
        self.repo.git("rm", "-q", "src/a.cpp")
        os.makedirs(os.path.join(self.tmp.name, "src"), exist_ok=True)
        os.symlink(HOME, os.path.join(self.tmp.name, "src", "a.cpp"))
        self.repo.commit("symlink")
        self.assertIn("src/a.cpp", self.repo.violations())

    def test_submodule(self):
        self.repo.git("update-index", "--add", "--cacheinfo", "160000," + "1" * 40 + ",vendor")
        self.repo.git("commit", "-q", "-m", "submodule")
        self.assertEqual(self.repo.violations(), {"vendor": ["is a submodule, which is not allowed"]})

    def test_main_end_to_end(self):
        self.repo.write("work/x", "x\n")
        self.repo.commit("change")
        proc = subprocess.run([sys.executable, hygiene.__file__, "HEAD~1", "HEAD"], cwd=self.tmp.name,
                              capture_output=True, text=True)
        self.assertEqual(proc.returncode, 1)
        self.assertIn("hygiene: work/x: lives under work/", proc.stdout)
        self.assertIn("1 changed file checked, 1 violation", proc.stdout)


if __name__ == "__main__":
    unittest.main()
