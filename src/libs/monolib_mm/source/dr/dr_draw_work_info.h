#pragma once
#include "types.h"

namespace ml {

class IDrDrawWorkInfo {
public:
  u8 _000[0x580];
};

static_assert(sizeof(IDrDrawWorkInfo) == 0x580, "");

} // namespace ml
