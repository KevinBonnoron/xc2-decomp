#pragma once
#include <stddef.h>

#include "dr/dr_pixl_post_obj.h"
#include "types.h"

namespace mm {
struct Vec4;
} // namespace mm

namespace ml {

class DrMan;
class DrPixlMan;
class DrPixlPostMan;
class DrPixlRenderTarget;

class DrPixlPostObjTSSAO : public DrPixlPostObj {
public:
  enum BlurAxis {
    BLUR_AXIS_UNKNOWN_1 = 1,
    BLUR_AXIS_UNKNOWN_2 = 2,
  };

  DrPixlPostObjTSSAO(DrMan *drMan, DrPixlMan *pixlMan, DrPixlPostMan *postMan);
  ~DrPixlPostObjTSSAO();
  void resetColorBuff(bool isForce);
  void render_beforeTemporal();
  void passQuaterNormal();
  void passSSAO();
  void passPrevBlur();
  void passTemporalFiltering();
  void render_afterTemporal();
  void passPostBlur();
  void passUpScaling();
  void passBlur_Sub(BlurAxis axis, f32 strength, DrPixlRenderTarget *source, DrPixlRenderTarget *destination, bool flag);
  void passUpScaleToMiddle();
  void update();
  void releaseColorBuff();
  void calcFragCoordToUV(mm::Vec4 &uv, f32 width, f32 height);
  void calcFragCoordToScreen(mm::Vec4 &screen, f32 width, f32 height);
  void debugRender();

  u32 unknown18;                    // Inferred role: flags; original member name unknown.
  DrPixlRenderTarget *unknown20;    // Inferred role: render target; original member name unknown.
  DrPixlRenderTarget *unknown28[2]; // Inferred role: render targets per buffer; original member name unknown.
  DrPixlRenderTarget *unknown38;    // Inferred role: render target; original member name unknown.
  DrPixlRenderTarget *unknown40;    // Inferred role: render target; original member name unknown.
  DrPixlRenderTarget *unknown48;    // Inferred role: render target; original member name unknown.
  DrPixlRenderTarget *unknown50[2]; // Inferred role: render targets per buffer; original member name unknown.
  DrPixlRenderTarget *unknown60;    // Inferred role: render target; original member name unknown.
  DrPixlRenderTarget *unknown68;    // Inferred role: render target; original member name unknown.
  s32 unknown70;                    // Inferred role: scale; original member name unknown.
};

static_assert(offsetof(DrPixlPostObjTSSAO, unknown18) == 0x18, "");
static_assert(offsetof(DrPixlPostObjTSSAO, unknown20) == 0x20, "");
static_assert(offsetof(DrPixlPostObjTSSAO, unknown28) == 0x28, "");
static_assert(offsetof(DrPixlPostObjTSSAO, unknown38) == 0x38, "");
static_assert(offsetof(DrPixlPostObjTSSAO, unknown40) == 0x40, "");
static_assert(offsetof(DrPixlPostObjTSSAO, unknown48) == 0x48, "");
static_assert(offsetof(DrPixlPostObjTSSAO, unknown50) == 0x50, "");
static_assert(offsetof(DrPixlPostObjTSSAO, unknown60) == 0x60, "");
static_assert(offsetof(DrPixlPostObjTSSAO, unknown68) == 0x68, "");
static_assert(offsetof(DrPixlPostObjTSSAO, unknown70) == 0x70, "");

} // namespace ml
