#pragma once
#include "mm_math/mm_vec3.h"
#include "types.h"
#include <stddef.h>

namespace fw {
struct UpdateInfo;
}

namespace gf {
struct GF_OBJ_HANDLE;
}

namespace btl {

class CharacterParameter;
class GROUP_DATA;

class BattleCharacter {
public:
  enum ANIM_ID {};
  enum ACTION_ID {};

  enum {
    DEAD_CHECK_IGNORE_CHAIN_ATTACK = 0x02,
  };

  enum MOVE_TYPE {
    MOVE_TYPE_TARGET = 0,
    MOVE_TYPE_FRONT = 2,
    MOVE_TYPE_SIDE = 3,
    MOVE_TYPE_LEFT = 4,
    MOVE_TYPE_RIGHT = 5,
    MOVE_TYPE_BACK = 6,
    MOVE_TYPE_BACKWARD = 7,
    MOVE_TYPE_SATELLITE_CLOCKWISE = 8,
    MOVE_TYPE_SATELLITE_COUNTERCLOCKWISE = 9,
    MOVE_TYPE_POSITION = 10,
  };

  struct AI_MOVE_PARAM {
    AI_MOVE_PARAM() : distance(0.0f), time(0.0f), type(MOVE_TYPE_TARGET), position(nullptr), target(reinterpret_cast<gf::GF_OBJ_HANDLE *>(-1)) {}

    f32 distance;
    f32 time;
    MOVE_TYPE type;
    const mm::Vec3 *position;
    gf::GF_OBJ_HANDLE *target;
  };

  BattleCharacter();
  virtual ~BattleCharacter();
  virtual void BeforeUpdate(const fw::UpdateInfo &updateInfo);
  virtual void Update();
  virtual void AfterUpdate();
  virtual void SetAnimationCallback(ANIM_ID animId, int, int, const char *);
  virtual void OnLandCallback(bool, bool);
  virtual void LandingCallback();
  virtual void BoundCallback();
  virtual void SetActionCallback(ACTION_ID actionId);

  const CharacterParameter *GetCharacterParameterConst(bool) const;
  bool IsPlayer() const;
  bool IsBlade() const;
  bool IsEnemy() const;
  bool IsDriver() const;
  CharacterParameter *GetCharacterParameter(bool);
  bool IsControlCharacter() const;
  bool IsControlCharacterGroup() const;
  bool IsDead(u32 flags) const;
  u8 CheckAttackPosition(gf::GF_OBJ_HANDLE *handle, bool, bool *) const;
  bool IsBattle() const;
  bool IsMove() const;
  const GROUP_DATA *GetGroupDataConst() const;
  bool IsEnableSpeakVoice() const;
  bool IsEnableTurnAI() const;
  void TurnDirection(const mm::Vec3 &direction, bool, bool);
  void TurnTarget(bool, bool, bool);
  int GetKizunaStage(f32 *rate) const;
  void AddRecast(f32 recast, bool, int);
  void SetAngry(bool isAngry, f32 time);
  bool IsAngry() const;
  void HealHpRate(f32 rate, int, BattleCharacter *healer);
  void FluctuatePartyGauge(int);
  void StartBackHome();
  int GetArtsSlotIndex(int arts) const;
  bool IsInAttackRange(int slot, f32 *distance) const;
  int IsEnableArts(int, int slot, int, gf::GF_OBJ_HANDLE *target) const;
  bool IsRescue() const;
  void AddKizuna(f32 kizuna);
  void SetSpAttackRecastByLevel(int level, bool);
  void SetSuperArmorTime(f32 time);
  bool AI_Rescue(ACTION_ID actionId, int target);
  bool AI_BladeChange(ACTION_ID actionId, int blade);
  bool AI_SpAttack(ACTION_ID actionId, bool, bool);
  bool AI_Arts(ACTION_ID actionId, int slot);
  bool AI_Attack(ACTION_ID actionId, bool);
  bool IsProcAI(bool) const;
  bool AI_Move(ACTION_ID actionId, bool, const AI_MOVE_PARAM *param);
  void MoveStop(bool);
  void SetScout(bool isScout);
  bool IsScout() const;
  gf::GF_OBJ_HANDLE *GetRescueTarget() const;
  void BattleEndInitialize();
  void PreManagerUpdate(const fw::UpdateInfo &updateInfo);
  void ManagerUpdate(const fw::UpdateInfo &updateInfo);

  u8 _08[0x10 - 0x08];
  mm::Vec3 position;
  u8 _20[0x118 - 0x20];
  gf::GF_OBJ_HANDLE *handle;
  gf::GF_OBJ_HANDLE *target;
  u8 _128[0xc58 - 0x128];
  char voiceCode[0x10];
  u8 _c68[0xcc8 - 0xc68];
  int bdatId;
  u8 _ccc[0xf7d - 0xccc];
  s8 id;
  s8 aiId;
  u8 _f7f[0xf8f - 0xf7f];
  u8 : 7;
  u8 isFly : 1;
  u8 _f90[0x107c - 0xf90];
  u8 actionId;
  u8 _107d[0x10c6 - 0x107d];
  u8 reactionId : 5;
  u8 : 3;
  u8 _10c7[0x10c8 - 0x10c7];
  s8 artsTarget;
  u8 _10c9[0x10fe - 0x10c9];
  s16 backAttacker;
  u8 _1100[0x11d8 - 0x1100];
  int stamp;
  u8 _11dc[0x11e2 - 0x11dc];
  u16 : 10;
  u16 isUseNavi : 1;
  u16 isBattleOpening : 1;
  u8 _11e4[0x11f0 - 0x11e4];
};

static_assert(offsetof(BattleCharacter, position) == 0x10, "");
static_assert(offsetof(BattleCharacter, handle) == 0x118, "");
static_assert(offsetof(BattleCharacter, target) == 0x120, "");
static_assert(offsetof(BattleCharacter, voiceCode) == 0xc58, "");
static_assert(offsetof(BattleCharacter, bdatId) == 0xcc8, "");
static_assert(offsetof(BattleCharacter, id) == 0xf7d, "");
static_assert(offsetof(BattleCharacter, aiId) == 0xf7e, "");
static_assert(offsetof(BattleCharacter, actionId) == 0x107c, "");
static_assert(offsetof(BattleCharacter, artsTarget) == 0x10c8, "");
static_assert(offsetof(BattleCharacter, backAttacker) == 0x10fe, "");
static_assert(offsetof(BattleCharacter, stamp) == 0x11d8, "");
static_assert(sizeof(BattleCharacter) == 0x11f0, "");

} // namespace btl
