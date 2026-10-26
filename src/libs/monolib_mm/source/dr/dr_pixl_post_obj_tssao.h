#pragma once
#include <stddef.h>

#include "types.h"

namespace ml {

class DrPixlPostMan;

class DrPixlPostObjTSSAO {
public:
  void render_afterTemporal();
  void passUpScaling();
  void passUpScaleToMiddle();
  void update();

  u8 _00[0x10];
  DrPixlPostMan *unknown10; // Inferred role: post man; original member name unknown.
};

static_assert(offsetof(DrPixlPostObjTSSAO, unknown10) == 0x10, "");

} // namespace ml
