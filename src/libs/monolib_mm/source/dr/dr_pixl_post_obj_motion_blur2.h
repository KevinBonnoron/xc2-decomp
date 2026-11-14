#pragma once
#include <stddef.h>

#include "dr/dr_pixl_post_obj.h"
#include "types.h"

namespace grlib {
class CGLibVtxVertex;
} // namespace grlib

namespace ml {
class DrMan;
class DrPixlMan;
class DrPixlPostMan;
class DrPixlRenderTarget;

class DrPixlPostObjMotionBlur2 : public DrPixlPostObj {
public:
  DrPixlPostObjMotionBlur2(DrMan *drMan, DrPixlMan *pixlMan, DrPixlPostMan *postMan);
  ~DrPixlPostObjMotionBlur2();
  void resetColorBuff();
  void calcBludBuffColorBuff();
  void update();
  void render();
  void calcBlurWork();
  void calcObjMotionBlur();
  void renderCalcBlur();
  void lastRender();
  void calcVelocityBlur();
  void calcMaxVelocityPerTile();
  void calcBlurMask();
  void releaseColorBuff();
  void debugRender();

  f32 unknown18;                       // Inferred role: unknown, only cleared by the constructor; original member name unknown.
  f32 unknown1c;                       // Inferred role: unknown, only cleared by the constructor; original member name unknown.
  DrPixlRenderTarget *unknown20;       // Inferred role: render target; original member name unknown.
  DrPixlRenderTarget *unknown28;       // Inferred role: render target; original member name unknown.
  DrPixlRenderTarget *unknown30;       // Inferred role: render target; original member name unknown.
  DrPixlRenderTarget *unknown38;       // Inferred role: render target; original member name unknown.
  DrPixlRenderTarget *unknown40;       // Inferred role: render target; original member name unknown.
  DrPixlRenderTarget *unknown48;       // Inferred role: render target; original member name unknown.
  grlib::CGLibVtxVertex *unknown50[2]; // Inferred role: vertex buffers; original member name unknown.
  u32 unknown60;                       // Inferred role: vertex buffer index; original member name unknown.
  bool unknown64;                      // Inferred role: blur enable; original member name unknown.
  u8 _65[0x68 - 0x65];
};

static_assert(offsetof(DrPixlPostObjMotionBlur2, unknown18) == 0x18, "");
static_assert(offsetof(DrPixlPostObjMotionBlur2, unknown1c) == 0x1c, "");
static_assert(offsetof(DrPixlPostObjMotionBlur2, unknown20) == 0x20, "");
static_assert(offsetof(DrPixlPostObjMotionBlur2, unknown60) == 0x60, "");
static_assert(offsetof(DrPixlPostObjMotionBlur2, unknown48) == 0x48, "");
static_assert(offsetof(DrPixlPostObjMotionBlur2, unknown50) == 0x50, "");
static_assert(offsetof(DrPixlPostObjMotionBlur2, unknown64) == 0x64, "");
static_assert(sizeof(DrPixlPostObjMotionBlur2) == 0x68, "");

} // namespace ml
