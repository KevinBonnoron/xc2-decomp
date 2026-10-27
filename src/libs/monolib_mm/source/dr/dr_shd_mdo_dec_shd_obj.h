#pragma once
#include <stddef.h>

#include "types.h"

namespace ml {

class DrShdMdoDecShdObj {
public:
  void update();

  u8 _00[0x08 - 0x00];
  DrShdMdoDecShdObj *unknown08; // Inferred role: next shader object; original member name unknown.
};

static_assert(offsetof(DrShdMdoDecShdObj, unknown08) == 0x08, "");

} // namespace ml
