#pragma once
#include "battle/button_challenge.h"
#include "fw/fw_camera.h" // IWYU pragma: keep
#include "gf/data/gf_data_weapon.h"
#include "gf/sound/gf_sound.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/intrusive_ptr.h"
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
class GfComEffectCaster;
} // namespace gf

namespace btl {

constexpr f32 FRAME_RATE = 30.0f;

enum BTL_TUTORIAL_COND {
  BTL_TUTORIAL_COND_DRIVER_ARTS_RECAST_END = 2,
  BTL_TUTORIAL_COND_BLADE_ARTS_RECAST_END = 3,
  BTL_TUTORIAL_COND_SP_ATTACK_LEVEL3_RECAST_END = 4,
  BTL_TUTORIAL_COND_UNKNOWN_0B = 11, // Inferred role: raised on a player's elemental combo; original name unknown.
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

    f32 unknown00; // Inferred role: slow rate; original member name unknown.
    f32 unknown04; // Inferred role: slow time; original member name unknown.
    f32 unknown08; // Inferred role: slow fade; original member name unknown.
    u32 unknown0c; // Inferred role: slow id; original member name unknown.
    u8 unknown10;  // Inferred role: character id; original member name unknown.
    u8 _11[0x12 - 0x11];
    u16 unknown12; // Inferred role: dynamics speed; original member name unknown.
  };

  struct ATTACK_DAMAGE_DATA {
    u32 unknown00;        // Inferred role: attack id; original member name unknown.
    u32 unknown04;        // Inferred role: damage; original member name unknown.
    u32 unknown08_0 : 27; // Inferred role: damage rate; original member name unknown.
    u32 unknown0b_3 : 5;  // Inferred role: attribute; original member name unknown.
    u32 : 32;
    u32 : 0;
    u8 unknown10_0 : 1;         // Inferred role: just distance attack; original member name unknown.
    u8 unknown10_1 : 1;         // Inferred role: resistant break damage end; original member name unknown.
    u8 unknown10_2 : 1;         // Inferred role: permit arts; original member name unknown.
    u8 unknown10_3 : 1;         // Inferred role: do not shoot bullet; original member name unknown.
    u8 unknown10_4 : 1;         // Inferred role: overwrite damage rate; original member name unknown.
    u8 unknown10_5 : 1;         // Inferred role: end drop heal pot 2; original member name unknown.
    u8 unknown10_6 : 1;         // Inferred role: end critical recast enhance; original member name unknown.
    mutable u8 unknown10_7 : 1; // Inferred role: updated; original member name unknown.
    u8 _11[0x12 - 0x11];
    u8 unknown12_0 : 1; // Inferred role: enable add elemental ball; original member name unknown.
    u8 unknown12_1 : 1; // Inferred role: valid attack range; original member name unknown.
    u8 unknown13;       // Inferred role: main target; original member name unknown.
  };

  struct SPECIAL_EFFECT_DATA {
    u32 unknown00; // Inferred role: effect handle; original member name unknown.
    int unknown04; // Inferred role: special effect; original member name unknown.
  };

  struct LINK_JOIN_DATA {
    gf::GF_OBJ_HANDLE *unknown00; // Inferred role: enemy handle; original member name unknown.
    f32 unknown08;                // Inferred role: join time; original member name unknown.
  };

  struct ELEMENTAL_COMBO_FLOW_DATA {
    u8 unknown00;       // Inferred role: parent combo; original member name unknown.
    u8 unknown01_0 : 3; // Inferred role: stage; original member name unknown.
    u8 unknown01_3 : 5; // Inferred role: attribute; original member name unknown.
    u8 unknown02[9][2]; // Inferred role: next combo and needed attribute count of each attribute; original member name unknown.
  };

  struct LEVER_GACHA_DATA {
    enum BUTTON {};

    f32 unknown00[4]; // Inferred role: button gauges; original member name unknown.
    u8 _10[0x15 - 0x10];
    u8 unknown15;   // Inferred role: input count; original member name unknown.
    bool unknown16; // Inferred role: input flag; original member name unknown.
    u8 _17[0x18 - 0x17];
  };

  struct MAP_DRIVER_REV_DATA {
    u16 unknown00_0 : 11; // Inferred role: kizuna max; original member name unknown.
    u16 unknown01_3 : 4;  // Inferred role: SP level max; original member name unknown.
    u16 unknown01_7 : 1;  // Inferred role: support enabled; original member name unknown.
    u8 unknown02;         // Inferred role: attack rate; original member name unknown.
    u8 unknown03;         // Inferred role: defence rate; original member name unknown.
  };

  BattleGlobal();
  ~BattleGlobal();
  static void Create();
  void Initialize();
  void NotifyMapChange();
  void BattleEndInitialize();
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
  void DeleteSlowAll();
  void PlayJingle(JINGLE_TYPE jingle);
  void StopJingle(bool isReset);
  bool InputLeverGachaButton(LEVER_GACHA_DATA::BUTTON button);
  static void PostUpdate(const fw::UpdateInfo &updateInfo);
  void PostUpdateProc(const fw::UpdateInfo &updateInfo);
  void Tutorial(BTL_TUTORIAL_COND cond, int combo, void *character);
  void ResetBGM();
  void InitializeConditionParameter();
  void DeleteElementalComboSlow();
  void DeleteElementalComboCamera();
  void UpdateMapRev();
  void RegisterElementalComboCamera(mm::mtl::IntrusivePtr<fw::Camera> camera, gf::GF_OBJ_HANDLE *handle);
  void AddChainCount(bool isControl);
  void InitializeElementalComboFlowData();
  void RegisterElementalComboSlow();
  void FinalizeJingle();
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
  int RegisterSlow(f32 rate, f32 time, f32 fade);
  void DeleteSlow(u32 slow);
  void SetSlowDynamicsSpeed(u32 slow, int characterId, u32 speed);
  void CreateSpecialEffect(int special);
  void DeleteSpecialEffect(int special);
  const SLOW_PROC_DATA *GetSlowProcDataConst(u32 slow) const;
  void SetBGM(u32 bgm);
  void RequestJingle(JINGLE_TYPE jingle);
  bool IsJinglePlaying() const;
  void PlayErrorSE();
  void NotifyLinkJoinBattle(gf::GF_OBJ_HANDLE *handle);
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
  void EndSpecialEffect(SPECIAL_EFFECT_DATA &data);

  u8 _08[0x18 - 0x08];
  mutable const char *unknown18[185];                      // Inferred role: SE tag names; original member name unknown.
  ShakeCameraManager *unknown5e0;                          // Inferred role: shake camera manager; original member name unknown.
  ButtonChallenge unknown5e8;                              // Inferred role: button challenge; original member name unknown.
  mm::mtl::FixedVector<LINK_JOIN_DATA, 8> unknown620;      // Inferred role: link join enemies; original member name unknown.
  mm::mtl::FixedVector<SPECIAL_EFFECT_DATA, 1> unknown6a8; // Inferred role: special effects; original member name unknown.
  f32 unknown6b8;                                          // Inferred role: stop time; original member name unknown.
  u8 _6bc[0x6c0 - 0x6bc];
  mm::mtl::FixedVector<SLOW_PROC_DATA, 20> unknown6c0; // Inferred role: slow procs; original member name unknown.
  u8 _858[0x864 - 0x858];
  s32 unknown864; // Inferred role: battle count; original member name unknown.
  u8 _868[0x86c - 0x868];
  f32 unknown86c; // Inferred role: battle time; original member name unknown.
  u32 unknown870; // Role and original member name unknown.
  u8 _874[0x878 - 0x874];
  mm::mtl::FixedVector<ATTACK_DAMAGE_DATA, 1000> unknown878; // Inferred role: attack damages; original member name unknown.
  ELEMENTAL_COMBO_FLOW_DATA unknown56a0[50];                 // Inferred role: elemental combo flows; original member name unknown.
  LEVER_GACHA_DATA unknown5a88;                              // Inferred role: lever gacha; original member name unknown.
  gf::GF_SE_CATEGORY_HANDLE *unknown5aa0;                    // Inferred role: jingle handle; original member name unknown.
  gf::SoundHandle unknown5aa8;                               // Inferred role: jingle sound; original member name unknown.
  u32 unknown5ab0;                                           // Role and original member name unknown.
  u32 unknown5ab4;                                           // Role and original member name unknown.
  u32 unknown5ab8;                                           // Role and original member name unknown.
  u8 _5abc[0x5ac0 - 0x5abc];
  MAP_DRIVER_REV_DATA unknown5ac0[9]; // Inferred role: map driver revisions; original member name unknown.
  int unknown5ae4;                    // Inferred role: anti blade area bdat id; original member name unknown.
  u8 _5ae8[0x5af0 - 0x5ae8];
  gf::GF_OBJ_HANDLE *unknown5af0; // Role and original member name unknown.
  gf::GF_OBJ_HANDLE *m_elementalComboImmortal;
  mm::mtl::IntrusivePtr<fw::Camera> unknown5b00; // Inferred role: elemental combo camera; original member name unknown.
  gf::GfComEffectCaster *unknown5b08;            // Inferred role: slow effect caster; original member name unknown.
  gf::GfComEffectCaster *unknown5b10;            // Role and original member name unknown.
  u32 unknown5b18;                               // Inferred role: slow effect id; original member name unknown.
  u32 unknown5b1c;                               // Role and original member name unknown.
  u32 unknown5b20;                               // Inferred role: elemental combo slow id; original member name unknown.
  u8 _5b24[0x5b28 - 0x5b24];
  gf::GF_OBJ_HANDLE *unknown5b28; // Inferred role: unite combo target; original member name unknown.
  u8 _5b30[0x5b38 - 0x5b30];
  mm::mtl::IntrusivePtr<fw::Camera> unknown5b38; // Inferred role: unite combo camera; original member name unknown.
  u8 _5b40[0x5b5f - 0x5b40];
  bool unknown5b5f; // Inferred role: unite combo direction; original member name unknown.
  u8 _5b60[0x5b68 - 0x5b60];
  f32 unknown5b68; // Inferred role: kakusei rest time; original member name unknown.
  u8 _5b6c[0x5b88 - 0x5b6c];
  u32 unknown5b88; // Inferred role: debuff flags; original member name unknown.
  u8 _5b8c[0x5b8e - 0x5b8c];
  u16 unknown5b8e;                                   // Inferred role: enemy kill count; original member name unknown.
  u16 unknown5b90[16][gf::WEAPON_TYPE_COUNT + 1][3]; // Inferred role: normal attack arts ids; original member name unknown.
  u16 unknown65b0[17];                               // Inferred role: condition parameters; original member name unknown.
  u16 unknown65d2;                                   // Inferred role: BGM id; original member name unknown.
  u8 unknown65d4;                                    // Inferred role: BGM priority; original member name unknown.
  u8 unknown65d5;                                    // Inferred role: requested jingle; original member name unknown.
  u8 unknown65d6[7];                                 // Inferred role: pause flags; original member name unknown.
  u8 unknown65dd;                                    // Inferred role: link join max level; original member name unknown.
  u64 unknown65de_0 : 1;                             // Inferred role: lock arts palette; original member name unknown.
  u64 : 5;
  u64 unknown65de_6 : 1; // Role and original member name unknown.
  u64 : 1;
  u64 unknown65df_0 : 1; // Role and original member name unknown.
  u64 unknown65df_1 : 1; // Role and original member name unknown.
  u64 unknown65de_10 : 1;
  u64 unknown65df_3 : 1; // Inferred role: kakusei order; original member name unknown.
  u64 unknown65df_4 : 1; // Inferred role: kakusei; original member name unknown.
  u64 unknown65df_5 : 1; // Inferred role: kakusei finished; original member name unknown.
  u64 : 1;
  u64 unknown65df_7 : 1; // Role and original member name unknown.
  u64 unknown65e0_0 : 1; // Inferred role: game over; original member name unknown.
  u64 : 1;
  u64 unknown65e0_2 : 1; // Role and original member name unknown.
  u64 unknown65e0_3 : 1; // Role and original member name unknown.
  u64 unknown65e0_4 : 1; // Inferred role: scout; original member name unknown.
  u64 : 2;
  u64 unknown65e0_7 : 1; // Role and original member name unknown.
  u64 unknown65e1_0 : 1; // Inferred role: kill child; original member name unknown.
  u64 : 3;
  u64 unknown65e1_4 : 1; // Role and original member name unknown.
  u64 unknown65e1_5 : 1; // Role and original member name unknown.
  u64 unknown65e1_6 : 1; // Inferred role: shift decided; original member name unknown.
  u64 unknown65e1_7 : 1; // Inferred role: shift time over; original member name unknown.
  u64 : 1;
  u64 unknown65e2_1 : 1; // Role and original member name unknown.
  u64 unknown65e2_2 : 1; // Inferred role: play error SE; original member name unknown.
  u64 : 5;
  u8 _65e3[0x65e8 - 0x65e3];
};

static_assert(sizeof(BattleGlobal::LINK_JOIN_DATA) == 0x10, "");
static_assert(sizeof(BattleGlobal::LEVER_GACHA_DATA) == 0x18, "");
static_assert(sizeof(BattleGlobal::SPECIAL_EFFECT_DATA) == 0x8, "");
static_assert(sizeof(BattleGlobal::SLOW_PROC_DATA) == 0x14, "");
static_assert(offsetof(BattleGlobal::SLOW_PROC_DATA, unknown04) == 0x4, "");
static_assert(offsetof(BattleGlobal::SLOW_PROC_DATA, unknown08) == 0x8, "");
static_assert(offsetof(BattleGlobal::SLOW_PROC_DATA, unknown0c) == 0xc, "");
static_assert(offsetof(BattleGlobal::SLOW_PROC_DATA, unknown10) == 0x10, "");
static_assert(sizeof(BattleGlobal::ATTACK_DAMAGE_DATA) == 0x14, "");
static_assert(sizeof(BattleGlobal::MAP_DRIVER_REV_DATA) == 0x4, "");
static_assert(offsetof(BattleGlobal, unknown18) == 0x18, "");
static_assert(offsetof(BattleGlobal, unknown5e0) == 0x5e0, "");
static_assert(sizeof(BattleGlobal::LINK_JOIN_DATA) == 0x10, "");
static_assert(offsetof(BattleGlobal, unknown620) == 0x620, "");
static_assert(offsetof(BattleGlobal, unknown5a88) == 0x5a88, "");
static_assert(offsetof(BattleGlobal, unknown5ae4) == 0x5ae4, "");
static_assert(offsetof(BattleGlobal, unknown5af0) == 0x5af0, "");
static_assert(offsetof(BattleGlobal, unknown6b8) == 0x6b8, "");
static_assert(offsetof(BattleGlobal, unknown6c0) == 0x6c0, "");
static_assert(offsetof(BattleGlobal, unknown864) == 0x864, "");
static_assert(offsetof(BattleGlobal, unknown86c) == 0x86c, "");
static_assert(offsetof(BattleGlobal, unknown870) == 0x870, "");
static_assert(offsetof(BattleGlobal, unknown878) == 0x878, "");
static_assert(offsetof(BattleGlobal, unknown56a0) == 0x56a0, "");
static_assert(offsetof(BattleGlobal, unknown5aa0) == 0x5aa0, "");
static_assert(offsetof(BattleGlobal, unknown5aa8) == 0x5aa8, "");
static_assert(offsetof(BattleGlobal, unknown5ab0) == 0x5ab0, "");
static_assert(offsetof(BattleGlobal, unknown5ac0) == 0x5ac0, "");
static_assert(offsetof(BattleGlobal, m_elementalComboImmortal) == 0x5af8, "");
static_assert(offsetof(BattleGlobal, unknown5b28) == 0x5b28, "");
static_assert(offsetof(BattleGlobal, unknown5b00) == 0x5b00, "");
static_assert(offsetof(BattleGlobal, unknown5b38) == 0x5b38, "");
static_assert(offsetof(BattleGlobal, unknown5b5f) == 0x5b5f, "");
static_assert(offsetof(BattleGlobal, unknown5b68) == 0x5b68, "");
static_assert(offsetof(BattleGlobal, unknown5b08) == 0x5b08, "");
static_assert(offsetof(BattleGlobal, unknown5b10) == 0x5b10, "");
static_assert(offsetof(BattleGlobal, unknown5b18) == 0x5b18, "");
static_assert(offsetof(BattleGlobal, unknown5b1c) == 0x5b1c, "");
static_assert(offsetof(BattleGlobal, unknown5b20) == 0x5b20, "");
static_assert(offsetof(BattleGlobal, unknown5b88) == 0x5b88, "");
static_assert(offsetof(BattleGlobal, unknown5b8e) == 0x5b8e, "");
static_assert(offsetof(BattleGlobal, unknown5b90) == 0x5b90, "");
static_assert(offsetof(BattleGlobal, unknown65b0) == 0x65b0, "");
static_assert(offsetof(BattleGlobal, unknown65d2) == 0x65d2, "");
static_assert(offsetof(BattleGlobal, unknown65d6) == 0x65d6, "");
static_assert(offsetof(BattleGlobal, unknown65dd) == 0x65dd, "");
static_assert(sizeof(BattleGlobal) == 0x65e8, "");

} // namespace btl
