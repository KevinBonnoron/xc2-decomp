#pragma once
#include "types.h"

namespace gf {

class GfMenuBdat {
public:
  static bool isValidBdatID(u8 *bdat, int id);
  static u32 getIconImageIndex(int icon);
};

} // namespace gf
