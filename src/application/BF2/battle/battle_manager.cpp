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
#include "bdat.h"
#include "gf/data/gf_bdat_chrenparam.h"
#include "gf/data/gf_bdat_id.h"
#include "gf/data/gf_data_bdat.h"
#include "gf/game/gf_game_manager.h"
#include "gf/game/gf_game_target.h"
#include "gf/game/sequential_play/gf_play_factory.h"

namespace gf {
struct GF_OBJ_HANDLE;
} // namespace gf

namespace btl {

constexpr int ENEMY_GROUP_ENEMY_COUNT = 8;

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

void BattleManager::QuestTaskProc(u32 task) {
  if (!BattleGlobal::get()->unknown65de_0) {
    return;
  }

  CharacterManager *manager = CharacterManager::get();
  u8 *bdat = gf::GfDataBdat::getFP(gf::BDAT_FLD_QUEST_BATTLE);
  u32 enemyLimit = Bdat::getValCheck(bdat, "ReduceEnemyHP", task, 2) & 0xffff;
  if (enemyLimit != 0) {
    u32 enemy = Bdat::getValCheck(bdat, "EnemyID", task, 2) & 0xffff;
    u32 group = Bdat::getValCheck(bdat, "EnemyGroupID", task, 2) & 0xffff;
    if (enemy == 0) {
      for (int id = CHARACTER_PLAYER_COUNT; id < CHARACTER_COUNT; id++) {
        BattleCharacter *character = manager->GetCharacterConst(id);
        if (character != nullptr) {
          int enemyId = character->unknowncc8;
          gf::GfBdatChrEnParam *parameter = gf::GfBdatChrEnParam::get();
          for (int index = 0; index < ENEMY_GROUP_ENEMY_COUNT; index++) {
            if (enemyId == parameter->getEnemyGroupEnemyID(group, index)) {
              character->SetLimitHP(enemyLimit);
              break;
            }
          }
        }
      }
    } else {
      for (int id = CHARACTER_PLAYER_COUNT; id < CHARACTER_COUNT; id++) {
        BattleCharacter *character = manager->GetCharacterConst(id);
        if (character != nullptr && character->unknowncc8 == enemy) {
          character->SetLimitHP(enemyLimit);
          break;
        }
      }
    }
  }

  u32 playerLimit = Bdat::getValCheck(bdat, "ReducePCHP", task, 2);
  if ((playerLimit & 0xffff) != 0) {
    for (int id = 0; id < CHARACTER_PLAYER_COUNT; id++) {
      BattleCharacter *character = manager->GetCharacterConst(id);
      if (character != nullptr) {
        if (character->IsControlCharacter()) {
          character->SetLimitHP(playerLimit & 0xffff);
        } else {
          character->SetLimitHP(0);
        }
      }
    }
  }
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
