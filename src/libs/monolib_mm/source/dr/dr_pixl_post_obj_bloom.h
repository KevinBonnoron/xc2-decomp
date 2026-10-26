#pragma once
#include <stddef.h>

#include "types.h"

namespace grlib {
class CGLibRenderTarget;
} // namespace grlib

namespace ml {

class DrPixlPostObjBloom {
public:
  void update();
  grlib::CGLibRenderTarget *getLgtDownTarget();

  u8 _00[0x90];
  u32 unknown90; // Inferred role: update request; original member name unknown.
  u8 _94[0x98 - 0x94];
  grlib::CGLibRenderTarget *unknown98[2]; // Inferred role: lgt down targets; original member name unknown.
};

static_assert(offsetof(DrPixlPostObjBloom, unknown90) == 0x90, "");
static_assert(offsetof(DrPixlPostObjBloom, unknown98) == 0x98, "");

} // namespace ml
