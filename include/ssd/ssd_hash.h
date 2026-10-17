#pragma once
#include "types.h"

namespace ssd {

class Hash {
public:
  Hash() : hash(0), size(0) {}

  void CalcDataHash(const void *data, u32 size);
  void CalcTextHash(const char *text);
  void CalcTextHash(const char16_t *text);

  u32 hash;
  u32 size;
};

} // namespace ssd
