#pragma once
#include <stddef.h>

#include "mm_math/mm_vec3.h"
#include "types.h"

namespace grlib {
class CGLibRenderTarget;
} // namespace grlib

namespace ml {

class DrPixlPostObjVolume {
public:
  ~DrPixlPostObjVolume();
  void resetColorBuff();
  void calcColorBuff();
  void update();
  void releaseColorBuff();
  u8 _00[0x18 - 0x00];
  grlib::CGLibRenderTarget *unknown18; // Inferred role: render target; original member name unknown.
  grlib::CGLibRenderTarget *unknown20; // Inferred role: render target; original member name unknown.
  grlib::CGLibRenderTarget *unknown28; // Inferred role: render target; original member name unknown.
  mm::Vec3 unknown30;                  // Inferred role: pos; original member name unknown.
};

static_assert(offsetof(DrPixlPostObjVolume, unknown18) == 0x18, "");
static_assert(offsetof(DrPixlPostObjVolume, unknown30) == 0x30, "");

} // namespace ml
