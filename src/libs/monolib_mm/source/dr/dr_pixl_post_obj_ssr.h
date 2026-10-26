#pragma once
#include <stddef.h>

#include "types.h"

namespace grlib {
class CGLibTextureBuffer;
} // namespace grlib

namespace ml {

class DrPixlPostObjSSR {
public:
  void setClear();
  grlib::CGLibTextureBuffer *getReflectionTexture() const;

  u8 _00[0x18];
  u32 unknown18; // Inferred role: clear request; original member name unknown.
  u8 _1c[0x28 - 0x1c];
  grlib::CGLibTextureBuffer *m_reflectionTexture[2];
};

static_assert(offsetof(DrPixlPostObjSSR, unknown18) == 0x18, "");
static_assert(offsetof(DrPixlPostObjSSR, m_reflectionTexture) == 0x28, "");

} // namespace ml
