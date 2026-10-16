#pragma once
#include <stddef.h>

#include "types.h"

namespace ml {

class DrCalcTexStreamMan {
public:
  enum Flag {
    FLAG_CACHER_CLEAR_MODE = 1 << 4,
  };

  u8 _0000[0x2068 - 0x0000];
  u32 m_flags;
};

static_assert(offsetof(DrCalcTexStreamMan, m_flags) == 0x2068, "");

} // namespace ml
