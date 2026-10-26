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

- [AGENTS.md](AGENTS.md) is the reference for naming: keep the names given by the game's symbols and strings, name a member after the game accessor that reads it (`m_` prefix), and use `unknownXX` with an inferred-role comment for everything else. Never invent a descriptive name.
- Write the code a programmer would have written, not decompiler output forced to match. No `goto`, `volatile`, attributes, inline assembly, raw byte offsets on pointers or type punning to force a match. When a block is the body of an existing function, call that function. When a function only matches with such a trick, leave it for later.
- Every function you keep must match. Before each commit the hook runs `format`, `includes` and `check`, and refuses the commit if anything fails to compile, does not match or is `NOT IN GAME`. Fix the problem rather than bypassing the hook.
- Document new layouts with `static_assert(offsetof(...))` and `static_assert(sizeof(...))`, like the existing headers.
- Never commit game executables, extracted assets, decompiler output, keys or SDK files. Keep local files under `work/`, which git ignores.

## Pull requests

- Use commit messages of the form `feat(<namespace>): match <Class> functions`.
- Keep a pull request to one namespace or a few classes, so it is easy to review and rebase. `main` moves often: rebase on it before opening the pull request.
- The continuous integration cannot run `check`, since it needs the game executable. Each pull request is checked locally against the game before it is merged, along with a review of naming and code style.

Questions are welcome in the issues.
