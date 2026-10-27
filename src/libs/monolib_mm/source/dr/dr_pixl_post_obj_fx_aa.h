#pragma once
#include <stddef.h>

#include "types.h"

namespace grlib {
class CGLibRenderTarget;
} // namespace grlib

namespace ml {

class DrMan;

class DrPixlPostObjFxAA {
public:
  ~DrPixlPostObjFxAA();
  void releaseColorBuff();
  void update();
  void resetColorBuff();
  void render();
  void calcScale();

  DrMan *unknown00; // Inferred role: driver manager; original member name unknown.
  u8 _08[0x18 - 0x08];
  grlib::CGLibRenderTarget *unknown18; // Inferred role: render target; original member name unknown.
  f32 unknown20;                       // Inferred role: screen width; original member name unknown.
  f32 unknown24;                       // Inferred role: screen height; original member name unknown.
};

static_assert(offsetof(DrPixlPostObjFxAA, unknown18) == 0x18, "");
static_assert(offsetof(DrPixlPostObjFxAA, unknown20) == 0x20, "");
static_assert(offsetof(DrPixlPostObjFxAA, unknown24) == 0x24, "");

} // namespace ml
