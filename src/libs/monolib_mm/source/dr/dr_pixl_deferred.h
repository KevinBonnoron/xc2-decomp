#pragma once
#include <stddef.h>

#include "types.h"

namespace grlib {
class CGLibTextureBuffer;
} // namespace grlib

namespace ml {

class DrMan;
class DrPixlRenderTarget;

class DrPixlDeferred {
public:
  void displayUpdate();
  void globalIBLRender();
  void lastDeferredRender();
  grlib::CGLibTextureBuffer *getShadowMapTexture() const;
  void shadowBuffBegin();
  void shadowBuffClear();
  DrPixlRenderTarget *getTemporalInputShadowMap();
  DrPixlRenderTarget *getTemporalOutputShadowMap();
  DrPixlRenderTarget *getTemporalOutputShadowMap() const;
  DrPixlRenderTarget *getTemporalHistoryShadowMap();

  u8 _00[0x08];
  DrMan *unknown08; // Inferred role: driver manager; original member name unknown.
  u8 _10[0x20 - 0x10];
  DrPixlRenderTarget *unknown20;    // Inferred role: temporal input shadow; original member name unknown.
  DrPixlRenderTarget *unknown28[2]; // Inferred role: temporal shadow buffers; original member name unknown.
};

static_assert(offsetof(DrPixlDeferred, unknown08) == 0x08, "");
static_assert(offsetof(DrPixlDeferred, unknown20) == 0x20, "");
static_assert(offsetof(DrPixlDeferred, unknown28) == 0x28, "");

} // namespace ml
