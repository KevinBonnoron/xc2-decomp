#pragma once
#include <stddef.h>

#include "grlib/cglib_dbl_uniform_block.h"
#include "types.h"

namespace ml {

class DrPixlShadowObj {
public:
  u8 _00[0x08 - 0x00];
  grlib::CGLibDblUniformBlock unknown08; // Inferred role: shadow uniform; original member name unknown.
};

static_assert(offsetof(DrPixlShadowObj, unknown08) == 0x08, "");

} // namespace ml
