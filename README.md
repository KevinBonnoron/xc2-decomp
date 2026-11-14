# Xenoblade Chronicles 2 decompilation

[![Matching](https://decompilati.onl/badge/xenoblade-chronicles-2/matching.svg)](https://decompilati.onl/projects/xenoblade-chronicles-2)
[![Functions](https://decompilati.onl/badge/xenoblade-chronicles-2/functions.svg)](https://decompilati.onl/projects/xenoblade-chronicles-2)
[![Main build](https://github.com/KevinBonnoron/xc2-decomp/actions/workflows/main.yml/badge.svg)](https://github.com/KevinBonnoron/xc2-decomp/actions/workflows/main.yml)

A work-in-progress matching decompilation of *Xenoblade Chronicles 2* (Nintendo Switch, version 1.0.0).

**This repository contains reconstructed C++ code, but must not include original game executables, extracted assets, console keys or proprietary SDK files.** You need your own legally obtained copy of the game to work on it.

## Progress

<!-- progress -->
43,573 / 48,739 functions (89.401%), 5,996,436 / 10,024,304 bytes of code (59.819%)
<!-- /progress -->

Counted over the named functions of `main`, as reported by `check`. Run `check --readme` to update this section. History and details: [decompilati.onl](https://decompilati.onl/projects/xenoblade-chronicles-2).

## Status and limits

- Matching is verified function by function: `check` places each function at its game address and compares its bytes. There is no link step and no executable is rebuilt, so the data sections and the vtables are not compared; only the read-only data a function uses, such as its strings and tables, must hold the game's bytes.
- Only version 1.0.0 is covered.
- The matched functions are mostly the small ones. From the totals above, a matched function averaged about 126 bytes of code and a function still to do about 655 when this section was written, so the byte percentage is the representative figure, not the function percentage.

## How it works

- The game was built with Clang 3.9.1. We write C++ that, compiled with the same compiler and flags, produces exactly the same machine code as the game, function by function.
- `check` compiles `src/`, places each function at the address of the original and compares the bytes. A function counts only when every byte matches.
- Version 1.0.0 still ships its dynamic symbol table: about 51,000 functions keep their original C++ names, so classes and functions use the original names. Names the binary does not give are written `unknownXX`, never invented.
- The original source paths (`C:/Monolithsoft/BF2/prog/application/BF2/...`) appear in assertion strings, and `src/application/BF2/` mirrors that layout.

## Quick start

```sh
nix develop
export XC2_ROM="/path/to/Xenoblade.xci"
setup                      # extract and verify the 1.0.0 executable into work/
check                      # compile src/ and compare every function with the game
check gf::GfDataBlade      # one class: its functions and the ones left to do
```

You need [Nix](https://nixos.org/) with flakes and your own XCI dump and `prod.keys`. Details are under Requirements and Setup below.

## Contributing

Contributions are welcome. Read [CONTRIBUTING.md](CONTRIBUTING.md) and [AGENTS.md](AGENTS.md) (naming rules) first. In short:

- Every function you keep must match, and no new data problem may appear: the pre-commit hook runs `format`, `includes` and `check --strict-data`, and refreshes the progress above on `main` only.
- Every pull request is also checked on GitHub, without the game: compilation, formatting, includes, the quality gate, repository hygiene and the title (see [CONTRIBUTING.md](CONTRIBUTING.md)). Matching the game is still checked locally before a merge.
- Use the game's names; anything the binary does not name is `unknown` plus its offset, with the inferred role in a comment. Write the code a programmer would have written, not decompiler output forced to match.
- Never commit anything from the game (executables, assets, keys, SDK files); local files stay in `work/`.
- To avoid working on the same code, say which namespace or classes you take in the [contribution issue](https://github.com/KevinBonnoron/xc2-decomp/issues/2). `ui` is reserved for contributors.

## Target

| | |
|---|---|
| Title ID | `0100E95004038000` |
| Version | 1.0.0 (base game, without update) |
| Build ID | `5087AF2917D85858A0FD49CB4D6EED67` |
| `main` (uncompressed NSO) SHA-256 | `956348ce46e0db8ed3f378847495f2869aa59027811351733eb17c6e5f1149d9` |

Version 1.0.0 is used because its executable still ships its dynamic symbol table: about 51,000 functions keep their original C++ names. Later updates are stripped.

The original source paths (`C:/Monolithsoft/BF2/prog/application/BF2/...`) appear in assertion strings, and `src/application/BF2/` mirrors that layout.

## Reference

<details>
<summary><b>Requirements</b></summary>

- [Nix](https://nixos.org/) with flakes enabled. The dev shell provides everything else: the original compiler, LLVM tools, hactool, Ghidra, Python.
- Optionally [direnv](https://direnv.net/), to enter the shell automatically (`direnv allow`).
- An XCI dump of the game, and the matching `prod.keys` from your own console.

</details>

<details>
<summary><b>Setup</b></summary>

Set `XC2_ROM` to the path of your own XCI dump; there is no machine-specific
default. Paths containing spaces must be quoted. `SWITCH_KEYS` is optional and
defaults to `$HOME/.switch/prod.keys`. The development shell preserves values
you have already exported.

```sh
nix develop
export XC2_ROM="/path/to/Xenoblade.xci"
export SWITCH_KEYS=~/.switch/prod.keys   # default
setup
```

`setup` extracts the 1.0.0 executable from the XCI, checks its hash, and converts it into `work/main_100.elf`, an ELF with relocations applied and the full symbol table. Everything under `work/` is ignored by git and must never be committed.

`setup --bdat` additionally extracts the BDAT tables of the 1.0.0 base game from the same program NCA into `work/bdat/` (`common*.bdat`, `lookat.bdat` and one subdirectory per language) and fails if the archive or the file count does not check out. It needs about 12 GB of temporary disk space under `work/`.

</details>

<details>
<summary><b>Checking functions</b></summary>

```sh
check                                       # every function defined in src/, and the overall progress
check -v                                    # same, listing the matching functions too
check --readme                              # same, and update the progress in this README
check --strict-data                         # same, and fail on a data problem tools/data_baseline.txt does not list (what the hook runs)
check --write-data-baseline                 # rewrite tools/data_baseline.txt from the data report (full check only)
check --compile                             # only compile every source and header with the game's flags, no game needed
check gf::GfDataBladeCreate                 # one class or namespace, and the functions left to do
check gf::GfDataBlade::setHikariCurrent     # side by side diff of one function
check 0x710028c7ec src/application/BF2/gf/data/gf_data_obj.cpp unknown001
                                            # diff a function the game has no symbol for
```

`check` compiles `src/`, places each of your functions at the address of the original with every relocation resolved, and compares the bytes: it prints `MATCH`, or a colored side by side diff and the first instruction that differs. Only source locations may differ: the directory of a `__FILE__` path, the `__LINE__` passed to an assertion or to `operator new`, and the spaces of an assertion text. Data local to your file has no symbol in the game: read-only data (strings, literals, tables) must hold the game's bytes, and writable data must be at one game address wherever the function uses it. A full `check` lists only the functions that do not match; `-v` lists them all. It also compiles every header on its own, so a header must include or forward-declare everything it uses. It exits with an error when something does not match or fails to compile.

`check` keeps its work in `work/check_cache`: each object and its results are reused until its source or one of the headers it includes changes, and the game's symbols are read once. A change to `tools/check.py`, the compiler or its flags discards the whole cache; delete the directory to start over.

`check --compile` does the compiling half of a full `check` and nothing else: every source and every header must build with Clang 3.9.1 and the game's flags, and no file may include another by an absolute path. It never opens the game executable, so it also runs in the continuous integration.

A function you define that the game has no symbol for is listed as `NOT IN GAME`, with the game functions of the same name: it usually means a wrong namespace or parameter type in its signature.

Functions local to their source file (`static`, anonymous namespace) have no symbol in the game. A full `check` finds the game address of each local function where the callers that match call it, and checks it too, listed as `(local, address)`; a local function only ever inlined has no call to follow. To diff one by hand, pass its game address and its name in your file. The game side of that diff ends at the next named function or at the next address called by a `bl`; your function is compared over its own size.

A full `check` also ends with a report of what the function check does not compare: global data (tables, vtables) whose size, bytes or pointers differ from the game's symbol of the same name, writable data local to a file that the game places on a symbol or that overlaps another local object, global functions defined by more than one source, and `(local, address)` functions that match only the start of the game's code. It is printed and counted (`data: N problems, duplicate definitions: N, local prefix matches: N`); `check --strict-data`, which the pre-commit hook runs, fails only on a problem that `tools/data_baseline.txt` does not list, and prints `fixed:` for a listed problem that is gone. To update the baseline, run `check --write-data-baseline` (it drops the fixed lines and keeps the reasons), then write the reason after the `#` of each line it added: a new entry needs a reason that is reviewed like a code change, and fixing the problem is preferred to listing it.

</details>

<details>
<summary><b>Includes</b></summary>

```sh
includes                                    # list the includes to add, remove or replace by a forward declaration
includes --fix                              # apply them
```

Each file includes the header of every name it uses, and a header forward-declares what it only needs by pointer or reference instead of including it. `includes` runs include-what-you-use over `src/` and `include/` to enforce it; class templates are always included, never forward-declared. Run `check` afterwards: adding a line above an `operator new` or an assertion shifts its `__LINE__`, which can change the instructions (pin it with `#line` when it does).

</details>

<details>
<summary><b>Compiler</b></summary>

The game was built with **Clang 3.9.1**. The flags that matter:

```
--target=aarch64-none-elf -O3 -std=c++14 -fno-exceptions -fno-rtti -fno-strict-aliasing -fno-slp-vectorize -mno-implicit-float -fPIC -g
```

`-g` is not optional: with Clang 3.9, debug info changes instruction scheduling, and nothing matches without it. `-fno-slp-vectorize` is needed too: the game was built without SLP vectorization (two vtable pointers stay an `stp`, a run of float to u16 conversions stays scalar). So is `-mno-implicit-float`: the game never copies structs through q registers (a 24-byte copy is three `ldr`/`str` pairs of x registers). Clang 4.0.1 is also available in the shell (`clang++-4.0.1`) for comparison.

To try another compiler: `XC2_CXX=clang++-4.0.1 check ...`.

`-nostdlibinc` (a header search flag, no effect on the generated code) keeps the compiler from reading the host's `/usr/include`, so that on a distribution that has one the musl headers of the sysroot are the only libc headers.

`-fno-spell-checking` (diagnostics only, no effect on the generated code) turns off the "did you mean" suggestions: on an undeclared identifier, Clang 3.9.1's spelling correction can allocate tens of gigabytes within seconds instead of reporting the error.

</details>

<details>
<summary><b>Standard library</b></summary>

The game uses the Nintendo SDK's libc++ (`std::__1`) on top of its musl based C library (`__nnmusl_init_dso`). The dev shell provides the same era of headers: the libc++ headers of LLVM 3.9.1, configured for musl and the pthread API, and the musl 1.1.16 headers for AArch64. The shell points `XC2_SYSROOT` at them (and links `work/sysroot` for editors). Include them as system headers: `<string.h>`, `<new>`, `<functional>`, `<unordered_map>`...

With exceptions disabled, libc++ 3.9 reports an allocation overflow with `fprintf(stderr, ...)` and `abort()` instead of throwing, as the game does. `std::sort`, `std::function`, `std::unordered_map<std::string, ...>` and the other `std::__1` templates the game instantiates compile to the same code as the game's.

</details>

<details>
<summary><b>Ghidra</b></summary>

The dev shell includes Ghidra. Import `work/main_100.elf` (AArch64, little endian, base `0x7100000000`) and run the auto analysis.

`tools/ghidra/ExportDecomp.java` exports the pseudo-C of every function to one file per class, which makes the decompiler output searchable with grep:

```sh
_JAVA_OPTIONS=-Xmx24g ghidra-analyzeHeadless <project dir> <project name> -process main_100.elf \
  -noanalysis -readOnly -scriptPath tools/ghidra -postScript ExportDecomp.java work/decomp
```

Ghidra cannot open a project that is already open in the GUI: run it on a copy.

</details>

<details>
<summary><b>Glossary</b></summary>

Abbreviations and names imposed by the game's symbols:

| Term | Meaning |
|---|---|
| `Dr`, `Bl` | Driver, Blade |
| `Chr` | Character (`GfBdatChrDr`: the driver table) |
| `Btl` | Battle |
| `Rsc` | Resource: models, motions, effects |
| `Pc`, `Wpn` | Player character, weapon (`getPcWpnDamage`) |
| `Cri` | Critical (`getPcWpnCriRate`) |
| `Wp` | Weapon points, spent to level up driver arts |
| `MS` | Message: `Bdat::getMSText` reads a text from a message table |
| `FP` | Pointer to a loaded BDAT table (`GfDataBdat::getFP`) |
| BDAT | The game's data tables (characters, items, quests, texts...), browsable at [xenoblade.github.io/xb2/bdat](https://xenoblade.github.io/xb2/bdat) |
| `Homura`, `Hikari` | Pyra, Mythra (Japanese names) |
| `Homuri` | Pyra and Mythra together |
| `Byakko` | Dromarch (Japanese name) |
| `Saika` | Pandoria (Japanese name) |
| `Hana` | Poppi (Japanese name) |
| `Hana JS`, `Hana JK`, `Hana JD` | Poppi α, Poppi QT, Poppi QTπ |
| `Metsu` | Malos (Japanese name) |
| `Nanakoori` | Ursula (Japanese name) |
| `Jiku` | Zeke (Japanese name) |
| `Meleph` | Mòrag (Japanese name) |
| `Shin` | Jin (Japanese name) |
| `Shin 2`, `Jiku hood` | Variants of a character, numbered or described as in the `CHR_Dr` BDAT table |
| `Avaritia`, `Gula`, `Invidia`, `Superbia`, `Luxuria`, `Liberalitas` | Argentum, Gormott, Uraya, Mor Ardain, Tantal, Leftheria (Japanese names) |
| `Arcadia` | Indol (Japanese name) |
| `Elpis` | Spirit Crucible Elpys |
| `Vandamme` | Vandham |
| `mm`, `mtl`, `ml` | Monolith Soft's in-house libraries (`mtl` is their template library, a replacement for the STL) |

</details>

## Repository layout

| Path | Content |
|---|---|
| `src/application/BF2/` | Decompiled game code, following the original source tree |
| `include/` | Shared headers (basic types, libraries); the C and C++ standard headers come from the dev shell |
| `tools/check.py` | Compile and compare functions; `check --compile` only compiles everything, without the game |
| `tools/quality_gate.py` | Flag match-forcing patterns and duplicated code added since a revision |
| `tools/includes.py`, `tools/iwyu.imp` | Include-what-you-use pass and its mappings |
| `tools/hygiene.py`, `tools/check_title.sh` | Pull request checks: files that must not be committed, commit message form of the title |
| `tools/tidy.py` | clang-tidy on the lines a change adds (dead stores, uninitialised reads, identical branches) |
| `tools/tests/` | Unit tests of the pull request check scripts |
| `tools/setup.sh`, `tools/extract_bdat.py` | Extract the executable (and with `--bdat` the BDAT tables) from the XCI |
| `tools/nso2elf.py`, `tools/nso_syms.py` | NSO to ELF conversion, symbol dump |
| `.github/workflows/` | Continuous integration: `pr.yml` checks every pull request, `main.yml` builds `main` and seeds the caches, `progress.yml` publishes the progress |
| `tools/ghidra/` | Ghidra scripts |

## Tips

- Functions appear in the binary in the order they were written in their source file. The neighbors of a function tell you which file it belongs to and what comes next.
- Ghidra guesses types and return values. When in doubt, the assembly is the reference.
- A destructor that must store the vtable pointer as the game does gets a body holding only `;`: with an empty body `{}`, the compiler drops the store.
- Different C++ can produce the same machine code. Prefer the version a programmer would naturally have written.

## License and disclaimer

The reconstructed code and the tools of this repository are dedicated to the public domain under [CC0 1.0 Universal](LICENSE), to the extent the contributors hold rights in them.

Third-party code keeps its own terms. The memory allocator embedded in `src/libs/monolib_mm/source/mtl/dlmalloc.inl` is dlmalloc 2.8.6 by Doug Lea, released to the public domain (CC0); the provenance comment at the top of that file is its notice.

This project is not affiliated with, endorsed by or sponsored by Nintendo or Monolith Soft. *Xenoblade Chronicles* is a trademark of Nintendo. The repository contains no game executable, asset or key: you need your own legally obtained copy of the game.
