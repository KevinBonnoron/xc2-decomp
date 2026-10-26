#pragma once
#include <stddef.h>

#include "types.h"

namespace grlib {
class CGLibTextureBuffer;
} // namespace grlib

namespace ml {

class DrPixlPostObjTMAA {
public:
  void render();
  void update();
  void debugRender();
  grlib::CGLibTextureBuffer *getBloomTexture();

  u8 _00[0x30];
  grlib::CGLibTextureBuffer *m_bloomTexture[2];
};

static_assert(offsetof(DrPixlPostObjTMAA, m_bloomTexture) == 0x30, "");

} // namespace ml
