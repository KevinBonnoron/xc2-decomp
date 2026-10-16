#pragma once
#include "battle/button_challenge.h"
#include "gf/data/gf_data_weapon.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/singleton.h"
#include "types.h"
#include <stddef.h>

namespace mm {
struct Vec3;
}

namespace fw {
struct UpdateInfo;
}

namespace gf {
struct GF_OBJ_HANDLE;
struct GF_SE_CATEGORY_HANDLE;
} // namespace gf

namespace btl {

constexpr f32 FRAME_RATE = 30.0f;

enum BTL_TUTORIAL_COND {
  BTL_TUTORIAL_COND_DRIVER_ARTS_RECAST_END = 2,
  BTL_TUTORIAL_COND_BLADE_ARTS_RECAST_END = 3,
  BTL_TUTORIAL_COND_SP_ATTACK_LEVEL3_RECAST_END = 4,
};

class BattleCharacter;
class ShakeCameraManager;

class BattleGlobal : public mm::mtl::PtrSingleton<BattleGlobal> {
public:
  enum JINGLE_TYPE {};

  enum PAUSE {
    PAUSE_BUTTON_CHALLENGE = 4,
  };

  struct SLOW_PROC_DATA {
    void Finalize();

    u8 _00[0xc - 0x0];
    u32 id;
    u8 characterId;
  };

  struct ATTACK_DAMAGE_DATA {
    u32 id;
    u32 damage;
    u32 damageRate : 27;
    u32 attribute : 5;
    u32 : 32;
    u32 : 0;
    u8 isJustDistanceAttack : 1;
    u8 isResistantBreakDamageEnd : 1;
    u8 isPermitArts : 1;
    u8 isNotShootBullet : 1;
    u8 isOverwriteDamageRate : 1;
    u8 isEndDropHealPot2 : 1;
    u8 isEndCriticalRecastEnhance : 1;
    mutable u8 isUpdated : 1;
    u8 _11[0x12 - 0x11];
    u8 isEnableAddElementalBall : 1;
    u8 isValidAttackRange : 1;
    u8 mainTarget;
  };

  struct ELEMENTAL_COMBO_FLOW_DATA {
    u8 parent;
    u8 stage : 3;
    u8 _02[0x14 - 0x02];
  };

  struct MAP_DRIVER_REV_DATA {
    u16 kizunaMax : 11;
    u16 spLevelMax : 4;
    u16 isEnableSupport : 1;
    u8 attackRate;
    u8 defenceRate;
  };

  BattleGlobal();
  static void Create();
  void Initialize();
  static void Destroy();
  void Finalize();
  int GetNormalAttackArtsID(int type, int weapon, int index) const;
  const ELEMENTAL_COMBO_FLOW_DATA *GetElementalComboFlowData(int combo) const;
  int GetElementalComboStage(int combo) const;
  int GetFirstStageElementalComboData(int combo) const;
  static void PreUpdate(const fw::UpdateInfo &updateInfo);
  void PreUpdateProc(const fw::UpdateInfo &updateInfo);
  static void Update(const fw::UpdateInfo &updateInfo);
  void UpdateProc(const fw::UpdateInfo &updateInfo);
  bool IsSlowProc(u32 slow) const;
  void DeleteUniteComboDirection();
  static void PostUpdate(const fw::UpdateInfo &updateInfo);
  void PostUpdateProc(const fw::UpdateInfo &updateInfo);
  void Tutorial(BTL_TUTORIAL_COND cond, int combo, void *character);
  void ResetBGM();
  void SetElementalComboImmortal(gf::GF_OBJ_HANDLE *handle);
  bool IsGameOver() const;
  bool IsEnableBattle() const;
  void NotifyShiftNone();
  void NotifyShiftTimeOver();
  const char *GetSeTag(int se) const;
  int GetAttackDamageDataNum() const;
  const ATTACK_DAMAGE_DATA *GetAttackDamageDataConst(u32 attack) const;
  void UpdateAttackData(u32 attack);
  int GetAttackDamage(u32 attack) const;
  gf::GF_OBJ_HANDLE *GetAttackMainTargetHandle(u32 attack) const;
  void SetAttackAttr(u32 attack, int attribute);
  int GetAttackAttr(u32 attack) const;
  void SetEndDropHealPot2(u32 attack);
  bool IsEndDropHealPot2(u32 attack) const;
  void SetCriticalRecastEnhanceEnd(u32 attack);
  bool IsEndCriticalRecastEnhance(u32 attack) const;
  void SetJustDistanceAttack(u32 attack);
  bool IsJustDistanceAttack(u32 attack) const;
  void SetEnableAddElementalBall(u32 attack, bool isEnable);
  bool IsEnableAddElementalBall(u32 attack) const;
  void SetResistantBreakDamageEnd(u32 attack);
  bool IsEnableResistantBreakDamage(u32 attack) const;
  void SetPermitArts(u32 attack);
  bool IsPermitArts(u32 attack) const;
  void SetShootBullet(u32 attack, bool isShoot);
  bool IsShootBullet(u32 attack) const;
  void SetValidAttackRange(u32 attack, bool isValid);
  bool IsValidAttackRange(u32 attack) const;
  void SetDamageRate(u32 attack, f32 rate, bool isOverwrite);
  void AddDamageRate(u32 attack, f32 rate, bool isOverwrite);
  void MulDamageRate(u32 attack, f32 rate, bool isOverwrite);
  f32 GetDamageRate(u32 attack, bool *isOverwrite) const;
  void SetPause(int pause, bool isPause);
  bool IsPause(int pause) const;
  void RegisterStop(f32 time);
  void DeleteSlow(u32 slow);
  const SLOW_PROC_DATA *GetSlowProcDataConst(u32 slow) const;
  void SetBGM(u32 bgm);
  void RequestJingle(JINGLE_TYPE jingle);
  bool IsJinglePlaying() const;
  void PlayErrorSE();
  gf::GF_OBJ_HANDLE *GetLinkJoinEnemyHandle(const mm::Vec3 &position);
  const MAP_DRIVER_REV_DATA *GetMapDriverRevData(const BattleCharacter *character) const;
  const MAP_DRIVER_REV_DATA *GetMapDriverRevDataByBdatID(int driver) const;
  int GetKizunaMax(const BattleCharacter *character) const;
  f32 GetAttackRate(const BattleCharacter *character) const;
  f32 GetDefenceRate(const BattleCharacter *character) const;
  int GetSpLevelMax(const BattleCharacter *character) const;
  bool IsEnableSupport(const BattleCharacter *character) const;
  bool IsKakuseiFinished() const;
  bool IsKakuseiOrder(bool isCheckRestTime) const;
  void ApplyBattleCameraAdjustment(mm::Vec3 &position, mm::Vec3 &target);

  u8 _08[0x18 - 0x08];
  mutable const char *seTags[185];
  ShakeCameraManager *shakeCameraManager;
  ButtonChallenge buttonChallenge;
  u8 _620[0x6b8 - 0x620];
  f32 stopTime;
  u8 _6bc[0x6c0 - 0x6bc];
  mm::mtl::FixedVector<SLOW_PROC_DATA, 20> slowProcs;
  u8 _858[0x878 - 0x858];
  mm::mtl::FixedVector<ATTACK_DAMAGE_DATA, 1000> attackDamages;
  ELEMENTAL_COMBO_FLOW_DATA elementalComboFlows[50];
  u8 _5a88[0x5aa0 - 0x5a88];
  gf::GF_SE_CATEGORY_HANDLE *jingleHandle;
  u8 _5aa8[0x5ac0 - 0x5aa8];
  MAP_DRIVER_REV_DATA mapDriverRevs[9];
  u8 _5ae4[0x5af8 - 0x5ae4];
  gf::GF_OBJ_HANDLE *elementalComboImmortal;
  u8 _5b00[0x5b28 - 0x5b00];
  gf::GF_OBJ_HANDLE *uniteComboTarget;
  u8 _5b30[0x5b5f - 0x5b30];
  bool isUniteComboDirection;
  u8 _5b60[0x5b68 - 0x5b60];
  f32 kakuseiRestTime;
  u8 _5b6c[0x5b8e - 0x5b6c];
  u16 enemyKillNum;
  u16 normalAttackArtsIds[16][gf::WEAPON_TYPE_COUNT + 1][3];
  u8 _65b0[0x65d2 - 0x65b0];
  u16 bgm;
  u8 bgmPriority;
  u8 requestJingle;
  u8 pauseFlags[8];
  u64 isLockArtsPalette : 1;
  u64 : 10;
  u64 isKakuseiOrder : 1;
  u64 isKakusei : 1;
  u64 isKakuseiFinished : 1;
  u64 : 2;
  u64 isGameOver : 1;
  u64 : 7;
  u64 isKillChild : 1;
  u64 : 5;
  u64 isShiftDecided : 1;
  u64 isShiftTimeOver : 1;
  u64 : 2;
  u64 isPlayErrorSE : 1;
  u64 : 5;
  u8 _65e3[0x65e8 - 0x65e3];
};

static_assert(sizeof(BattleGlobal::SLOW_PROC_DATA) == 0x14, "");
static_assert(sizeof(BattleGlobal::ATTACK_DAMAGE_DATA) == 0x14, "");
static_assert(sizeof(BattleGlobal::MAP_DRIVER_REV_DATA) == 0x4, "");
static_assert(offsetof(BattleGlobal, seTags) == 0x18, "");
static_assert(offsetof(BattleGlobal, shakeCameraManager) == 0x5e0, "");
static_assert(offsetof(BattleGlobal, stopTime) == 0x6b8, "");
static_assert(offsetof(BattleGlobal, slowProcs) == 0x6c0, "");
static_assert(offsetof(BattleGlobal, attackDamages) == 0x878, "");
static_assert(offsetof(BattleGlobal, elementalComboFlows) == 0x56a0, "");
static_assert(offsetof(BattleGlobal, jingleHandle) == 0x5aa0, "");
static_assert(offsetof(BattleGlobal, mapDriverRevs) == 0x5ac0, "");
static_assert(offsetof(BattleGlobal, elementalComboImmortal) == 0x5af8, "");
static_assert(offsetof(BattleGlobal, uniteComboTarget) == 0x5b28, "");
static_assert(offsetof(BattleGlobal, isUniteComboDirection) == 0x5b5f, "");
static_assert(offsetof(BattleGlobal, kakuseiRestTime) == 0x5b68, "");
static_assert(offsetof(BattleGlobal, enemyKillNum) == 0x5b8e, "");
static_assert(offsetof(BattleGlobal, normalAttackArtsIds) == 0x5b90, "");
static_assert(offsetof(BattleGlobal, bgm) == 0x65d2, "");
static_assert(offsetof(BattleGlobal, pauseFlags) == 0x65d6, "");
static_assert(sizeof(BattleGlobal) == 0x65e8, "");

} // namespace btl
