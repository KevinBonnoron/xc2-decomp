# Contributing

Thanks for your interest in the project. Contributions are welcome as pull requests against `main`.

## Getting started

1. Dump the game (an XCI of version 1.0.0) and the `prod.keys` of your own console. They are never shared or committed.
2. Follow the [README](README.md) setup: `nix develop`, export `XC2_ROM`, then `setup`. Entering the dev shell also enables the repository's pre-commit hook.
3. Run `check` once. It should report every function as matching.

## Pick something to work on

Most namespaces are worked on by regular automated passes, so code outside a reserved area may be matched by someone else before your pull request lands. To avoid duplicate work:

- Comment on the [contribution issue](https://github.com/KevinBonnoron/xc2-decomp/issues/2) (or open a new one) with the namespace or classes you take. They are then left out of the automated passes.
- The `ui` namespace (`src/application/BF2/ui/`) is currently reserved for contributors.
- `check ui` lists, per class, what matches and what is left. Small functions and classes that already match for the most part are the easiest start.

## Rules

- [AGENTS.md](AGENTS.md) is the reference for naming: keep the names given by the game's symbols and strings, name a member after the game accessor that reads it (`m_` prefix), and use `unknownXX` with an inferred-role comment for everything else. Never invent a descriptive name. The one exception is macros, whose names never reach the binary: they get a descriptive upper-case name marked as inferred.
- Write the code a programmer would have written, not decompiler output forced to match. No `goto`, `volatile`, attributes, inline assembly, raw byte offsets on pointers or type punning to force a match. There are two exceptions: `__attribute__((always_inline))` on the math helpers of `include/mm_math/mm_mat44.h` and `mm_math.h`, which the game inlines where Clang 3.9 would not, and the `volatile` store to `mparams.magic` in dlmalloc 2.8's `init_mparams`, copied verbatim from that library's public source. When a block is the body of an existing function, call that function. When a function only matches with such a trick, leave it for later.
- Every function you keep must match. Before each commit the hook runs `format`, `includes` and `check`, and refuses the commit if anything fails to compile, does not match or is `NOT IN GAME`. Fix the problem rather than bypassing the hook. On `main` only, the hook also updates the progress section of `README.md` and the per-directory totals in `progress/areas.json`; on other branches it leaves them alone, so pull requests do not touch them and never conflict on them.
- Run `python3 -I tools/quality_gate.py main HEAD` before opening a pull request. It flags the patterns above, destructors declared without a definition, and code duplicated from an existing function or across several new ones. It also runs on every pull request.
- Document new layouts with `static_assert(offsetof(...))` and `static_assert(sizeof(...))`, like the existing headers.
- Never commit game executables, extracted assets, decompiler output, keys or SDK files. Keep local files under `work/`, which git ignores.

## Pull requests

- Use commit messages of the form `feat(<namespace>): match <Class> functions`. Only squash merges are allowed, so the title of the pull request becomes the commit message on `main`: give it the same form, `type(scope): description`, with the types of `.githooks/commit-msg`. One scope only, in lower case letters, digits, `_` or `-`, no list: `feat(wnd, skd): ...` is refused, use `feat(wnd): ...` and name the rest in the description, or drop the scope. `Merge ...`, `fixup!` and `squash!` titles are refused too.
- Keep a pull request to one namespace or a few classes, so it is easy to review and rebase. `main` moves often: rebase on it before opening the pull request.
- Do not commit the progress snapshot: the hook writes the `<!-- progress -->` block of `README.md` and `progress/areas.json` on a branch named `main` only, and a pull request that changes them is refused (restore them with `git checkout origin/main -- README.md progress/areas.json`). So work on a feature branch of your fork, never on your fork's `main`: there the hook would write the snapshot into your commits.

### What the continuous integration checks

Every pull request against `main`, including one from a fork, runs the workflow `Pull request checks` on GitHub, with no game executable and no secret. All of it can be run on your machine too, from `nix develop`:

| Check | What it verifies | Locally |
|---|---|---|
| Quality gate | The patterns of the rules above, and duplicated code, in what the pull request adds | `python3 -I tools/quality_gate.py main HEAD` |
| Build | Every root source and every header of `src/` and `include/` compiles on its own with Clang 3.9.1 and the game's flags, and no file includes another by an absolute path | `check --compile` |
| Format | The changed `.h` and `.cpp` files are `clang-format` clean | `format --check main` |
| Includes | `includes` (include-what-you-use) has nothing to say about the changed files | `includes <files>` |
| Hygiene | Nothing under `work/`, no binary, game or SDK artefact, no file above 1 MiB, no progress snapshot change, no absolute home path | `python3 tools/hygiene.py main HEAD` |
| Title | The title of the pull request follows the commit message form | `PR_TITLE='feat(ui): ...' tools/check_title.sh` |
| Tooling | The Python tools compile and their tests pass, the workflows pass `actionlint`, the shell scripts `shellcheck` | `python3 -m unittest discover -s tools/tests` |

The quality gate, hygiene and title checks run the copy of their script that is on `main`, so a pull request cannot weaken them by editing them. That is the extent of it: the workflow file itself, `tools/check.py`, `tools/includes.py`, `tools/iwyu.imp`, `flake.nix`, `flake.lock`, `.clang-format`, `.gitattributes` and `.githooks/commit-msg` come from the pull request, so a pull request that edits them can change what the build, format and includes jobs do, or drop a job. It cannot reach a secret (there is none) or the caches written on `main`. The maintainer therefore reviews every change under `.github/`, `tools/`, `flake.*` and `.clang-format` by hand, and runs the full `check` locally before merging.

A `Static analysis` job also runs clang-tidy (`tidy main HEAD`) on the lines the pull request adds, for dead stores, reads of uninitialised values, identical branches and self assignments. It only annotates the pull request and never blocks it. A separate `Main build` workflow builds `main` on every push, so that pull requests restore its caches instead of starting cold. The last job of a pull request, `Pull request checks`, fails unless every blocking check passed; it is the one status to require in the branch protection. A pull request that conflicts with `main` gets no run at all and stays pending: rebase it.

What the continuous integration cannot do is compare the code with the game, since that needs the executable. Each pull request is still checked locally with `check` before it is merged, along with a review of naming and code style, and that is where a function that does not match is found.

Questions are welcome in the issues.
