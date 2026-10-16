#pragma once
#include "battle/character/action_command.h"
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

enum BTL_SE {
  BTL_SE_HIT = 1,
};

namespace btl {

class CharacterParameter;
class GROUP_DATA;

class BattleCharacter {
public:
  enum ANIM_ID {};
  enum SLOW_PROC_ID {};
  enum DELAY_VOICE_TYPE {
    DELAY_VOICE_TYPE_NORMAL,
  };
  enum ALPHA_PROC_ID {};
  enum ACTION_ID {
    ACTION_ID_IDLE = 1,
    ACTION_ID_PUT_AWAY_WEAPON = 3,
    ACTION_ID_MOVE = 4,
    ACTION_ID_ATTACK = 6,
    ACTION_ID_ARTS = 7,
    ACTION_ID_BLADE_ARTS = 8,
    ACTION_ID_BLADE_CHANGE = 9,
    ACTION_ID_RESCUE = 18,
  };

  enum {
    DEAD_CHECK_IGNORE_CHAIN_ATTACK = 0x02,
  };

  enum {
    AI_FLAG_STOP = 0x02,
    AI_FLAG_STOP_FORCE = 0x04,
    AI_FLAG_SCOUT = 0x10,
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

  struct CUSTOM_VOICE_DATA {
    u8 voice;
    u8 type;
  };

  enum EFFECT_ID {
    EFFECT_ID_KIZUNA_AURA = 2,
    EFFECT_ID_NUM = 13,
  };

  struct ANIMATION_MOVE_DISTANCE_DATA {
    f32 distance;
    u16 animation;
  };

  struct ALPHA_PROC_DATA {
    f32 targetRate;
    f32 startRate;
    f32 rate;
    f32 time;
    f32 duration;
  };

  struct SLOW_PROC_DATA {
    f32 rate;
    f32 time;
    f32 counter;
  };

  struct AI_ACTION_DATA {
    u8 action;
    int target;
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

  void ResetCustomVoiceData();
  void ResetAnimationMoveDistance();
  void ResetAlphaAnimation();
  const CharacterParameter *GetCharacterParameterConst(bool) const;
  bool IsPlayer() const;
  bool IsBlade() const;
  bool IsEnemy() const;
  bool IsDriver() const;
  CharacterParameter *GetCharacterParameter(bool);
  bool IsControlCharacter() const;
  bool IsControlCharacterGroup() const;
  bool IsDead(u32 flags) const;
  void SetAction(ACTION_ID actionId, bool, bool, int, f32);
  u8 CheckAttackPosition(gf::GF_OBJ_HANDLE *handle, bool, bool *) const;
  bool IsBattle() const;
  void DeleteKizunaAuraEffect();
  void CancelButtonChallenge();
  bool IsDispWeaponAlpha(int alpha) const;
  bool IsBoss() const;
  bool IsNamed() const;
  bool IsBossOrNamed() const;
  bool IsMove() const;
  int GetGroupIndex() const;
  void AddUseWeapon();
  void PlaySE(BTL_SE se, int number, const mm::Vec3 *position, bool isFollow);
  void PlayHitAttrSE(int attribute, const mm::Vec3 *position);
  void PlayHitBulletSE(int attribute, const mm::Vec3 *position);
  int GetIKData(f32 &weight, f32 &height) const;
  void SetupPosDir();
  const GROUP_DATA *GetGroupDataConst() const;
  bool IsEnableSpeakVoice() const;
  bool IsEnableTurnAI() const;
  void TurnDirection(const mm::Vec3 &direction, bool, bool);
  void TurnTarget(bool, bool, bool);
  int GetKizunaStage(f32 *rate) const;
  void AddRecast(f32 recast, bool isRate, int slot);
  void SetAngry(bool isAngry, f32 time);
  void RegisterDelayVoice(DELAY_VOICE_TYPE type, f32 time, int voice, int group, int priority);
  bool IsAngry() const;
  void UpdateBuffEffect(int buff);
  void UpdateTargetLockArrow();
  void ResetChangeActionStopSeData();
  void ReturnBladeChange();
  ActionCommand *GetFreeCommand();
  bool IsRegisterCommand(ActionCommand::COMMAND_TYPE type) const;
  void ActionCommandRun(const ActionCommand *command, ActionCommand::COMMAND_TYPE type);
  void ActionCommandBladeArts(const ActionCommand *command, ActionCommand::COMMAND_TYPE type);
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
  void AddSlotRecast(int slot, f32 recast, bool isRate);
  bool AI_Rescue(ACTION_ID actionId, int target);
  bool AI_BladeChange(ACTION_ID actionId, int blade);
  bool AI_SpAttack(ACTION_ID actionId, bool, bool);
  bool AI_Arts(ACTION_ID actionId, int slot);
  bool AI_Attack(ACTION_ID actionId, bool);
  bool IsProcAI(bool) const;
  bool AI_Move(ACTION_ID actionId, bool, const AI_MOVE_PARAM *param);
  bool MoveStop(bool isForce);
  AI_ACTION_DATA GetAIActionData() const { return aiAction; }
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
  const CUSTOM_VOICE_DATA *GetCustomVoiceData(int voice, int *index) const;
  bool IsCustomVoice(int voice) const;
  void SetCustomVoiceEndFlag(int voice, bool isEnd);
  void ClearCustomVoiceEndFlag(u32 flags);
  int GetWeaponSeType() const;
  void GetMoveDataPerSec(mm::Vec3 &moveData) const;
  void SetAnimationSpeed(f32 speed);
  void NotifyStrikeDamage(int);
  void ResetAlphaRate(int alpha);
  void UpdateEffectPositionScale(int effect, const char *node, f32 scale);
  f32 GetSyncCount(bool isSlow) const;
  f32 GetDt(bool isSlow, bool isStopCheck) const;
  void RegisterSlow(SLOW_PROC_ID slow, f32 rate, f32 time);
  void DeleteSlow(SLOW_PROC_ID slow);
  int GetAlphaSetID(ALPHA_PROC_ID alpha);
  bool IsPause() const;
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
  u8 _20[0x50 - 0x20];
  mm::Vec3 direction;
  u8 _60[0xb0 - 0x60];
  mm::Vec3 moveData;
  u8 _c0[0xf4 - 0xc0];
  f32 landHeight;
  u8 _f8[0x118 - 0xf8];
  gf::GF_OBJ_HANDLE *handle;
  gf::GF_OBJ_HANDLE *target;
  u8 _128[0x130 - 0x128];
  u32 effects[EFFECT_ID_NUM];
  u8 _164[0x168 - 0x164];
  mutable const CharacterParameter *parameter;
  u8 _170[0xc58 - 0x170];
  char voiceCode[0x10];
  u8 _c68[0xcb8 - 0xc68];
  f32 animationSpeed;
  u8 _cbc[0xcc0 - 0xcbc];
  f32 dt;
  f32 systemDt;
  int bdatId;
  u8 _ccc[0xce0 - 0xccc];
  ANIMATION_MOVE_DISTANCE_DATA animationMoveDistances[20];
  u8 _d80[0xdb8 - 0xd80];
  f32 ikWeight;
  f32 ikHeight;
  u32 ikId : 7;
  u32 : 25;
  u8 _dc4[0xdd0 - 0xdc4];
  s16 delayVoiceTime;
  s16 delayVoicePriority;
  s16 delayVoiceGroup;
  u8 delayVoice;
  u8 _dd7[0xdd8 - 0xdd7];
  ALPHA_PROC_DATA alphaProcs[17];
  f32 alphaRates[7];
  u8 _f48[0xf4c - 0xf48];
  SLOW_PROC_DATA slows[1];
  f32 slowRate;
  u32 customVoiceFlags;
  u32 customVoiceEndFlags;
  CUSTOM_VOICE_DATA customVoices[3];
  s16 parameterId;
  u8 _f6c[0xf7d - 0xf6c];
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
  u8 _f90[0xf93 - 0xf90];
  u8 : 6;
  u8 isStop : 1;
  u8 _f94[0xfb0 - 0xf94];
  ActionCommand commands[10];
  int commandNum;
  u8 actionId;
  u8 _107d[0x107e - 0x107d];
  u16 actionPhase;
  u8 _1080[0x108c - 0x1080];
  int rescueTarget;
  u8 _1090[0x10c0 - 0x1090];
  u32 buttonChallenge;
  u32 changeActionStopSe : 16;
  u32 reactionId : 5;
  u32 : 3;
  u8 _10c7[0x10c8 - 0x10c7];
  s8 artsTarget;
  u8 _10c9[0x10e0 - 0x10c9];
  f32 noDamageTime;
  f32 superArmorTime;
  f32 perfectAvoidTime;
  u8 _10ec[0x10fe - 0x10ec];
  s16 backAttacker;
  u8 _1100[0x1160 - 0x1100];
  AI_ACTION_DATA aiAction;
  u8 _1168[0x1174 - 0x1168];
  f32 aiScoutTime;
  int aiState;
  u8 _117c[0x1180 - 0x117c];
  u32 aiFlags;
  u8 _1184[0x11cc - 0x1184];
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
static_assert(offsetof(BattleCharacter, direction) == 0x50, "");
static_assert(offsetof(BattleCharacter, moveData) == 0xb0, "");
static_assert(offsetof(BattleCharacter, landHeight) == 0xf4, "");
static_assert(offsetof(BattleCharacter, handle) == 0x118, "");
static_assert(offsetof(BattleCharacter, target) == 0x120, "");
static_assert(offsetof(BattleCharacter, effects) == 0x130, "");
static_assert(offsetof(BattleCharacter, parameter) == 0x168, "");
static_assert(offsetof(BattleCharacter, voiceCode) == 0xc58, "");
static_assert(offsetof(BattleCharacter, animationSpeed) == 0xcb8, "");
static_assert(offsetof(BattleCharacter, systemDt) == 0xcc4, "");
static_assert(offsetof(BattleCharacter, bdatId) == 0xcc8, "");
static_assert(offsetof(BattleCharacter, animationMoveDistances) == 0xce0, "");
static_assert(offsetof(BattleCharacter, ikWeight) == 0xdb8, "");
static_assert(offsetof(BattleCharacter, delayVoiceTime) == 0xdd0, "");
static_assert(offsetof(BattleCharacter, delayVoice) == 0xdd6, "");
static_assert(offsetof(BattleCharacter, alphaProcs) == 0xdd8, "");
static_assert(offsetof(BattleCharacter, alphaRates) == 0xf2c, "");
static_assert(offsetof(BattleCharacter, dt) == 0xcc0, "");
static_assert(offsetof(BattleCharacter, slows) == 0xf4c, "");
static_assert(offsetof(BattleCharacter, slowRate) == 0xf58, "");
static_assert(offsetof(BattleCharacter, customVoiceFlags) == 0xf5c, "");
static_assert(offsetof(BattleCharacter, customVoices) == 0xf64, "");
static_assert(offsetof(BattleCharacter, parameterId) == 0xf6a, "");
static_assert(offsetof(BattleCharacter, id) == 0xf7d, "");
static_assert(offsetof(BattleCharacter, aiId) == 0xf7e, "");
static_assert(offsetof(BattleCharacter, weaponType) == 0xf7f, "");
static_assert(offsetof(BattleCharacter, commands) == 0xfb0, "");
static_assert(offsetof(BattleCharacter, commandNum) == 0x1078, "");
static_assert(offsetof(BattleCharacter, actionId) == 0x107c, "");
static_assert(offsetof(BattleCharacter, actionPhase) == 0x107e, "");
static_assert(offsetof(BattleCharacter, rescueTarget) == 0x108c, "");
static_assert(offsetof(BattleCharacter, buttonChallenge) == 0x10c0, "");
static_assert(offsetof(BattleCharacter, artsTarget) == 0x10c8, "");
static_assert(offsetof(BattleCharacter, noDamageTime) == 0x10e0, "");
static_assert(offsetof(BattleCharacter, backAttacker) == 0x10fe, "");
static_assert(offsetof(BattleCharacter, aiAction) == 0x1160, "");
static_assert(offsetof(BattleCharacter, aiScoutTime) == 0x1174, "");
static_assert(offsetof(BattleCharacter, aiState) == 0x1178, "");
static_assert(offsetof(BattleCharacter, aiFlags) == 0x1180, "");
static_assert(offsetof(BattleCharacter, stopAiTime) == 0x11cc, "");
static_assert(offsetof(BattleCharacter, stamp) == 0x11d8, "");
static_assert(offsetof(BattleCharacter, bladeSupportConditionFlags) == 0x11e0, "");
static_assert(sizeof(BattleCharacter) == 0x11f0, "");

} // namespace btl
