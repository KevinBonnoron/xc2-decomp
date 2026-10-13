#!/usr/bin/env bash
set -euo pipefail
cd "$(git rev-parse --show-toplevel)"

MAIN_SHA256=956348ce46e0db8ed3f378847495f2869aa59027811351733eb17c6e5f1149d9
ELF_SHA256=fdf529bc23b318ca6ac3530e5f3a448d9bef7924fe8ea322b863bbf587d49646

: "${XC2_ROM:?set XC2_ROM to your Xenoblade Chronicles 2 XCI dump}"
keys=${SWITCH_KEYS:-$HOME/.switch/prod.keys}
[ -f "$keys" ] || { echo "Switch keys not found at $keys, set SWITCH_KEYS" >&2; exit 1; }

mkdir -p work
tmp=$(mktemp -d -p work)
trap 'rm -rf "$tmp"' EXIT

secure=work/secure
if [ ! -d "$secure" ]; then
  secure=$tmp/secure
  echo "Extracting $XC2_ROM"
  hactool -k "$keys" -t xci --securedir="$secure" "$XC2_ROM" >/dev/null 2>&1
fi

for nca in "$secure"/*.nca; do
  rm -rf "$tmp/exefs" "$tmp/main.bin"
  hactool -k "$keys" --exefsdir="$tmp/exefs" "$nca" >/dev/null 2>&1 || true
  [ -f "$tmp/exefs/main" ] || continue
  hactool -t nso0 --uncompressed="$tmp/main.bin" "$tmp/exefs/main" >/dev/null 2>&1 || continue
  echo "$MAIN_SHA256  $tmp/main.bin" | sha256sum -c --status || continue

  mv "$tmp/main.bin" work/main_base.bin
  python3 tools/nso2elf.py work/main_base.bin work/main_100.elf
  echo "$ELF_SHA256  work/main_100.elf" | sha256sum -c --quiet
  echo "work/main_100.elf is ready"
  exit 0
done

echo "no Xenoblade Chronicles 2 1.0.0 executable found in $XC2_ROM" >&2
exit 1
