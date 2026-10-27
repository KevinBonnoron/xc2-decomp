#pragma once
#include <stddef.h>

#include "types.h"

namespace grlib {
class CGLibRenderVolume;
} // namespace grlib

namespace ml {

class DrMan;
class DrPixlMan;
class DrPixlPostMan;

class DrPixlPostObj3dLut {
public:
  void update();
  void render(bool isFirst, bool isSecond);
  void renderLUT();
  void render_applyLUT(bool isFirst, bool isSecond);
  void render_updateLUT();

  DrMan *unknown00;         // Inferred role: driver manager; original member name unknown.
  DrPixlMan *unknown08;     // Inferred role: pixel manager; original member name unknown.
  DrPixlPostMan *unknown10; // Inferred role: post manager; original member name unknown.
  bool unknown18;           // Inferred role: LUT updated flag; original member name unknown.
  u8 _19[0x20 - 0x19];
  grlib::CGLibRenderVolume *unknown20[2]; // Inferred role: LUT volume targets; original member name unknown.
};

static_assert(offsetof(DrPixlPostObj3dLut, unknown18) == 0x18, "");
static_assert(offsetof(DrPixlPostObj3dLut, unknown20) == 0x20, "");

} // namespace ml
