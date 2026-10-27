#pragma once
#include <stddef.h>

#include "types.h"

namespace grlib {
class CGLibTextureBuffer;
} // namespace grlib

namespace ml {

class DrPixlRenderTarget;

class DrPixlPostObjTMAA {
public:
  ~DrPixlPostObjTMAA();
  void render();
  void update();
  void debugRender();
  grlib::CGLibTextureBuffer *getBloomTexture();

  u8 _00[0x20];
  DrPixlRenderTarget *unknown20; // Inferred role: render target; original member name unknown.
  DrPixlRenderTarget *unknown28; // Inferred role: render target; original member name unknown.
  DrPixlRenderTarget *m_bloomTexture[2];
};

static_assert(offsetof(DrPixlPostObjTMAA, unknown20) == 0x20, "");
static_assert(offsetof(DrPixlPostObjTMAA, m_bloomTexture) == 0x30, "");

} // namespace ml
