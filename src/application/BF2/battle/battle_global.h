#pragma once
#include "mm_mtl/singleton.h"
#include "types.h"
#include <stddef.h>

namespace mm {
struct Vec3;
}

namespace gf {
struct GF_OBJ_HANDLE;
}

namespace btl {

class BattleGlobal : public mm::mtl::PtrSingleton<BattleGlobal> {
public:
  int GetElementalComboStage(int combo) const;
  gf::GF_OBJ_HANDLE *GetLinkJoinEnemyHandle(const mm::Vec3 &position);

  u8 _08[0x5b8e - 0x08];
  u16 enemyKillNum;
};

static_assert(offsetof(BattleGlobal, enemyKillNum) == 0x5b8e, "");

} // namespace btl
