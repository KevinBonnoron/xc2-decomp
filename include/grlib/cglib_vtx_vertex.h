#pragma once
#include "types.h"

namespace grlib {

class CGLibVtxVertex {
public:
  u8 _00[0x28 - 0x00];
};

static_assert(sizeof(CGLibVtxVertex) == 0x28, "");

} // namespace grlib
