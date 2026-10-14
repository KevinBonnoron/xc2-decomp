#pragma once
#include "types.h"

namespace gf {

enum {
  PAUSE_BIT_SYSTEM = 1 << 0,
};

class GfPause {
public:
  static bool isPause(u32 pauseBits);
};

} // namespace gf
