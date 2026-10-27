#pragma once
#include <stddef.h>

#include "grlib/cglib_render_target_1d.h"
#include "types.h"

namespace ml {

class DrMan;

class DrPixlRenderTarget1D : public grlib::CGLibRenderTarget1D {
public:
  explicit DrPixlRenderTarget1D(DrMan *man);
  ~DrPixlRenderTarget1D();
  void debugRender(int x, int y, int width, int height, bool isAlpha, bool isDepth);
  void debugRenderCh(int x, int y, int width, int height, u32 channel);

  DrMan *unknownc0; // Inferred role: DrMan owner; original member name unknown.
};

static_assert(offsetof(DrPixlRenderTarget1D, unknownc0) == 0xc0, "");

} // namespace ml
