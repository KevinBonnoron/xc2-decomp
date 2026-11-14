#pragma once
#include "types.h"

namespace gf {
namespace GfMenuTypes {

// Inferred role: menu UI event ids; original type name unknown.
enum unknown003 {
  unknown003_33 = 0x21,   // Inferred role: open; original name unknown.
  unknown003_34 = 0x22,   // Inferred role: close; original name unknown.
  unknown003_256 = 0x100, // Inferred role: start; original name unknown.
  unknown003_257 = 0x101, // Inferred role: suspend; original name unknown.
  unknown003_258 = 0x102, // Inferred role: resume; original name unknown.
  unknown003_259 = 0x103, // Inferred role: end; original name unknown.
  unknown003_260 = 0x104, // Inferred role: update; original name unknown.
};

struct Param {
  Param() : unknown00() {}

  template <typename T> void set(const T &value) { *reinterpret_cast<T *>(unknown00) = value; }
  template <typename T> T &get() { return *reinterpret_cast<T *>(unknown00); }
  template <typename T> const T &get() const { return *reinterpret_cast<const T *>(unknown00); }

  u64 unknown00[2]; // Inferred role: data; original member name unknown.
  u8 _10[0x20 - 0x10];
};

static_assert(sizeof(Param) == 0x20, "");

} // namespace GfMenuTypes
} // namespace gf
