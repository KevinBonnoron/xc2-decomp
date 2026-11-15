#pragma once
#include <stddef.h>

#include "dr/dr_pixl_post_obj.h"
#include "types.h"

namespace grlib {
class CGLibRenderTarget;
} // namespace grlib

namespace ml {

class DrMan;
class DrPixlMan;
class DrPixlPostMan;
class DrPixlRenderTarget;

class DrPixlPostObjBloom : public DrPixlPostObj {
public:
  enum DownScaleType {
    DOWN_SCALE_TYPE_UNKNOWN_0 = 0,
    DOWN_SCALE_TYPE_UNKNOWN_1 = 1,
    DOWN_SCALE_TYPE_UNKNOWN_2 = 2,
  };

  static f32 BLOOMTEX_SCALE;
  static const f32 BLOOMTEX_SCALE_OLD; // Name from the game symbol _ZN2ml18DrPixlPostObjBloom18BLOOMTEX_SCALE_OLDE; also in torna and xc1de.
  static const f32 BLOOMTEX_SCALE_NEW; // Name from the game symbol _ZN2ml18DrPixlPostObjBloom18BLOOMTEX_SCALE_NEWE; also in torna and xc1de.

  DrPixlPostObjBloom(DrMan *drMan, DrPixlMan *pixlMan, DrPixlPostMan *postMan);
  ~DrPixlPostObjBloom();
  void resetColorBuff(bool isForce);
  void releaseBloomTexture();
  void update();
  void calcRender();
  void releaseColorBuff(bool isForce);
  grlib::CGLibRenderTarget *getLgtDownTarget();
  void calculateDownScale();
  void calculateDownScale_TwoPass();
  void calculateGaussBlur();
  void calculateDownScaleImpl(DownScaleType type);
  void calculateGaussBlurImplPS();
  void calculateFlareBuff();
  void calculateLensFlare();
  void bloomLensFlare();
  void debugRender();
  void calcCollectRender(bool isVolume);

  // Decision 2026-11-14 #35: the constructor allocates a DrPixlRenderTarget for every one of these members and debugRender inlines
  // DrPixlRenderTarget::debugRender (0x710083be9c, which calls DrPixlMan::debugRender), so they are typed DrPixlRenderTarget *; no downcast
  // is needed to reach its methods (DrPixlPostObjBloom::debugRender is at 0x71008552c8).
  DrPixlRenderTarget *unknown18;    // Inferred role: render target; original member name unknown.
  DrPixlRenderTarget *unknown20;    // Inferred role: render target; original member name unknown.
  DrPixlRenderTarget *unknown28;    // Inferred role: render target; original member name unknown.
  DrPixlRenderTarget *unknown30;    // Inferred role: render target; original member name unknown.
  DrPixlRenderTarget *unknown38[5]; // Inferred role: render targets; original member name unknown.
  DrPixlRenderTarget *unknown60[5]; // Inferred role: render targets; original member name unknown.
  u8 _88[0x90 - 0x88];
  u32 unknown90; // Inferred role: update request; original member name unknown.
  u32 unknown94; // Inferred role: flags; original member name unknown.
  DrPixlRenderTarget *m_lgtDownTarget[2];
  s32 unknowna8; // Inferred role: bloom scale type; original member name unknown.
};

static_assert(offsetof(DrPixlPostObjBloom, unknown18) == 0x18, "");
static_assert(offsetof(DrPixlPostObjBloom, unknown38) == 0x38, "");
static_assert(offsetof(DrPixlPostObjBloom, unknown60) == 0x60, "");
static_assert(offsetof(DrPixlPostObjBloom, unknown90) == 0x90, "");
static_assert(offsetof(DrPixlPostObjBloom, m_lgtDownTarget) == 0x98, "");
static_assert(offsetof(DrPixlPostObjBloom, unknown94) == 0x94, "");
static_assert(offsetof(DrPixlPostObjBloom, unknowna8) == 0xa8, "");

} // namespace ml
