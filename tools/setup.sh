#!/usr/bin/env bash
set -euo pipefail
cd "$(git rev-parse --show-toplevel)"

MAIN_SHA256=956348ce46e0db8ed3f378847495f2869aa59027811351733eb17c6e5f1149d9
ELF_SHA256=fdf529bc23b318ca6ac3530e5f3a448d9bef7924fe8ea322b863bbf587d49646

bdat=0
case "${1:-}" in
  "") ;;
  --bdat) bdat=1 ;;
  *) echo "usage: setup [--bdat]" >&2; exit 2 ;;
esac

keys=${SWITCH_KEYS:-$HOME/.switch/prod.keys}
[ -f "$keys" ] || { echo "Switch keys not found at $keys, set SWITCH_KEYS" >&2; exit 1; }

mkdir -p work
tmp=$(mktemp -d -p work)
trap 'rm -rf "$tmp"' EXIT

secure=work/secure
where=$secure
if [ ! -d "$secure" ]; then
  : "${XC2_ROM:?set XC2_ROM to your Xenoblade Chronicles 2 XCI dump}"
  secure=$tmp/secure
  where=$XC2_ROM
  echo "Extracting $XC2_ROM"
  hactool -k "$keys" -t xci --securedir="$secure" "$XC2_ROM" >/dev/null 2>&1
fi

# The game data (BDAT tables) lives in the romfs of the base program NCA, the one
# whose executable was just hash-checked, so it is the 1.0.0 data and not the update's.
extract_bdat() {
  local nca=$1
  echo "Extracting the BDAT tables from $(basename "$nca")"
  hactool -k "$keys" --romfsdir="$tmp/romfs" "$nca" >/dev/null 2>"$tmp/romfs.log" \
    || { cat "$tmp/romfs.log" >&2; echo "hactool failed to extract the romfs" >&2; exit 1; }
  [ -f "$tmp/romfs/bf2.arh" ] && [ -f "$tmp/romfs/bf2.ard" ] \
    || { echo "bf2.arh or bf2.ard is missing from the romfs of $nca" >&2; exit 1; }
  python3 tools/extract_bdat.py "$tmp/romfs/bf2.arh" "$tmp/romfs/bf2.ard" "$tmp/bdat"
  rm -rf work/bdat "$tmp/romfs"
  mv "$tmp/bdat/bdat" work/bdat
  echo "work/bdat is ready"
}

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
  if [ "$bdat" = 1 ]; then extract_bdat "$nca"; fi
  exit 0
done

echo "no Xenoblade Chronicles 2 1.0.0 executable found in $where" >&2
exit 1
