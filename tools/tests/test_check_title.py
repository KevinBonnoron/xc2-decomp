"""Unit tests of tools/check_title.sh: python3 -m unittest discover -s tools/tests"""
import os
import subprocess
import tempfile
import unittest

SCRIPT = os.path.join(os.path.dirname(os.path.abspath(__file__)), "..", "check_title.sh")


def run(title):
    env = {key: value for key, value in os.environ.items() if key != "PR_TITLE"}
    if title is not None:
        env["PR_TITLE"] = title
    return subprocess.run(["bash", SCRIPT], env=env, capture_output=True, text=True)


class CheckTitleTest(unittest.TestCase):
    def test_accepted_titles(self):
        for title in ("feat(ui): match UiFoo functions", "ci: add pull request checks", "fix!: breaking change",
                      "docs(readme): update", 'Revert "feat: x"', "chore: $(touch pwned) `id`"):
            with self.subTest(title=title):
                self.assertEqual(run(title).returncode, 0, title)

    def test_rejected_titles(self):
        for title in ("Fix the thing", "feat(UI): upper case scope", "feat: ", "feat(ui):match", "#12 fix",
                      "fixup! feat: x", "squash! feat: x", "Merge branch 'main' into x", "feat: first\nsecond line", "",
                      None):
            with self.subTest(title=title):
                self.assertEqual(run(title).returncode, 1, title)

    def test_title_is_never_executed(self):
        with tempfile.TemporaryDirectory() as tmp:
            marker = os.path.join(tmp, "marker")
            self.assertEqual(run(f"chore: $(touch {marker}) `touch {marker}`").returncode, 0)
            self.assertFalse(os.path.exists(marker))


if __name__ == "__main__":
    unittest.main()
