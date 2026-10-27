#pragma once
#include <stddef.h>

#include "grlib/cglib_render_target.h"
#include "types.h"

namespace ml {

class DrMan;

class DrPixlRenderTarget : public grlib::CGLibRenderTarget {
public:
  explicit DrPixlRenderTarget(DrMan *man);
  ~DrPixlRenderTarget();
  void debugRender(int x, int y, int width, int height, bool isAlpha, bool isDepth, f32 scale, bool isFlip);
  void debugRenderCh(int x, int y, int width, int height, u32 channel);

  DrMan *unknown3c8; // Inferred role: DrMan owner; original member name unknown.
};

static_assert(offsetof(DrPixlRenderTarget, unknown3c8) == 0x3c8, "");

} // namespace ml
