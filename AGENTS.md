# Reconstruction rules

- Preserve names established by original symbols. Do not present inferred names
  as original names.
- Preserve existing opaque field names such as `_18` and `_1c0`.
- When replacing a speculative descriptive member name, use `unknown` followed
  by its hexadecimal byte offset, for example `unknown18`. For reconstructed
  helper functions, use `unknown001`, `unknown002`, etc., within each file.
  Keep the inferred role in a comment and state that the original name is
  unknown. Do not rename exported symbols to follow this convention.
- Document evidence for reconstructed layouts (assembly offsets, symbols and
  matching checks). Matching machine code does not prove the original types or
  variable names.
- Never commit game executables, ROMs, extracted assets, decompiler dumps,
  console keys or proprietary SDK files. Keep local inputs and generated
  analysis under `work/`. Reconstructed SDK declarations need documented
  provenance; do not copy SDK headers.
