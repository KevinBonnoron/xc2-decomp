#pragma once
#include "types.h"

namespace ml {

class DrShdDataObj {
public:
  u8 _00[0x78 - 0x00];
};

static_assert(sizeof(DrShdDataObj) == 0x78, "");

} // namespace ml
