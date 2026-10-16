#include "gf/game/gf_game_manager.h"

#include "battle/battle_manager.h"
#include "framework/framework.h"
#include "gf/asset/gf_asset_manager.h"
#include "gf/data/gf_bdat_rsc.h"
#include "gf/data/gf_character_id.h"
#include "gf/data/gf_data_blade.h"
#include "gf/data/gf_data_driver.h"
#include "gf/data/gf_data_enemy.h"
#include "gf/data/gf_data_manager.h"
#include "gf/data/gf_data_map.h"
#include "gf/data/gf_data_param_acc.h"
#include "gf/data/gf_data_util.h"
#include "gf/data/gf_game_flag.h"
#include "gf/data/gf_object_type.h"
#include "gf/field/gf_field_sound.h"
#include "gf/field/gf_field_time.h"
#include "gf/field/gf_field_weather.h"
#include "gf/game/achiev/gf_achiev_manager.h"
#include "gf/game/auto_talk/gf_auto_talk.h"
#include "gf/game/blade/gf_blade_manager.h"
#include "gf/game/event/gf_game_event.h"
#include "gf/game/gf_game_camera.h"
#include "gf/game/gf_game_cond.h"
#include "gf/game/gf_game_depop_meter_manager.h"
#include "gf/game/gf_game_env.h"
#include "gf/game/gf_game_inside_battle_lock.h"
#include "gf/game/gf_game_mount.h"
#include "gf/game/gf_game_mover_switcher.h"
#include "gf/game/gf_game_obj.h"
#include "gf/game/gf_game_pad.h"
#include "gf/game/gf_game_party.h"
#include "gf/game/gf_game_player_camera.h"
#include "gf/game/gf_game_player_formation.h"
#include "gf/game/gf_game_player_unique_scheduler.h"
#include "gf/game/gf_game_ride.h"
#include "gf/game/gf_game_scene.h"
#include "gf/game/gf_game_speed.h"
#include "gf/game/gf_game_state.h"
#include "gf/game/gf_game_target.h"
#include "gf/game/gf_game_util.h"
#include "gf/game/gf_game_util_hana.h"
#include "gf/game/gf_game_visible.h"
#include "gf/game/gf_game_voice.h"
#include "gf/game/gf_layer_pause.h"
#include "gf/game/item/gf_item_manager.h"
#include "gf/game/kizunaring/gf_kizunaring_manager.h"
#include "gf/game/mercenaries/gf_game_mercenaries.h"
#include "gf/game/quest/gf_quest_id.h"
#include "gf/game/salvage/gf_game_salvage.h"
#include "gf/game/sequential_play/gf_play_command.h"
#include "gf/game/sequential_play/gf_sequential_play.h"
#include "gf/game/smn_enemy/gf_smn_enemy.h"
#include "gf/game/talk/gf_game_talk.h"
#include "gf/gf_allocator.h"
#include "gf/gf_manager.h"
#include "gf/gf_pause.h"
#include "gf/menu/gf_menu_manager.h"
#include "gf/menu/object/gf_menu_obj_tutorial.h"
#include "gf/object/gf_obj_acc.h"
#include "gf/object/gf_obj_handle.h"
#include "gf/object/gf_obj_manager.h"
#include "gf/object/gf_obj_setup.h"
#include "gf/object/gf_obj_util.h"
#include "gf/request/gf_req_scom.h"
#include "gf/sound/gf_sound.h"
#include "mm_math/mm_col4.h"
#include "mm_mtl/fixed_array.h"
#include "mm_mtl/fixed_list.h"
#include "mm_mtl/fixstr.h"

namespace gf {

constexpr u32 PARTY_ID_LEADER = 0;
constexpr u32 SALVAGE_STATE_COMPLETE = 20;
constexpr u32 SALVAGE_COUNT_FLAG_SIZE = 16;
constexpr int SALVAGE_COUNT_FLAG = 1547;
constexpr u32 SALVAGE_COUNT_MAX = 0xffff;
constexpr u16 CHILD_QUEST_FORCE_BOSS_BATTLE_BGM = 210;
constexpr u16 SCENARIO_FLAG_FORCE_BOSS_BATTLE_BGM = 8024;
constexpr u16 SCENARIO_FLAG_GAME_END = 10033;
constexpr u16 SCENARIO_FLAG_PER_SCENARIO = 1000;
constexpr u32 FADE_ALL = 0xffffffff;
constexpr u32 FADE_LAYER_COUNT = 3;
constexpr f32 FADEOUT_ALPHA = 0.9f;
constexpr u32 PAUSE_BITS_MAIN_MENU = 0x40;
constexpr u32 PAUSE_BITS_GIMMICK = 0x59;
constexpr u32 TIME_RANGE_DN_NIGHT = 7;
constexpr u32 ASSET_PACK_MAX = 512;
constexpr u32 DEPOP_METER_COUNT = 4;

static u32 getValidDriverId(const DataParamAcc &paramAcc) {
  return paramAcc.isValid() && paramAcc.getObjType() == OBJECT_TYPE_DRIVER ? paramAcc.getBdatId() : 0;
}

static bool isEventCharacter(u32 characterType) {
  switch (characterType) {
  case CHARACTER_TYPE_EVENT_DRIVER:
  case CHARACTER_TYPE_EVENT_BLADE:
  case CHARACTER_TYPE_EVENT_NPC:
    return true;
  default:
    return false;
  }
}

GfGameManager::GfGameManager(const GfSetupParam &param) : mInitialized(false), mIsLeaveGame(false) { initialize(param); }

void GfGameManager::initialize(const GfSetupParam &param) {
  GfEvent::addEventCallback(this);
  GfGameState::build(param);
  GfLayerPause::build(param);
  GfGameSpeed::build(param);
  GfGameEnv::build(param);
  GfGamePad::build(param);
  GfGameCamera::build(param);
  GfGameCond::build(param);
  GfGameObj::build(param);
  GfMountManager::build(param);
  GfGameParty::build(param);
  GfItemManager::build(param);
  GfQuestManager::build(param);
  GfGameMercenaries::build(param);
  GfGameTalk::build(param);
  GfGameEvent::build(param);
  GfGameTarget::build(param);
  GfGameSalvage::build(param);
  GfSequentialPlay::build(param);
  GfAutoTalkManager::build(param);
  GfGamePlayerFormation::build(param);
  GfBladeManager::build(param);
  GfAchievManager::build(param);
  GfKizunaringManager::build(param);
  GfGameVisible::build(param);
  GfGamePlayerUniqueScheduler::build(param);
  GfGameScene::build(param);
  GfGameDepopMeterManager::create(DEPOP_METER_COUNT);
  GfSmnEnemyManager::create();
  GfGamePlayerCamera::build(param);
  GfGameRide::build(param);
  GfGameMoverSwitcher::build(param);
  GfGameVoice::build(param);
  GfGameInsideBattleLock::build(param);
  GfQuestManager::addEvent(this);
  GfMenuManager::initOptionData(*GfDataManager::getDataOption());
  mInitialized = true;
}

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

void GfGameManager::finalize() {
  GfLayerPause::destroyLayerPause();
  if (!GfGameObj::isEmpty()) {
    GfSleep(1);
  }

  if (GfGameState::getState() != GF_STATE_CONTROL) {
    GfSleep(1);
  }

  GfGameState::setState(GF_STATE_DESTROY, false);
  GfQuestManager::removeEvent(this);
  GfGameInsideBattleLock::destroy();
  GfGameVoice::destroy();
  GfGameMoverSwitcher::destroy();
  GfGameRide::destroy();
  GfGamePlayerCamera::destroy();
  GfSmnEnemyManager::dispose();
  GfGameDepopMeterManager::dispose();
  GfGameScene::destroy();
  GfGamePlayerUniqueScheduler::destroy();
  GfGameVisible::destroy();
  GfKizunaringManager::destroy();
  GfAchievManager::destroy();
  GfBladeManager::destroy();
  GfGamePlayerFormation::destroy();
  GfAutoTalkManager::destroy();
  GfSequentialPlay::destroy();
  GfGameSalvage::destroy();
  GfGameTarget::destroy();
  GfGameEvent::destroy();
  GfGameTalk::destroy();
  GfGameMercenaries::destroy();
  GfItemManager::destroy();
  GfQuestManager::destroy();
  GfGameParty::destroy();
  GfMountManager::destroy();
  GfGameObj::destroy();
  GfGameCond::destroy();
  GfGameCamera::destroy();
  GfGamePad::destroy();
  GfGameEnv::destroy();
  GfGameSpeed::destroy();
  GfLayerPause::destroy();
  GfGameState::destroy();
  GfEvent::removeEventCallback(this);
  mInitialized = false;
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

bool GfGameManager::isInnerState(GF_STATE state) { return GfSequentialPlay::isInnerState(state); }

GF_OBJ_HANDLE *GfGameManager::getPartyLeader() {
  GF_OBJ_HANDLE *leader = GfGameParty::getLeader();
  GfObjAcc objAcc(leader);
  if (objAcc.isValid() && (GfGameObj::isValidGameObj(leader, true, nullptr) || GfGameObj::isEnterGameObj(leader) ||
                           (fw::Framework::isLayerPause(objAcc.getLayer()) && GfObjUtil::isUpdate(leader)))) {
    return leader;
  }

  return INVALID_HANDLE;
}

GF_OBJ_HANDLE *GfGameManager::getPartyLeaderDriver() {
  GF_OBJ_HANDLE *driver = GfGameParty::getLeaderDriver();
  GfObjAcc objAcc(driver);
  if (GfGameObj::isValidGameObj(driver, true, nullptr) || GfGameObj::isEnterGameObj(driver) ||
      (fw::Framework::isLayerPause(objAcc.getLayer()) && GfObjUtil::isUpdate(driver))) {
    return driver;
  }

  return INVALID_HANDLE;
}

GF_OBJ_HANDLE *GfGameManager::getControlMover() {
  GfGamePlayerFormation *formation = GfGamePlayerFormation::get();
  if (formation != nullptr && formation->players[0].handle != INVALID_HANDLE) {
    return formation->players[0].handle;
  }

  return getPartyLeader();
}

GF_OBJ_HANDLE *GfGameManager::getControlRider() {
  GfObjAcc moverAcc(getControlMover());
  if (moverAcc.isValid()) {
    u32 partyId = GfGameParty::getPartyId(moverAcc.getHandle());
    if (partyId != PARTY_ID_NONE) {
      GF_OBJ_HANDLE *driver = GfGameParty::getHandleDriver(partyId);
      GF_OBJ_HANDLE *blade = GfGameParty::getHandleBlade(partyId, -1);
      GfObjAcc driverAcc(driver);
      GfObjAcc bladeAcc(blade);
      return GfGameRide::testRideOn() ? driverAcc.getHandle() : moverAcc.getHandle();
    }
  }

  return INVALID_HANDLE;
}

void GfGameManager::collectPadCharList(mm::mtl::FixedArray<GF_OBJ_HANDLE *, 2> *characters) { (*characters)[0] = getControlMover(); }

bool GfGameManager::isPlayerPause() { return GfGameScene::get() != nullptr && GfGameScene::get()->isPlayerPause(); }

void GfGameManager::enterBattle(bool isForce) {
  if (GfGameScene::get() != nullptr) {
    GfGameScene::get()->enterBattle(isForce);
  }
}

bool GfGameManager::isBattle() { return GfGameScene::get() != nullptr && GfGameScene::get()->isBattle(); }

bool GfGameManager::isBattleStop() { return GfGameScene::get() != nullptr && GfGameScene::get()->isBattleStop(); }

bool GfGameManager::isControlMoverBattle() {
  GfObjAcc moverAcc(getControlMover());
  return moverAcc.isBattle();
}

bool GfGameManager::isQuestCompleteUI() { return GfPlayComQuestCompleteUI::s_active > 0; }

bool GfGameManager::isPartySelect() { return GfPlayComOpenMenu::s_active > 0; }

bool GfGameManager::isEvent(bool isIncludeSequentialPlay) {
  return get() != nullptr && (GfGameState::test(GF_STATE_FLAG_EVENT) || (isIncludeSequentialPlay && GfSequentialPlay::isInnerState(GF_STATE_EVENT)));
}

bool GfGameManager::isEventWait() { return GfGameState::getState() == GF_STATE_WAIT_EVENT; }

bool GfGameManager::isPlayEvent() { return GfGameScene::get() != nullptr && GfGameScene::get()->isPlayEvent(); }

bool GfGameManager::isField() {
  if (get() == nullptr || GfGameState::getState() != GF_STATE_CONTROL) {
    return false;
  }

  if (isPlayerPause() || isBattle()) {
    return false;
  }

  return GfGameState::getStateReserve() == GF_STATE_CONTROL;
}

bool GfGameManager::isPlaySequenceClear() { return !GfSequentialPlay::isPlay(); }

bool GfGameManager::isControlFree() { return GfGameScene::get() != nullptr && GfGameScene::get()->isControlFree(); }

bool GfGameManager::isControlFree(u32 state) {
  if (!isControlFree()) {
    return false;
  }

  if (GfGameState::getStateReserve() == GF_STATE_CONTROL) {
    return true;
  }

  return GfGameState::getStateReserve() == state;
}

bool GfGameManager::isBladeChange() { return isInnerState(GF_STATE_RESET_BLADE); }

bool GfGameManager::isDisableBattou() {
  if (GfPlayComResetBlade::isPlaying(PARTY_ID_LEADER)) {
    return true;
  }

  GfObjAcc bladeAcc(GfGameParty::getHandleBlade(PARTY_ID_LEADER, -1));
  if (bladeAcc.isRebuild()) {
    return true;
  }

  return isEnableBattouWithHoodHomura(true);
}

bool GfGameManager::isEnableBattouWithHoodHomura(bool isCheckCondition) {
  if (isBattle()) {
    return false;
  }

  GfObjAcc moverAcc(getControlMover());
  if (moverAcc.getType() != OBJECT_TYPE_DRIVER || moverAcc.getDriverId() != DRIVER_REX || GfDataDriver::getBlade(DRIVER_REX, -1) != BLADE_HOMURA) {
    return false;
  }

  GfObjAcc bladeAcc(GfGameParty::getHandleBlade(PARTY_ID_LEADER, -1));
  if (bladeAcc.getBladeId() != BLADE_HOMURA) {
    return false;
  }

  if (moverAcc.isBattle() || bladeAcc.isRebuild()) {
    return false;
  }

  if (GfGameScene::get() != nullptr && !GfGameScene::isPlayerWalkAndRun()) {
    return false;
  }

  if (isCheckCondition && GfPlayComResetBlade::isPlaying(PARTY_ID_LEADER)) {
    return false;
  }

  GfObjAcc targetAcc(moverAcc.getTarget());
  if (targetAcc.getType() != OBJECT_TYPE_ENEMY) {
    return false;
  }

  if (isCheckCondition && !GfGameCond::isGameCond(GfDataBlade::getSDataBlade(bladeAcc.getBladeId())->condition)) {
    return false;
  }

  if (!isEnableOpenMainMenuSequence()) {
    return false;
  }

  if (isCheckCondition && !isEnableOpenMainMenu()) {
    return false;
  }

  return true;
}

bool GfGameManager::isTalkOK() { return isControlFree(); }

bool GfGameManager::isTalking() {
  if (GfGameScene::get() != nullptr && GfGameScene::get()->isPlayerTalkForce()) {
    return true;
  }

  return GfGameState::test(GF_STATE_FLAG_TALK);
}

bool GfGameManager::isFullScreenMenu() { return GfMenuManager::isOpenFullScreen(); }

bool GfGameManager::isPlayCommonMenu() { return GfMenuManager::isOpenCommonWindow() && GfPause::isPause(PAUSE_BIT_SYSTEM); }

bool GfGameManager::isMapjumpOK() {
  if (GfGameState::getState() == GF_STATE_MAPJUMP) {
    return false;
  }

  if (GfGameState::getStateReserve() == GF_STATE_MAPJUMP) {
    return false;
  }

  if (GfGameState::getState() == GF_STATE_MAPJUMP_SKIP_TRAVEL) {
    return false;
  }

  return GfGameState::getStateReserve() != GF_STATE_MAPJUMP_SKIP_TRAVEL;
}

bool GfGameManager::isExecTutorial() { return GfMenuObjTutorial::isWaiting(); }

bool GfGameManager::isGmkTutorialMoverOK() {
  return GfGameScene::get() != nullptr && GfGameScene::get()->isPlayerStopFlag(PLSTOP_GMK_TUTORIAL_MOVER);
}

void GfGameManager::setGmkTutorialMoverOK(bool isOK) {
  if (GfGameScene::get() != nullptr) {
    GfGameScene::get()->setPlayerStopFlag(PLSTOP_GMK_TUTORIAL_MOVER, isOK);
  }
}

bool GfGameManager::isGmkTutorialSequenceOK() {
  GfGameScene *scene = GfGameScene::get();
  if (scene == nullptr) {
    return false;
  }

  return scene->isPlayerStopFlag(PLSTOP_GMK_TUTORIAL_SEQUENCE) || scene->isPlayerStopFlag(PLSTOP_EVENT) ||
         scene->isPlayerStopFlag(PLSTOP_RESET_BLADE);
}

void GfGameManager::setGmkTutorialSequenceOK(bool isOK) {
  if (GfGameScene::get() != nullptr) {
    GfGameScene::get()->setPlayerStopFlag(PLSTOP_GMK_TUTORIAL_SEQUENCE, isOK);
  }
}

bool GfGameManager::isValidCollisionVelocity() { return GfGameScene::get() != nullptr && GfGameScene::get()->isValidCollisionVelocity; }

void GfGameManager::setValidCollisionVelocity(bool isValid) {
  if (GfGameScene::get() != nullptr) {
    GfGameScene::get()->isValidCollisionVelocity = isValid;
  }
}

bool GfGameManager::isLeaveGameForDebug() { return get() != nullptr && (get()->mIsLeaveGame || GfManager::isDestroyNow()); }

bool GfGameManager::isGameOver() { return GfDataUtil::getScenarioFlag() > SCENARIO_FLAG_GAME_END; }

bool GfGameManager::isFieldLockMsgOK() { return isEnableFieldAccess() && isControlFree(); }

bool GfGameManager::isEnableFieldAccess() {
  if (GfSequentialPlay::isInnerState(GF_STATE_RESET_BLADE) || GfSequentialPlay::isInnerState(GF_STATE_PLAYER_DEAD)) {
    return false;
  }

  if (!isEnableOpenMainMenuSequence()) {
    return false;
  }

  GfGameScene *scene = GfGameScene::get();
  if (scene != nullptr) {
    DataParamAcc driverAcc(GfGameParty::getHandleDriver(PARTY_ID_LEADER));
    if (driverAcc.isValid() && getValidDriverId(driverAcc) == DRIVER_NIA) {
      if (scene->isNeedFieldBladeChange(PARTY_ID_LEADER)) {
        return false;
      }

      if (GfDataDriver::getBlade(getValidDriverId(driverAcc), -1) == BLADE_BYAKKO &&
          GfObjUtil::getParentHandle(driverAcc.handle) != GfGameParty::getHandleBlade(PARTY_ID_LEADER, -1)) {
        return false;
      }
    }
  }

  return true;
}

bool GfGameManager::isAutoTalkOK() { return !isBattle() && isControlFree(); }

bool GfGameManager::isInGamePauseMenuOK() {
  if (GfPlayComMenuChapter::s_activate > 0 || GfPlayComMenuZone::s_activate > 0) {
    return false;
  }

  return isControlFree(GF_STATE_MENU);
}

bool GfGameManager::isRoom() { return GfGameEnv::isRoom(); }

bool GfGameManager::isWeatherSE() { return GfFieldWeather::isWeatherSE(); }

u32 GfGameManager::getMapJumpID() { return GfGameEnv::getMapJumpID(); }

u32 GfGameManager::getMapID() { return GfGameEnv::getMapID(); }

void GfGameManager::setMapID(u32 mapJump, u32 map) { GfGameEnv::setMapID(mapJump, map); }

u32 GfGameManager::getMapZoneID() { return GfDataMap::getZoneIdForGameMap(GfGameEnv::getMapID()); }

void GfGameManager::setAccessTarget(GF_OBJ_HANDLE *target) { GfEvent::callTargetAccess(target); }

void GfGameManager::setTargetUI(GF_OBJ_HANDLE *target) { GfEvent::callTargetChange(target); }

bool GfGameManager::isEnableFieldBattleTarget() {
  GfObjAcc driverAcc(getPartyLeaderDriver());
  if (driverAcc.isBattle()) {
    return true;
  }

  if (isInnerState(GF_STATE_MENU)) {
    return false;
  }

  if (isInnerState(GF_STATE_SALVAGE)) {
    return false;
  }

  if (isInnerState(GF_STATE_GIMMICK_TASK)) {
    return false;
  }

  if (isInnerState(GF_STATE_MAP_GIMMICK)) {
    return false;
  }

  if (isInnerState(GF_STATE_COLLECT)) {
    return false;
  }

  if (isInnerState(GF_STATE_FIELD_TBOX)) {
    return false;
  }

  if (isInnerState(GF_STATE_TALK)) {
    return false;
  }

  if (isInnerState(GF_STATE_GMK_CAMERA)) {
    return false;
  }

  if (isInnerState(GF_STATE_JUMP)) {
    return false;
  }

  if (isInnerState(GF_STATE_WARP)) {
    return false;
  }

  if (isInnerState(GF_STATE_GMK_TUTORIAL)) {
    return false;
  }

  return !isInnerState(GF_STATE_EVENT);
}

void GfGameManager::setupGame() {
  if (GfManager::isContinueGame() || GfManager::isNewGame()) {
  }

  GfQuestManager::setupGame();
  GfKizunaringManager::setupGame();
  GfBladeManager::setupGame();
  GfMenuManager::setupGame();
  if (GfGameScene::get() != nullptr) {
    GfGameScene::get()->setupGame();
  }

  if (GfSound::get() != nullptr) {
    GfSound::get()->setupGame();
  }
}

bool GfGameManager::isFading(u32 fade) {
  if (fade == FADE_ALL) {
    for (u32 layer = 0; layer < FADE_LAYER_COUNT; layer++) {
      if (GfMenuManager::isFading(layer)) {
        return true;
      }
    }

    return false;
  }

  return GfMenuManager::isFading(fade) || GfReqSmallCom::isExistCommand(SCOM_TYPE_FADE);
}

bool GfGameManager::isFadeout() {
  for (u32 layer = 0; layer < FADE_LAYER_COUNT; layer++) {
    mm::Col4 color;
    GfMenuManager::getFadeColor(layer, color);
    if (color.a >= FADEOUT_ALPHA) {
      return true;
    }
  }

  return false;
}

void GfGameManager::getFadeColor(u32 fade, mm::Col4 &color) { GfMenuManager::getFadeColor(fade, color); }

bool GfGameManager::isFadeClear() {
  if (isFadeout() || isFading(FADE_ALL)) {
    return false;
  }

  for (u32 layer = 0; layer < FADE_LAYER_COUNT; layer++) {
    mm::Col4 color;
    GfMenuManager::getFadeColor(layer, color);
    if (color.a > 0.0f) {
      return false;
    }
  }

  return true;
}

f32 GfGameManager::getFadeoutAlpha() {
  f32 alpha = 0.0f;
  for (u32 layer = 0; layer < FADE_LAYER_COUNT; layer++) {
    mm::Col4 color = mm::Col4::zero;
    GfMenuManager::getFadeColor(layer, color);
    alpha = alpha < color.a ? color.a : alpha;
  }

  return alpha > 1.0f ? 1.0f : alpha;
}
bool GfGameManager::isStopBattleSequence() {
  if (get() == nullptr || btl::BattleManager::get() == nullptr) {
    return true;
  }

  if (!btl::BattleManager::isInitialized()) {
    return true;
  }

  if (GfReqSmallCom::isExistCommand(SCOM_TYPE_PARTY_ADD)) {
    return true;
  }

  if (GfObjManager::get() != nullptr && GfObjManager::get()->hasReloadObjForDebug()) {
    return true;
  }

  return false;
}

bool GfGameManager::isMapjump() { return GfGameEnv::isMapjump(); }

bool GfGameManager::isMapjumpWithSaveData() { return GfGameEnv::isMapjumpWithSaveData(); }

bool GfGameManager::isMapjumpBlackout() { return GfGameEnv::isMapjumpBlackout(); }

bool GfGameManager::isPlayerCameraPause() {
  if (GfManager::isDestroyNow()) {
    return false;
  }

  if (isFadeout()) {
    return true;
  }

  return GfGameScene::get() != nullptr && GfGameScene::get()->isPlayerCameraPause();
}

u32 GfGameManager::getDeadType() { return GfGameScene::get() != nullptr ? GfGameScene::get()->getDeadType() : 0; }

void GfGameManager::leaveGameForDebug() {
  GfGameManager *manager = get();
  if (manager != nullptr) {
    manager->mIsLeaveGame = true;
    GfGameEvent::finishNewGameWait();
    GfGameEvent::stop();
    if (GfGameScene::get() != nullptr) {
      GfGameScene::get()->setForceStopBattle(true);
    }
  }
}

bool GfGameManager::isPadCameraForDebug() { return false; }

void GfGameManager::setInterruptPadOnForDebug(DWPAD pad) { GfGamePad::setInterruptPadOnForDebug(pad); }

bool GfGameManager::isScenarioGame() { return GfManager::isExecModeScenarioGame(); }

bool GfGameManager::isAdvertize() { return GfManager::isExecModeAdvertize(); }

bool GfGameManager::isPartyCreateForMapjump() { return !GfManager::isExecKillPartyCreate(); }

bool GfGameManager::isActivateHikari(bool isCheckLeader) {
  bool isActivate = GfDataBlade::isActivateDriver(BLADE_HIKARI);
  if (isCheckLeader) {
    GfObjAcc leaderAcc(GfGameParty::getLeaderDriver());
    return leaderAcc.isValid() && isActivate && leaderAcc.getDriverId() == GfDataDriver::getDriverBySetBlade(BLADE_HIKARI);
  }

  return isActivate;
}

bool GfGameManager::isActivateHomuri(bool isCheckLeader) {
  bool isActivate = GfDataBlade::isActivateDriver(BLADE_HOMURI);
  if (isCheckLeader) {
    GfObjAcc leaderAcc(GfGameParty::getLeaderDriver());
    return leaderAcc.isValid() && isActivate && leaderAcc.getDriverId() == GfDataDriver::getDriverBySetBlade(BLADE_HOMURI);
  }

  return isActivate;
}

bool GfGameManager::isInMetJIJI() { return GfGameCond::isGameCond(GfBdatRsc::get()->getDriverParamExtMountCond(DRIVER_REX)); }

OwnerBonus *GfGameManager::getOwnerBonus() { return &GfGameScene::get()->getOwnerBonus(); }

bool GfGameManager::isPlayerFinishBattleState() {
  if (GfGameParty::isLeaderBlade()) {
    return true;
  }

  DataParamAcc leaderAcc(GfGameParty::getLeader());
  if (leaderAcc.getObjType() == OBJECT_TYPE_DRIVER && getValidDriverId(leaderAcc) == DRIVER_NIA && leaderAcc.getBlade(-1, false) == BLADE_BYAKKO) {
    return true;
  }

  return false;
}

bool GfGameManager::isEnableOpenMainMenuSequence() {
  if (GfGameScene::get() == nullptr || GfGameScene::get()->isStartGame) {
    return false;
  }

  if (GfGameEnv::isMapjump()) {
    return false;
  }

  if (isLeaveGameForDebug()) {
    return false;
  }

  if (GfSequentialPlay::isInnerPause(PAUSE_BITS_MAIN_MENU)) {
    return false;
  }

  if (isBattle()) {
    return false;
  }

  {
    GfObjAcc moverAcc(getControlMover());
    if (moverAcc.isBattle()) {
      return false;
    }
  }

  {
    DataParamAcc driverAcc(getPartyLeaderDriver());
    if (driverAcc.isValid() && driverAcc.getHp() == 0) {
      return false;
    }
  }

  if (GfSequentialPlay::isInnerState(GF_STATE_SALVAGE)) {
    return false;
  }

  if (GfGameScene::get() != nullptr && GfGameScene::get()->isNeedResetBladeForBattleEndForMenuOpen()) {
    return false;
  }

  return true;
}

bool GfGameManager::isStartGame() { return GfGameScene::get() == nullptr || GfGameScene::get()->isStartGame; }

bool GfGameManager::isStopMainMenuOpenForGimmick() { return GfGameScene::get() != nullptr && GfGameScene::get()->isStopMainMenuOpenForGimmick; }

bool GfGameManager::isEnableHoodHomuraScenes() { return !isInnerState(GF_STATE_RESET_BLADE) && !isInnerState(GF_STATE_PLAYER_DEAD); }

bool GfGameManager::isEnableGimmickPhantomDamage() { return !GfSequentialPlay::isInnerPause(PAUSE_BITS_GIMMICK); }

bool GfGameManager::isEnableGetFieldPrecious() { return isEnableOpenMainMenuSequence() && isEnableOpenMainMenu(); }

bool GfGameManager::isEnableCreateBattleLock() { return !GfSequentialPlay::isInnerPause(PAUSE_BITS_GIMMICK); }

bool GfGameManager::isPartyMover(GF_OBJ_HANDLE *handle) {
  int partyId = GfObjUtil::getPartyID(handle);
  return partyId != -1 && GfGameParty::getHandleMover(partyId) == handle;
}

bool GfGameManager::isBusyBladeCreateEvent() {
  if (!GfPause::isPause(PAUSE_BIT_SYSTEM)) {
    return false;
  }

  if (isEvent(false)) {
    return true;
  }

  for (GF_OBJ_HANDLE *const &handle : *GfGameObj::getList(OBJECT_TYPE_NONE)) {
    GfObjSetup *setup = GfObjUtil::getObjSetup(handle);
    if (setup == nullptr) {
      continue;
    }

    if (!isEventCharacter(setup->characterType)) {
      continue;
    }

    GfObjAcc acc(handle);
    if (acc.getAlpha() <= 0.0f) {
      continue;
    }

    if (acc.isDisp(static_cast<OBJDISP>(0))) {
      return true;
    }
  }

  return false;
}

bool GfGameManager::isExistBossEnemy() {
  for (GF_OBJ_HANDLE *const &handle : *GfGameObj::getList(OBJECT_TYPE_ENEMY)) {
    GfObjAcc acc(handle);
    if (GfDataEnemy::isBoss(acc.getEnArrangeId())) {
      return true;
    }
  }

  return false;
}

bool GfGameManager::isExistBossEnemyWithHp() {
  for (GF_OBJ_HANDLE *const &handle : *GfGameObj::getList(OBJECT_TYPE_ENEMY)) {
    GfObjAcc acc(handle);
    if (!acc.isBattle()) {
      continue;
    }

    DataParamAcc dataParamAcc(handle);
    if (GfDataEnemy::isBoss(dataParamAcc.isValid() ? dataParamAcc.getBdatId() : 0) && dataParamAcc.getHp() != 0 &&
        dataParamAcc.getHp() < dataParamAcc.getHpMax(false)) {
      return true;
    }
  }

  return false;
}

bool GfGameManager::isNeedResetBlade() {
  return GfSelectBlade::isNeedFieldBladeChange(0) || GfSelectBlade::isNeedFieldBladeChange(1) || GfSelectBlade::isNeedFieldBladeChange(2);
}

bool GfGameManager::isStopEnemySearch() { return GfGameEnv::isStopEnemySearch(); }

bool GfGameManager::isPlayerDeadSequence() { return GfPlayComPlayerDead::isDead(); }

bool GfGameManager::isForceBossBattleBgm() { return GfGameScene::get() != nullptr && GfGameScene::get()->isForceBossBattleBgm(); }

bool GfGameManager::isForceEventBgm() { return GfGameScene::get() != nullptr && GfGameScene::get()->isForceEventBgm(); }

bool GfGameManager::isNight() { return GfFieldTime::get() != nullptr && GfFieldTime::get()->getTimeRangeDN() == TIME_RANGE_DN_NIGHT; }

void GfGameManager::destroyBattleEnemy() {
  for (GF_OBJ_HANDLE *const &handle : *GfGameObj::getList(OBJECT_TYPE_ENEMY)) {
    GfObjAcc acc(handle);
    if (!acc.isBattle()) {
      continue;
    }

    DataParamAcc dataParamAcc(handle);
    if (dataParamAcc.getHp() != 0) {
      GfGameUtil::debugHpZero(handle);
    }
  }
}

const char *GfGameManager::getMapSePackName() {
  GfFieldSound *fieldSound = GfFieldSound::get();
  return fieldSound != nullptr ? fieldSound->mapSePackName.c_str() : nullptr;
}

u32 GfGameManager::getScenarioId() {
  if (!GfManager::isExecModeScenarioGame()) {
    return 0;
  }

  u16 scenarioFlag = GfDataUtil::getScenarioFlag();
  return scenarioFlag == 0 ? 1 : scenarioFlag / SCENARIO_FLAG_PER_SCENARIO;
}

bool GfGameManager::isRexAwakening() { return GfGameUtil::isCondDriverModel(DRIVER_REX); }

void GfGameManager::setStartGame() {
  if (GfGameScene::get() != nullptr) {
    GfGameScene::get()->isStartGame = true;
  }
}

bool GfGameManager::isEnableRoomForHikariLv4() { return GfGameScene::get() != nullptr && GfGameScene::get()->isEnableRoomForHikariLv4; }

void GfGameManager::setHomuriWeaponExtraMesh(bool isVisible, f32 alpha) {
  if (GfGameScene::get() != nullptr) {
    GfGameScene::get()->setHomuriWeaponExtraMesh(isVisible, alpha);
  }
}

bool GfGameManager::isOpenPreciousMenu() { return GfPlayComMenuPrecious::s_activate > 0; }

bool GfGameManager::isStopEnemyAttack() { return GfGameScene::get() != nullptr && GfGameScene::get()->stopEnemyAttackCount > 0; }

bool GfGameManager::isPlayEnemyVoice() { return GfGameVoice::get() != nullptr && GfGameVoice::get()->isPlayEnemyVoice(); }

bool GfGameManager::isPlayVoice(GF_OBJ_HANDLE *handle) { return GfGameVoice::get() != nullptr && GfGameVoice::get()->isPlayVoice(handle); }

bool GfGameManager::isPartyMemberPlayVoice() {
  GfGameVoice *voice = GfGameVoice::get();
  if (voice == nullptr) {
    return false;
  }

  for (u32 partyId = 0; partyId < PARTY_MEMBER_NUM; partyId++) {
    if (voice->isPlayVoice(GfGameParty::getHandleDriver(partyId)) || voice->isPlayVoice(GfGameParty::getHandleBlade(partyId, -1))) {
      return true;
    }
  }

  return false;
}

void GfGameManager::setStopMainMenuOpenForGimmick(bool isStop) {
  if (GfGameScene::get() != nullptr) {
    GfGameScene::get()->isStopMainMenuOpenForGimmick = isStop;
  }
}

bool GfGameManager::isDisableJumpForRide() { return GfGameScene::get() != nullptr && GfGameScene::get()->isDisableJumpForRide(); }

bool GfGameManager::isDisableAutoRun() { return GfMenuManager::isEnableQuestOpen(); }

bool GfGameManager::isHoodHomura(GF_OBJ_HANDLE *handle) {
  GfObjAcc objAcc(handle);
  if (!objAcc.isValid() || objAcc.getType() != OBJECT_TYPE_BLADE || objAcc.getBladeId() != BLADE_HOMURA) {
    return false;
  }

  if (!GfGameCond::isGameCond(GfDataBlade::getSDataBlade(objAcc.getBladeId())->condition)) {
    return false;
  }

  GfWeapon *weapon = GfGameParty::getHandleWeapon(PARTY_ID_LEADER, -1);
  if (weapon != nullptr) {
    for (u32 index = 0; index < WEAPON_HANDLE_NUM; index++) {
      if (weapon->getCurrentHandles()[index] != INVALID_HANDLE && (objAcc.isRebuild() || !GfGameObj::isValidGameObj(handle, true, nullptr))) {
        return true;
      }
    }
  }

  return objAcc.isRebuild() || !GfGameObj::isValidGameObj(handle, true, nullptr);
}

bool GfGameManager::isChangeNormalHomuraForce(u32 blade) { return blade == BLADE_HOMURA && GfPlayComHoodHomuraBattou::get() != nullptr; }

bool GfGameManager::isAssetNumberInvalid() { return GfAssetManager::getUsedAssetPackInfo() >= ASSET_PACK_MAX; }

void GfGameManager::updateParam(const fw::UpdateInfo &info) {
  if (GfGameScene::get() != nullptr) {
    GfGameScene::get()->updateParam(info);
  }
}

void GfGameManager::postUpdate(const fw::UpdateInfo &info) {
  GfSequentialPlay::postUpdate(info);
  GfGameObj::postUpdate(info);
  if (GfGameScene::get() != nullptr) {
    GfGameScene::get()->postUpdate(info);
  }

  GfGameEvent::postUpdate(info);
}

} // namespace gf
