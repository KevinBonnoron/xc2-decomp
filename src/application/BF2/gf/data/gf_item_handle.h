#pragma once
#include "types.h"

namespace gf {

class GfItemHandle {
public:
  struct Bits {
    u32 type : 6;
    u32 serial : 26;
  };

  GfItemHandle() {}
  GfItemHandle(u32 value) : value(value) {}
  GfItemHandle(const GfItemHandle &other) : value(other.value) {}

  union {
    u32 value;
    Bits bits;
  };
};

static_assert(sizeof(GfItemHandle) == 4, "");

} // namespace gf
