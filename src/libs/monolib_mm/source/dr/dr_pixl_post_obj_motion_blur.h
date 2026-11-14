#pragma once
#include <stddef.h>

#include "dr/dr_pixl_post_obj.h"
#include "grlib/cglib_dbl_uniform_block.h"
#include "types.h"

namespace grlib {
class CGLibRenderTarget;
} // namespace grlib

namespace ml {
class DrMan;
class DrPixlMan;
class DrPixlPostMan;

class DrPixlPostObjMotionBlur : public DrPixlPostObj {
public:
  DrPixlPostObjMotionBlur(DrMan *drMan, DrPixlMan *pixlMan, DrPixlPostMan *postMan);
  ~DrPixlPostObjMotionBlur();
  void update();
  void render();
  void debugRender();
  void resetColorBuff();
  void calcBludBuffColorBuff();
  void releaseColorBuff();
  void calcBlurWork();
  void calcObjMotionBlur();
  void renderCalcBlur();
  void lastRender();
  void calcVelocityBlur();

  f32 unknown18;                         // Inferred role: unknown, only cleared by the constructor; original member name unknown.
  f32 unknown1c;                         // Inferred role: unknown, only cleared by the constructor; original member name unknown.
  grlib::CGLibRenderTarget *unknown20;   // Inferred role: render target; original member name unknown.
  grlib::CGLibRenderTarget *unknown28;   // Inferred role: velocity map; original member name unknown.
  grlib::CGLibRenderTarget *unknown30;   // Inferred role: render target; original member name unknown.
  grlib::CGLibDblUniformBlock unknown38; // Inferred role: uniform block; original member name unknown.
};

static_assert(offsetof(DrPixlPostObjMotionBlur, unknown18) == 0x18, "");
static_assert(offsetof(DrPixlPostObjMotionBlur, unknown1c) == 0x1c, "");
static_assert(offsetof(DrPixlPostObjMotionBlur, unknown20) == 0x20, "");
static_assert(offsetof(DrPixlPostObjMotionBlur, unknown28) == 0x28, "");
static_assert(offsetof(DrPixlPostObjMotionBlur, unknown30) == 0x30, "");
static_assert(offsetof(DrPixlPostObjMotionBlur, unknown38) == 0x38, "");

} // namespace ml
