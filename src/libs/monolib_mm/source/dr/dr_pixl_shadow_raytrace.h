#pragma once
#include <stddef.h>

#include "types.h"

namespace grlib {
class CGLibRenderTarget;
class CGLibTextureBuffer;
} // namespace grlib

namespace ml {

class DrPixlShadowRaytrace {
public:
  void update();
  grlib::CGLibRenderTarget *getTemporalOutputTexture();
  grlib::CGLibRenderTarget *getTemporalHistoryTexture();
  grlib::CGLibTextureBuffer *getScreenSpaceShadow() const;

  u8 _00[0x20];
  grlib::CGLibRenderTarget *unknown20[2]; // Inferred role: temporal textures; original member name unknown.
};

static_assert(offsetof(DrPixlShadowRaytrace, unknown20) == 0x20, "");

} // namespace ml
