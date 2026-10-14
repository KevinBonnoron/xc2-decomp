#pragma once
#include "types.h"

namespace gf {

class GfDataBattle {
public:
  static bool getClassName(u8 *&bdat, u32 &textId, u32 battleClass);
  static const char *getClassName(u32 battleClass);
};

} // namespace gf
