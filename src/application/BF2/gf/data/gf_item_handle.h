#pragma once
#include "types.h"

namespace gf {

class GfItemHandle {
public:
  struct Bits {
    u32 unknown00_0 : 6;  // Inferred role: type; original member name unknown.
    u32 unknown00_6 : 26; // Inferred role: serial; original member name unknown.
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
