#pragma once
#include "types.h"

namespace gf {

class GfItemHandle {
public:
  GfItemHandle(const GfItemHandle &other) : value(other.value) {}

  GfItemHandle &operator=(const GfItemHandle &other) {
    value = other.value;
    return *this;
  }

  u32 value;
};

static_assert(sizeof(GfItemHandle) == 4, "");

} // namespace gf
