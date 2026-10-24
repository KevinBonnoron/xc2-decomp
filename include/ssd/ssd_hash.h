#pragma once
#include "types.h"

namespace ssd {

class Hash {
public:
  Hash() : unknown00(0), unknown04(0) {}

  void CalcDataHash(const void *data, u32 size);
  void CalcTextHash(const char *text);
  void CalcTextHash(const char16_t *text);

  u32 unknown00; // Inferred role: hash; original member name unknown.
  u32 unknown04; // Inferred role: size; original member name unknown.
};

} // namespace ssd
