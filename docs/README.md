# Project notes

Notes for contributors, written so that every contributor, human or automated, reads the same text.

- [decisions.md](decisions.md): the rulings and the numbered decisions (1 to 57) that say which forms are accepted as original code (single-use locals, `{}` blocks, helpers, casts, retypes) and which are refused as steering the compiler, each with its reason, scope and evidence. Source comments cite them as `ruling N`, `P1` to `P5` and `decision N`.
- [lessons.md](lessons.md): what clang 3.9 does and which natural source gives the game's code: switches, store merging, kept branches, null and zero tests, member widths, inlined helpers and frame layout, unity units, operand order, loop strength reduction, compiler flags.

The naming rules are in [AGENTS.md](../AGENTS.md), the contribution workflow and the checks in [CONTRIBUTING.md](../CONTRIBUTING.md).
