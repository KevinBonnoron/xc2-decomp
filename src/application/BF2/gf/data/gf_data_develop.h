#pragma once
#include "types.h"

namespace gf {

enum {
  NATION_FIRST = 1,
  NATION_IYASAKI = 5,
  NATION_ARCADIA = 6,
};

constexpr u32 NATION_COUNT = 8;
constexpr u32 DEVELOP_LEVEL_MAX = 5;

class GfDataDevelop {
public:
  static u32 getPoint(u32 nation);
  static void setPoint(u32 nation, u32 point);
  static void resetPoint(u32 nation);

  static u32 getLevel(u32 nation);
  static void setLevel(u32 nation, u32 level);
};

} // namespace gf
