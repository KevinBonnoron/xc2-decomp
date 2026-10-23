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
  if (!m_player && unknown118 != gf::INVALID_HANDLE && unknownf7d >= 0) {
    HateRingManager::get()->SetData(unknownf7d, unknown118, -1);
  }
}

void BattleCharacter::ResetDelayVoice() { unknowndd0 = -1; }

void BattleCharacter::ResetCustomVoiceData() {
  unknownf5c = 0;
  unknownf60 = 0;
  for (int i = 0; i < 3; i++) {
    unknownf64[i].unknown00 = 0;
    unknownf64[i].unknown01 = 0;
  }
}

const CharacterParameter *BattleCharacter::GetCharacterParameterConst(bool) const {
  if (unknown168 == nullptr) {
    if (unknownf6a < 0) {
      return nullptr;
    }
    unknown168 = DataManager::get()->GetCharacterParameterConst(unknownf6a);
  }
  return unknown168;
}

bool BattleCharacter::IsPlayer() const { return m_player; }

bool BattleCharacter::IsBlade() const {
  const CharacterParameter *parameter = GetCharacterParameterConst(true);
  return parameter != nullptr && parameter->m_invalidTarget;
}

gf::GfObj *BattleCharacter::GetObject() const { return gf::GfObjUtil::getObj(unknown118); }

bool BattleCharacter::IsEnemy() const { return !m_player; }

bool BattleCharacter::IsDriver() const {
  const CharacterParameter *parameter = GetCharacterParameterConst(true);
  return parameter != nullptr && !parameter->m_invalidTarget && parameter->unknown10 != gf::INVALID_HANDLE;
}

CharacterParameter *BattleCharacter::GetCharacterParameter(bool isBattle) {
  return const_cast<CharacterParameter *>(GetCharacterParameterConst(isBattle));
}

gf::GF_OBJ_HANDLE *BattleCharacter::GetControlCharacterHandle() const { return Utility::GetControlCharacterHandle(); }

gf::GfObj *BattleCharacter::GetObject(gf::GF_OBJ_HANDLE *handle) const { return gf::GfObjUtil::getObj(handle); }

bool BattleCharacter::IsBattle() const { return m_battle; }

void BattleCharacter::ResetAnimationMoveDistance() {
  for (int i = 0; i < 20; i++) {
    unknownce0[i].unknown04 = ANIMATION_INVALID;
  }
}

void BattleCharacter::ResetAlphaAnimation() {
  for (int i = 0; i < 17; i++) {
    unknowndd8[i].unknown10 = 0.0f;
    unknowndd8[i].unknown0c = 0.0f;
    unknowndd8[i].unknown04 = -1.0f;
    unknowndd8[i].unknown08 = -1.0f;
    unknowndd8[i].unknown00 = -1.0f;
  }
}

void BattleCharacter::InitializeEnhanceProcData(bool isFinalizeArtsEffect) {
  for (f32 &timer : unknown1108) {
    timer = 0.0f;
  }
  if (isFinalizeArtsEffect) {
    FinalizeArtsEffect(true);
  }
}

void BattleCharacter::DeleteKizunaAuraEffect() {
  if (unknown130[EFFECT_ID_KIZUNA_AURA] != 0) {
    if (gf::GfGameManager::isPlayEvent()) {
      fw::EffectManager::get()->remove(unknown130[EFFECT_ID_KIZUNA_AURA]);
    } else {
      fw::EffectManager::get()->dead(unknown130[EFFECT_ID_KIZUNA_AURA]);
    }
    unknown130[EFFECT_ID_KIZUNA_AURA] = 0;
  }
}

void BattleCharacter::CancelButtonChallenge() {
  if (unknown10c0 != 0) {
    BattleGlobal::get()->unknown5e8.Cancel(unknown10c0);
    unknown10c0 = 0;
  }
}

bool BattleCharacter::IsDispWeaponAlpha(int alpha) const {
  if (alpha >= ALPHA_WEAPON_FIRST && alpha <= ALPHA_WEAPON_LAST) {
    f32 rate = unknowndd8[alpha].unknown08;
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

bool BattleCharacter::IsMove() const { return unknown107c == ACTION_ID_MOVE || unknown1178 == AI_STATE_ACTIVE; }

void BattleCharacter::AddUseWeapon() {
  CharacterParameter *parameter = GetCharacterParameter(true);
  if (parameter != nullptr) {
    int weapon = unknownf7f;
    parameter->AddUseWeapon(weapon);
  }
}

void BattleCharacter::EndBladeTimer(BLADE_TIMER_MODE mode) {
  if (unknownf77_1 == mode) {
    unknowncd0 = 0.0f;
    unknownf77_1 = 0;
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
  int id = unknowndc0_0;
  if (id == 0) {
    weight = 0.0f;
    height = 0.0f;
    return id;
  }
  weight = unknowndb8;
  height = unknowndbc;
  return id;
}

void BattleCharacter::SetupPosDir() {
  unknownf4 = FLT_MAX;
  Misc::GetObjectTransform(unknown118, unknown10, Misc::TRANS_TYPE_POSITION);
  Misc::GetObjectDirection(unknown118, unknown50, true);
}

int BattleCharacter::GetGroupIndex() const {
  const CharacterParameter *parameter = GetCharacterParameterConst(true);
  return parameter != nullptr ? parameter->unknown1c : -1;
}

bool BattleCharacter::IsEnableBackHome() const { return unknown107c == ACTION_ID_IDLE; }

bool BattleCharacter::IsDisp() const { return unknownf2c[0] > 0.0f; }

int BattleCharacter::GetWeaponType(bool isAsm) const {
  if (isAsm) {
    return gf::GfDataWeapon::getAsmWeaponType(unknownf7f);
  }

  return unknownf7f;
}

const BattleCharacter::CUSTOM_VOICE_DATA *BattleCharacter::GetCustomVoiceData(int voice, int *index) const {
  for (int i = 0; i < 3; i++) {
    if (unknownf64[i].unknown00 == voice) {
      if (index != nullptr) {
        *index = i;
      }
      return &unknownf64[i];
    }
  }
  return nullptr;
}

bool BattleCharacter::IsCustomVoice(int voice) const {
  u32 flag = 1 << voice;
  if ((unknownf5c & flag) == 0) {
    return false;
  }

  return (unknownf60 & flag) == 0;
}

void BattleCharacter::SetCustomVoiceEndFlag(int voice, bool isEnd) {
  if (isEnd) {
    unknownf60 |= 1 << voice;
  } else {
    unknownf60 &= ~(1 << voice);
  }
}

void BattleCharacter::ClearCustomVoiceEndFlag(u32 flags) { unknownf60 &= ~flags; }

int BattleCharacter::GetWeaponSeType() const { return Utility::GetWeaponSeType(unknownf7f); }

bool BattleCharacter::IsEnableTurnAI() const { return ((1 << unknown107c) & ((1 << ACTION_ID_IDLE) | (1 << ACTION_ID_MOVE))) != 0; }

void BattleCharacter::GetMoveDataPerSec(mm::Vec3 &moveData) const {
  moveData.x = this->unknownb0.x * FRAME_RATE;
  moveData.y = this->unknownb0.y * FRAME_RATE;
  moveData.z = this->unknownb0.z * FRAME_RATE;
}

void BattleCharacter::SetAnimationSpeed(f32 speed) { m_animationSpeed = speed; }

void BattleCharacter::SetIKData(const ARTS_DATA &data) {
  unknowndc0_7 = data.unknown15_0;
  unknowndc1_3 = data.unknown15_4;
  unknowndc2_3 = data.unknown16_4;
  unknowndc2_7 = data.unknown17_0;
  unknowndc3_7 = data.unknown2f_0;
}

void BattleCharacter::NotifyStrikeDamage(int) { TalkManager::get()->NotifyTrigger(unknownf7d, TalkManager::TRIGGER_STRIKE_DAMAGE, 0, 0); }

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
    unknownf2c[i] = -1.0f;
  }
}

f32 BattleCharacter::GetSyncCount(bool isSlow) const { return GetDt(isSlow, true) * FRAME_RATE; }

f32 BattleCharacter::GetDt(bool isSlow, bool isStopCheck) const {
  if (isStopCheck && unknownf93_6) {
    return 0.0f;
  }
  return isSlow ? unknowncc0 * unknownf58 : unknowncc0;
}

void BattleCharacter::RegisterSlow(SLOW_PROC_ID slow, f32 rate, f32 time) {
  unknownf4c[slow].unknown00 = rate;
  unknownf4c[slow].unknown04 = time;
  unknownf4c[slow].unknown08 = 0.0f;
}

void BattleCharacter::DeleteSlow(SLOW_PROC_ID slow) {
  unknownf4c[slow].unknown00 = 1.0f;
  unknownf4c[slow].unknown04 = 0.0f;
  unknownf4c[slow].unknown08 = 0.0f;
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
    unknowndd0 = time * (1.0f / FRAME_RATE) * DELAY_VOICE_TIME_SCALE;
    unknowndd2 = priority;
    unknowndd4 = group;
    unknowndd6 = voice;
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

void BattleCharacter::ResetChangeActionStopSeData() { unknown10c4_0 = 0; }

void BattleCharacter::ReturnBladeChange() {
  SetAction(ACTION_ID_BLADE_CHANGE, false, false, 0, 0.0f);
  unknown107e = ACTION_PHASE_BLADE_CHANGE_RETURN;
}

ActionCommand *BattleCharacter::GetFreeCommand() {
  if (unknown1078 >= COMMAND_NUM) {
    return nullptr;
  }
  ActionCommand *command = &unknownfb0[unknown1078];
  unknown1078++;
  command->Reset();
  return command;
}

bool BattleCharacter::IsRegisterCommand(ActionCommand::COMMAND_TYPE type) const {
  for (int i = 0; i < unknown1078; i++) {
    if (unknownfb0[i].unknown10_0 == type) {
      return true;
    }
  }
  return false;
}

void BattleCharacter::ActionCommandBladeArts(const ActionCommand *command, ActionCommand::COMMAND_TYPE type) {
  if ((type == ActionCommand::COMMAND_TYPE_MOVE_DIR_RATE || type == ActionCommand::COMMAND_TYPE_MOVE_LOCK) &&
      unknown107e == ACTION_PHASE_BLADE_ARTS_MOVE) {
    ActionCommandRun(command, type);
  }
}

bool BattleCharacter::IsRescue() const {
  if (unknown107c == ACTION_ID_RESCUE) {
    return true;
  }
  if (unknown107c == ACTION_ID_MOVE && unknown1178 == AI_STATE_ACTIVE && unknown1160.unknown00 == ACTION_ID_RESCUE) {
    return true;
  }
  return false;
}

bool BattleCharacter::MoveStop(bool isForce) {
  if (unknown1178 != AI_STATE_ACTIVE || unknown1160.unknown00 != ACTION_ID_IDLE || (unknown1180 & AI_FLAG_SCOUT) != 0) {
    return false;
  }
  unknown1180 |= isForce ? AI_FLAG_STOP_FORCE : AI_FLAG_STOP;
  return true;
}

void BattleCharacter::SetScout(bool isScout) {
  if (unknown1178 == AI_STATE_ACTIVE) {
    if (isScout) {
      unknown1180 |= AI_FLAG_SCOUT;
      unknown1174 += AI_SCOUT_TIME;
    } else {
      unknown1180 &= ~AI_FLAG_SCOUT;
    }
  }
}

bool BattleCharacter::IsScout() const { return unknown1178 == AI_STATE_ACTIVE && (unknown1180 & AI_FLAG_SCOUT) != 0; }

gf::GF_OBJ_HANDLE *BattleCharacter::GetRescueTarget() const {
  int target;
  if (unknown107c == ACTION_ID_RESCUE) {
    target = unknown108c;
  } else if (unknown107c == ACTION_ID_MOVE && unknown1178 == AI_STATE_ACTIVE) {
    AI_ACTION_DATA action = GetAIActionData();
    if (action.unknown00 != ACTION_ID_RESCUE) {
      return gf::INVALID_HANDLE;
    }
    target = action.unknown04;
  } else {
    return gf::INVALID_HANDLE;
  }

  if (target < 0) {
    return gf::INVALID_HANDLE;
  }
  return gf::GfGameParty::getHandleDriver(target);
}

bool BattleCharacter::IsPause() const { return GetDt(true, true) <= PAUSE_DT; }

f32 BattleCharacter::GetSystemDt() const { return m_systemDt; }

f32 BattleCharacter::GetSystemSyncCount() const { return m_systemDt * FRAME_RATE; }

bool BattleCharacter::IsEnableBladeChangeAction(ACTION_ID actionId) const { return ((1 << static_cast<u8>(actionId)) & BLADE_CHANGE_ACTIONS) != 0; }

void BattleCharacter::EnhanceProc() { EnhanceTimerProc(); }

bool BattleCharacter::IsEnableBattleFace() const { return m_player; }

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

void BattleCharacter::AddIdea(u32 idea, u32 point) { gf::SCOM_ADD_IDEA::create(unknown118, idea, point); }

void BattleCharacter::SetNoDamageTime(f32 time) { unknown10e0 = unknown10e0 > time ? unknown10e0 : time; }

void BattleCharacter::SetSuperArmorTime(f32 time) { unknown10e4 = unknown10e4 > time ? unknown10e4 : time; }

void BattleCharacter::SetPerfectAvoidTime(f32 time) { unknown10e8 = unknown10e8 > time ? unknown10e8 : time; }

f32 BattleCharacter::GetArtsDamageRate(const ARTS_DATA::LEVEL_DATA &level) const { return level.unknown00 * 0.01f; }

f32 BattleCharacter::ApplyResistantAttr(f32 damage, int attribute) const {
  if (GetCharacterParameterConst(false)->unknown59e & (1 << attribute)) {
    damage = BtlSystemBalanceAccess::get()->unknown10 * damage;
  }
  return damage;
}

f32 BattleCharacter::GetArtsDamageRate(const ARTS_DATA &data, int level) const { return GetArtsDamageRate(data.unknown90[level - 1]); }

void BattleCharacter::StopAI(f32 time) { unknown11cc = unknown11cc > time ? unknown11cc : time; }

bool BattleCharacter::CheckRandFriendEnhanceRate(int enhance) const {
  f32 rate = GetFriendEnhanceRate(enhance, false);
  if (rate <= 0.0f) {
    return false;
  }

  return ml::mtRandf1() <= rate;
}

void BattleCharacter::ResetBladeSupportConditionFlag() { unknown11e0 = 0; }

void BattleCharacter::SetActionCallback(ACTION_ID) {}

} // namespace btl
