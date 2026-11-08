#pragma once

#include "types.h"

namespace gf {

class GfGameUtilSkipTravel {
public:
  static bool isEnableSkipTravel(u32 mapjump);
  static void execSkipTravel(u32 mapjump);
};

} // namespace gf
