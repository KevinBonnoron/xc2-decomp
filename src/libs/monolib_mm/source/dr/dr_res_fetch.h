#pragma once
#include "types.h"

namespace ml {

class DrResFetch {
public:
  u8 _00[0x10 - 0x00];
};

static_assert(sizeof(DrResFetch) == 0x10, "");

} // namespace ml
