#pragma once
#include <stddef.h>

#include "types.h"

namespace grlib {
class CGLibTextureBuffer;
} // namespace grlib

namespace ml {

class DrMan;
class DrPixlMan;
class DrPixlRenderTarget;

class DrPixlDeferred {
public:
  DrPixlDeferred(DrMan *man, DrPixlMan *pixlMan);
  ~DrPixlDeferred();
  void resetColorBuff();
  void displayUpdate();
  void globalIBLRender();
  void lastDeferredRender();
  void fastDeferredRender(int cate);
  bool shadowTexRender(int cate);
  void shadowLightRender();
  void shadowCharacterRender();
  void shadowBuffCacheRender();
  bool shadowBuffDefRender();
  void debugRender();
  grlib::CGLibTextureBuffer *getShadowMapTexture() const;
  void shadowBuffBegin();
  void shadowBuffClear();
  void releaseColorBuff();
  void lgtCalcRender();
  DrPixlRenderTarget *getTemporalInputShadowMap();
  DrPixlRenderTarget *getTemporalOutputShadowMap();
  DrPixlRenderTarget *getTemporalOutputShadowMap() const;
  DrPixlRenderTarget *getTemporalHistoryShadowMap();

  u8 _00[0x08 - 0x00];
  DrMan *unknown08; // Inferred role: driver manager; original member name unknown.
  u8 _10[0x18 - 0x10];
  DrPixlMan *unknown18; // Inferred role: pixl man; original member name unknown.
  DrPixlRenderTarget *m_temporalInputShadowMap;
  DrPixlRenderTarget *unknown28[2]; // Inferred role: temporal shadow buffers; original member name unknown.
  s16 unknown38;                    // Inferred role: temporal shadow buffer width; original member name unknown.
  s16 unknown3a;                    // Inferred role: temporal shadow buffer height; original member name unknown.
};

static_assert(offsetof(DrPixlDeferred, unknown08) == 0x08, "");
static_assert(offsetof(DrPixlDeferred, unknown18) == 0x18, "");
static_assert(offsetof(DrPixlDeferred, m_temporalInputShadowMap) == 0x20, "");
static_assert(offsetof(DrPixlDeferred, unknown28) == 0x28, "");
static_assert(offsetof(DrPixlDeferred, unknown38) == 0x38, "");
static_assert(offsetof(DrPixlDeferred, unknown3a) == 0x3a, "");

} // namespace ml
