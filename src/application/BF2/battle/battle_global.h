#pragma once
#include "mm_mtl/singleton.h"
#include "types.h"
#include <stddef.h>

namespace btl {

class BattleGlobal : public mm::mtl::PtrSingleton<BattleGlobal> {
public:
  int GetElementalComboStage(int combo) const;

  u8 _08[0x5b8e - 0x08];
  u16 enemyKillNum;
};

static_assert(offsetof(BattleGlobal, enemyKillNum) == 0x5b8e, "");

} // namespace btl
