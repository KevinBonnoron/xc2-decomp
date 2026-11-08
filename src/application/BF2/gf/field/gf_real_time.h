#pragma once
#include "types.h"

namespace gf {

struct RealTime {
  u64 : 6;
  u64 unknown00_6 : 10; // Inferred role: millisecond; original member name unknown.
  u64 unknown02_0 : 6;  // Inferred role: second; original member name unknown.
  u64 unknown02_6 : 6;  // Inferred role: minute; original member name unknown.
  u64 unknown03_4 : 5;  // Inferred role: hour; original member name unknown.
  u64 unknown04_1 : 5;  // Inferred role: day; original member name unknown.
  u64 unknown04_6 : 9;  // Inferred role: day of year; original member name unknown.
  u64 unknown05_7 : 4;  // Inferred role: month; original member name unknown.
  u64 unknown06_3 : 13; // Inferred role: year; original member name unknown.
};

static_assert(sizeof(RealTime) == 8, "");

} // namespace gf
