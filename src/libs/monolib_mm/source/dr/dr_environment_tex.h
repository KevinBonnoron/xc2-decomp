#pragma once
#include <stddef.h>

#include "types.h"

namespace grlib {
class CGLibTextureBuffer;
} // namespace grlib

namespace ml {

class DrEnvironmentTex {
public:
  DrEnvironmentTex();
  static int getTextureWork(int count);
  grlib::CGLibTextureBuffer *getTexture(int index);
  void releaseTexture();

  grlib::CGLibTextureBuffer *unknown00; // Inferred role: textures; original member name unknown.
  s32 unknown08;                        // Inferred role: texture count; original member name unknown.
};

static_assert(offsetof(DrEnvironmentTex, unknown08) == 0x08, "");

} // namespace ml
