#pragma once
#include "types.h"

namespace gf {
namespace enemy {

class GfEnemyBattleProperty {
public:
  GfEnemyBattleProperty();

private:
  u8 _00[0x10 - 0x00];
  u32 _10;
  u8 _14[0x1e - 0x14];
  u16 _1e;
};

} // namespace enemy
} // namespace gf
