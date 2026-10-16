#include "battle/character/action_command.h"

#include "battle/character/battle_character.h"
#include "battle/misc_battle.h"
#include "mm_math/mm_vec3.h"

namespace btl {

ActionCommand::ActionCommand() { Reset(); }

void ActionCommand::Reset() { __builtin_memset(this, 0, sizeof(ActionCommand)); }

void ActionCommand::SetActionID(int action) { actionFlags |= 1 << action; }

bool ActionCommand::IsProcAction(int action) const { return (actionFlags & (1 << action)) != 0; }

namespace act_cmd {

void MOVE_DIR_RATE::Initialize(mm::Vec3 &direction, f32 rate, bool isFieldRun) {
  type = COMMAND_TYPE_MOVE_DIR_RATE;
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
  type = COMMAND_TYPE_MOVE_LOCK;
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
  type = COMMAND_TYPE_SUFFER_DAMAGE;
  SetActionID(BattleCharacter::ACTION_ID_IDLE);
}

void ATTACK_REPELLED::Initialize() {
  type = COMMAND_TYPE_ATTACK_REPELLED;
  SetActionID(BattleCharacter::ACTION_ID_ATTACK);
  SetActionID(BattleCharacter::ACTION_ID_ARTS);
}

void BLADE_GUARD::Initialize() {
  type = COMMAND_TYPE_BLADE_GUARD;
  SetActionID(BattleCharacter::ACTION_ID_IDLE);
  SetActionID(BattleCharacter::ACTION_ID_MOVE);
}

} // namespace act_cmd

} // namespace btl
