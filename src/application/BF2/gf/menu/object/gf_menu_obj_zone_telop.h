#pragma once
#include "types.h"

namespace gf {

class GfMenuCallContext;

class GfMenuObjZoneTelop {
public:
  static void open(GfMenuCallContext *context, u16 zone);
  static void close(f32 wait);
};

} // namespace gf
