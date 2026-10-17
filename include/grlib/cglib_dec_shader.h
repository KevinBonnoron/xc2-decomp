#pragma once
#include "types.h"

namespace grlib {

class CGLibDecShader {
public:
  CGLibDecShader();
  ~CGLibDecShader();

  u8 _00[0x68 - 0x00];
};

static_assert(sizeof(CGLibDecShader) == 0x68, "");

} // namespace grlib
