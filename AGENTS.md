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
  `unknown002`, etc., within each file. Keep the inferred role in a comment
  and state that the original name is unknown. Do not rename exported symbols
  to follow this convention. A bitfield member is `unknownXX_N`, N being the
  index of its first bit in byte XX.
- A macro leaves no trace in the binary, so its original name can never be
  recovered: give it a descriptive upper-case name and say in a comment that
  the name is inferred (`// Inferred macro name; macros leave no trace in the
  binary.`). Macros of a public SDK keep their documented names.
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
