#include "battle/chain_attack_manager.h"

#include "battle/character/battle_character.h"
#include "battle/character/character_manager_battle.h"
#include "gf/game/gf_game_party.h"
#include "mm_math/mm_math.h"

namespace btl {

constexpr int DAMAGE_RATE_MIN = 1783;
constexpr int DAMAGE_RATE_MAX = 11782;

void ChainAttackManager::Initialize() { Reset(0); }

void ChainAttackManager::Destroy() {
  if (get() != nullptr) {
    delete get();
  }
}

void ChainAttackManager::Finalize() {}

void ChainAttackManager::Update(const fw::UpdateInfo &updateInfo) { get()->UpdateProc(updateInfo); }

void ChainAttackManager::AddDamageRate(int rate) {
  if (rate != 0 && state >= STATE_START_WAIT && state < STATE_RESULT) {
    damageRate = mm::clamp<int>(damageRate + rate, DAMAGE_RATE_MIN, DAMAGE_RATE_MAX);
  }
}

void ChainAttackManager::ModifyPosition() {
  int num = groupNum;
  for (int i = 0; i < num; i++) {
    u8 group = groups[i];
    gf::GF_OBJ_HANDLE *driver = gf::GfGameParty::getHandleDriver(group);
    ModifyPositionDriver(driver);
    ModifyPositionBlade(driver, gf::GfGameParty::getHandleBlade(group, -1));
  }
}

int ChainAttackManager::GetSpAttackLevel(int group) const { return spAttacks[group].level; }

f32 ChainAttackManager::GetSpAttackRecast(int group, int blade) const {
  for (int i = 0; i < 3; i++) {
    int slotBlade = spAttacks[group].blades[i].blade;
    if (slotBlade >= 0 && slotBlade == blade) {
      return spAttacks[group].blades[i].recast;
    }
  }

  return 0.0f;
}

int ChainAttackManager::GetOrderAttr(int order) const {
  if (order >= 0 && order <= 8) {
    return orderAttrs[order];
  }

  return 0;
}

bool ChainAttackManager::IsProc(bool isExcludeStartWait) const {
  if (state == STATE_NONE) {
    return false;
  }

  if (isExcludeStartWait && IsStartWait()) {
    return false;
  }

  return true;
}

bool ChainAttackManager::IsResult() const { return state >= STATE_RESULT; }

void ChainAttackManager::AddTotalDamage(u32 damage) {
  if (state >= STATE_START_WAIT && state < STATE_RESULT) {
    totalDamage += damage;
  }
}

int ChainAttackManager::GetGroupIndex() const {
  if (groupIndex > 2) {
    return -1;
  }

  u8 group = groups[groupIndex];
  return group > 2 ? -1 : group;
}

bool ChainAttackManager::IsStartWait() const { return state >= STATE_START_WAIT && state < STATE_START_WAIT + 3; }

bool ChainAttackManager::IsSelectAction() const { return state == STATE_SELECT_ACTION; }

bool ChainAttackManager::IsStopTime() const { return state == STATE_SELECT_ACTION; }

bool ChainAttackManager::IsTargetDead() const {
  if (state == STATE_NONE) {
    return true;
  }

  BattleCharacter *character = CharacterManager::get()->GetCharacterConst(target);
  if (character == nullptr) {
    return true;
  }

  return character->IsDead(BattleCharacter::DEAD_CHECK_IGNORE_CHAIN_ATTACK);
}

} // namespace btl
