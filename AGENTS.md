# Reconstruction rules

- Preserve names established by original symbols. Do not present inferred names
  as original names.
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
- When several accessors read the same member, pick the one that states its
  meaning (`IsPlayer` over `IsEnableBattleFace`); a union read by accessors of
  different types stays `unknownXX`.
- Exceptions: the math types of `include/mm_math/` keep their component names
  (`x`, `y`, `z`, `w`...), and the SDK and NVN declarations of `include/nn/`
  and `include/nvn/` keep the names of their public API.
- Document evidence for reconstructed layouts (assembly offsets, symbols and
  matching checks). Matching machine code does not prove the original types or
  variable names.
- Never commit game executables, ROMs, extracted assets, decompiler dumps,
  console keys or proprietary SDK files. Keep local inputs and generated
  analysis under `work/`. Reconstructed SDK declarations need documented
  provenance; do not copy SDK headers.
