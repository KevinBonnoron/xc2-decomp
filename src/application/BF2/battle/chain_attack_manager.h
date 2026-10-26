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
    f32 unknown00; // Inferred role: recast; original member name unknown.
    s8 unknown04;  // Inferred role: blade; original member name unknown.
  };

  struct SP_ATTACK_DATA {
    SP_ATTACK_BLADE_DATA unknown00[3]; // Inferred role: blades; original member name unknown.
    u8 unknown18;                      // Inferred role: level; original member name unknown.
  };

  void Initialize();
  static void Destroy();
  void Finalize();
  void Reset(int);
  void Start(gf::GF_OBJ_HANDLE *handle);
  static void PreUpdate(const fw::UpdateInfo &updateInfo);
  void PreUpdateProc(const fw::UpdateInfo &updateInfo);
  static void Update(const fw::UpdateInfo &updateInfo);
  void UpdateProc(const fw::UpdateInfo &updateInfo);
  void AddDamageRate(int rate);
  void ModifyPosition();
  void ModifyPositionDriver(gf::GF_OBJ_HANDLE *driver);
  void ModifyPositionBlade(gf::GF_OBJ_HANDLE *driver, gf::GF_OBJ_HANDLE *blade);
  f32 GetDamageRate() const;
  int GetSpAttackLevel(int group) const;
  f32 GetSpAttackRecast(int group, int blade) const;
  int GetOrderAttr(int order) const;
  int GetAttrOrder(int attr) const;
  void RecoveryRecastAll(f32 recast);
  void RecoveryRecastOne(int group, f32 recast);
  bool IsProc(bool isExcludeStartWait) const;
  bool IsResult() const;
  void AddTotalDamage(u32 damage);
  void RecoveryKizuna(int partyId);
  int GetGroupIndex() const;
  bool IsStartWait() const;
  bool IsSelectAction() const;
  bool IsStopTime() const;
  bool IsTargetDead() const;
  f32 GetBonusRate() const;

  gf::GF_OBJ_HANDLE *unknown08; // Inferred role: target handle; original member name unknown.
  u8 _10[0x192c - 0x10];
  f32 unknown192c; // Inferred role: bonus rate time; original member name unknown.
  u32 unknown1930; // Inferred role: total damage; original member name unknown.
  u8 _1934[0x1974 - 0x1934];
  SP_ATTACK_DATA unknown1974[3]; // Inferred role: SP attacks; original member name unknown.
  u8 _19c8[0x19cc - 0x19c8];
  u16 unknown19cc; // Inferred role: damage rate; original member name unknown.
  u8 unknown19ce;  // Inferred role: state; original member name unknown.
  u8 _19cf[0x19d1 - 0x19cf];
  u8 unknown19d1;    // Inferred role: group index; original member name unknown.
  u8 unknown19d2[3]; // Inferred role: groups; original member name unknown.
  u8 unknown19d5;    // Inferred role: group count; original member name unknown.
  u8 unknown19d6[9]; // Inferred role: order attributes; original member name unknown.
  u8 _19df[0x19e1 - 0x19df];
  u8 unknown19e1; // Role and original member name unknown.
  u8 unknown19e2; // Role and original member name unknown.
  u8 unknown19e3; // Role and original member name unknown.
  u16 : 4;
  u16 unknown19e4_4 : 1; // Inferred role: start full burst; original member name unknown.
  u16 : 11;
};

static_assert(sizeof(ChainAttackManager::SP_ATTACK_DATA) == 0x1c, "");
static_assert(offsetof(ChainAttackManager, unknown08) == 0x8, "");
static_assert(offsetof(ChainAttackManager, unknown192c) == 0x192c, "");
static_assert(offsetof(ChainAttackManager, unknown1930) == 0x1930, "");
static_assert(offsetof(ChainAttackManager, unknown1974) == 0x1974, "");
static_assert(offsetof(ChainAttackManager, unknown19cc) == 0x19cc, "");
static_assert(offsetof(ChainAttackManager, unknown19ce) == 0x19ce, "");
static_assert(offsetof(ChainAttackManager, unknown19d1) == 0x19d1, "");
static_assert(offsetof(ChainAttackManager, unknown19d2) == 0x19d2, "");
static_assert(offsetof(ChainAttackManager, unknown19d5) == 0x19d5, "");
static_assert(offsetof(ChainAttackManager, unknown19d6) == 0x19d6, "");

} // namespace btl
