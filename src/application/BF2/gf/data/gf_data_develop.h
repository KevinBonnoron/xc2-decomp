#pragma once
#include "types.h"

namespace gf {

enum {
  NATION_UNKNOWN_1 = 1, // Inferred role: nation first; original name unknown.
  NATION_UNKNOWN_5 = 5, // Inferred role: nation iyasaki; original name unknown.
  NATION_UNKNOWN_6 = 6, // Inferred role: nation arcadia; original name unknown.
};

constexpr u32 NATION_UNKNOWN_8 = 8;        // Inferred role: nation count; original name unknown.
constexpr u32 DEVELOP_LEVEL_UNKNOWN_5 = 5; // Inferred role: develop level max; original name unknown.

class GfDataDevelop {
public:
  static u32 getPoint(u32 nation);
  static void setPoint(u32 nation, u32 point);
  static void resetPoint(u32 nation);

  static u32 getLevel(u32 nation);
  static void setLevel(u32 nation, u32 level);
};

} // namespace gf
