#pragma once
#include "types.h"

namespace gf {

struct SDataGame {
  u8 _0[0x10ad48];
  u32 assurePoint;
  u32 assureCount;
  u16 rareBladeAppearType;
  u8 _10ad52[0x10ae7d - 0x10ad52];
  u8 hikariCurrent;
};

} // namespace gf
