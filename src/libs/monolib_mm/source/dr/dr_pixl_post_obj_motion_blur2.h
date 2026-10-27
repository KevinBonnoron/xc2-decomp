#pragma once
#include <stddef.h>

#include "types.h"

namespace grlib {
class CGLibRenderTarget;
} // namespace grlib

namespace ml {

class DrPixlPostObjMotionBlur2 {
public:
  void resetColorBuff();
  void calcBludBuffColorBuff();
  void update();
  void releaseColorBuff();

  u8 _00[0x20 - 0x00];
  grlib::CGLibRenderTarget *unknown20; // Inferred role: render target; original member name unknown.
  grlib::CGLibRenderTarget *unknown28; // Inferred role: render target; original member name unknown.
  grlib::CGLibRenderTarget *unknown30; // Inferred role: render target; original member name unknown.
  grlib::CGLibRenderTarget *unknown38; // Inferred role: render target; original member name unknown.
  grlib::CGLibRenderTarget *unknown40; // Inferred role: render target; original member name unknown.
  grlib::CGLibRenderTarget *unknown48; // Inferred role: render target; original member name unknown.
};

static_assert(offsetof(DrPixlPostObjMotionBlur2, unknown20) == 0x20, "");
static_assert(offsetof(DrPixlPostObjMotionBlur2, unknown48) == 0x48, "");

} // namespace ml
