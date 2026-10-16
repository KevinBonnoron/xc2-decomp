#include "battle/battle_manager.h"

#include "battle/battle_global.h"
#include "battle/character/character_manager_battle.h"
#include "battle/data_manager_battle.h"

namespace btl {

BattleManager::~BattleManager() { ; }

void BattleManager::destroy() {
  BattleManager *manager = get();
  manager->Finalize();
  delete manager;
}

bool BattleManager::isInitialized() {
  if (get() == nullptr) {
    return false;
  }

  return get()->initialized;
}

void BattleManager::postUpdate(const fw::UpdateInfo &updateInfo) {
  if (!initialized) {
    return;
  }

  DataManager::PostUpdate(updateInfo);
  BattleGlobal::PostUpdate(updateInfo);
  CharacterManager::PostUpdate(updateInfo);
}

void BattleManager::gevBattleStart() {}

void BattleManager::gevBattleEnd() {}

} // namespace btl
