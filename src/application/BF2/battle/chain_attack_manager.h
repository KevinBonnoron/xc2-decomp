#pragma once
#include "mm_mtl/singleton.h"
#include "types.h"
#include <stddef.h>

namespace fw {
struct UpdateInfo;
}

namespace gf {
struct GF_OBJ_HANDLE;
}

namespace btl {

class ChainAttackManager : public mm::mtl::PtrSingleton<ChainAttackManager> {
public:
  enum STATE {
    STATE_NONE = 0,
    STATE_START_WAIT = 1,
    STATE_SELECT_ACTION = 9,
    STATE_RESULT = 51,
  };

  struct SP_ATTACK_BLADE_DATA {
    f32 recast;
    s8 blade;
  };

  struct SP_ATTACK_DATA {
    SP_ATTACK_BLADE_DATA blades[3];
    u8 level;
  };

  void Initialize();
  static void Destroy();
  void Finalize();
  void Reset(int);
  static void PreUpdate(const fw::UpdateInfo &updateInfo);
  void PreUpdateProc(const fw::UpdateInfo &updateInfo);
  static void Update(const fw::UpdateInfo &updateInfo);
  void UpdateProc(const fw::UpdateInfo &updateInfo);
  void AddDamageRate(int rate);
  void ModifyPosition();
  void ModifyPositionDriver(gf::GF_OBJ_HANDLE *driver);
  void ModifyPositionBlade(gf::GF_OBJ_HANDLE *driver, gf::GF_OBJ_HANDLE *blade);
  int GetSpAttackLevel(int group) const;
  f32 GetSpAttackRecast(int group, int blade) const;
  int GetOrderAttr(int order) const;
  bool IsProc(bool isExcludeStartWait) const;
  bool IsResult() const;
  void AddTotalDamage(u32 damage);
  int GetGroupIndex() const;
  bool IsStartWait() const;
  bool IsSelectAction() const;
  bool IsStopTime() const;
  bool IsTargetDead() const;

  gf::GF_OBJ_HANDLE *target;
  u8 _10[0x1930 - 0x10];
  u32 totalDamage;
  u8 _1934[0x1974 - 0x1934];
  SP_ATTACK_DATA spAttacks[3];
  u8 _19c8[0x19cc - 0x19c8];
  u16 damageRate;
  u8 state;
  u8 _19cf[0x19d1 - 0x19cf];
  u8 groupIndex;
  u8 groups[3];
  u8 groupNum;
  u8 orderAttrs[9];
  u8 _19df[0x19e4 - 0x19df];
  u16 : 4;
  u16 isStartFullBurst : 1;
  u16 : 11;
};

static_assert(sizeof(ChainAttackManager::SP_ATTACK_DATA) == 0x1c, "");
static_assert(offsetof(ChainAttackManager, target) == 0x8, "");
static_assert(offsetof(ChainAttackManager, totalDamage) == 0x1930, "");
static_assert(offsetof(ChainAttackManager, spAttacks) == 0x1974, "");
static_assert(offsetof(ChainAttackManager, damageRate) == 0x19cc, "");
static_assert(offsetof(ChainAttackManager, state) == 0x19ce, "");
static_assert(offsetof(ChainAttackManager, groupIndex) == 0x19d1, "");
static_assert(offsetof(ChainAttackManager, groups) == 0x19d2, "");
static_assert(offsetof(ChainAttackManager, groupNum) == 0x19d5, "");
static_assert(offsetof(ChainAttackManager, orderAttrs) == 0x19d6, "");

} // namespace btl
