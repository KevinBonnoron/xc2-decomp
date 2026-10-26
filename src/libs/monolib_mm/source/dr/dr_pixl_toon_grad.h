#pragma once
#include <stddef.h>

#include "types.h"

namespace grlib {
class CGLibRenderTarget;
class CGLibTextureBuffer;
} // namespace grlib

namespace ml {

class DrPixlToonGrad {
public:
  void render();
  void update();
  const grlib::CGLibTextureBuffer &getGradTex() const;
  const grlib::CGLibTextureBuffer &getDarkGradTex() const;

  u8 _00[0x10];
  grlib::CGLibRenderTarget *m_gradTex[2];
  grlib::CGLibRenderTarget *m_darkGradTex[2];
};

static_assert(offsetof(DrPixlToonGrad, m_gradTex) == 0x10, "");
static_assert(offsetof(DrPixlToonGrad, m_darkGradTex) == 0x20, "");

} // namespace ml
