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
  void setupTexture(void *work, int count, const u8 *table, const u8 *data);
  grlib::CGLibTextureBuffer *getTexture(int index);
  void releaseTexture();

  grlib::CGLibTextureBuffer *m_texture; // Inferred role: textures; named after the game accessor ml::DrEnvironmentTex::getTexture.
  s32 unknown08;                        // Inferred role: texture count; original member name unknown.
};

static_assert(offsetof(DrEnvironmentTex, unknown08) == 0x08, "");

} // namespace ml
