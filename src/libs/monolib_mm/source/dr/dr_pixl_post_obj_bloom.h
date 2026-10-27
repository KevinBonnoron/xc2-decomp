#pragma once
#include <stddef.h>

#include "types.h"

namespace grlib {
class CGLibRenderTarget;
} // namespace grlib

namespace ml {

class DrMan;

class DrPixlPostObjBloom {
public:
  void update();
  void releaseColorBuff(bool isForce);
  grlib::CGLibRenderTarget *getLgtDownTarget();

  DrMan *unknown00; // Inferred role: driver manager; original member name unknown.
  u8 _08[0x18 - 0x08];
  grlib::CGLibRenderTarget *unknown18; // Inferred role: render target; original member name unknown.
  grlib::CGLibRenderTarget *unknown20; // Inferred role: render target; original member name unknown.
  grlib::CGLibRenderTarget *unknown28; // Inferred role: render target; original member name unknown.
  grlib::CGLibRenderTarget *unknown30; // Inferred role: render target; original member name unknown.
  grlib::CGLibRenderTarget *unknown38; // Inferred role: render target; original member name unknown.
  grlib::CGLibRenderTarget *unknown40; // Inferred role: render target; original member name unknown.
  grlib::CGLibRenderTarget *unknown48; // Inferred role: render target; original member name unknown.
  grlib::CGLibRenderTarget *unknown50; // Inferred role: render target; original member name unknown.
  grlib::CGLibRenderTarget *unknown58; // Inferred role: render target; original member name unknown.
  grlib::CGLibRenderTarget *unknown60; // Inferred role: render target; original member name unknown.
  grlib::CGLibRenderTarget *unknown68; // Inferred role: render target; original member name unknown.
  grlib::CGLibRenderTarget *unknown70; // Inferred role: render target; original member name unknown.
  grlib::CGLibRenderTarget *unknown78; // Inferred role: render target; original member name unknown.
  grlib::CGLibRenderTarget *unknown80; // Inferred role: render target; original member name unknown.
  u8 _88[0x90 - 0x88];
  u32 unknown90; // Inferred role: update request; original member name unknown.
  u8 _94[0x98 - 0x94];
  grlib::CGLibRenderTarget *unknown98[2]; // Inferred role: lgt down targets; original member name unknown.
};

static_assert(offsetof(DrPixlPostObjBloom, unknown18) == 0x18, "");
static_assert(offsetof(DrPixlPostObjBloom, unknown80) == 0x80, "");
static_assert(offsetof(DrPixlPostObjBloom, unknown90) == 0x90, "");
static_assert(offsetof(DrPixlPostObjBloom, unknown98) == 0x98, "");

} // namespace ml
