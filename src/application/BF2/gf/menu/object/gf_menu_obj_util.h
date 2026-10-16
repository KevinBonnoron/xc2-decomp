#pragma once
#include "types.h"

namespace gf {

class GfMenuObjUtil {
public:
  static u16 getMsgIDFromList(u32 bdat, u16 id);
  static void playSE(u32 se);
  static void playSECommon(u32 se);
};

} // namespace gf
