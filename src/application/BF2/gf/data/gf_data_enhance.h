#pragma once
#include "types.h"

namespace gf {

class GfDataEnhance {
public:
  static bool getCaption(u8 *&bdat, u32 &textId, u32 enhance);
  static const char *getCaption(u32 enhance);
};

} // namespace gf
