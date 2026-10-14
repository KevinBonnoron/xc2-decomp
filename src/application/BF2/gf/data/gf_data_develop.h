#pragma once
#include "types.h"

namespace gf {

class GfDataDevelop {
public:
  static u32 getPoint(u32 nation);
  static void setPoint(u32 nation, u32 point);
  static void resetPoint(u32 nation);

  static u32 getLevel(u32 nation);
  static void setLevel(u32 nation, u32 level);
};

} // namespace gf
