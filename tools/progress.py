#!/usr/bin/env python3
"""Convert the verified README progress snapshot to decompilati.onl JSON.

Run `check --readme` locally before committing updated progress. This script
does not compile sources or require the original game binary.
"""
import argparse
import json
from pathlib import Path
import re


ROOT = Path(__file__).resolve().parent.parent
NUMBER = r"(?:0|[1-9][0-9]*|[1-9][0-9]{0,2}(?:,[0-9]{3})+)"
PROGRESS = re.compile(
    rf"\s*({NUMBER}) / ({NUMBER}) functions \([0-9]+\.[0-9]+%\), "
    rf"({NUMBER}) / ({NUMBER}) bytes of code \([0-9]+\.[0-9]+%\)\s*"
)


def read_progress(text):
    blocks = re.findall(r"<!-- progress -->(.*?)<!-- /progress -->", text, re.S)
    if len(blocks) != 1:
        raise ValueError("expected exactly one README progress block")
    match = PROGRESS.fullmatch(blocks[0])
    if not match:
        raise ValueError("unrecognized README progress format; run check --readme")
    functions, total_functions, code, total_code = (
        int(value.replace(",", "")) for value in match.groups()
    )
    if not 0 <= functions <= total_functions or total_functions == 0:
        raise ValueError("invalid function counts")
    if not 0 <= code <= total_code or total_code == 0:
        raise ValueError("invalid code byte counts")
    return {
        "unit": "bytes",
        "version": "1.0.0",
        "code": {"total": total_code, "matching": code, "non_matching": 0},
        "functions": {"total": total_functions, "matching": functions},
    }


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--readme", type=Path, default=ROOT / "README.md")
    args = parser.parse_args()
    try:
        report = read_progress(args.readme.read_text())
    except (OSError, ValueError) as error:
        parser.exit(1, f"progress: {error}\n")
    print(json.dumps(report, indent=2))


if __name__ == "__main__":
    main()
