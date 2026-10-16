#pragma once
#include "types.h"

namespace mm {
struct Col4;
} // namespace mm

namespace gf {

class GfMenuObjFade {
public:
  static void dispLoading(bool disp, u16 type);
  static void getFadeColor(u8 type, mm::Col4 &color);
};

} // namespace gf
