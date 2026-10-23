#include "battle/character/action_command.h"

#include "battle/character/battle_character.h"
#include "battle/misc_battle.h"
#include "mm_math/mm_vec3.h"

namespace btl {

ActionCommand::ActionCommand() { Reset(); }

void ActionCommand::Reset() { __builtin_memset(this, 0, sizeof(ActionCommand)); }

void ActionCommand::SetActionID(int action) { unknown10_6 |= 1 << action; }

bool ActionCommand::IsProcAction(int action) const { return (unknown10_6 & (1 << action)) != 0; }

namespace act_cmd {

void MOVE_DIR_RATE::Initialize(mm::Vec3 &direction, f32 rate, bool isFieldRun) {
  unknown10_0 = COMMAND_TYPE_MOVE_DIR_RATE;
  SetActionID(BattleCharacter::ACTION_ID_IDLE);
  SetActionID(BattleCharacter::ACTION_ID_MOVE);
  SetActionID(BattleCharacter::ACTION_ID_ATTACK);
  SetActionID(BattleCharacter::ACTION_ID_ARTS);
  SetActionID(BattleCharacter::ACTION_ID_BLADE_ARTS);
  mm::Vec3 directionXZ = direction;
  Misc::NormalizeXZ(directionXZ);
  f32 length = Misc::CalcLengthXZ(direction);
  unknown00_0.unknown00 = directionXZ.x;
  unknown00_0.unknown04 = directionXZ.z;
  unknown00_0.unknown08 = length * rate;
  unknown00_0.unknown0c = isFieldRun;
}

void MOVE_DIR_RATE::GetMoveData(mm::Vec3 &move) const {
  GetDirection(move);
  f32 rate = GetRate();
  move.x = rate * move.x;
  move.z = rate * move.z;
}

void MOVE_DIR_RATE::GetDirection(mm::Vec3 &direction) const {
  direction.x = unknown00_0.unknown00;
  direction.y = 0.0f;
  direction.z = unknown00_0.unknown04;
}

f32 MOVE_DIR_RATE::GetRate() const { return unknown00_0.unknown08; }

bool MOVE_DIR_RATE::IsFieldRun() const { return unknown00_0.unknown0c != 0; }

void MOVE_LOCK::Initialize(f32 inputX, f32 inputY, bool isFieldRun, bool isTurnTarget, bool isSatellite) {
  unknown10_0 = COMMAND_TYPE_MOVE_LOCK;
  SetActionID(BattleCharacter::ACTION_ID_IDLE);
  SetActionID(BattleCharacter::ACTION_ID_MOVE);
  SetActionID(BattleCharacter::ACTION_ID_ATTACK);
  SetActionID(BattleCharacter::ACTION_ID_ARTS);
  SetActionID(BattleCharacter::ACTION_ID_BLADE_ARTS);
  unknown00_1.unknown00 = inputX;
  unknown00_1.unknown04 = inputY;
  u32 flags = isFieldRun;
  if (isTurnTarget) {
    flags |= MOVE_LOCK_TURN_TARGET;
  }
  if (isSatellite) {
    flags |= MOVE_LOCK_SATELLITE;
  }
  unknown00_1.unknown08 = flags;
}

void MOVE_LOCK::GetInput(f32 &inputX, f32 &inputY) const {
  inputX = unknown00_1.unknown00;
  inputY = unknown00_1.unknown04;
}

bool MOVE_LOCK::IsFieldRun() const { return (unknown00_1.unknown08 & MOVE_LOCK_FIELD_RUN) != 0; }

bool MOVE_LOCK::IsTurnTarget() const { return (unknown00_1.unknown08 & MOVE_LOCK_TURN_TARGET) != 0; }

bool MOVE_LOCK::IsSatellite() const { return (unknown00_1.unknown08 & MOVE_LOCK_SATELLITE) != 0; }

void SUFFER_DAMAGE::Initialize() {
  unknown10_0 = COMMAND_TYPE_SUFFER_DAMAGE;
  SetActionID(BattleCharacter::ACTION_ID_IDLE);
}

void ATTACK_REPELLED::Initialize() {
  unknown10_0 = COMMAND_TYPE_ATTACK_REPELLED;
  SetActionID(BattleCharacter::ACTION_ID_ATTACK);
  SetActionID(BattleCharacter::ACTION_ID_ARTS);
}

void BLADE_GUARD::Initialize() {
  unknown10_0 = COMMAND_TYPE_BLADE_GUARD;
  SetActionID(BattleCharacter::ACTION_ID_IDLE);
  SetActionID(BattleCharacter::ACTION_ID_MOVE);
}

} // namespace act_cmd

} // namespace btl
