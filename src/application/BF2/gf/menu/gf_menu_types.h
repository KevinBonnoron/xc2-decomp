#pragma once
#include "types.h"

namespace gf {
namespace GfMenuTypes {

enum UIEvent {
  UI_EVENT_OPEN = 0x21,
  UI_EVENT_CLOSE = 0x22,
};

struct Param {
  Param() : unknown00() {}

  template <typename T> void set(const T &value) { *reinterpret_cast<T *>(unknown00) = value; }
  template <typename T> const T &get() const { return *reinterpret_cast<const T *>(unknown00); }

  u64 unknown00[2]; // Inferred role: data; original member name unknown.
  u8 _10[0x20 - 0x10];
};

static_assert(sizeof(Param) == 0x20, "");

} // namespace GfMenuTypes
} // namespace gf
