#pragma once
#include "types.h"

namespace gf {

class GfDataBladeArtsN {
public:
  static bool getName(u8 *&bdat, u32 &textId, u32 arts);
  static const char *getName(u32 arts);
  static bool getCaption(u8 *&bdat, u32 &textId, u32 arts);
  static const char *getCaption(u32 arts);
};

} // namespace gf
