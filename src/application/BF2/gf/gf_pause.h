#pragma once
#include "types.h"

namespace gf {

enum {
  PAUSE_BIT_SYSTEM = 1 << 0,
  PAUSE_BIT_GAME = 1 << 1,
  PAUSE_BIT_FIELD_TIME = 1 << 4,
};

class GfPause {
public:
  static bool isPause(u32 pauseBits);
};

} // namespace gf
