#pragma once
#include <stddef.h>

#include "types.h"

namespace grlib {
class CGLibRenderTarget;
class CGLibTextureBuffer;
} // namespace grlib

namespace ml {

class DrMan;

class DrPixlRenderTarget;

class DrPixlShadowRaytrace {
public:
  enum BlurAxis {
    BLUR_AXIS_UNKNOWN_1 = 1,
    BLUR_AXIS_UNKNOWN_2 = 2,
  };

  void update();
  void releaseColorBuff();
  void render_beforeTemporal();
  void raytracePass();
  void temporalFiltering();
  void blurPass();
  void blurPassSub(BlurAxis axis, DrPixlRenderTarget *source, DrPixlRenderTarget *destination);
  grlib::CGLibRenderTarget *getTemporalOutputTexture();
  grlib::CGLibRenderTarget *getTemporalHistoryTexture();
  grlib::CGLibTextureBuffer *getScreenSpaceShadow() const;

  DrMan *unknown00; // Inferred role: driver manager; original member name unknown.
  u8 _08[0x10 - 0x08];
  bool unknown10; // Inferred role: blur enable; original member name unknown.
  u8 _11[0x18 - 0x11];
  DrPixlRenderTarget *unknown18;          // Inferred role: render target; original member name unknown.
  grlib::CGLibRenderTarget *unknown20[2]; // Inferred role: temporal textures; original member name unknown.
  DrPixlRenderTarget *unknown30;          // Inferred role: render target; original member name unknown.
  DrPixlRenderTarget *unknown38;          // Inferred role: render target; original member name unknown.
};

static_assert(offsetof(DrPixlShadowRaytrace, unknown10) == 0x10, "");
static_assert(offsetof(DrPixlShadowRaytrace, unknown18) == 0x18, "");
static_assert(offsetof(DrPixlShadowRaytrace, unknown20) == 0x20, "");
static_assert(offsetof(DrPixlShadowRaytrace, unknown30) == 0x30, "");
static_assert(offsetof(DrPixlShadowRaytrace, unknown38) == 0x38, "");

} // namespace ml
