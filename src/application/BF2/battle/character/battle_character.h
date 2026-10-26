#pragma once
#include <stddef.h>

#include "battle/arts_data.h"
#include "battle/character/action_command.h"
#include "battle/character/character_parameter_battle.h"
#include "mm_math/mm_vec3.h"
#include "types.h"

namespace fw {
struct UpdateInfo;
}

namespace gf {
struct GF_OBJ_HANDLE;
class GfComEffectCaster;
class GfComProperty;
class GfObj;
class GfWeapon;
} // namespace gf

enum BTL_SE {
  BTL_SE_HIT = 1,
};

namespace btl {

class GROUP_DATA;

class BattleCharacter {
public:
  enum ANIM_ID {};
  enum SLOW_PROC_ID {};
  enum DELAY_VOICE_TYPE {
    DELAY_VOICE_TYPE_NORMAL,
  };
  enum ALPHA_PROC_ID {};
  enum BLADE_TIMER_MODE {};
  enum RIMBLOOM_ID {};
  enum ACTION_ID {
    ACTION_ID_IDLE = 1,
    ACTION_ID_PUT_AWAY_WEAPON = 3,
    ACTION_ID_MOVE = 4,
    ACTION_ID_ATTACK = 6,
    ACTION_ID_ARTS = 7,
    ACTION_ID_BLADE_ARTS = 8,
    ACTION_ID_BLADE_CHANGE = 9,
    ACTION_ID_SP_ATTACK = 10,
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
    u8 unknown00; // Inferred role: voice id; original member name unknown.
    u8 unknown01; // Inferred role: voice type; original member name unknown.
  };

  enum EFFECT_ID {
    EFFECT_ID_KIZUNA_LINK = 1,
    EFFECT_ID_KIZUNA_AURA = 2,
    EFFECT_ID_NUM = 13,
  };

  struct ANIMATION_MOVE_DISTANCE_DATA {
    f32 unknown00; // Inferred role: distance; original member name unknown.
    u16 unknown04; // Inferred role: animation id; original member name unknown.
  };

  struct ALPHA_PROC_DATA {
    f32 unknown00; // Inferred role: target alpha rate; original member name unknown.
    f32 unknown04; // Inferred role: start alpha rate; original member name unknown.
    f32 unknown08; // Inferred role: alpha rate; original member name unknown.
    f32 unknown0c; // Inferred role: time; original member name unknown.
    f32 unknown10; // Inferred role: duration; original member name unknown.
  };

  struct SLOW_PROC_DATA {
    f32 unknown00; // Inferred role: slow rate; original member name unknown.
    f32 unknown04; // Inferred role: time; original member name unknown.
    f32 unknown08; // Inferred role: counter; original member name unknown.
  };

  struct AI_ACTION_DATA {
    u8 unknown00;  // Inferred role: action; original member name unknown.
    int unknown04; // Inferred role: target; original member name unknown.
  };

  struct DIRECT_DAMAGE_DATA {
    BattleCharacter *unknown00; // Inferred role: healer; original member name unknown.
    int unknown08;              // Inferred role: damage type; original member name unknown.
    u32 unknown0c;              // Inferred role: value; original member name unknown.
    u8 unknown10;               // Inferred role: heal flag; original member name unknown.
    u8 unknown11;               // Role and original member name unknown.
    u8 unknown12;               // Role and original member name unknown.
  };

  struct AI_MOVE_PARAM {
    AI_MOVE_PARAM() : unknown00(0.0f), unknown04(0.0f), unknown08(MOVE_TYPE_TARGET), unknown10(nullptr), unknown18(reinterpret_cast<gf::GF_OBJ_HANDLE *>(-1)) {}

    f32 unknown00;                // Inferred role: distance; original member name unknown.
    f32 unknown04;                // Inferred role: time; original member name unknown.
    MOVE_TYPE unknown08;          // Inferred role: move type; original member name unknown.
    const mm::Vec3 *unknown10;    // Inferred role: position; original member name unknown.
    gf::GF_OBJ_HANDLE *unknown18; // Inferred role: target handle; original member name unknown.
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
  void SetupCustomVoiceData();
  void ResetAnimationMoveDistance();
  void ResetAlphaAnimation();
  void InitializeEnhanceProcData(bool isFinalizeArtsEffect);
  const CharacterParameter *GetCharacterParameterConst(bool) const;
  bool IsPlayer() const;
  bool IsBlade() const;
  bool IsEnemy() const;
  bool IsDriver() const;
  void JoinProc(f32 rate, bool isScout);
  void SetWeaponType(int weaponType);
  void SetCollisionPriority(int priority);
  void StartFullBurst(int value);
  CharacterParameter *GetCharacterParameter(bool);
  bool IsControlCharacter() const;
  bool IsControlCharacterGroup() const;
  bool IsDead(u32 flags) const;
  bool IsMoveHealPot() const;
  void NotifyAngryEnd();
  void DispEnhanceName(const CharacterParameter::ENHANCE_DATA &data) const;
  void DispEnhanceNameDirect(int text, bool flag) const;
  int GetArtsAttr(const ARTS_DATA &data, u32 attack) const;
  f32 GetAnimationMoveLength(f32, f32, bool);
  bool GetObjectNearPosition(gf::GF_OBJ_HANDLE *handle, gf::GF_OBJ_HANDLE *target, mm::Vec3 &position, mm::Vec3 *, mm::Vec3 *) const;
  void CalcLocomotionMoveRate(f32 maxRate);
  bool IsNoDamage(bool) const;
  bool GetTargetPosDirection(const mm::Vec3 &position, mm::Vec3 &direction, bool, bool) const;
  bool GetTargetDirection(mm::Vec3 &direction, bool, bool, gf::GF_OBJ_HANDLE *target) const;
  void AddTrust(u32 point, int level);
  void StopStart(f32 time, bool isSyncBuddy);
  bool CheckPowerCharge(u32 attack);
  void NotifyBuddyFightCombo(gf::GF_OBJ_HANDLE *handle, int fightCombo);
  void NotifyBuddySufferFightCombo(int id, int fightCombo);
  void NotifyElementalCombo(gf::GF_OBJ_HANDLE *handle, int combo, bool isUnite);
  void NotifySufferElementalCombo(int id, int combo);
  void NotifyBuffEnd(int buff, f32 rest, bool isEnd);
  void NotifyAngryStart();
  void NotifyBackAttack(int id);
  void NotifyChangeAttr(gf::GF_OBJ_HANDLE *handle, u32 attribute, u32 oldAttribute);
  void NotifyDropHealpot();
  void NotifyEnemyAngry(gf::GF_OBJ_HANDLE *handle);
  void NotifyFriendDead(int id);
  void NotifyKillSpAttack();
  void NotifyLostHateTarget(int);
  void ResetHate();
  void SetAction(ACTION_ID actionId, bool, bool, int, f32);
  u8 CheckAttackPosition(gf::GF_OBJ_HANDLE *handle, bool, bool *) const;
  bool IsBattle() const;
  void DeleteKizunaAuraEffect();
  void DeleteKizunaLinkEffect();
  int GetBuffEffectIndex(int buff) const;
  void DeleteEffect(int effect, int fadeFrame);
  void CancelButtonChallenge();
  bool IsDispWeaponAlpha(int alpha) const;
  bool IsBoss() const;
  bool IsNamed() const;
  bool IsBossOrNamed() const;
  bool IsMove() const;
  bool IsBound() const;
  void SetRimBloom(RIMBLOOM_ID id, bool isEnable);
  int GetGroupIndex() const;
  void AddUseWeapon();
  void StartBladeTimer(BLADE_TIMER_MODE mode);
  void EndBladeTimer(BLADE_TIMER_MODE mode);
  void PlaySE(BTL_SE se, int number, const mm::Vec3 *position, bool isFollow);
  void PlayHitAttrSE(int attribute, const mm::Vec3 *position);
  void PlayHitBulletSE(int attribute, const mm::Vec3 *position);
  int GetIKData(f32 &weight, f32 &height) const;
  void SetupPosDir();
  const GROUP_DATA *GetGroupDataConst() const;
  bool IsEnableSpeakVoice() const;
  gf::GF_OBJ_HANDLE *GetBuddyTargetObjectHandle() const;
  int GetTrustRank(int index) const;
  bool IsPriorityReaction(int left, int right) const;
  int GetArtsSlotIndex(int arts) const;
  bool IsBladeArtsEnd() const;
  bool IsPerfectAvoid() const;
  gf::GF_OBJ_HANDLE *GetWeaponObjectHandle(bool isAlternate) const;
  void ResetRequestPermit();
  gf::GfComProperty *GetComPropertyConst() const;
  gf::GfComEffectCaster *GetEffectCaster();
  gf::GfWeapon *GetWeaponInfo() const;
  gf::GfComEffectCaster *GetWeaponEffectCaster();
  int GetDriverType() const;
  bool IsAnimationEnd() const;
  const void *GetAnimationAppendix(const char *) const;
  const char *GetNowAnimationStateName() const;
  bool IsAnimationState(const char *) const;
  f32 GetAnimationTime() const;
  f32 GetAnimationFrame() const;
  f32 GetAnimationLengthFrame() const;
  f32 GetAnimationLengthSec() const;
  bool IsEnableTurnAI() const;
  void TurnDirection(const mm::Vec3 &direction, bool, bool);
  void TurnTarget(bool, bool, bool);
  int GetKizunaStage(f32 *rate) const;
  int GetHateEnemyNum() const;
  int GetSeType(int type, int attr) const;
  void AddRecast(f32 recast, bool isRate, int slot);
  bool SetAngry(bool isAngry, f32 time);
  void RegisterDelayVoice(DELAY_VOICE_TYPE type, f32 time, int voice, int group, int priority);
  bool IsAngry() const;
  void UpdateBuffEffect();
  void UpdateBuffEffect(int buff);
  void UpdateLaunchEffect();
  f32 GetLaunchEffectScale() const;
  void UpdateTargetLockArrow();
  void DispElementalEffectUI(int effect);
  void SlowProc();
  void ScoutProc();
  f32 GetChainSec();
  f32 SatisfyEnhanceCondition(int enhance, int, f32, void *, bool);
  void ResetChangeActionStopSeData();
  void ReturnBladeChange();
  void ReturnBladeArts();
  void FinalizeArtsEffect(bool);
  ActionCommand *GetFreeCommand();
  ActionCommand *GetActionCommand(ACTION_ID action, bool isSet);
  bool IsRegisterCommand(ActionCommand::COMMAND_TYPE type) const;
  void ActionCommandRun(const ActionCommand *command, ActionCommand::COMMAND_TYPE type);
  void ActionCommandBladeArts(const ActionCommand *command, ActionCommand::COMMAND_TYPE type);
  void HealDirect(u32 value, int, BattleCharacter *healer);
  void HealHpRate(f32 rate, int, BattleCharacter *healer);
  void AddPartyGauge(f32 value);
  void FluctuatePartyGauge(int);
  void StartBackHome();
  bool IsInAttackRange(int slot, f32 *distance) const;
  int IsEnableArts(int, int slot, int, gf::GF_OBJ_HANDLE *target) const;
  bool IsRescue() const;
  void AddKizuna(f32 kizuna);
  void AddKizunaStage(int stage);
  void SetKizunaStage(int stage);
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
  AI_ACTION_DATA GetAIActionData() const { return unknown1160; }
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
  bool PlayCustomVoice(int voice);
  void ClearCustomVoiceEndFlag(u32 flags);
  int GetWeaponSeType() const;
  void GetMoveDataPerSec(mm::Vec3 &moveData) const;
  void SetAnimationSpeed(f32 speed);
  void SetIKData(const ARTS_DATA &data);
  void NotifyStrikeDamage(int);
  void NotifyDirectDamage(const DIRECT_DAMAGE_DATA &data);
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
  f32 GetArtsDamageRate(const ARTS_DATA::LEVEL_DATA &level) const;
  f32 ApplyResistantAttr(f32 damage, int attribute) const;
  f32 GetArtsDamageRate(const ARTS_DATA &data, int level) const;
  void EnhanceTimerProc();
  void StopAI(f32 time);
  bool CheckRandFriendEnhanceRate(int enhance) const;
  void ResetBladeSupportConditionFlag();
  void ResetActionCommand();
  void ActionCommandEndRun();
  void UpdateCulling();
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

  // Inferred role: sets the stop time to the longest of the current and the new one; original name unknown.
  void unknown001(f32 time) {
    f32 stop;
    if (time <= 0.0f) {
      stop = 0.0f;
    } else {
      stop = unknownccc > time ? unknownccc : time;
    }
    unknownccc = stop;
  }

  u8 _08[0x10 - 0x08];
  mm::Vec3 unknown10; // Inferred role: position; original member name unknown.
  u8 _20[0x50 - 0x20];
  mm::Vec3 unknown50; // Inferred role: direction; original member name unknown.
  u8 _60[0xb0 - 0x60];
  mm::Vec3 unknownb0; // Inferred role: move data; original member name unknown.
  u8 _c0[0xf4 - 0xc0];
  f32 unknownf4; // Inferred role: land height; original member name unknown.
  u8 _f8[0x118 - 0xf8];
  gf::GF_OBJ_HANDLE *unknown118; // Inferred role: object handle; original member name unknown.
  gf::GF_OBJ_HANDLE *unknown120; // Inferred role: target handle; original member name unknown.
  gf::GF_OBJ_HANDLE *unknown128; // Inferred role: second target handle; original member name unknown.
  u32 unknown130[EFFECT_ID_NUM]; // Inferred role: effects; original member name unknown.
  u8 _164[0x168 - 0x164];
  mutable const CharacterParameter *unknown168; // Inferred role: parameter; original member name unknown.
  u8 _170[0xc58 - 0x170];
  char unknownc58[0x10]; // Inferred role: voice code; original member name unknown.
  u8 _c68[0xcb8 - 0xc68];
  f32 m_animationSpeed;
  u8 _cbc[0xcc0 - 0xcbc];
  f32 unknowncc0; // Inferred role: delta time; original member name unknown.
  f32 m_systemDt;
  int unknowncc8; // Inferred role: bdat id; original member name unknown.
  f32 unknownccc; // Inferred role: stop time; original member name unknown.
  f32 unknowncd0; // Inferred role: blade timer; original member name unknown.
  u8 _cd4[0xcdc - 0xcd4];
  f32 unknowncdc;                              // Role and original member name unknown.
  ANIMATION_MOVE_DISTANCE_DATA unknownce0[20]; // Inferred role: animation move distances; original member name unknown.
  u8 _d80[0xdb4 - 0xd80];
  u8 : 7;
  u8 unknowndb4_7 : 1; // Role and original member name unknown.
  u8 _db5[0xdb8 - 0xdb5];
  f32 unknowndb8;       // Inferred role: IK weight; original member name unknown.
  f32 unknowndbc;       // Inferred role: IK height; original member name unknown.
  u32 unknowndc0_0 : 7; // Inferred role: IK id; original member name unknown.
  u32 unknowndc0_7 : 4; // Inferred role: IK start number; original member name unknown.
  u32 unknowndc1_3 : 8; // Inferred role: IK start frame; original member name unknown.
  u32 unknowndc2_3 : 4; // Inferred role: IK end number; original member name unknown.
  u32 unknowndc2_7 : 8; // Inferred role: IK end frame; original member name unknown.
  u32 unknowndc3_7 : 1; // Inferred role: IK flag; original member name unknown.
  u8 _dc4[0xdd0 - 0xdc4];
  s16 unknowndd0; // Inferred role: delay voice time; original member name unknown.
  s16 unknowndd2; // Inferred role: delay voice priority; original member name unknown.
  s16 unknowndd4; // Inferred role: delay voice group; original member name unknown.
  u8 unknowndd6;  // Inferred role: delay voice id; original member name unknown.
  u8 _dd7[0xdd8 - 0xdd7];
  ALPHA_PROC_DATA unknowndd8[17]; // Inferred role: alpha procs; original member name unknown.
  f32 unknownf2c[7];              // Inferred role: alpha rates; original member name unknown.
  u8 _f48[0xf4c - 0xf48];
  SLOW_PROC_DATA unknownf4c[1];    // Inferred role: slows; original member name unknown.
  f32 unknownf58;                  // Inferred role: slow rate; original member name unknown.
  u32 unknownf5c;                  // Inferred role: custom voice flags; original member name unknown.
  u32 unknownf60;                  // Inferred role: custom voice end flags; original member name unknown.
  CUSTOM_VOICE_DATA unknownf64[3]; // Inferred role: custom voices; original member name unknown.
  s16 unknownf6a;                  // Inferred role: parameter id; original member name unknown.
  u8 _f6c[0xf72 - 0xf6c];
  u16 unknownf72; // Inferred role: effect scale rate; original member name unknown.
  u8 _f74[0xf76 - 0xf74];
  u16 m_driverType : 3;
  u16 : 6;
  u16 unknownf77_1 : 3; // Inferred role: blade timer mode; original member name unknown.
  u16 : 4;
  u16 unknownf78_0 : 10; // Inferred role: SE type; original member name unknown.
  u16 : 6;
  u16 unknownf7a; // Inferred role: rim bloom flags; original member name unknown.
  u8 unknownf7c;  // Inferred role: bound action id; original member name unknown.
  s8 unknownf7d;  // Inferred role: id; original member name unknown.
  s8 unknownf7e;  // Inferred role: AI id; original member name unknown.
  s8 unknownf7f;  // Inferred role: weapon type; original member name unknown.
  u8 _f80[0xf83 - 0xf80];
  u8 unknownf83; // Inferred role: camera fade disable for battle; original member name unknown.
  u8 _f84[0xf86 - 0xf84];
  u8 unknownf86; // Role and original member name unknown.
  u8 _f87[0xf8c - 0xf87];
  u8 : 7;
  u8 m_player : 1;
  u8 m_battle : 1;
  u8 : 7;
  // Kept apart from the bitfields around it: in one run, clang reads unknownf8f_7 with a 32-bit load (Utility::AI_IsFly).
  struct {
    u8 : 4;
    u8 unknownf8e_4 : 1; // Inferred role: event flag; original member name unknown.
    u8 : 3;
  };
  u8 : 7;
  u8 unknownf8f_7 : 1; // Inferred role: fly flag; original member name unknown.
  u8 unknownf90;       // Inferred role: bound flags; original member name unknown.
  u8 _f91[0xf93 - 0xf91];
  u8 : 6;
  u8 unknownf93_6 : 1; // Inferred role: stop flag; original member name unknown.
  u8 _f94[0xfb0 - 0xf94];
  ActionCommand unknownfb0[10]; // Inferred role: action commands; original member name unknown.
  int unknown1078;              // Inferred role: command count; original member name unknown.
  u8 unknown107c;               // Inferred role: action id; original member name unknown.
  u8 _107d[0x107e - 0x107d];
  u16 unknown107e; // Inferred role: action phase; original member name unknown.
  int unknown1080; // Inferred role: action phase time; original member name unknown.
  u8 _1084[0x108c - 0x1084];
  int unknown108c; // Inferred role: rescue target; original member name unknown.
  u8 _1090[0x10a0 - 0x1090];
  int unknown10a0; // Inferred role: send power state; original member name unknown.
  f32 unknown10a4; // Inferred role: send power time; original member name unknown.
  u32 unknown10a8; // Inferred role: send power value; original member name unknown.
  u16 unknown10ac; // Inferred role: full burst counter; original member name unknown.
  u8 unknown10ae;  // Inferred role: full burst count; original member name unknown.
  u8 _10af[0x10b0 - 0x10af];
  f32 unknown10b0; // Inferred role: full burst time; original member name unknown.
  u8 _10b4[0x10c0 - 0x10b4];
  u32 unknown10c0;        // Inferred role: button challenge id; original member name unknown.
  u32 unknown10c4_0 : 16; // Inferred role: change action stop SE; original member name unknown.
  u32 unknown10c6_0 : 5;  // Inferred role: reaction id; original member name unknown.
  u32 unknown10c6_5 : 3;  // Inferred role: reaction state; original member name unknown.
  u8 _10c7[0x10c8 - 0x10c7];
  s8 unknown10c8; // Inferred role: arts target; original member name unknown.
  u8 _10c9[0x10d0 - 0x10c9];
  f32 unknown10d0; // Role and original member name unknown.
  u8 _10d4[0x10e0 - 0x10d4];
  f32 unknown10e0; // Inferred role: no damage time; original member name unknown.
  f32 unknown10e4; // Inferred role: super armor time; original member name unknown.
  f32 unknown10e8; // Inferred role: perfect avoid time; original member name unknown.
  u8 _10ec[0x10f4 - 0x10ec];
  u16 unknown10f4; // Inferred role: displayed elemental effect flags; original member name unknown.
  u8 _10f6[0x10fe - 0x10f6];
  s16 unknown10fe; // Inferred role: back attacker; original member name unknown.
  u8 _1100[0x1108 - 0x1100];
  f32 unknown1108[7]; // Inferred role: enhance timers; original member name unknown.
  u8 _1124[0x1160 - 0x1124];
  AI_ACTION_DATA unknown1160; // Inferred role: AI action; original member name unknown.
  u8 _1168[0x1174 - 0x1168];
  f32 unknown1174; // Inferred role: AI scout time; original member name unknown.
  int unknown1178; // Inferred role: AI state; original member name unknown.
  u8 _117c[0x1180 - 0x117c];
  u32 unknown1180; // Inferred role: AI flags; original member name unknown.
  u8 _1184[0x11cc - 0x1184];
  f32 unknown11cc; // Inferred role: stop AI time; original member name unknown.
  u8 _11d0[0x11d8 - 0x11d0];
  int unknown11d8; // Inferred role: stamp; original member name unknown.
  u8 _11dc[0x11e0 - 0x11dc];
  u16 unknown11e0; // Inferred role: blade support condition flags; original member name unknown.
  u16 : 10;
  u16 unknown11e3_2 : 1; // Inferred role: use navi flag; original member name unknown.
  u16 unknown11e3_3 : 1; // Inferred role: battle opening flag; original member name unknown.
  u8 _11e4[0x11f0 - 0x11e4];
};

static_assert(sizeof(BattleCharacter::DIRECT_DAMAGE_DATA) == 0x18, "");
static_assert(offsetof(BattleCharacter, unknown10) == 0x10, "");
static_assert(offsetof(BattleCharacter, unknown50) == 0x50, "");
static_assert(offsetof(BattleCharacter, unknownb0) == 0xb0, "");
static_assert(offsetof(BattleCharacter, unknownf4) == 0xf4, "");
static_assert(offsetof(BattleCharacter, unknown118) == 0x118, "");
static_assert(offsetof(BattleCharacter, unknown120) == 0x120, "");
static_assert(offsetof(BattleCharacter, unknown128) == 0x128, "");
static_assert(offsetof(BattleCharacter, unknown130) == 0x130, "");
static_assert(offsetof(BattleCharacter, unknown168) == 0x168, "");
static_assert(offsetof(BattleCharacter, unknownc58) == 0xc58, "");
static_assert(offsetof(BattleCharacter, m_animationSpeed) == 0xcb8, "");
static_assert(offsetof(BattleCharacter, m_systemDt) == 0xcc4, "");
static_assert(offsetof(BattleCharacter, unknowncc8) == 0xcc8, "");
static_assert(offsetof(BattleCharacter, unknownccc) == 0xccc, "");
static_assert(offsetof(BattleCharacter, unknowncdc) == 0xcdc, "");
static_assert(offsetof(BattleCharacter, unknownce0) == 0xce0, "");
static_assert(offsetof(BattleCharacter, unknowndb8) == 0xdb8, "");
static_assert(offsetof(BattleCharacter, unknowndd0) == 0xdd0, "");
static_assert(offsetof(BattleCharacter, unknowndd6) == 0xdd6, "");
static_assert(offsetof(BattleCharacter, unknowndd8) == 0xdd8, "");
static_assert(offsetof(BattleCharacter, unknownf2c) == 0xf2c, "");
static_assert(offsetof(BattleCharacter, unknowncc0) == 0xcc0, "");
static_assert(offsetof(BattleCharacter, unknownf4c) == 0xf4c, "");
static_assert(offsetof(BattleCharacter, unknownf58) == 0xf58, "");
static_assert(offsetof(BattleCharacter, unknownf5c) == 0xf5c, "");
static_assert(offsetof(BattleCharacter, unknownf64) == 0xf64, "");
static_assert(offsetof(BattleCharacter, unknownf6a) == 0xf6a, "");
static_assert(offsetof(BattleCharacter, unknownf72) == 0xf72, "");
static_assert(offsetof(BattleCharacter, unknownf7a) == 0xf7a, "");
static_assert(offsetof(BattleCharacter, unknownf7c) == 0xf7c, "");
static_assert(offsetof(BattleCharacter, unknownf7d) == 0xf7d, "");
static_assert(offsetof(BattleCharacter, unknownf7e) == 0xf7e, "");
static_assert(offsetof(BattleCharacter, unknownf7f) == 0xf7f, "");
static_assert(offsetof(BattleCharacter, unknownf83) == 0xf83, "");
static_assert(offsetof(BattleCharacter, unknownf86) == 0xf86, "");
static_assert(offsetof(BattleCharacter, unknownf90) == 0xf90, "");
static_assert(offsetof(BattleCharacter, unknownfb0) == 0xfb0, "");
static_assert(offsetof(BattleCharacter, unknown1078) == 0x1078, "");
static_assert(offsetof(BattleCharacter, unknown107c) == 0x107c, "");
static_assert(offsetof(BattleCharacter, unknown107e) == 0x107e, "");
static_assert(offsetof(BattleCharacter, unknown1080) == 0x1080, "");
static_assert(offsetof(BattleCharacter, unknown108c) == 0x108c, "");
static_assert(offsetof(BattleCharacter, unknown10a0) == 0x10a0, "");
static_assert(offsetof(BattleCharacter, unknown10a4) == 0x10a4, "");
static_assert(offsetof(BattleCharacter, unknown10c0) == 0x10c0, "");
static_assert(offsetof(BattleCharacter, unknown10c8) == 0x10c8, "");
static_assert(offsetof(BattleCharacter, unknown10d0) == 0x10d0, "");
static_assert(offsetof(BattleCharacter, unknown10f4) == 0x10f4, "");
static_assert(offsetof(BattleCharacter, unknown10e0) == 0x10e0, "");
static_assert(offsetof(BattleCharacter, unknown10fe) == 0x10fe, "");
static_assert(offsetof(BattleCharacter, unknown1108) == 0x1108, "");
static_assert(offsetof(BattleCharacter, unknown1160) == 0x1160, "");
static_assert(offsetof(BattleCharacter, unknown1174) == 0x1174, "");
static_assert(offsetof(BattleCharacter, unknown1178) == 0x1178, "");
static_assert(offsetof(BattleCharacter, unknown1180) == 0x1180, "");
static_assert(offsetof(BattleCharacter, unknown11cc) == 0x11cc, "");
static_assert(offsetof(BattleCharacter, unknown11d8) == 0x11d8, "");
static_assert(offsetof(BattleCharacter, unknown11e0) == 0x11e0, "");
static_assert(sizeof(BattleCharacter) == 0x11f0, "");

} // namespace btl
