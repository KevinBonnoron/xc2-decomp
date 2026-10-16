#include "battle/character/battle_character.h"

#include "battle/hate_ring_manager.h"
#include "battle/talk_manager_battle.h"
#include "battle/utility_battle.h"
#include "gf/data/gf_data_weapon.h"
#include "gf/object/gf_obj_handle.h"
#include "gf/object/gf_obj_util.h"
#include "gf/request/gf_req_scom.h"
#include "ml/rand.h"

namespace btl {

constexpr f32 FRAME_RATE = 30.0f;
constexpr int ALPHA_RATE_NUM = 7;
constexpr u32 BLADE_CHANGE_ACTIONS = 0xd2;
constexpr int BLADE_SUPPORT_CONDITION_HATE_ELSE = 8;

void BattleCharacter::ResetHateRingData() {
  if (!isPlayer && handle != gf::INVALID_HANDLE && id >= 0) {
    HateRingManager::get()->SetData(id, handle, -1);
  }
}

void BattleCharacter::ResetDelayVoice() { delayVoiceTime = -1; }

bool BattleCharacter::IsPlayer() const { return isPlayer; }

gf::GfObj *BattleCharacter::GetObject() const { return gf::GfObjUtil::getObj(handle); }

bool BattleCharacter::IsEnemy() const { return !isPlayer; }

gf::GF_OBJ_HANDLE *BattleCharacter::GetControlCharacterHandle() const { return Utility::GetControlCharacterHandle(); }

gf::GfObj *BattleCharacter::GetObject(gf::GF_OBJ_HANDLE *handle) const { return gf::GfObjUtil::getObj(handle); }

bool BattleCharacter::IsBattle() const { return isBattle; }

bool BattleCharacter::IsEnableBackHome() const { return actionId == ACTION_ID_IDLE; }

bool BattleCharacter::IsDisp() const { return alphaRates[0] > 0.0f; }

int BattleCharacter::GetWeaponType(bool isAsm) const {
  if (isAsm) {
    return gf::GfDataWeapon::getAsmWeaponType(weaponType);
  }

  return weaponType;
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

f32 BattleCharacter::GetSystemDt() const { return systemDt; }

f32 BattleCharacter::GetSystemSyncCount() const { return systemDt * FRAME_RATE; }

bool BattleCharacter::IsEnableBladeChangeAction(ACTION_ID actionId) const { return ((1 << static_cast<u8>(actionId)) & BLADE_CHANGE_ACTIONS) != 0; }

void BattleCharacter::EnhanceProc() { EnhanceTimerProc(); }

bool BattleCharacter::IsEnableBattleFace() const { return isPlayer; }

void BattleCharacter::NotifyHateElse() { SetBladeSupportCondition(BLADE_SUPPORT_CONDITION_HATE_ELSE); }

void BattleCharacter::AddIdea(u32 idea, u32 point) { gf::SCOM_ADD_IDEA::create(handle, idea, point); }

void BattleCharacter::SetNoDamageTime(f32 time) { noDamageTime = noDamageTime > time ? noDamageTime : time; }

void BattleCharacter::SetSuperArmorTime(f32 time) { superArmorTime = superArmorTime > time ? superArmorTime : time; }

void BattleCharacter::SetPerfectAvoidTime(f32 time) { perfectAvoidTime = perfectAvoidTime > time ? perfectAvoidTime : time; }

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
