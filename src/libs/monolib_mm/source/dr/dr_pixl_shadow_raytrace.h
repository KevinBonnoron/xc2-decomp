#pragma once
#include <stddef.h>

#include "types.h"

namespace grlib {
class CGLibRenderTarget;
class CGLibTextureBuffer;
} // namespace grlib

namespace ml {

class DrMan;

class DrPixlShadowRaytrace {
public:
  void update();
  void releaseColorBuff();
  grlib::CGLibRenderTarget *getTemporalOutputTexture();
  grlib::CGLibRenderTarget *getTemporalHistoryTexture();
  grlib::CGLibTextureBuffer *getScreenSpaceShadow() const;

  DrMan *unknown00; // Inferred role: driver manager; original member name unknown.
  u8 _08[0x18 - 0x08];
  grlib::CGLibRenderTarget *unknown18;    // Inferred role: render target; original member name unknown.
  grlib::CGLibRenderTarget *unknown20[2]; // Inferred role: temporal textures; original member name unknown.
  grlib::CGLibRenderTarget *unknown30;    // Inferred role: render target; original member name unknown.
  grlib::CGLibRenderTarget *unknown38;    // Inferred role: render target; original member name unknown.
};

static_assert(offsetof(DrPixlShadowRaytrace, unknown18) == 0x18, "");
static_assert(offsetof(DrPixlShadowRaytrace, unknown20) == 0x20, "");
static_assert(offsetof(DrPixlShadowRaytrace, unknown30) == 0x30, "");
static_assert(offsetof(DrPixlShadowRaytrace, unknown38) == 0x38, "");

} // namespace ml
