#pragma once
#include <stddef.h>

#include "types.h"

namespace grlib {
class CGLibRenderTarget;
} // namespace grlib

namespace ml {

class DrPixlPostObjMotionBlur {
public:
  void debugRender();
  void resetColorBuff();
  void calcBludBuffColorBuff();
  void releaseColorBuff();
  u8 _00[0x20 - 0x00];
  grlib::CGLibRenderTarget *unknown20; // Inferred role: render target; original member name unknown.
  grlib::CGLibRenderTarget *unknown28; // Inferred role: velocity map; original member name unknown.
  grlib::CGLibRenderTarget *unknown30; // Inferred role: render target; original member name unknown.
};

static_assert(offsetof(DrPixlPostObjMotionBlur, unknown20) == 0x20, "");
static_assert(offsetof(DrPixlPostObjMotionBlur, unknown28) == 0x28, "");
static_assert(offsetof(DrPixlPostObjMotionBlur, unknown30) == 0x30, "");

} // namespace ml
