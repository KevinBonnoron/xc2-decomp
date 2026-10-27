#pragma once
#include <stddef.h>

#include "types.h"

namespace grlib {
class CGLibTextureBuffer;
} // namespace grlib

namespace ml {

class DrMan;
class DrPixlRenderTarget;

class DrPixlPostObjTMAA {
public:
  ~DrPixlPostObjTMAA();
  void render();
  void update();
  void debugRender();
  void releaseColorBuff();
  grlib::CGLibTextureBuffer *getBloomTexture();

  DrMan *unknown00; // Inferred role: driver manager; original member name unknown.
  u8 _08[0x20 - 0x08];
  DrPixlRenderTarget *unknown20[2]; // Inferred role: render targets; original member name unknown.
  DrPixlRenderTarget *m_bloomTexture[2];
};

static_assert(offsetof(DrPixlPostObjTMAA, unknown00) == 0x00, "");
static_assert(offsetof(DrPixlPostObjTMAA, unknown20) == 0x20, "");
static_assert(offsetof(DrPixlPostObjTMAA, m_bloomTexture) == 0x30, "");

} // namespace ml
