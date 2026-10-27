#pragma once
#include <stddef.h>

#include "types.h"

namespace grlib {
class CGLibTextureBuffer;
} // namespace grlib

namespace ml {

class DrPixlRenderTarget;

class DrPixlPostObjSSR {
public:
  ~DrPixlPostObjSSR();
  void setClear();
  grlib::CGLibTextureBuffer *getReflectionTexture() const;

  u8 _00[0x18];
  u32 unknown18; // Inferred role: clear request; original member name unknown.
  u8 _1c[0x20 - 0x1c];
  DrPixlRenderTarget *unknown20; // Inferred role: render target; original member name unknown.
  DrPixlRenderTarget *m_reflectionTexture[2];
  DrPixlRenderTarget *unknown38; // Inferred role: render target; original member name unknown.
};

static_assert(offsetof(DrPixlPostObjSSR, unknown18) == 0x18, "");
static_assert(offsetof(DrPixlPostObjSSR, unknown20) == 0x20, "");
static_assert(offsetof(DrPixlPostObjSSR, m_reflectionTexture) == 0x28, "");
static_assert(offsetof(DrPixlPostObjSSR, unknown38) == 0x38, "");

} // namespace ml
