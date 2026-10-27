#pragma once
#include <stddef.h>

#include "types.h"

namespace ml {

class DrCalcClipObj {
public:
  void release();

  u8 _00[0x3c - 0x00];
  u32 unknown3c; // Inferred role: state flags; original member name unknown.
};

static_assert(offsetof(DrCalcClipObj, unknown3c) == 0x3c, "");

} // namespace ml
