# Reconstruction rules

- Preserve names established by original symbols. Do not present inferred names
  as original names.
- The symbol tables of Monolith's sibling builds, Xenoblade Chronicles 2: Torna
  - The Golden Country and Xenoblade Chronicles: Definitive Edition, also count
  as original symbols for the code they share with this game (same class, same
  library): a name taken from them cites the game and the mangled symbol in a
  comment, and the match must be shown (same class and signature, or the same
  body). Their executables stay local under `work/` like the game's.
- Data members follow Monolith Soft's convention, seen in the game's assertion
  strings (`m_size`, `m_allocator`, `m_RefCount`, `m_stateInfos`): an `m_`
  prefix.
- A member read or written by a game accessor takes its name from that
  accessor: `getWp()` gives `m_wp`, `GetHateValue()` gives `m_hateValue`
  (drop `get`, `set` or `is`, lowercase the first letter of a capitalized
  word but keep an uppercase prefix such as `BLD_`, add `m_`). A name
  quoted in an assertion or debug string is kept exactly as written.
- Preserve existing opaque field names such as `_18` and `_1c0`.
- A member with no accessor and no string naming it is `unknown` followed by
  its hexadecimal byte offset, for example `unknown18`, never a descriptive
  invented name. For reconstructed helper functions, use `unknown001`,
  `unknown002`, etc., within each file (see the exception below for a helper
  with a single user). Keep the inferred role in a comment and state that the
  original name is unknown. Do not rename exported symbols to follow this
  convention. A bitfield member is `unknownXX_N`, N being the index of its
  first bit in byte XX.
  - Exception: an inline helper with a single user, whose existence is proven
    only because that function matches with it and no other valid form
    matches (clang optimises a separate function before inlining it), takes a
    descriptive name that states its role (`hasPlace`, `isHighVariant`...),
    like a macro. Mark it with the comment `// Inferred name; kept as an
    exception to the unknown-name rule (AGENTS.md): single-user helper whose
    existence only the match proves; rename if a sibling build gives a
    symbol.`, and list in a comment the forms tried without the helper and
    the game address of its user. Helpers with several users stay
    `unknownNNN`, except the private `setFlag`/`setDispFlag` helpers of the
    event classes, which keep their descriptive names with an `// Inferred
    name` comment (decision of 2026-11-14 #26).
- A macro leaves no trace in the binary, so its original name can never be
  recovered: give it a descriptive upper-case name and say in a comment that
  the name is inferred (`// Inferred macro name; macros leave no trace in the
  binary.`). Macros of a public SDK keep their documented names.
- The no-invented-name rule also covers `constexpr` and `const` constants and
  enumerators. One without an original name is `<PREFIX>_UNKNOWN_<N>`: PREFIX
  is the prefix its named siblings share (the enum's own, or the group a
  standalone constant belongs to, such as `KAKUSEI_BDAT_ID`) and N is its
  value in decimal (the index of the bit for a flag, so `1 << 2` is
  `FLAG_UNKNOWN_2`). Keep the inferred role in a comment, like for members.
  For example, in `src/application/BF2/battle/character/battle_character.h`:
  `ACTION_ID_UNKNOWN_5 = 5, // Inferred role: kizuna max, paired with
  STATE_ID_BATTLE_KIZUNA_MAX; original name unknown.` A name is kept only
  when the game gives it: a symbol, an assertion or debug string, a BDAT table
  or column name, or a symbol of a sibling build. Cite that source in a
  comment. Unlike macros, constants do not get a free descriptive name.
  - A name derived mechanically from a game name counts as original when the
    transformation is written down. A BDAT table id is `BDAT_` plus the
    game's table name from `s_aszGfBdatName`, split at each lower-case or
    digit to upper-case boundary and upper-cased (`bgmList` gives
    `BDAT_BGM_LIST`), with `_MS` appended when a lower-case message table
    would otherwise get the id of an upper-case table (`itm_orb` against
    `ITM_Orb`). A BDAT column enumerator is the name of its game accessor
    without `get`, `is` or `init` (the same logic as the member rule, where
    `getWp()` gives `m_wp`). `tools/gen_bdat.py` applies both: `bdat_id_name`
    and the `_MS` check in `write_ids` for the table ids, and the `init`
    prefix removal in `main` for the column enumerators. The `Flag` suffix
    the generator gives the second flag member of a column is not covered by
    this rule.
  - A range marker `<PREFIX>_COUNT`, `<PREFIX>_NUM` or `<PREFIX>_MAX` is kept
    only when its value is verifiably the number of enumerators or the value
    of the last one, checked against the enum and its uses. Any other marker
    (`_NONE`, `_INVALID`, `_FIRST`, `_LAST`...) follows the `_UNKNOWN_<N>`
    rule like any other name.
  - A constant whose value is a BDAT row id keeps a descriptive name only
    when a row of the game's BDAT tables gives that name; cite the table, row
    and column in a comment. Otherwise it is `<PREFIX>_UNKNOWN_<N>`.
  - A game string table read by a game function (for example
    `getASMCmdNameField::TABLE`, `GfObj::getTypeName`, the sound category
    names) gives enumerator names through a written-down derivation, like the
    BDAT ids: state in a comment which table the name comes from and how the
    string becomes the name.
  - Exception: the static members that templates read by name keep their
    inferred names: `GMK_TYPE` (every gimmick class; read by the `TGmkList`
    templates and `gf_com_behavior_enemy.cpp`), `COMPONENT_INDEX`
    (`getComponent<T>`), `PLUGIN_INDEX` (`GfPluginManager`) and `OBJECT_TYPE`
    (`GfObjUtil`). Each is marked once, at the template that reads it, with a
    comment `// Inferred name; shared by every ... class for ...`, for example
    `// Inferred name; shared by every gimmick class for the TGmkList
    templates.`. An enumerator of `GmkType` whose suffix is exactly a game
    class name (`GMK_TYPE_ENEMY` for `GmkEnemy`) counts as derived from that
    class symbol.
  - Exception: `mm::DEG_TO_RAD` and `mm::RAD_TO_DEG` in `include/mm_math/mm_math.h`
    keep their inferred names, marked with the comment `// Inferred name; kept
    as an exception to the unknown-name rule (AGENTS.md).`.
- When several accessors read the same member, pick the one that states its
  meaning (`IsPlayer` over `IsEnableBattleFace`); a union read by accessors of
  different types stays `unknownXX`.
- Exceptions: the math types of `include/mm_math/` keep their component names
  (`x`, `y`, `z`, `w`...), the SDK and NVN declarations of `include/nn/`
  and `include/nvn/` keep the names of their public API, and the dlmalloc code
  Monolith embedded (`src/libs/monolib_mm/source/mtl/dlmalloc.inl`) keeps the
  names of dlmalloc 2.8's public source, with a provenance comment.
- The public names of the Switch SDK and of the NVN API (functions, types,
  enumerators, parameter names) may be taken from the open-ead nnheaders
  project (https://github.com/open-ead/nnheaders), a community-written set of
  declarations. This applies only to what the game imports or uses, and the
  declaration cites nnheaders in a comment, as the existing headers of
  `include/nn/` and `include/nvn/` do. Sizes and layouts must agree with the
  game's code: they win over nnheaders when the two differ, and a comment says
  so. Nintendo's own SDK headers are never used or copied.
- Document evidence for reconstructed layouts (assembly offsets, symbols and
  matching checks). Matching machine code does not prove the original types or
  variable names.
- Never commit game executables, ROMs, extracted assets, decompiler dumps,
  console keys or proprietary SDK files. Keep local inputs and generated
  analysis under `work/`. Reconstructed SDK declarations need documented
  provenance; do not copy SDK headers.
