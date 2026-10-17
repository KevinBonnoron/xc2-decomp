#pragma once
#include "types.h"

namespace gf {
namespace GfMenuTypes {

struct Param {
  Param() : data() {}

  template <typename T> void set(const T &value) { *reinterpret_cast<T *>(data) = value; }
  template <typename T> const T &get() const { return *reinterpret_cast<const T *>(data); }

  u64 data[2];
  u8 _10[0x20 - 0x10];
};

static_assert(sizeof(Param) == 0x20, "");

} // namespace GfMenuTypes
} // namespace gf
