#pragma once
#include <stddef.h>

#include "types.h"

namespace ml {

class DrPixlPostObjMotionBlur {
public:
  u8 _00[0x28 - 0x00];
  void *unknown28; // Inferred role: velocity map; original member name unknown.
};

static_assert(offsetof(DrPixlPostObjMotionBlur, unknown28) == 0x28, "");

} // namespace ml
