#pragma once
#include <stddef.h>

#include "types.h"

namespace grlib {
class CGLibTextureBuffer;
} // namespace grlib

namespace ml {

class DrMan;
class DrPixlRenderTarget;

class DrPixlToonGrad {
public:
  explicit DrPixlToonGrad(DrMan *drMan);
  ~DrPixlToonGrad();
  void render();
  void debugRender();
  void update();
  const grlib::CGLibTextureBuffer &getGradTex() const;
  const grlib::CGLibTextureBuffer &getDarkGradTex() const;

  DrMan *unknown00; // Inferred role: driver manager; original member name unknown.
  bool unknown08;   // Inferred role: gradient clear flag; original member name unknown.
  u8 _09[0x10 - 0x09];
  DrPixlRenderTarget *m_gradTex[2];
  DrPixlRenderTarget *m_darkGradTex[2];
};

static_assert(offsetof(DrPixlToonGrad, unknown08) == 0x08, "");
static_assert(offsetof(DrPixlToonGrad, m_gradTex) == 0x10, "");
static_assert(offsetof(DrPixlToonGrad, m_darkGradTex) == 0x20, "");

} // namespace ml
