#include "battle/chain_attack_manager.h"

#include "battle/battle_global.h"
#include "battle/btl_system_balance_access.h"
#include "battle/character/battle_character.h"
#include "battle/character/character_manager_battle.h"
#include "battle/data_manager_battle.h"
#include "battle/group_data.h"
#include "battle/misc_battle.h"
#include "gf/game/gf_game_party.h"
#include "mm_math/mm_math.h"

namespace btl {

constexpr int DAMAGE_RATE_MIN = 1783;
constexpr int DAMAGE_RATE_MAX = 11782;

ChainAttackManager::~ChainAttackManager() {}

void ChainAttackManager::Initialize() { Reset(0); }

void ChainAttackManager::Start(gf::GF_OBJ_HANDLE *handle) {
  Reset(1);
  unknown08 = handle;
  BattleGlobal::get()->unknown65de_6 = true;
  unknown19e3 = 0;
  unknown19e1 = 0;
  unknown19e2 = 0;
}

void ChainAttackManager::Destroy() {
  if (get() != nullptr) {
    delete get();
  }
}

void ChainAttackManager::Finalize() {}

void ChainAttackManager::PreUpdate(const fw::UpdateInfo &updateInfo) { get()->PreUpdateProc(updateInfo); }

void ChainAttackManager::PreUpdateProc(const fw::UpdateInfo &) { unknown19e4_4 = false; }

void ChainAttackManager::Update(const fw::UpdateInfo &updateInfo) { get()->UpdateProc(updateInfo); }

void ChainAttackManager::RecoveryRecastAll(f32 recast) {
  int num = unknown19d5;
  for (int i = 0; i < num; i++) {
    u8 group = unknown19d2[i];
    SP_ATTACK_DATA &data = unknown1974[group];
    for (int j = 0; j < 3; j++) {
      if (data.unknown00[j].unknown04 >= 0) {
        data.unknown00[j].unknown00 = mm::clamp(data.unknown00[j].unknown00 + recast, 0.0f, 1.0f);
      }
    }
  }
}

void ChainAttackManager::RecoveryRecastOne(int group, f32 recast) {
  SP_ATTACK_DATA &data = unknown1974[group];
  for (int j = 0; j < 3; j++) {
    if (data.unknown00[j].unknown04 >= 0) {
      data.unknown00[j].unknown00 = mm::clamp(data.unknown00[j].unknown00 + recast, 0.0f, 1.0f);
    }
  }
}

int ChainAttackManager::GetAttrOrder(int attr) const {
  for (int i = 0; i < 9; i++) {
    u8 order = unknown19d6[i];
    if (order == 0) {
      break;
    }
    if (order == attr) {
      return i;
    }
  }
  return -1;
}

f32 ChainAttackManager::GetBonusRate() const {
  f32 rate = 0.0f;
  if (unknown19ce == STATE_NONE) {
    return rate;
  }
  if (unknown19ce >= STATE_RESULT && unknown192c >= 0.2f) {
    return rate;
  }
  return NextFloat(static_cast<f32>(BtlSystemBalanceAccess::get()->unknown76) * 0.01f);
}

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

void ChainAttackManager::RecoveryKizuna(int partyId) {
  GROUP_DATA *group = &DataManager::get()->unknown10758[partyId];
  for (int i = 0; i < 5; i++) {
    if (group->GetBladeDataConst(i)->unknown28_3) {
      GROUP_BLADE_DATA *blade = group->unknown001(i);
      if (blade->unknown00 < 300.0f) {
        blade->SetGauge(300.0f, false);
      }
    }
  }
}

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
