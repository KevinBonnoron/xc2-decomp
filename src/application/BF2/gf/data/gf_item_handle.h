#pragma once
#include "types.h"

namespace gf {

class GfItemHandle {
public:
  GfItemHandle(const GfItemHandle &other) : mHandle(other.mHandle) {}

  GfItemHandle &operator=(const GfItemHandle &other) {
    mHandle = other.mHandle;
    return *this;
  }

private:
  u32 mHandle;
};

static_assert(sizeof(GfItemHandle) == 4, "");

} // namespace gf
