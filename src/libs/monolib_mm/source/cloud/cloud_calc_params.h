#pragma once
#include <stddef.h>

#include "mm_math/mm_col3.h"
#include "types.h"

namespace cloud {

class CloudCalcParams {
public:
  u8 _000[0x194 - 0x000];
  f32 m_height;
  u8 _198[0x19c - 0x198];
  u32 m_cldNum;
  u8 _1a0[0x1b8 - 0x1a0];
  mm::Col3 m_planeCols[2];
};

static_assert(offsetof(CloudCalcParams, m_height) == 0x194, "");
static_assert(offsetof(CloudCalcParams, m_cldNum) == 0x19c, "");
static_assert(offsetof(CloudCalcParams, m_planeCols) == 0x1b8, "");

} // namespace cloud
