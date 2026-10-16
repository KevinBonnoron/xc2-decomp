#include "battle/data_manager_battle.h"

#include "battle/battle_global.h"
#include "gf/game/gf_game_party.h"
#include "gf/menu/call/gf_menu_call_context.h"
#include "gf/menu/object/gf_menu_obj_party_status.h"
#include "gf/object/gf_obj_handle.h"

namespace btl {

constexpr int ENEMY_GROUP_NUM = 35;
constexpr int ENEMY_GROUP_INDEX_OFFSET = 3;

void DataManager::Destroy() {
  DataManager *manager = get();
  manager->Finalize();
  if (manager != nullptr) {
    delete manager;
  }
}

void DataManager::Finalize() {
  if (comboRequestContext != nullptr) {
    comboRequestContext->release();
    comboRequestContext = nullptr;
  }
}

void DataManager::InitializeComboRequestUI() {
  if (comboRequestContext == nullptr) {
    comboRequestContext = gf::GfMenuCallContext::create();
    if (comboRequestContext != nullptr) {
      gf::GfMenuObjPartyStatus::attachComboRequest(comboRequestContext);
    }
  }
}

f32 DataManager::GetPouchBuffParam(int type, int pouch) const {
  if (pouch > 2) {
    return 0.0f;
  }

  return pouchBuffs[pouch].params[type];
}

int DataManager::GetPartyGauge() const { return gf::GfGameParty::getPartyGauge(); }

bool DataManager::IsPouchBuffTiming(int pouch) const {
  if (pouch > 2) {
    return false;
  }

  return pouchBuffs[pouch].isTiming;
}

int DataManager::RegisterEnemyGroup(gf::GF_OBJ_HANDLE *leader, gf::GF_OBJ_HANDLE *member) {
  if (leader == gf::INVALID_HANDLE || member == gf::INVALID_HANDLE) {
    return -1;
  }

  for (int i = 0; i < ENEMY_GROUP_NUM; i++) {
    if (enemyGroups[i].leader == gf::INVALID_HANDLE) {
      enemyGroups[i].leader = leader;
      enemyGroups[i].member = member;
      return i + ENEMY_GROUP_INDEX_OFFSET;
    }
  }

  return -1;
}

int DataManager::GetEnemyGroupIndex(gf::GF_OBJ_HANDLE *handle) {
  if (handle == gf::INVALID_HANDLE) {
    return -1;
  }

  int index = -1;
  for (int i = 0; i < ENEMY_GROUP_NUM; i++) {
    if (enemyGroups[i].leader == handle || enemyGroups[i].member == handle) {
      index = i + ENEMY_GROUP_INDEX_OFFSET;
      break;
    }
  }

  return index;
}

void DataManager::DeleteElementalEffect() { elementalEffectId = 0; }

void DataManager::PreUpdate(const fw::UpdateInfo &updateInfo) {
  if (get() != nullptr) {
    get()->PreUpdateProc(updateInfo);
  }
}

void DataManager::PreUpdateProc(const fw::UpdateInfo &updateInfo) {
  for (int i = 0; i < PLAYER_PARAMETER_COUNT; i++) {
    if (playerParameters[i].user != gf::INVALID_HANDLE) {
      playerParameters[i].PreUpdate(updateInfo);
    }
  }
  for (EnemyParameter *parameter : enemyParameters) {
    if (parameter != nullptr && parameter->user != gf::INVALID_HANDLE) {
      parameter->PreUpdate(updateInfo);
    }
  }
}

void DataManager::Update(const fw::UpdateInfo &updateInfo) {
  if (get() != nullptr) {
    get()->UpdateProc(updateInfo);
  }
}

void DataManager::UpdateElementalEffect(f32) {
  if (!BattleGlobal::get()->isLockArtsPalette) {
    elementalEffectId = 0;
  }
}

void DataManager::SetSpecialEffects(int effect, bool isEnable) { specialEffects[effect] = isEnable; }

void DataManager::ResetRequestPermit() {
  permitTarget = reinterpret_cast<gf::GF_OBJ_HANDLE *>(-1);
  permitParty = -1;
  permitComboId = 0;
  permitComboStage = 0;
  isPermitCanceled = false;
}

void DataManager::PostUpdate(const fw::UpdateInfo &updateInfo) { get()->PostUpdateProc(updateInfo); }

void DataManager::PostUpdateProc(const fw::UpdateInfo &updateInfo) {
  for (int i = 0; i < PLAYER_PARAMETER_COUNT; i++) {
    if (playerParameters[i].user != gf::INVALID_HANDLE) {
      playerParameters[i].PostUpdate(updateInfo);
    }
  }
  for (EnemyParameter *parameter : enemyParameters) {
    if (parameter != nullptr && parameter->user != gf::INVALID_HANDLE) {
      parameter->PostUpdate(updateInfo);
    }
  }
}

bool DataManager::IsSpecialEffects(int effect) const { return specialEffects[effect]; }

} // namespace btl
