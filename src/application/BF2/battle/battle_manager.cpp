#include "battle/battle_manager.h"

#include "battle/battle_global.h"
#include "battle/blade_arts_manager.h"
#include "battle/blade_change_manager.h"
#include "battle/character/battle_character.h"
#include "battle/character/character_manager_battle.h"
#include "battle/character/character_parameter_battle.h"
#include "battle/data_manager_battle.h"
#include "battle/effect/effect_manager_battle.h"
#include "battle/sp_attack_manager.h"
#include "battle/talk_manager_battle.h"
#include "battle/ui_manager_battle.h"
#include "battle/utility_battle.h"
#include "gf/game/gf_game_manager.h"
#include "gf/game/gf_game_target.h"
#include "gf/game/sequential_play/gf_play_factory.h"

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

void BattleManager::Update(const fw::UpdateInfo &updateInfo) {
  if (!unknown15) {
    return;
  }

  bool isGameOver = CheckGameOver(updateInfo);
  if (!isGameOver) {
    unknown16 = false;
    unknown17 = false;
  } else {
    if (!unknown17) {
      CharacterManager::get()->PlayEnemyWinVoice();
      unknown17 = true;
    }
    unknown16 = true;
    if (Utility::IsEnableDeadSequence()) {
      gf::GfPlayFactory::createPlayerDead(gf::PLAYER_DEAD_GAME_OVER);
      unknown16 = false;
    }
  }

  BattleGlobal *global = BattleGlobal::get();
  f32 time = unknown10 * (1.0f / 15.0f);
  global->unknown65e0_0 = isGameOver;
  global->unknown86c = time;
  CheckBattle();
  CheckTargetMode();
  CheckInBattle();
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

void BattleManager::gevMapjump(gf::GEV gev, const gf::MapjumpCallbackInfo &) {
  if (gev == gf::GEV_MAPJUMP_DESTROY_FIELD) {
    if (BattleGlobal::get() != nullptr) {
      BattleGlobal::get()->NotifyMapChange();
    }
    if (BladeArtsManager::get() != nullptr) {
      BladeArtsManager::get()->NotifyMapChange();
    }
    if (BladeChangeManager::get() != nullptr) {
      BladeChangeManager::get()->NotifyMapChange();
    }
    if (SpAttackManager::get() != nullptr) {
      SpAttackManager::get()->NotifyMapChange();
    }
    if (EffectManager::get() != nullptr) {
      EffectManager::get()->NotifyMapChange();
    }
    if (TalkManager::get() != nullptr) {
      TalkManager::get()->NotifyMapChange();
    }
    if (UIManager::get() != nullptr) {
      UIManager::get()->NotifyMapChange();
    }
  }
  unknown15 = gev == gf::GEV_MAPJUMP_END;
}

} // namespace btl
