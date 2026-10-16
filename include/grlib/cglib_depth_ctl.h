#pragma once
#include "types.h"

enum GrlCompare {
  GRL_COMPARE_LEQUAL = 3,
  GRL_COMPARE_ALWAYS = 7,
};

namespace grlib {

class CGLibDepthCtl {
public:
  static void setDepthControl(u8 isTest, u8 isWrite, GrlCompare compare);
};

} // namespace grlib
