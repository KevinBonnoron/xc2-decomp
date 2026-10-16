#include "battle/character/battle_character.h"

#include "battle/battle_global.h"
#include "battle/hate_ring_manager.h"
#include "battle/misc_battle.h"
#include "battle/talk_manager_battle.h"
#include "battle/utility_battle.h"
#include "gf/data/gf_data_weapon.h"
#include "gf/object/gf_obj_handle.h"
#include "gf/object/gf_obj_util.h"
#include "gf/request/gf_req_scom.h"
#include "ml/rand.h"

namespace btl {

constexpr int ALPHA_RATE_NUM = 7;
constexpr u32 BLADE_CHANGE_ACTIONS = 0xd2;
constexpr int BLADE_SUPPORT_CONDITION_HATE_ELSE = 8;

ActionCommand::ActionCommand() { Reset(); }

void ActionCommand::Reset() { __builtin_memset(this, 0, sizeof(ActionCommand)); }

void ActionCommand::SetActionID(int action) { actionFlags |= 1 << action; }

bool ActionCommand::IsProcAction(int action) const { return (actionFlags & (1 << action)) != 0; }

namespace act_cmd {

void MOVE_DIR_RATE::Initialize(mm::Vec3 &direction, f32 rate, bool isFieldRun) {
  id = ID_MOVE_DIR_RATE;
  SetActionID(BattleCharacter::ACTION_ID_IDLE);
  SetActionID(BattleCharacter::ACTION_ID_MOVE);
  SetActionID(BattleCharacter::ACTION_ID_ATTACK);
  SetActionID(BattleCharacter::ACTION_ID_ARTS);
  SetActionID(BattleCharacter::ACTION_ID_BLADE_ARTS);
  mm::Vec3 directionXZ = direction;
  Misc::NormalizeXZ(directionXZ);
  f32 length = Misc::CalcLengthXZ(direction);
  moveDirRate.directionX = directionXZ.x;
  moveDirRate.directionZ = directionXZ.z;
  moveDirRate.rate = length * rate;
  moveDirRate.isFieldRun = isFieldRun;
}

void MOVE_DIR_RATE::GetMoveData(mm::Vec3 &move) const {
  GetDirection(move);
  f32 rate = GetRate();
  move.x = rate * move.x;
  move.z = rate * move.z;
}

void MOVE_DIR_RATE::GetDirection(mm::Vec3 &direction) const {
  direction.x = moveDirRate.directionX;
  direction.y = 0.0f;
  direction.z = moveDirRate.directionZ;
}

f32 MOVE_DIR_RATE::GetRate() const { return moveDirRate.rate; }

bool MOVE_DIR_RATE::IsFieldRun() const { return moveDirRate.isFieldRun != 0; }

void MOVE_LOCK::Initialize(f32 inputX, f32 inputY, bool isFieldRun, bool isTurnTarget, bool isSatellite) {
  id = ID_MOVE_LOCK;
  SetActionID(BattleCharacter::ACTION_ID_IDLE);
  SetActionID(BattleCharacter::ACTION_ID_MOVE);
  SetActionID(BattleCharacter::ACTION_ID_ATTACK);
  SetActionID(BattleCharacter::ACTION_ID_ARTS);
  SetActionID(BattleCharacter::ACTION_ID_BLADE_ARTS);
  moveLock.inputX = inputX;
  moveLock.inputY = inputY;
  u32 flags = isFieldRun;
  if (isTurnTarget) {
    flags |= MOVE_LOCK_TURN_TARGET;
  }
  if (isSatellite) {
    flags |= MOVE_LOCK_SATELLITE;
  }
  moveLock.flags = flags;
}

void MOVE_LOCK::GetInput(f32 &inputX, f32 &inputY) const {
  inputX = moveLock.inputX;
  inputY = moveLock.inputY;
}

bool MOVE_LOCK::IsFieldRun() const { return (moveLock.flags & MOVE_LOCK_FIELD_RUN) != 0; }

bool MOVE_LOCK::IsTurnTarget() const { return (moveLock.flags & MOVE_LOCK_TURN_TARGET) != 0; }

bool MOVE_LOCK::IsSatellite() const { return (moveLock.flags & MOVE_LOCK_SATELLITE) != 0; }

void SUFFER_DAMAGE::Initialize() {
  id = ID_SUFFER_DAMAGE;
  SetActionID(BattleCharacter::ACTION_ID_IDLE);
}

void ATTACK_REPELLED::Initialize() {
  id = ID_ATTACK_REPELLED;
  SetActionID(BattleCharacter::ACTION_ID_ATTACK);
  SetActionID(BattleCharacter::ACTION_ID_ARTS);
}

void BLADE_GUARD::Initialize() {
  id = ID_BLADE_GUARD;
  SetActionID(BattleCharacter::ACTION_ID_IDLE);
  SetActionID(BattleCharacter::ACTION_ID_MOVE);
}

} // namespace act_cmd

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
