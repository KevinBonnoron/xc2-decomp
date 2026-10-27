#pragma once
#include <stddef.h>

#include "types.h"

namespace grlib {
class CGLibRenderTarget;
} // namespace grlib

namespace ml {

class DrPixlPostObjFxAA {
public:
  void releaseColorBuff();

  u8 _00[0x18 - 0x00];
  grlib::CGLibRenderTarget *unknown18; // Inferred role: render target; original member name unknown.
};

static_assert(offsetof(DrPixlPostObjFxAA, unknown18) == 0x18, "");

} // namespace ml
