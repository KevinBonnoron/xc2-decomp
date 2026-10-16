#pragma once
#include "mm_math/mm_vec3.h"
#include "types.h"
#include <stddef.h>

namespace fw {
struct UpdateInfo;
}

namespace gf {
struct GF_OBJ_HANDLE;
class GfObj;
} // namespace gf

namespace btl {

class CharacterParameter;
class GROUP_DATA;

class ActionCommand {
public:
  enum COMMAND_TYPE {};

  void SetActionID(int action);
  bool IsProcAction(int action) const;

  u8 _00[0x10 - 0x00];
  u32 : 6;
  u32 actionFlags : 25;
};

static_assert(sizeof(ActionCommand) == 0x14, "");

class BattleCharacter {
public:
  enum ANIM_ID {};
  enum ACTION_ID {
    ACTION_ID_IDLE = 1,
    ACTION_ID_MOVE = 4,
  };

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
  void ResetHateRingData();
  void ResetDelayVoice();
  gf::GfObj *GetObject() const;
  gf::GF_OBJ_HANDLE *GetControlCharacterHandle() const;
  gf::GfObj *GetObject(gf::GF_OBJ_HANDLE *handle) const;
  bool IsEnableBackHome() const;
  bool IsDisp() const;
  int GetWeaponType(bool isAsm) const;
  bool IsCustomVoice(int voice) const;
  void SetCustomVoiceEndFlag(int voice, bool isEnd);
  void ClearCustomVoiceEndFlag(u32 flags);
  int GetWeaponSeType() const;
  void GetMoveDataPerSec(mm::Vec3 &moveData) const;
  void SetAnimationSpeed(f32 speed);
  void NotifyStrikeDamage(int);
  void ResetAlphaRate(int alpha);
  f32 GetSystemDt() const;
  f32 GetSystemSyncCount() const;
  bool IsEnableBladeChangeAction(ACTION_ID actionId) const;
  void EnhanceProc();
  bool IsEnableBattleFace() const;
  void NotifyHateElse();
  void SetBladeSupportCondition(int condition);
  void AddIdea(u32 idea, u32 point);
  void SetNoDamageTime(f32 time);
  void SetPerfectAvoidTime(f32 time);
  f32 GetFriendEnhanceRate(int enhance, bool) const;
  void EnhanceTimerProc();
  void StopAI(f32 time);
  bool CheckRandFriendEnhanceRate(int enhance) const;
  void ResetBladeSupportConditionFlag();
  void ActionCommandEndIdle();
  void ActionCommandPutOutWeapon(const ActionCommand *command, ActionCommand::COMMAND_TYPE type);
  void ActionCommandEndPutOutWeapon();
  void ActionCommandPutAwayWeapon(const ActionCommand *command, ActionCommand::COMMAND_TYPE type);
  void ActionCommandEndPutAwayWeapon();
  void ActionCommandKizunaMax(const ActionCommand *command, ActionCommand::COMMAND_TYPE type);
  void ActionCommandEndKizunaMax();
  void ActionCommandEndAttack();
  void ActionCommandEndArts();
  void ActionCommandBladeChange(const ActionCommand *command, ActionCommand::COMMAND_TYPE type);
  void ActionCommandEndBladeChange();
  void ActionCommandSpAttack(const ActionCommand *command, ActionCommand::COMMAND_TYPE type);
  void ActionCommandEndSpAttack();
  void ActionCommandSupport(const ActionCommand *command, ActionCommand::COMMAND_TYPE type);
  void ActionCommandEndSupport();
  void ActionCommandBladeGuard(const ActionCommand *command, ActionCommand::COMMAND_TYPE type);
  void ActionCommandEndBladeGuard();
  void ActionCommandRepelled(const ActionCommand *command, ActionCommand::COMMAND_TYPE type);
  void ActionCommandEndRepelled();
  void ActionCommandDown(const ActionCommand *command, ActionCommand::COMMAND_TYPE type);
  void ActionCommandEndDown();
  void ActionCommandKnockBack(const ActionCommand *command, ActionCommand::COMMAND_TYPE type);
  void ActionCommandEndKnockBack();
  void ActionCommandBreak(const ActionCommand *command, ActionCommand::COMMAND_TYPE type);
  void ActionCommandEndBreak();
  void ActionCommandDead(const ActionCommand *command, ActionCommand::COMMAND_TYPE type);
  void ActionCommandEndDead();
  void ActionCommandRescue(const ActionCommand *command, ActionCommand::COMMAND_TYPE type);
  void ActionCommandEndRescue();

  u8 _08[0x10 - 0x08];
  mm::Vec3 position;
  u8 _20[0xb0 - 0x20];
  mm::Vec3 moveData;
  u8 _c0[0x118 - 0xc0];
  gf::GF_OBJ_HANDLE *handle;
  gf::GF_OBJ_HANDLE *target;
  u8 _128[0xc58 - 0x128];
  char voiceCode[0x10];
  u8 _c68[0xcb8 - 0xc68];
  f32 animationSpeed;
  u8 _cbc[0xcc4 - 0xcbc];
  f32 systemDt;
  int bdatId;
  u8 _ccc[0xdd0 - 0xccc];
  s16 delayVoiceTime;
  u8 _dd2[0xf2c - 0xdd2];
  f32 alphaRates[7];
  u8 _f48[0xf5c - 0xf48];
  u32 customVoiceFlags;
  u32 customVoiceEndFlags;
  u8 _f64[0xf7d - 0xf64];
  s8 id;
  s8 aiId;
  s8 weaponType;
  u8 _f80[0xf8c - 0xf80];
  u8 : 7;
  u8 isPlayer : 1;
  u8 isBattle : 1;
  u8 : 7;
  u8 _f8e[0xf8f - 0xf8e];
  u8 : 7;
  u8 isFly : 1;
  u8 _f90[0x107c - 0xf90];
  u8 actionId;
  u8 _107d[0x10c6 - 0x107d];
  u8 reactionId : 5;
  u8 : 3;
  u8 _10c7[0x10c8 - 0x10c7];
  s8 artsTarget;
  u8 _10c9[0x10e0 - 0x10c9];
  f32 noDamageTime;
  f32 superArmorTime;
  f32 perfectAvoidTime;
  u8 _10ec[0x10fe - 0x10ec];
  s16 backAttacker;
  u8 _1100[0x11cc - 0x1100];
  f32 stopAiTime;
  u8 _11d0[0x11d8 - 0x11d0];
  int stamp;
  u8 _11dc[0x11e0 - 0x11dc];
  u16 bladeSupportConditionFlags;
  u16 : 10;
  u16 isUseNavi : 1;
  u16 isBattleOpening : 1;
  u8 _11e4[0x11f0 - 0x11e4];
};

static_assert(offsetof(BattleCharacter, position) == 0x10, "");
static_assert(offsetof(BattleCharacter, moveData) == 0xb0, "");
static_assert(offsetof(BattleCharacter, handle) == 0x118, "");
static_assert(offsetof(BattleCharacter, target) == 0x120, "");
static_assert(offsetof(BattleCharacter, voiceCode) == 0xc58, "");
static_assert(offsetof(BattleCharacter, animationSpeed) == 0xcb8, "");
static_assert(offsetof(BattleCharacter, systemDt) == 0xcc4, "");
static_assert(offsetof(BattleCharacter, bdatId) == 0xcc8, "");
static_assert(offsetof(BattleCharacter, delayVoiceTime) == 0xdd0, "");
static_assert(offsetof(BattleCharacter, alphaRates) == 0xf2c, "");
static_assert(offsetof(BattleCharacter, customVoiceFlags) == 0xf5c, "");
static_assert(offsetof(BattleCharacter, id) == 0xf7d, "");
static_assert(offsetof(BattleCharacter, aiId) == 0xf7e, "");
static_assert(offsetof(BattleCharacter, weaponType) == 0xf7f, "");
static_assert(offsetof(BattleCharacter, actionId) == 0x107c, "");
static_assert(offsetof(BattleCharacter, artsTarget) == 0x10c8, "");
static_assert(offsetof(BattleCharacter, noDamageTime) == 0x10e0, "");
static_assert(offsetof(BattleCharacter, backAttacker) == 0x10fe, "");
static_assert(offsetof(BattleCharacter, stopAiTime) == 0x11cc, "");
static_assert(offsetof(BattleCharacter, stamp) == 0x11d8, "");
static_assert(offsetof(BattleCharacter, bladeSupportConditionFlags) == 0x11e0, "");
static_assert(sizeof(BattleCharacter) == 0x11f0, "");

} // namespace btl
