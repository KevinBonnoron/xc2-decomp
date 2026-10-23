#include "battle/chain_attack_manager.h"

#include "battle/character/battle_character.h"
#include "battle/character/character_manager_battle.h"
#include "battle/misc_battle.h"
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

void ChainAttackManager::PreUpdate(const fw::UpdateInfo &updateInfo) { get()->PreUpdateProc(updateInfo); }

void ChainAttackManager::PreUpdateProc(const fw::UpdateInfo &) { unknown19e4_4 = false; }

void ChainAttackManager::Update(const fw::UpdateInfo &updateInfo) { get()->UpdateProc(updateInfo); }

void ChainAttackManager::AddDamageRate(int rate) {
  if (rate != 0 && unknown19ce >= STATE_START_WAIT && unknown19ce < STATE_RESULT) {
    unknown19cc = mm::clamp<int>(unknown19cc + rate, DAMAGE_RATE_MIN, DAMAGE_RATE_MAX);
  }
}

void ChainAttackManager::ModifyPosition() {
  int num = unknown19d5;
  for (int i = 0; i < num; i++) {
    u8 group = unknown19d2[i];
    gf::GF_OBJ_HANDLE *driver = gf::GfGameParty::getHandleDriver(group);
    ModifyPositionDriver(driver);
    ModifyPositionBlade(driver, gf::GfGameParty::getHandleBlade(group, -1));
  }
}

f32 ChainAttackManager::GetDamageRate() const {
  if (unknown19ce == STATE_NONE) {
    return 1.0f;
  }
  return NextFloat((unknown19cc - DAMAGE_RATE_MIN + 100) * 0.01f);
}

int ChainAttackManager::GetSpAttackLevel(int group) const { return unknown1974[group].unknown18; }

f32 ChainAttackManager::GetSpAttackRecast(int group, int blade) const {
  for (int i = 0; i < 3; i++) {
    int slotBlade = unknown1974[group].unknown00[i].unknown04;
    if (slotBlade >= 0 && slotBlade == blade) {
      return unknown1974[group].unknown00[i].unknown00;
    }
  }

  return 0.0f;
}

int ChainAttackManager::GetOrderAttr(int order) const {
  if (order >= 0 && order <= 8) {
    return unknown19d6[order];
  }

  return 0;
}

bool ChainAttackManager::IsProc(bool isExcludeStartWait) const {
  if (unknown19ce == STATE_NONE) {
    return false;
  }

  if (isExcludeStartWait && IsStartWait()) {
    return false;
  }

  return true;
}

bool ChainAttackManager::IsResult() const { return unknown19ce >= STATE_RESULT; }

void ChainAttackManager::AddTotalDamage(u32 damage) {
  if (unknown19ce >= STATE_START_WAIT && unknown19ce < STATE_RESULT) {
    unknown1930 += damage;
  }
}

int ChainAttackManager::GetGroupIndex() const {
  if (unknown19d1 > 2) {
    return -1;
  }

  u8 group = unknown19d2[unknown19d1];
  return group > 2 ? -1 : group;
}

bool ChainAttackManager::IsStartWait() const { return unknown19ce >= STATE_START_WAIT && unknown19ce < STATE_START_WAIT + 3; }

bool ChainAttackManager::IsSelectAction() const { return unknown19ce == STATE_SELECT_ACTION; }

bool ChainAttackManager::IsStopTime() const { return unknown19ce == STATE_SELECT_ACTION; }

bool ChainAttackManager::IsTargetDead() const {
  if (unknown19ce == STATE_NONE) {
    return true;
  }

  BattleCharacter *character = CharacterManager::get()->GetCharacterConst(unknown08);
  if (character == nullptr) {
    return true;
  }

  return character->IsDead(BattleCharacter::DEAD_CHECK_IGNORE_CHAIN_ATTACK);
}

} // namespace btl
