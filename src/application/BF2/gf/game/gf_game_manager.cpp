#include "gf/game/gf_game_manager.h"

#include "battle/battle_manager.h"
#include "framework/framework.h"
#include "fw/fw_transform.h"
#include "fw/fw_update_info.h"
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
#include "gf/object/gf_init_param.h"
#include "gf/object/gf_obj.h"
#include "gf/object/gf_obj_acc.h"
#include "gf/object/gf_obj_handle.h"
#include "gf/object/gf_obj_manager.h"
#include "gf/object/gf_obj_property.h"
#include "gf/object/gf_obj_setup.h"
#include "gf/object/gf_obj_util.h"
#include "gf/request/gf_req_scom.h"
#include "gf/request/gf_scom.h"
#include "gf/sound/gf_sound.h"
#include "mm_math/mm_col4.h"
#include "mm_math/mm_math.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/fixed_array.h"
#include "mm_mtl/fixed_list.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/fixstr.h"

namespace gf {

constexpr u32 PARTY_ID_UNKNOWN_0 = 0;               // Inferred role: party id leader; original name unknown.
constexpr u32 SALVAGE_UNKNOWN_20 = 20;              // Inferred role: salvage state complete; original name unknown.
constexpr u32 SALVAGE_UNKNOWN_16 = 16;              // Inferred role: salvage count flag size; original name unknown.
constexpr int SALVAGE_UNKNOWN_1547 = 1547;          // Inferred role: salvage count flag; original name unknown.
constexpr u32 SALVAGE_UNKNOWN_65535 = 0xffff;       // Inferred role: salvage count max; original name unknown.
constexpr u16 CHILD_UNKNOWN_210 = 210;              // Inferred role: child quest force boss battle bgm; original name unknown.
constexpr u16 SCENARIO_FLAG_UNKNOWN_8024 = 8024;    // Inferred role: scenario flag force boss battle bgm; original name unknown.
constexpr u16 SCENARIO_FLAG_UNKNOWN_10033 = 10033;  // Inferred role: scenario flag game end; original name unknown.
constexpr u16 SCENARIO_FLAG_UNKNOWN_1000 = 1000;    // Inferred role: scenario flag per scenario; original name unknown.
constexpr u32 FADE_UNKNOWN_4294967295 = 0xffffffff; // Inferred role: fade all; original name unknown.
constexpr u32 FADE_UNKNOWN_3 = 3;                   // Inferred role: fade layer count; original name unknown.
constexpr f32 unknown023 = 0.9f;                    // Inferred role: fadeout alpha; original name unknown.
constexpr u32 PAUSE_UNKNOWN_89 = 0x59;              // Inferred role: pause bits gimmick; original name unknown.
constexpr u32 TIME_UNKNOWN_7 = 7;                   // Inferred role: time range dn night; original name unknown.
constexpr u32 PACK_UNKNOWN_512 = 512;               // Inferred role: asset pack max; original name unknown.
constexpr u32 METER_UNKNOWN_4 = 4;                  // Inferred role: depop meter count; original name unknown.

GfGameManager::GfGameManager(const GfSetupParam &param) : unknown18(false), unknown19(false) { initialize(param); }

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
  GfGameDepopMeterManager::create(METER_UNKNOWN_4);
  GfSmnEnemyManager::create();
  GfGamePlayerCamera::build(param);
  GfGameRide::build(param);
  GfGameMoverSwitcher::build(param);
  GfGameVoice::build(param);
  GfGameInsideBattleLock::build(param);
  GfQuestManager::addEvent(this);
  GfMenuManager::initOptionData(*GfDataManager::getDataOption());
  unknown18 = true;
}

// The empty statement makes the body non-trivial, which keeps the vtable pointer stores of the original.
GfGameManager::~GfGameManager() { ; }

void GfGameManager::build(const GfSetupParam &param) {
  // __LINE__ must be 124 as in the original file: its value changes the instruction order.
#line 124
  new (getAllocator(ALLOCATOR_UNKNOWN_1), __FILE__, __LINE__, 8) GfGameManager(param);
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

  if (GfGameState::getState() != GF_STATE_UNKNOWN_3) {
    GfSleep(1);
  }

  GfGameState::setState(GF_STATE_UNKNOWN_2, false);
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
  unknown18 = false;
}

bool GfGameManager::isGameObjEmpty() { return GfGameObj::isEmpty(); }

GF_STATE GfGameManager::getState() { return GfGameState::getState(); }

void GfGameManager::setState(GF_STATE state, bool isForce) { GfGameState::setState(state, isForce); }

void GfGameManager::clear() {
  GfGameManager *manager = get();
  SCOM_ACCESS_TARGET::create(unknown020);
  SCOM_TARGET_UI::create(unknown020);
  manager->unknown19 = false;
  GfGameCamera::clear();
  GfGameState::clear();
  GfGameEnv::clear();
  GfGameEvent::clear();
  if (GfGameScene::get() != nullptr) {
    GfGameScene::get()->clear();
  }

  GfGameSpeed::clear();
}

bool GfGameManager::isInitialized() { return get() != nullptr && get()->unknown18; }

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
  if (pauseBits & PAUSE_BIT_UNKNOWN_1) {
    GfGameSpeed::setGlobalSpeed(0.0f);
  }

  if (resumeBits & PAUSE_BIT_UNKNOWN_1) {
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
  if (activateType == ACTIVATE_TYPE_UNKNOWN_0 && oldActivateType != ACTIVATE_TYPE_UNKNOWN_0) {
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
  if (blade == BLADE_UNKNOWN_1050 && GfDataBlade::getCreator(BLADE_UNKNOWN_1050) == 0) {
    GfDataBlade::setCreator(BLADE_UNKNOWN_1050, GfDataBlade::getCreator(BLADE_UNKNOWN_1022));
  }

  GfFieldTime *fieldTime = GfFieldTime::get();
  if (fieldTime != nullptr) {
    SDataBlade &dataBlade = GfDataBlade::getSDataBlade(blade);
    if (dataBlade.unknown08 == 0) {
      dataBlade.unknown08 = reinterpret_cast<const u32 &>(fieldTime->getElapseTime());
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
  if (reload == RELOAD_BDAT_UNKNOWN_1) {
    GfGameObj::bdatReload();
  }
}

void GfGameManager::gevSalvageStateChange(u32 state) {
  if (state == SALVAGE_UNKNOWN_20) {
    u16 count = GfGameFlag::getLocal(SALVAGE_UNKNOWN_16, SALVAGE_UNKNOWN_1547);
    if (count != SALVAGE_UNKNOWN_65535) {
      count++;
    }

    GfGameFlag::setLocal(SALVAGE_UNKNOWN_16, SALVAGE_UNKNOWN_1547, count);
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

void GfGameManager::gevGameState(GF_STATE previousState, GF_STATE state) { GfGameEnv::gevGameState(previousState, state); }

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

void IQuestEvent::qevCompleteQuest(const QuestCompleteParam &) {}

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
  if (param.unknown04.unknown00 == CHILD_UNKNOWN_210 && GfDataUtil::getScenarioFlag() == SCENARIO_FLAG_UNKNOWN_8024) {
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
  if (objAcc.isValid() && (GfGameObj::isValidGameObj(leader, true, nullptr) || GfGameObj::isEnterGameObj(leader) || (fw::Framework::isLayerPause(objAcc.getLayer()) && GfObjUtil::isUpdate(leader)))) {
    return leader;
  }

  return unknown020;
}

GF_OBJ_HANDLE *GfGameManager::getPartyLeaderDriver() {
  GF_OBJ_HANDLE *driver = GfGameParty::getLeaderDriver();
  GfObjAcc objAcc(driver);
  if (GfGameObj::isValidGameObj(driver, true, nullptr) || GfGameObj::isEnterGameObj(driver) || (fw::Framework::isLayerPause(objAcc.getLayer()) && GfObjUtil::isUpdate(driver))) {
    return driver;
  }

  return unknown020;
}

GF_OBJ_HANDLE *GfGameManager::getControlMover() {
  GfGamePlayerFormation *formation = GfGamePlayerFormation::get();
  if (formation != nullptr && formation->unknown1a0[0].unknown08 != unknown020) {
    return formation->unknown1a0[0].unknown08;
  }

  return getPartyLeader();
}

GF_OBJ_HANDLE *GfGameManager::getControlRider() {
  GfObjAcc moverAcc(getControlMover());
  if (moverAcc.isValid()) {
    u32 partyId = GfGameParty::getPartyId(moverAcc.getHandle());
    if (partyId != PARTY_UNKNOWN_4294967295) {
      GF_OBJ_HANDLE *driver = GfGameParty::getHandleDriver(partyId);
      GF_OBJ_HANDLE *blade = GfGameParty::getHandleBlade(partyId, -1);
      GfObjAcc driverAcc(driver);
      GfObjAcc bladeAcc(blade);
      return GfGameRide::testRideOn() ? driverAcc.getHandle() : moverAcc.getHandle();
    }
  }

  return unknown020;
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
  return get() != nullptr && (GfGameState::test(GF_STATE_FLAG_UNKNOWN_1) || (isIncludeSequentialPlay && GfSequentialPlay::isInnerState(GF_STATE_UNKNOWN_20)));
}

bool GfGameManager::isEventWait() { return GfGameState::getState() == GF_STATE_UNKNOWN_7; }

bool GfGameManager::isPlayEvent() { return GfGameScene::get() != nullptr && GfGameScene::get()->isPlayEvent(); }

bool GfGameManager::isField() {
  if (get() == nullptr || GfGameState::getState() != GF_STATE_UNKNOWN_3) {
    return false;
  }

  if (isPlayerPause() || isBattle()) {
    return false;
  }

  return GfGameState::getStateReserve() == GF_STATE_UNKNOWN_3;
}

bool GfGameManager::isPlaySequenceClear() { return !GfSequentialPlay::isPlay(); }

bool GfGameManager::isControlFree() { return GfGameScene::get() != nullptr && GfGameScene::get()->isControlFree(); }

bool GfGameManager::isControlFree(u32 state) {
  if (!isControlFree()) {
    return false;
  }

  if (GfGameState::getStateReserve() == GF_STATE_UNKNOWN_3) {
    return true;
  }

  return GfGameState::getStateReserve() == state;
}

bool GfGameManager::isBladeChange() { return isInnerState(GF_STATE_UNKNOWN_24); }

bool GfGameManager::isDisableBattou() {
  if (GfPlayComResetBlade::isPlaying(PARTY_ID_UNKNOWN_0)) {
    return true;
  }

  GfObjAcc bladeAcc(GfGameParty::getHandleBlade(PARTY_ID_UNKNOWN_0, -1));
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
  if (moverAcc.getType() != OBJECT_TYPE_PC || moverAcc.getDriverId() != DRIVER_UNKNOWN_1 || GfDataDriver::getBlade(DRIVER_UNKNOWN_1, -1) != BLADE_HOMURA) {
    return false;
  }

  GfObjAcc bladeAcc(GfGameParty::getHandleBlade(PARTY_ID_UNKNOWN_0, -1));
  if (bladeAcc.getBladeId() != BLADE_HOMURA) {
    return false;
  }

  if (moverAcc.isBattle() || bladeAcc.isRebuild()) {
    return false;
  }

  if (GfGameScene::get() != nullptr && !GfGameScene::isPlayerWalkAndRun()) {
    return false;
  }

  if (isCheckCondition && GfPlayComResetBlade::isPlaying(PARTY_ID_UNKNOWN_0)) {
    return false;
  }

  GfObjAcc targetAcc(moverAcc.getTarget());
  if (targetAcc.getType() != OBJECT_TYPE_ENEMY) {
    return false;
  }

  if (isCheckCondition && !GfGameCond::isGameCond(GfDataBlade::getSDataBlade(bladeAcc.getBladeId()).unknown82a)) {
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

  return GfGameState::test(GF_STATE_FLAG_UNKNOWN_5);
}

bool GfGameManager::isFullScreenMenu() { return GfMenuManager::isOpenFullScreen(); }

bool GfGameManager::isPlayCommonMenu() { return GfMenuManager::isOpenCommonWindow() && GfPause::isPause(PAUSE_BIT_UNKNOWN_0); }

bool GfGameManager::isMapjumpOK() {
  if (GfGameState::getState() == GF_STATE_UNKNOWN_8) {
    return false;
  }

  if (GfGameState::getStateReserve() == GF_STATE_UNKNOWN_8) {
    return false;
  }

  if (GfGameState::getState() == GF_STATE_UNKNOWN_9) {
    return false;
  }

  return GfGameState::getStateReserve() != GF_STATE_UNKNOWN_9;
}

bool GfGameManager::isExecTutorial() { return GfMenuObjTutorial::isWaiting(); }

bool GfGameManager::isGmkTutorialMoverOK() { return GfGameScene::get() != nullptr && GfGameScene::get()->isPlayerStopFlag(PLSTOP_UNKNOWN_2); }

void GfGameManager::setGmkTutorialMoverOK(bool isOK) {
  if (GfGameScene::get() != nullptr) {
    GfGameScene::get()->setPlayerStopFlag(PLSTOP_UNKNOWN_2, isOK);
  }
}

bool GfGameManager::isGmkTutorialSequenceOK() {
  GfGameScene *scene = GfGameScene::get();
  if (scene == nullptr) {
    return false;
  }

  return scene->isPlayerStopFlag(PLSTOP_UNKNOWN_1) || scene->isPlayerStopFlag(PLSTOP_UNKNOWN_3) || scene->isPlayerStopFlag(PLSTOP_UNKNOWN_4);
}

void GfGameManager::setGmkTutorialSequenceOK(bool isOK) {
  if (GfGameScene::get() != nullptr) {
    GfGameScene::get()->setPlayerStopFlag(PLSTOP_UNKNOWN_1, isOK);
  }
}

bool GfGameManager::isValidCollisionVelocity() { return GfGameScene::get() != nullptr && GfGameScene::get()->unknown270; }

void GfGameManager::setValidCollisionVelocity(bool isValid) {
  if (GfGameScene::get() != nullptr) {
    GfGameScene::get()->unknown270 = isValid;
  }
}

bool GfGameManager::isLeaveGameForDebug() { return get() != nullptr && (get()->unknown19 || GfManager::isDestroyNow()); }

bool GfGameManager::isGameOver() { return GfDataUtil::getScenarioFlag() > SCENARIO_FLAG_UNKNOWN_10033; }

bool GfGameManager::isFieldLockMsgOK() { return isEnableFieldAccess() && isControlFree(); }

bool GfGameManager::isEnableFieldAccess() {
  if (GfSequentialPlay::isInnerState(GF_STATE_UNKNOWN_24) || GfSequentialPlay::isInnerState(GF_STATE_UNKNOWN_10)) {
    return false;
  }

  if (!isEnableOpenMainMenuSequence()) {
    return false;
  }

  GfGameScene *scene = GfGameScene::get();
  if (scene != nullptr) {
    DataParamAcc driverAcc(GfGameParty::getHandleDriver(PARTY_ID_UNKNOWN_0));
    if (driverAcc.isValid() && driverAcc.getValidDriverId() == DRIVER_UNKNOWN_2) {
      if (scene->isNeedFieldBladeChange(PARTY_ID_UNKNOWN_0)) {
        return false;
      }

      if (GfDataDriver::getBlade(driverAcc.getValidDriverId(), -1) == BLADE_BYAKKO && GfObjUtil::getParentHandle(driverAcc.unknown10) != GfGameParty::getHandleBlade(PARTY_ID_UNKNOWN_0, -1)) {
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

  return isControlFree(GF_STATE_UNKNOWN_6);
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

  if (isInnerState(GF_STATE_UNKNOWN_6)) {
    return false;
  }

  if (isInnerState(GF_STATE_UNKNOWN_11)) {
    return false;
  }

  if (isInnerState(GF_STATE_UNKNOWN_21)) {
    return false;
  }

  if (isInnerState(GF_STATE_UNKNOWN_14)) {
    return false;
  }

  if (isInnerState(GF_STATE_UNKNOWN_12)) {
    return false;
  }

  if (isInnerState(GF_STATE_UNKNOWN_13)) {
    return false;
  }

  if (isInnerState(GF_STATE_UNKNOWN_4)) {
    return false;
  }

  if (isInnerState(GF_STATE_UNKNOWN_19)) {
    return false;
  }

  if (isInnerState(GF_STATE_UNKNOWN_16)) {
    return false;
  }

  if (isInnerState(GF_STATE_UNKNOWN_17)) {
    return false;
  }

  if (isInnerState(GF_STATE_UNKNOWN_18)) {
    return false;
  }

  return !isInnerState(GF_STATE_UNKNOWN_20);
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
  if (fade == FADE_UNKNOWN_4294967295) {
    for (u32 layer = 0; layer < FADE_UNKNOWN_3; layer++) {
      if (GfMenuManager::isFading(layer)) {
        return true;
      }
    }

    return false;
  }

  return GfMenuManager::isFading(fade) || GfReqSmallCom::isExistCommand(SCOM_TYPE_FADE);
}

bool GfGameManager::isFadeout() {
  for (u32 layer = 0; layer < FADE_UNKNOWN_3; layer++) {
    mm::Col4 color;
    GfMenuManager::getFadeColor(layer, color);
    if (color.a >= unknown023) {
      return true;
    }
  }

  return false;
}

void GfGameManager::getFadeColor(u32 fade, mm::Col4 &color) { GfMenuManager::getFadeColor(fade, color); }

bool GfGameManager::isFadeClear() {
  if (isFadeout() || isFading(FADE_UNKNOWN_4294967295)) {
    return false;
  }

  for (u32 layer = 0; layer < FADE_UNKNOWN_3; layer++) {
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
  for (u32 layer = 0; layer < FADE_UNKNOWN_3; layer++) {
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
    manager->unknown19 = true;
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

bool GfGameManager::isInMetJIJI() { return GfGameCond::isGameCond(GfBdatRsc::get()->getDriverParamExtMountCond(DRIVER_UNKNOWN_1)); }

OwnerBonus *GfGameManager::getOwnerBonus() { return &GfGameScene::get()->getOwnerBonus(); }

bool GfGameManager::isPlayerFinishBattleState() {
  if (GfGameParty::isLeaderBlade()) {
    return true;
  }

  DataParamAcc leaderAcc(GfGameParty::getLeader());
  if (leaderAcc.getObjType() == OBJECT_TYPE_PC && leaderAcc.getValidDriverId() == DRIVER_UNKNOWN_2 && leaderAcc.getBlade(-1, false) == BLADE_BYAKKO) {
    return true;
  }

  return false;
}

f32 GfGameManager::getFieldSpeed(const fw::UpdateInfo &info) {
  f32 speed = GfGameSpeed::getLayerSpeed(0);
  f32 pause = GfLayerPause::isLayerPause(0) ? 0.0f : 1.0f;
  return info.unknown08 * (speed * pause);
}

const mm::Vec3 &GfGameManager::getControlMoverPosition() {
  GfObjAcc moverAcc(getControlMover());
  if (moverAcc.isValidTransform()) {
    return moverAcc.getWorldTransform().unknown00;
  }
  return mm::Vec3::zero;
}

mm::Vec3 GfGameManager::getControlMoverRotation() {
  GfObjAcc moverAcc(getControlMover());
  if (!moverAcc.isValidTransform()) {
    return mm::Vec3::zero;
  }
  mm::Vec3 rotation;
  mm::quatToEuler(moverAcc.getWorldTransform().unknown10, rotation);
  return rotation;
}

bool GfGameManager::isEnemyChangeBattleOK() {
  if (GfGameScene::get() != nullptr && GfGameScene::get()->isPlayerPauseForBattle()) {
    return false;
  }

  GfObj *mover = GfObjUtil::getObj(getControlMover());
  if (mover == nullptr) {
    return false;
  }

  GfObjProperty *property = GfObjUtil::getProperty(mover->unknownf8);
  if (property == nullptr || property->unknown18 == nullptr) {
    return false;
  }

  return property->unknown18->unknown00 != PROPERTY_MOVE_UNKNOWN_3;
}

u8 GfGameManager::isPlayEventOK() {
  GfObj *mover = GfObjUtil::getObj(getControlMover());
  if (mover == nullptr) {
    return false;
  }

  GfObjProperty *property = GfObjUtil::getProperty(mover->unknownf8);
  if (property == nullptr || property->unknown18 == nullptr) {
    return false;
  }

  switch (property->unknown18->unknown00) {
  case PROPERTY_MOVE_UNKNOWN_0:
  case PROPERTY_MOVE_UNKNOWN_2:
  case 5: // Inferred role: move type that allows an event; original name unknown.
    break;
  case PROPERTY_MOVE_UNKNOWN_1:
    return property->unknown18->unknown7d;
  default:
    return false;
  }

  if (GfGameScene::get() == nullptr || !GfGameScene::get()->isControlFree()) {
    return false;
  }
  if (GfGameState::getStateReserve() == GF_STATE_UNKNOWN_3) {
    return true;
  }
  return GfGameState::getStateReserve() == GF_STATE_UNKNOWN_20;
}

void GfGameManager::callbackBladeActivateForGimmick() {
  mm::mtl::FixedVector<u16, 422> blades;
  GfDataBlade::getListReserver(blades);
  for (const u16 *it = blades.begin(), *end = blades.end(); it != end; ++it) {
    if (GfDataBlade::getBladeActivateType(*it) == ACTIVATE_TYPE_UNKNOWN_1) {
      GfEvent::callBladeActivate(*it, ACTIVATE_TYPE_UNKNOWN_1, ACTIVATE_TYPE_UNKNOWN_1);
    }
  }
}

bool GfGameManager::isEnableOpenMainMenuSequence() {
  if (GfGameScene::get() == nullptr || GfGameScene::get()->unknown1c9) {
    return false;
  }

  if (GfGameEnv::isMapjump()) {
    return false;
  }

  if (isLeaveGameForDebug()) {
    return false;
  }

  if (GfSequentialPlay::isInnerPause(PAUSE_BIT_UNKNOWN_6)) {
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

  if (GfSequentialPlay::isInnerState(GF_STATE_UNKNOWN_11)) {
    return false;
  }

  if (GfGameScene::get() != nullptr && GfGameScene::get()->isNeedResetBladeForBattleEndForMenuOpen()) {
    return false;
  }

  return true;
}

bool GfGameManager::isStartGame() { return GfGameScene::get() == nullptr || GfGameScene::get()->unknown1c9; }

bool GfGameManager::isStopMainMenuOpenForGimmick() { return GfGameScene::get() != nullptr && GfGameScene::get()->unknown1d0; }

bool GfGameManager::isEnableHoodHomuraScenes() { return !isInnerState(GF_STATE_UNKNOWN_24) && !isInnerState(GF_STATE_UNKNOWN_10); }

bool GfGameManager::isEnableGimmickPhantomDamage() { return !GfSequentialPlay::isInnerPause(PAUSE_UNKNOWN_89); }

bool GfGameManager::isEnableGetFieldPrecious() { return isEnableOpenMainMenuSequence() && isEnableOpenMainMenu(); }

bool GfGameManager::isEnableCreateBattleLock() { return !GfSequentialPlay::isInnerPause(PAUSE_UNKNOWN_89); }

bool GfGameManager::isPartyMover(GF_OBJ_HANDLE *handle) {
  int partyId = GfObjUtil::getPartyID(handle);
  return partyId != -1 && GfGameParty::getHandleMover(partyId) == handle;
}

bool GfGameManager::isBusyBladeCreateEvent() {
  if (!GfPause::isPause(PAUSE_BIT_UNKNOWN_0)) {
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

    if (!isEventCharacter(setup->unknown1c)) {
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
    if (GfDataEnemy::isBoss(dataParamAcc.isValid() ? dataParamAcc.getBdatId() : 0) && dataParamAcc.getHp() != 0 && dataParamAcc.getHp() < dataParamAcc.getHpMax(false)) {
      return true;
    }
  }

  return false;
}

bool GfGameManager::isNeedResetBlade() { return GfSelectBlade::isNeedFieldBladeChange(0) || GfSelectBlade::isNeedFieldBladeChange(1) || GfSelectBlade::isNeedFieldBladeChange(2); }

bool GfGameManager::isStopEnemySearch() { return GfGameEnv::isStopEnemySearch(); }

bool GfGameManager::isPlayerDeadSequence() { return GfPlayComPlayerDead::isDead(); }

bool GfGameManager::isForceBossBattleBgm() { return GfGameScene::get() != nullptr && GfGameScene::get()->isForceBossBattleBgm(); }

bool GfGameManager::isForceEventBgm() { return GfGameScene::get() != nullptr && GfGameScene::get()->isForceEventBgm(); }

bool GfGameManager::isNight() { return GfFieldTime::get() != nullptr && GfFieldTime::get()->getTimeRangeDN() == TIME_UNKNOWN_7; }

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
  return fieldSound != nullptr ? fieldSound->unknownc4.c_str() : nullptr;
}

u32 GfGameManager::getScenarioId() {
  if (!GfManager::isExecModeScenarioGame()) {
    return 0;
  }

  u16 scenarioFlag = GfDataUtil::getScenarioFlag();
  return scenarioFlag == 0 ? 1 : scenarioFlag / SCENARIO_FLAG_UNKNOWN_1000;
}

bool GfGameManager::isRexAwakening() { return GfGameUtil::isCondDriverModel(DRIVER_UNKNOWN_1); }

void GfGameManager::setStartGame() {
  if (GfGameScene::get() != nullptr) {
    GfGameScene::get()->unknown1c9 = true;
  }
}

bool GfGameManager::isEnableRoomForHikariLv4() { return GfGameScene::get() != nullptr && GfGameScene::get()->unknown1ca; }

void GfGameManager::setHomuriWeaponExtraMesh(bool isVisible, f32 alpha) {
  if (GfGameScene::get() != nullptr) {
    GfGameScene::get()->setHomuriWeaponExtraMesh(isVisible, alpha);
  }
}

bool GfGameManager::isOpenPreciousMenu() { return GfPlayComMenuPrecious::s_activate > 0; }

bool GfGameManager::isStopEnemyAttack() { return GfGameScene::get() != nullptr && GfGameScene::get()->unknown620 > 0; }

bool GfGameManager::isPlayEnemyVoice() { return GfGameVoice::get() != nullptr && GfGameVoice::get()->isPlayEnemyVoice(); }

bool GfGameManager::isPlayVoice(GF_OBJ_HANDLE *handle) { return GfGameVoice::get() != nullptr && GfGameVoice::get()->isPlayVoice(handle); }

bool GfGameManager::isPartyMemberPlayVoice() {
  GfGameVoice *voice = GfGameVoice::get();
  if (voice == nullptr) {
    return false;
  }

  for (u32 partyId = 0; partyId < PARTY_UNKNOWN_3; partyId++) {
    if (voice->isPlayVoice(GfGameParty::getHandleDriver(partyId)) || voice->isPlayVoice(GfGameParty::getHandleBlade(partyId, -1))) {
      return true;
    }
  }

  return false;
}

void GfGameManager::setStopMainMenuOpenForGimmick(bool isStop) {
  if (GfGameScene::get() != nullptr) {
    GfGameScene::get()->unknown1d0 = isStop;
  }
}

bool GfGameManager::isDisableJumpForRide() { return GfGameScene::get() != nullptr && GfGameScene::get()->isDisableJumpForRide(); }

bool GfGameManager::isDisableAutoRun() { return GfMenuManager::isEnableQuestOpen(); }

bool GfGameManager::isHoodHomura(GF_OBJ_HANDLE *handle) {
  GfObjAcc objAcc(handle);
  if (!objAcc.isValid() || objAcc.getType() != OBJECT_TYPE_BLADE || objAcc.getBladeId() != BLADE_HOMURA) {
    return false;
  }

  if (!GfGameCond::isGameCond(GfDataBlade::getSDataBlade(objAcc.getBladeId()).unknown82a)) {
    return false;
  }

  GfWeapon *weapon = GfGameParty::getHandleWeapon(PARTY_ID_UNKNOWN_0, -1);
  if (weapon != nullptr) {
    for (u32 index = 0; index < HANDLE_UNKNOWN_10; index++) {
      if (weapon->getCurrentHandles()[index] != unknown020 && (objAcc.isRebuild() || !GfGameObj::isValidGameObj(handle, true, nullptr))) {
        return true;
      }
    }
  }

  return objAcc.isRebuild() || !GfGameObj::isValidGameObj(handle, true, nullptr);
}

bool GfGameManager::isChangeNormalHomuraForce(u32 blade) { return blade == BLADE_HOMURA && GfPlayComHoodHomuraBattou::get() != nullptr; }

bool GfGameManager::isAssetNumberInvalid() { return GfAssetManager::getUsedAssetPackInfo() >= PACK_UNKNOWN_512; }

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
