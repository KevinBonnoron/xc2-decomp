#include "battle/character/battle_character.h"

#include <float.h>

#include "battle/battle_global.h"
#include "battle/btl_system_balance_access.h"
#include "battle/button_challenge.h"
#include "battle/character/character_parameter_battle.h"
#include "battle/data_manager_battle.h"
#include "battle/hate_ring_manager.h"
#include "battle/misc_battle.h"
#include "battle/talk_manager_battle.h"
#include "battle/utility_battle.h"
#include "framework/effect/effect_manager.h"
#include "gf/data/gf_data_weapon.h"
#include "gf/game/gf_game_manager.h"
#include "gf/game/gf_game_party.h"
#include "gf/object/gf_obj_handle.h"
#include "gf/object/gf_obj_util.h"
#include "gf/request/gf_req_scom.h"
#include "ml/rand.h"

namespace btl {

constexpr int ALPHA_RATE_NUM = 7;
constexpr f32 PAUSE_DT = 0.000001f;
constexpr u16 ANIMATION_INVALID = 39;
constexpr int ALPHA_WEAPON_FIRST = 12;
constexpr int ALPHA_WEAPON_LAST = 16;
constexpr int ALPHA_PROC_WEAPON = 6;
constexpr int ALPHA_PROC_LAST = 11;
constexpr int SE_HIT_ATTRIBUTE = 9;
constexpr int SE_HIT_BULLET = 17;
constexpr int SLOT_ALL = -17;
constexpr f32 DELAY_VOICE_TIME_SCALE = 4096.0f;
constexpr int BUFF_EFFECT_TARGET_LOCK = 8;
constexpr int COMMAND_NUM = 10;
constexpr u16 ACTION_PHASE_BLADE_ARTS_MOVE = 8;
constexpr u16 ACTION_PHASE_BLADE_CHANGE_RETURN = 6;
constexpr int AI_STATE_ACTIVE = 1;
constexpr f32 AI_SCOUT_TIME = 10.0f;
constexpr u32 BLADE_CHANGE_ACTIONS = 0xd2;
constexpr int BLADE_SUPPORT_CONDITION_HATE_ELSE = 8;

void BattleCharacter::ResetHateRingData() {
  if (!isPlayer && handle != gf::INVALID_HANDLE && id >= 0) {
    HateRingManager::get()->SetData(id, handle, -1);
  }
}

void BattleCharacter::ResetDelayVoice() { delayVoiceTime = -1; }

void BattleCharacter::ResetCustomVoiceData() {
  customVoiceFlags = 0;
  customVoiceEndFlags = 0;
  for (int i = 0; i < 3; i++) {
    customVoices[i].voice = 0;
    customVoices[i].type = 0;
  }
}

const CharacterParameter *BattleCharacter::GetCharacterParameterConst(bool) const {
  if (parameter == nullptr) {
    if (parameterId < 0) {
      return nullptr;
    }
    parameter = DataManager::get()->GetCharacterParameterConst(parameterId);
  }
  return parameter;
}

bool BattleCharacter::IsPlayer() const { return isPlayer; }

bool BattleCharacter::IsBlade() const {
  const CharacterParameter *parameter = GetCharacterParameterConst(true);
  return parameter != nullptr && parameter->isBlade;
}

gf::GfObj *BattleCharacter::GetObject() const { return gf::GfObjUtil::getObj(handle); }

bool BattleCharacter::IsEnemy() const { return !isPlayer; }

bool BattleCharacter::IsDriver() const {
  const CharacterParameter *parameter = GetCharacterParameterConst(true);
  return parameter != nullptr && !parameter->isBlade && parameter->buddy != gf::INVALID_HANDLE;
}

CharacterParameter *BattleCharacter::GetCharacterParameter(bool isBattle) {
  return const_cast<CharacterParameter *>(GetCharacterParameterConst(isBattle));
}

gf::GF_OBJ_HANDLE *BattleCharacter::GetControlCharacterHandle() const { return Utility::GetControlCharacterHandle(); }

gf::GfObj *BattleCharacter::GetObject(gf::GF_OBJ_HANDLE *handle) const { return gf::GfObjUtil::getObj(handle); }

bool BattleCharacter::IsBattle() const { return isBattle; }

void BattleCharacter::ResetAnimationMoveDistance() {
  for (int i = 0; i < 20; i++) {
    animationMoveDistances[i].animation = ANIMATION_INVALID;
  }
}

void BattleCharacter::ResetAlphaAnimation() {
  for (int i = 0; i < 17; i++) {
    alphaProcs[i].duration = 0.0f;
    alphaProcs[i].time = 0.0f;
    alphaProcs[i].startRate = -1.0f;
    alphaProcs[i].rate = -1.0f;
    alphaProcs[i].targetRate = -1.0f;
  }
}

void BattleCharacter::InitializeEnhanceProcData(bool isFinalizeArtsEffect) {
  for (f32 &timer : enhanceTimers) {
    timer = 0.0f;
  }
  if (isFinalizeArtsEffect) {
    FinalizeArtsEffect(true);
  }
}

void BattleCharacter::DeleteKizunaAuraEffect() {
  if (effects[EFFECT_ID_KIZUNA_AURA] != 0) {
    if (gf::GfGameManager::isPlayEvent()) {
      fw::EffectManager::get()->remove(effects[EFFECT_ID_KIZUNA_AURA]);
    } else {
      fw::EffectManager::get()->dead(effects[EFFECT_ID_KIZUNA_AURA]);
    }
    effects[EFFECT_ID_KIZUNA_AURA] = 0;
  }
}

void BattleCharacter::CancelButtonChallenge() {
  if (buttonChallenge != 0) {
    BattleGlobal::get()->buttonChallenge.Cancel(buttonChallenge);
    buttonChallenge = 0;
  }
}

bool BattleCharacter::IsDispWeaponAlpha(int alpha) const {
  if (alpha >= ALPHA_WEAPON_FIRST && alpha <= ALPHA_WEAPON_LAST) {
    f32 rate = alphaProcs[alpha].rate;
    return rate < 0.0f || rate > 0.0f;
  }
  return false;
}

bool BattleCharacter::IsBoss() const {
  const CharacterParameter *parameter = GetCharacterParameterConst(true);
  return parameter != nullptr && parameter->IsBoss();
}

bool BattleCharacter::IsNamed() const {
  const CharacterParameter *parameter = GetCharacterParameterConst(true);
  return parameter != nullptr && parameter->IsNamed();
}

bool BattleCharacter::IsBossOrNamed() const {
  const CharacterParameter *parameter = GetCharacterParameterConst(true);
  return parameter != nullptr && parameter->IsBossOrNamed();
}

bool BattleCharacter::IsMove() const { return actionId == ACTION_ID_MOVE || aiState == AI_STATE_ACTIVE; }

void BattleCharacter::AddUseWeapon() {
  CharacterParameter *parameter = GetCharacterParameter(true);
  if (parameter != nullptr) {
    int weapon = weaponType;
    parameter->AddUseWeapon(weapon);
  }
}

void BattleCharacter::EndBladeTimer(BLADE_TIMER_MODE mode) {
  if (bladeTimerMode == mode) {
    bladeTimer = 0.0f;
    bladeTimerMode = 0;
  }
}

void BattleCharacter::PlayHitAttrSE(int attribute, const mm::Vec3 *position) {
  if (attribute >= 1 && attribute <= ATTRIBUTE_COUNT) {
    PlaySE(BTL_SE_HIT, attribute + SE_HIT_ATTRIBUTE, position, true);
  }
}

void BattleCharacter::PlayHitBulletSE(int attribute, const mm::Vec3 *position) {
  if (attribute >= 1 && attribute <= ATTRIBUTE_COUNT) {
    PlaySE(BTL_SE_HIT, attribute + SE_HIT_BULLET, position, true);
  }
}

int BattleCharacter::GetIKData(f32 &weight, f32 &height) const {
  int id = ikId;
  if (id == 0) {
    weight = 0.0f;
    height = 0.0f;
    return id;
  }
  weight = ikWeight;
  height = ikHeight;
  return id;
}

void BattleCharacter::SetupPosDir() {
  landHeight = FLT_MAX;
  Misc::GetObjectTransform(handle, position, Misc::TRANS_TYPE_POSITION);
  Misc::GetObjectDirection(handle, direction, true);
}

int BattleCharacter::GetGroupIndex() const {
  const CharacterParameter *parameter = GetCharacterParameterConst(true);
  return parameter != nullptr ? parameter->partyId : -1;
}

bool BattleCharacter::IsEnableBackHome() const { return actionId == ACTION_ID_IDLE; }

bool BattleCharacter::IsDisp() const { return alphaRates[0] > 0.0f; }

int BattleCharacter::GetWeaponType(bool isAsm) const {
  if (isAsm) {
    return gf::GfDataWeapon::getAsmWeaponType(weaponType);
  }

  return weaponType;
}

const BattleCharacter::CUSTOM_VOICE_DATA *BattleCharacter::GetCustomVoiceData(int voice, int *index) const {
  for (int i = 0; i < 3; i++) {
    if (customVoices[i].voice == voice) {
      if (index != nullptr) {
        *index = i;
      }
      return &customVoices[i];
    }
  }
  return nullptr;
}

bool BattleCharacter::IsCustomVoice(int voice) const {
  u32 flag = 1 << voice;
  if ((customVoiceFlags & flag) == 0) {
    return false;
  }

  return (customVoiceEndFlags & flag) == 0;
}

void BattleCharacter::SetCustomVoiceEndFlag(int voice, bool isEnd) {
  if (isEnd) {
    customVoiceEndFlags |= 1 << voice;
  } else {
    customVoiceEndFlags &= ~(1 << voice);
  }
}

void BattleCharacter::ClearCustomVoiceEndFlag(u32 flags) { customVoiceEndFlags &= ~flags; }

int BattleCharacter::GetWeaponSeType() const { return Utility::GetWeaponSeType(weaponType); }

bool BattleCharacter::IsEnableTurnAI() const { return ((1 << actionId) & ((1 << ACTION_ID_IDLE) | (1 << ACTION_ID_MOVE))) != 0; }

void BattleCharacter::GetMoveDataPerSec(mm::Vec3 &moveData) const {
  moveData.x = this->moveData.x * FRAME_RATE;
  moveData.y = this->moveData.y * FRAME_RATE;
  moveData.z = this->moveData.z * FRAME_RATE;
}

void BattleCharacter::SetAnimationSpeed(f32 speed) { animationSpeed = speed; }

void BattleCharacter::SetIKData(const ARTS_DATA &data) {
  ikStartNo = data.unknown15_0;
  ikStartFrame = data.unknown15_4;
  ikEndNo = data.unknown16_4;
  ikEndFrame = data.unknown17_0;
  isIK = data.unknown2f_0;
}

void BattleCharacter::NotifyStrikeDamage(int) { TalkManager::get()->NotifyTrigger(id, TalkManager::TRIGGER_STRIKE_DAMAGE, 0, 0); }

void BattleCharacter::LandingCallback() {}

void BattleCharacter::BoundCallback() {}

void BattleCharacter::ResetAlphaRate(int alpha) {
  int first = 0;
  int last = ALPHA_RATE_NUM - 1;
  if (alpha >= 0) {
    first = alpha;
    last = alpha;
  }

  for (int i = first; i <= last; i++) {
    alphaRates[i] = -1.0f;
  }
}

f32 BattleCharacter::GetSyncCount(bool isSlow) const { return GetDt(isSlow, true) * FRAME_RATE; }

f32 BattleCharacter::GetDt(bool isSlow, bool isStopCheck) const {
  if (isStopCheck && isStop) {
    return 0.0f;
  }
  return isSlow ? dt * slowRate : dt;
}

void BattleCharacter::RegisterSlow(SLOW_PROC_ID slow, f32 rate, f32 time) {
  slows[slow].rate = rate;
  slows[slow].time = time;
  slows[slow].counter = 0.0f;
}

void BattleCharacter::DeleteSlow(SLOW_PROC_ID slow) {
  slows[slow].rate = 1.0f;
  slows[slow].time = 0.0f;
  slows[slow].counter = 0.0f;
}

int BattleCharacter::GetAlphaSetID(ALPHA_PROC_ID alpha) {
  int id = alpha;
  if (id > ALPHA_PROC_LAST) {
    return ALPHA_PROC_WEAPON;
  }
  if (id >= 0 && id < ALPHA_PROC_WEAPON) {
    return id;
  }
  if (id >= ALPHA_PROC_WEAPON && id <= ALPHA_PROC_LAST) {
    return id - ALPHA_PROC_WEAPON;
  }
  return -1;
}

void BattleCharacter::AddRecast(f32 recast, bool isRate, int slot) { AddSlotRecast(slot < 0 ? SLOT_ALL : -1 - slot, recast, isRate); }

void BattleCharacter::RegisterDelayVoice(DELAY_VOICE_TYPE type, f32 time, int voice, int group, int priority) {
  if (type == DELAY_VOICE_TYPE_NORMAL) {
    delayVoiceTime = time * (1.0f / FRAME_RATE) * DELAY_VOICE_TIME_SCALE;
    delayVoicePriority = priority;
    delayVoiceGroup = group;
    delayVoice = voice;
  }
}

bool BattleCharacter::IsAngry() const {
  const CharacterParameter *parameter = GetCharacterParameterConst(true);
  return parameter != nullptr && parameter->IsAngry();
}

void BattleCharacter::UpdateBuffEffect(int buff) {
  if (buff == BUFF_EFFECT_TARGET_LOCK) {
    UpdateTargetLockArrow();
  } else {
    UpdateEffectPositionScale(buff, nullptr, -1.0f);
  }
}

void BattleCharacter::ResetChangeActionStopSeData() { changeActionStopSe = 0; }

void BattleCharacter::ReturnBladeChange() {
  SetAction(ACTION_ID_BLADE_CHANGE, false, false, 0, 0.0f);
  actionPhase = ACTION_PHASE_BLADE_CHANGE_RETURN;
}

ActionCommand *BattleCharacter::GetFreeCommand() {
  if (commandNum >= COMMAND_NUM) {
    return nullptr;
  }
  ActionCommand *command = &commands[commandNum];
  commandNum++;
  command->Reset();
  return command;
}

bool BattleCharacter::IsRegisterCommand(ActionCommand::COMMAND_TYPE type) const {
  for (int i = 0; i < commandNum; i++) {
    if (commands[i].type == type) {
      return true;
    }
  }
  return false;
}

void BattleCharacter::ActionCommandBladeArts(const ActionCommand *command, ActionCommand::COMMAND_TYPE type) {
  if ((type == ActionCommand::COMMAND_TYPE_MOVE_DIR_RATE || type == ActionCommand::COMMAND_TYPE_MOVE_LOCK) &&
      actionPhase == ACTION_PHASE_BLADE_ARTS_MOVE) {
    ActionCommandRun(command, type);
  }
}

bool BattleCharacter::IsRescue() const {
  if (actionId == ACTION_ID_RESCUE) {
    return true;
  }
  if (actionId == ACTION_ID_MOVE && aiState == AI_STATE_ACTIVE && aiAction.action == ACTION_ID_RESCUE) {
    return true;
  }
  return false;
}

bool BattleCharacter::MoveStop(bool isForce) {
  if (aiState != AI_STATE_ACTIVE || aiAction.action != ACTION_ID_IDLE || (aiFlags & AI_FLAG_SCOUT) != 0) {
    return false;
  }
  aiFlags |= isForce ? AI_FLAG_STOP_FORCE : AI_FLAG_STOP;
  return true;
}

void BattleCharacter::SetScout(bool isScout) {
  if (aiState == AI_STATE_ACTIVE) {
    if (isScout) {
      aiFlags |= AI_FLAG_SCOUT;
      aiScoutTime += AI_SCOUT_TIME;
    } else {
      aiFlags &= ~AI_FLAG_SCOUT;
    }
  }
}

bool BattleCharacter::IsScout() const { return aiState == AI_STATE_ACTIVE && (aiFlags & AI_FLAG_SCOUT) != 0; }

gf::GF_OBJ_HANDLE *BattleCharacter::GetRescueTarget() const {
  int target;
  if (actionId == ACTION_ID_RESCUE) {
    target = rescueTarget;
  } else if (actionId == ACTION_ID_MOVE && aiState == AI_STATE_ACTIVE) {
    AI_ACTION_DATA action = GetAIActionData();
    if (action.action != ACTION_ID_RESCUE) {
      return gf::INVALID_HANDLE;
    }
    target = action.target;
  } else {
    return gf::INVALID_HANDLE;
  }

  if (target < 0) {
    return gf::INVALID_HANDLE;
  }
  return gf::GfGameParty::getHandleDriver(target);
}

bool BattleCharacter::IsPause() const { return GetDt(true, true) <= PAUSE_DT; }

f32 BattleCharacter::GetSystemDt() const { return systemDt; }

f32 BattleCharacter::GetSystemSyncCount() const { return systemDt * FRAME_RATE; }

bool BattleCharacter::IsEnableBladeChangeAction(ACTION_ID actionId) const { return ((1 << static_cast<u8>(actionId)) & BLADE_CHANGE_ACTIONS) != 0; }

void BattleCharacter::EnhanceProc() { EnhanceTimerProc(); }

bool BattleCharacter::IsEnableBattleFace() const { return isPlayer; }

void BattleCharacter::NotifyHateElse() { SetBladeSupportCondition(BLADE_SUPPORT_CONDITION_HATE_ELSE); }

void BattleCharacter::ActionCommandEndIdle() {}

void BattleCharacter::ActionCommandPutOutWeapon(const ActionCommand *, ActionCommand::COMMAND_TYPE) {}

void BattleCharacter::ActionCommandEndPutOutWeapon() {}

void BattleCharacter::ActionCommandPutAwayWeapon(const ActionCommand *, ActionCommand::COMMAND_TYPE) {}

void BattleCharacter::ActionCommandEndPutAwayWeapon() {}

void BattleCharacter::ActionCommandKizunaMax(const ActionCommand *, ActionCommand::COMMAND_TYPE) {}

void BattleCharacter::ActionCommandEndKizunaMax() {}

void BattleCharacter::ActionCommandEndAttack() {}

void BattleCharacter::ActionCommandEndArts() {}

void BattleCharacter::ActionCommandBladeChange(const ActionCommand *, ActionCommand::COMMAND_TYPE) {}

void BattleCharacter::ActionCommandEndBladeChange() {}

void BattleCharacter::ActionCommandSpAttack(const ActionCommand *, ActionCommand::COMMAND_TYPE) {}

void BattleCharacter::ActionCommandEndSpAttack() {}

void BattleCharacter::ActionCommandSupport(const ActionCommand *, ActionCommand::COMMAND_TYPE) {}

void BattleCharacter::ActionCommandEndSupport() {}

void BattleCharacter::ActionCommandBladeGuard(const ActionCommand *, ActionCommand::COMMAND_TYPE) {}

void BattleCharacter::ActionCommandEndBladeGuard() {}

void BattleCharacter::ActionCommandRepelled(const ActionCommand *, ActionCommand::COMMAND_TYPE) {}

void BattleCharacter::ActionCommandEndRepelled() {}

void BattleCharacter::ActionCommandDown(const ActionCommand *, ActionCommand::COMMAND_TYPE) {}

void BattleCharacter::ActionCommandEndDown() {}

void BattleCharacter::ActionCommandKnockBack(const ActionCommand *, ActionCommand::COMMAND_TYPE) {}

void BattleCharacter::ActionCommandEndKnockBack() {}

void BattleCharacter::ActionCommandBreak(const ActionCommand *, ActionCommand::COMMAND_TYPE) {}

void BattleCharacter::ActionCommandEndBreak() {}

void BattleCharacter::ActionCommandDead(const ActionCommand *, ActionCommand::COMMAND_TYPE) {}

void BattleCharacter::ActionCommandEndDead() {}

void BattleCharacter::ActionCommandRescue(const ActionCommand *, ActionCommand::COMMAND_TYPE) {}

void BattleCharacter::ActionCommandEndRescue() {}

void BattleCharacter::AddIdea(u32 idea, u32 point) { gf::SCOM_ADD_IDEA::create(handle, idea, point); }

void BattleCharacter::SetNoDamageTime(f32 time) { noDamageTime = noDamageTime > time ? noDamageTime : time; }

void BattleCharacter::SetSuperArmorTime(f32 time) { superArmorTime = superArmorTime > time ? superArmorTime : time; }

void BattleCharacter::SetPerfectAvoidTime(f32 time) { perfectAvoidTime = perfectAvoidTime > time ? perfectAvoidTime : time; }

f32 BattleCharacter::GetArtsDamageRate(const ARTS_DATA::LEVEL_DATA &level) const { return level.unknown00 * 0.01f; }

f32 BattleCharacter::ApplyResistantAttr(f32 damage, int attribute) const {
  if (GetCharacterParameterConst(false)->resistantAttributeFlags & (1 << attribute)) {
    damage = BtlSystemBalanceAccess::get()->resistantAttrDamageRate * damage;
  }
  return damage;
}

f32 BattleCharacter::GetArtsDamageRate(const ARTS_DATA &data, int level) const { return GetArtsDamageRate(data.unknown90[level - 1]); }

void BattleCharacter::StopAI(f32 time) { stopAiTime = stopAiTime > time ? stopAiTime : time; }

bool BattleCharacter::CheckRandFriendEnhanceRate(int enhance) const {
  f32 rate = GetFriendEnhanceRate(enhance, false);
  if (rate <= 0.0f) {
    return false;
  }

  return ml::mtRandf1() <= rate;
}

void BattleCharacter::ResetBladeSupportConditionFlag() { bladeSupportConditionFlags = 0; }

void BattleCharacter::SetActionCallback(ACTION_ID) {}

} // namespace btl
