#!/usr/bin/env bash
# Check that a pull request title follows the commit message convention of .githooks/commit-msg.
# Only squash merges are allowed, so the title becomes the commit message on main.
#
# Usage: PR_TITLE='feat(ui): match UiFoo functions' tools/check_title.sh
#
# The title comes from the environment, never from the command line or a shell expansion of the workflow.
set -euo pipefail

: "${PR_TITLE?check_title: set PR_TITLE to the pull request title}"
root=$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)

fail() {
  echo "check_title: the pull request title becomes the commit message on main (squash merge)." >&2
  echo "check_title: $1" >&2
  exit 1
}

case "$PR_TITLE" in
  *$'\n'*) fail "the title must be a single line" ;;
  "fixup! "* | "squash! "* | "amend! "*) fail "a fixup!, squash! or amend! title is not a message for main" ;;
esac

message=$(mktemp)
trap 'rm -f "$message"' EXIT
printf '%s\n' "$PR_TITLE" >"$message"
bash "$root/.githooks/commit-msg" "$message" || fail "rename the pull request, for example: feat(ui): match UiFoo functions"
echo "check_title: ok: $PR_TITLE"
