#include "gf/game/gf_game_manager.h"
#include "gf/data/gf_character_id.h"
#include "gf/data/gf_data_blade.h"
#include "gf/data/gf_data_util.h"
#include "gf/data/gf_game_flag.h"
#include "gf/field/gf_field_time.h"
#include "gf/game/achiev/gf_achiev_manager.h"
#include "gf/game/event/gf_game_event.h"
#include "gf/game/gf_game_camera.h"
#include "gf/game/gf_game_env.h"
#include "gf/game/gf_game_mount.h"
#include "gf/game/gf_game_obj.h"
#include "gf/game/gf_game_party.h"
#include "gf/game/gf_game_scene.h"
#include "gf/game/gf_game_speed.h"
#include "gf/game/gf_game_util_hana.h"
#include "gf/game/gf_game_voice.h"
#include "gf/game/gf_layer_pause.h"
#include "gf/game/kizunaring/gf_kizunaring_manager.h"
#include "gf/game/mercenaries/gf_game_mercenaries.h"
#include "gf/gf_allocator.h"
#include "gf/gf_pause.h"
#include "gf/request/gf_req_scom.h"

namespace gf {

static GF_OBJ_HANDLE *const INVALID_HANDLE = reinterpret_cast<GF_OBJ_HANDLE *>(-1);

constexpr u32 SALVAGE_STATE_COMPLETE = 20;
constexpr u32 SALVAGE_COUNT_FLAG_SIZE = 16;
constexpr int SALVAGE_COUNT_FLAG = 1547;
constexpr u32 SALVAGE_COUNT_MAX = 0xffff;
constexpr u16 CHILD_QUEST_FORCE_BOSS_BATTLE_BGM = 210;
constexpr u16 SCENARIO_FLAG_FORCE_BOSS_BATTLE_BGM = 8024;

GfGameManager::GfGameManager(const GfSetupParam &param) : mInitialized(false), mIsLeaveGame(false) { initialize(param); }

// The empty statement makes the body non-trivial, which keeps the vtable pointer stores of the original.
GfGameManager::~GfGameManager() { ; }

void GfGameManager::build(const GfSetupParam &param) {
  // __LINE__ must be 124 as in the original file: its value changes the instruction order.
#line 124
  new (getAllocator(ALLOCATOR_SYSTEM), __FILE__, __LINE__, 8) GfGameManager(param);
}

void GfGameManager::destroy() {
  GfGameManager *manager = get();
  manager->finalize();
  delete manager;
}

bool GfGameManager::isGameObjEmpty() { return GfGameObj::isEmpty(); }

GF_STATE GfGameManager::getState() { return GfGameState::getState(); }

void GfGameManager::setState(GF_STATE state, bool isForce) { GfGameState::setState(state, isForce); }

void GfGameManager::clear() {
  GfGameManager *manager = get();
  SCOM_ACCESS_TARGET::create(INVALID_HANDLE);
  SCOM_TARGET_UI::create(INVALID_HANDLE);
  manager->mIsLeaveGame = false;
  GfGameCamera::clear();
  GfGameState::clear();
  GfGameEnv::clear();
  GfGameEvent::clear();
  if (GfGameScene::get() != nullptr) {
    GfGameScene::get()->clear();
  }

  GfGameSpeed::clear();
}

bool GfGameManager::isInitialized() { return get() != nullptr && get()->mInitialized; }

void GfGameManager::gevExecBuy(u32 item, u32 count, u32 shop) {
  if (GfGameScene::get() != nullptr) {
    GfGameScene::get()->gevExecBuy(item, count, shop);
  }
}

void GfGameManager::gevChangeParty() {
  if (GfGameScene::get() != nullptr) {
    GfGameScene::get()->gevChangeParty();
  }
}

void GfGameManager::gevGetArts(u32 driver, u32 arts, bool isPopup) {
  if (isPopup) {
    SCOM_POPUP::createArts(driver, arts);
  }
}

void GfGameManager::gevDriverLevel(u32 driver, u32 level, u32 oldLevel) {
  if (GfGameScene::get() != nullptr) {
    GfGameScene::get()->gevDriverLevel(driver, level, oldLevel);
  }
}

void GfGameManager::gevSelectHikari(bool hikariCurrent) {
  if (GfGameScene::get() != nullptr) {
    GfGameScene::get()->gevSelectHikari(hikariCurrent);
  }
}

void GfGameManager::gevBattleStart() {
  if (GfGameScene::get() != nullptr) {
    GfGameScene::get()->gevBattleStart();
  }
}

void GfGameManager::gevBattleEnd() {
  if (GfGameScene::get() != nullptr) {
    GfGameScene::get()->gevBattleEnd();
  }

  GfQuestManager::gevBattleEnd();
}

void GfGameManager::gevPause(u32 resumeBits, u32 pauseBits) {
  GfLayerPause::gevPause(resumeBits, pauseBits);
  GfGameEvent::gevPause(resumeBits, pauseBits);
  if (pauseBits & PAUSE_BIT_GAME) {
    GfGameSpeed::setGlobalSpeed(0.0f);
  }

  if (resumeBits & PAUSE_BIT_GAME) {
    GfGameSpeed::setGlobalSpeed(1.0f);
  }
}

void GfGameManager::gevChangeBlade(GF_OBJ_HANDLE *handle, int oldSlot, int newSlot) { GfGameParty::gevChangeBlade(handle, oldSlot, newSlot); }

void GfGameManager::gevMapjump(GEV event, const MapjumpCallbackInfo &info) {
  GfGameEnv::gevMapjump(event, info);
  GfGameEvent::gevMapjump(event, info);
  if (GfGameScene::get() != nullptr) {
    GfGameScene::get()->gevMapjump(event, info);
  }

  GfGameVoice::gevMapjump(event, info);
  GfQuestManager::gevMapjump(event, info);
  GfGameMercenaries::gevMapjump(event, info);
}

void GfGameManager::gevGameObjEnter(GF_OBJ_HANDLE *handle) {
  GfMountManager::gevGameObjEnter(handle);
  GfGameParty::gevGameObjEnter(handle);
  if (GfGameScene::get() != nullptr) {
    GfGameScene::get()->gevGameObjEnter(handle);
  }
}

void GfGameManager::gevGameObjLeave(GF_OBJ_HANDLE *handle) {
  if (GfGameScene::get() != nullptr) {
    GfGameScene::get()->gevGameObjLeave(handle);
  }

  GfGameParty::gevGameObjLeave(handle);
  GfMountManager::gevGameObjLeave(handle);
}

void GfGameManager::gevDriverActivate(u32 driver, ActivateType activateType, ActivateType oldActivateType) {
  if (GfGameScene::get() != nullptr) {
    GfGameScene::get()->gevDriverActivate(driver, activateType, oldActivateType);
  }
}

void GfGameManager::gevBladeActivate(u32 blade, ActivateType activateType, ActivateType oldActivateType) {
  if (activateType == ACTIVATE_TYPE_UNUSE && oldActivateType != ACTIVATE_TYPE_UNUSE) {
    GfKizunaringManager::orderAchievement(blade);
  }

  if (GfAchievManager::get() != nullptr) {
    GfAchievManager::get()->gevBladeActivate(blade, activateType, oldActivateType);
  }

  if (GfGameScene::get() != nullptr) {
    GfGameScene::get()->gevBladeActivate(blade, activateType, oldActivateType);
  }
}

void GfGameManager::gevBladeUnselect(u32 blade, bool unselect) {
  if (GfGameScene::get() != nullptr) {
    GfGameScene::get()->gevBladeUnselect(blade, unselect);
  }
}

void GfGameManager::gevBladeEnable(u32 blade) {
  GfGameUtilHana::setupDefaultParts(blade);
  if (blade == BLADE_REAL_ALIAS && GfDataBlade::getCreator(BLADE_REAL_ALIAS) == 0) {
    GfDataBlade::setCreator(BLADE_REAL_ALIAS, GfDataBlade::getCreator(BLADE_REAL_ALIAS_TARGET));
  }

  GfFieldTime *fieldTime = GfFieldTime::get();
  if (fieldTime != nullptr) {
    SDataBlade *dataBlade = GfDataBlade::getSDataBlade(blade);
    if (dataBlade->bornTime == 0) {
      dataBlade->bornTime = reinterpret_cast<const u32 &>(fieldTime->getElapseTime());
    }
  }
}

void GfGameManager::gevPlayEvent(GEV event, u32 eventId) {
  GfQuestManager::gevPlayEvent(event, eventId);
  if (GfGameEvent::get() != nullptr) {
    GfGameEvent::get()->gevPlayEvent(event, eventId);
  }

  GfGameEnv::gevPlayEvent(event, eventId);
  if (GfGameScene::get() != nullptr) {
    GfGameScene::get()->gevPlayEvent(event, eventId);
  }
}

void GfGameManager::gevItemAdd(u32 item, int count) {
  if (GfAchievManager::get() != nullptr) {
    GfAchievManager::get()->gevItemAdd(item, count);
  }

  GfQuestManager::gevItemAdd(item, count);
  if (GfGameScene::get() != nullptr) {
    GfGameScene::get()->gevItemAdd(item, count);
  }
}

void GfGameManager::gevPartyMemberOK(bool) {}

void GfGameManager::gevLayerPause(u32 layer, bool isPause) { GfGameVoice::gevLayerPause(layer, isPause); }

void GfGameManager::gevPartyIDMemberOK(bool isOK, u32 partyId) { GfGameParty::gevPartyIDMemberOK(isOK, partyId); }

void GfGameManager::gevReloadBdat(RELOAD_BDAT reload, u32 value) {
  GfQuestManager::gevReloadBdat(reload, value);
  if (reload == RELOAD_BDAT_ALL) {
    GfGameObj::bdatReload();
  }
}

void GfGameManager::gevSalvageStateChange(u32 state) {
  if (state == SALVAGE_STATE_COMPLETE) {
    u16 count = GfGameFlag::getLocal(SALVAGE_COUNT_FLAG_SIZE, SALVAGE_COUNT_FLAG);
    if (count != SALVAGE_COUNT_MAX) {
      count++;
    }

    GfGameFlag::setLocal(SALVAGE_COUNT_FLAG_SIZE, SALVAGE_COUNT_FLAG, count);
  }
}

void GfGameManager::gevChangeScenarioFlag(u32 scenarioFlag, u32 oldScenarioFlag) {
  if (GfGameScene::get() != nullptr) {
    GfGameScene::get()->gevChangeScenarioFlag(scenarioFlag, oldScenarioFlag);
  }
}

void GfGameManager::gevChangeWeather(u32 weather, u32 oldWeather) {
  if (GfGameScene::get() != nullptr) {
    GfGameScene::get()->gevChangeWeather(weather, oldWeather);
  }

  GfQuestManager::gevChangeWeather(weather, oldWeather);
}

void GfGameManager::gevChangeTimeRange(u32 timeRange) {
  if (GfGameScene::get() != nullptr) {
    GfGameScene::get()->gevChangeTimeRange(timeRange);
  }

  GfQuestManager::gevChangeTimeRange(timeRange);
}

void GfGameManager::gevGameState(GF_STATE state, GF_STATE oldState) { GfGameEnv::gevGameState(state, oldState); }

void GfGameManager::gevControllFree(bool isFree) {
  if (GfGameScene::get() != nullptr) {
    GfGameScene::get()->gevControllFree(isFree);
  }
}

void GfGameManager::gevMercenariesMissionFlag(u32 mission, u32 flag, u32 value) {
  if (GfAchievManager::get() != nullptr) {
    GfAchievManager::get()->gevMercenariesMissionFlag(mission, flag, value);
  }

  if (GfGameScene::get() != nullptr) {
    GfGameScene::get()->gevMercenariesMissionFlag(mission, flag, value);
  }

  GfQuestManager::gevMercenariesMissionFlag(mission, flag, value);
  GfGameMercenaries::gevMercenariesMissionFlag(mission, flag, value);
}

void GfGameManager::qevCompleteQuest(const QuestCompleteParam &param) {
  GfGameMercenaries::qevCompleteQuest(param);
  if (GfKizunaringManager::get() != nullptr) {
    GfKizunaringManager::get()->qevCompleteQuest(param);
  }

  if (GfGameScene::get() != nullptr) {
    GfGameScene::get()->qevCompleteQuest(param);
  }
}

void GfGameManager::qevOrderQuest(const QuestOrderParam &param) { GfGameMercenaries::qevOrderQuest(param); }

void GfGameManager::qevCompleteChildQuest(const QuestCompleteChildParam &param) {
  if (param.quest.id == CHILD_QUEST_FORCE_BOSS_BATTLE_BGM && GfDataUtil::getScenarioFlag() == SCENARIO_FLAG_FORCE_BOSS_BATTLE_BGM) {
    GfGameScene *scene = GfGameScene::get();
    if (scene != nullptr && !scene->isForceBossBattleBgm()) {
      scene->setForceBossBattleBgm(true);
    }
  }
}

} // namespace gf
