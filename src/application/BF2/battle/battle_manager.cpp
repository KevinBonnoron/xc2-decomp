#include "battle/battle_manager.h"

#include "battle/battle_global.h"
#include "battle/character/battle_character.h"
#include "battle/character/character_manager_battle.h"
#include "battle/character/character_parameter_battle.h"
#include "battle/data_manager_battle.h"
#include "battle/utility_battle.h"
#include "gf/game/gf_game_manager.h"
#include "gf/game/gf_game_target.h"

namespace gf {
struct GF_OBJ_HANDLE;
} // namespace gf

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

  return get()->unknown14;
}

void BattleManager::postUpdate(const fw::UpdateInfo &updateInfo) {
  if (!unknown14) {
    return;
  }

  DataManager::PostUpdate(updateInfo);
  BattleGlobal::PostUpdate(updateInfo);
  CharacterManager::PostUpdate(updateInfo);
}

void BattleManager::gevBattleStart() {}

void BattleManager::CheckTargetMode() {
  bool enable = false;
  if (gf::GfGameManager::isEnableFieldBattleTarget()) {
    if (BattleGlobal::get()->unknown65de_0) {
      enable = true;
    } else {
      gf::GF_OBJ_HANDLE *leaderHandle = Utility::GetLeader();
      BattleCharacter *leader = CharacterManager::get()->GetCharacterConst(leaderHandle);
      if (leader != nullptr) {
        const CharacterParameter *parameter = leader->GetCharacterParameterConst(true);
        if (parameter != nullptr) {
          enable = parameter->unknown5df_1;
        }
      }
    }
  }

  if (gf::GfGameTarget::get() != nullptr) {
    gf::GfGameTarget::get()->changeBattleTarget(enable);
  }
}

void BattleManager::gevBattleEnd() {}

} // namespace btl
