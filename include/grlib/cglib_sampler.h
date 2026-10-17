#pragma once
#include "types.h"

namespace grlib {

class CGLibSampler {
public:
  ~CGLibSampler();

  u8 _00[0x20 - 0x00];
};

static_assert(sizeof(CGLibSampler) == 0x20, "");

} // namespace grlib
