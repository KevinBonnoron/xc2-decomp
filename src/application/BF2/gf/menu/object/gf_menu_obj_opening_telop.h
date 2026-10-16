#pragma once
#include "types.h"

namespace gf {

class GfMenuObjOpeningTelop {
public:
  static void openCenter(u32 telop);
  static void closeCenter();
  static void openLeft(u32 telop);
  static void closeLeft();
  static void openRight(u32 telop);
  static void closeRight();
};

} // namespace gf
