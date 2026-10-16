#pragma once
#include "mm_mtl/singleton.h"
#include "types.h"
#include <stddef.h>

namespace btl {

class BtlSystemBalanceAccess : public mm::mtl::PtrSingleton<BtlSystemBalanceAccess> {
public:
  BtlSystemBalanceAccess();
  ~BtlSystemBalanceAccess();
  static void Create();
  void Initialize();
  static void Destroy();
  void Finalize();
  bool IsOneBoundEnemy(u32 enemy) const;
  int IsSpSizeEnemy(u32 enemy) const;
  bool IsSpKizunaLineEnemy(u32 enemy) const;
  bool IsSpForceLandEnemy(u32 enemy) const;
  bool IsSpBenkeiWeapondEnemy(u32 enemy) const;

  u8 _08[0x10 - 0x08];
  f32 resistantAttrDamageRate;
  u8 _14[0x40 - 0x14];
  u8 resistantAttrMaxHP;
  u8 _41[0xb6 - 0x41];
  u16 oneBoundEnemies[2];
  u16 spSizeEnemies[1];
  u16 spKizunaLineEnemies[2];
  u16 spForceLandEnemies[2];
  u16 spBenkeiWeaponEnemies[1];
  u8 _c6[0xdc - 0xc6];
  f32 dyingHpRate;
  u8 _e0[0xf0 - 0xe0];
};

static_assert(offsetof(BtlSystemBalanceAccess, resistantAttrMaxHP) == 0x40, "");
static_assert(offsetof(BtlSystemBalanceAccess, oneBoundEnemies) == 0xb6, "");
static_assert(offsetof(BtlSystemBalanceAccess, spSizeEnemies) == 0xba, "");
static_assert(offsetof(BtlSystemBalanceAccess, spKizunaLineEnemies) == 0xbc, "");
static_assert(offsetof(BtlSystemBalanceAccess, spForceLandEnemies) == 0xc0, "");
static_assert(offsetof(BtlSystemBalanceAccess, spBenkeiWeaponEnemies) == 0xc4, "");
static_assert(offsetof(BtlSystemBalanceAccess, dyingHpRate) == 0xdc, "");
static_assert(sizeof(BtlSystemBalanceAccess) == 0xf0, "");

} // namespace btl
