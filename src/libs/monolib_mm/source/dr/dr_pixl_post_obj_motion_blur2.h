#pragma once
#include <stddef.h>

#include "types.h"

namespace grlib {
class CGLibVtxVertex;
} // namespace grlib

namespace ml {

class DrPixlRenderTarget;

class DrPixlPostObjMotionBlur2 {
public:
  ~DrPixlPostObjMotionBlur2();
  void resetColorBuff();
  void calcBludBuffColorBuff();
  void update();
  void releaseColorBuff();

  u8 _00[0x20 - 0x00];
  DrPixlRenderTarget *unknown20;    // Inferred role: render target; original member name unknown.
  DrPixlRenderTarget *unknown28;    // Inferred role: render target; original member name unknown.
  DrPixlRenderTarget *unknown30;    // Inferred role: render target; original member name unknown.
  DrPixlRenderTarget *unknown38;    // Inferred role: render target; original member name unknown.
  DrPixlRenderTarget *unknown40;    // Inferred role: render target; original member name unknown.
  DrPixlRenderTarget *unknown48;    // Inferred role: render target; original member name unknown.
  grlib::CGLibVtxVertex *unknown50; // Inferred role: vertex; original member name unknown.
  grlib::CGLibVtxVertex *unknown58; // Inferred role: vertex; original member name unknown.
};

static_assert(offsetof(DrPixlPostObjMotionBlur2, unknown20) == 0x20, "");
static_assert(offsetof(DrPixlPostObjMotionBlur2, unknown48) == 0x48, "");
static_assert(offsetof(DrPixlPostObjMotionBlur2, unknown58) == 0x58, "");

} // namespace ml
