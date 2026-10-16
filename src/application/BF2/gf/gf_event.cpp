#include "gf/event/gf_event.h"

#include "gf/gf_allocator.h"

namespace gf {

GfEvent::GfEvent(const GfSetupParam &param) { initialize(param); }

void GfEvent::initialize(const GfSetupParam &) { initialized = true; }

GfEvent::~GfEvent() {}

void GfEvent::build(const GfSetupParam &param) {
  // __LINE__ must be 40 as in the original file: its value changes the instruction order.
#line 40
  new (getAllocator(ALLOCATOR_SYSTEM), __FILE__, __LINE__, 8) GfEvent(param);
}

void GfEvent::destroy() {
  GfEvent *gfEvent = get();
  gfEvent->finalize();
  delete gfEvent;
}

void GfEvent::finalize() { initialized = false; }

bool GfEvent::isInitialized() { return get() != nullptr && get()->initialized; }

void GfEvent::callChangeScenarioFlag(u32 scenarioFlag, u32 oldScenarioFlag) {
  GfEvent *gfEvent = get();
  for (size_t i = 0; i < gfEvent->callbacks.size(); i++) {
    gfEvent->callbacks[i]->gevChangeScenarioFlag(scenarioFlag, oldScenarioFlag);
  }
}

void GfEvent::callSalvageStateChange(u32 state) {
  GfEvent *gfEvent = get();
  for (size_t i = 0; i < gfEvent->callbacks.size(); i++) {
    gfEvent->callbacks[i]->gevSalvageStateChange(state);
  }
}

void GfEvent::callBattleStart() {
  GfEvent *gfEvent = get();
  for (size_t i = 0; i < gfEvent->callbacks.size(); i++) {
    gfEvent->callbacks[i]->gevBattleStart();
  }
}

void GfEvent::callBattleEnd() {
  GfEvent *gfEvent = get();
  for (size_t i = 0; i < gfEvent->callbacks.size(); i++) {
    gfEvent->callbacks[i]->gevBattleEnd();
  }
}

void GfEvent::callGameMapModel(GF_OBJ_HANDLE *handle, bool isEnter) {
  GfEvent *gfEvent = get();
  for (size_t i = 0; i < gfEvent->callbacks.size(); i++) {
    gfEvent->callbacks[i]->gevGameMapModel(handle, isEnter);
  }
}

void GfEvent::callTargetAccess(GF_OBJ_HANDLE *target) {
  GfEvent *gfEvent = get();
  for (size_t i = 0; i < gfEvent->callbacks.size(); i++) {
    gfEvent->callbacks[i]->gevAccessTarget(target);
  }
}

void GfEvent::callTargetChange(GF_OBJ_HANDLE *target) {
  GfEvent *gfEvent = get();
  for (size_t i = 0; i < gfEvent->callbacks.size(); i++) {
    gfEvent->callbacks[i]->gevChangeTarget(target);
  }
}

void GfEvent::callCameraControl(int control) {
  GfEvent *gfEvent = get();
  for (size_t i = 0; i < gfEvent->callbacks.size(); i++) {
    gfEvent->callbacks[i]->gevCameraControl(control);
  }
}

void GfEvent::callEventPlay(GEV event, u32 eventId) {
  GfEvent *gfEvent = get();
  for (size_t i = 0; i < gfEvent->callbacks.size(); i++) {
    gfEvent->callbacks[i]->gevPlayEvent(event, eventId);
  }
}

void GfEvent::callBladeChange(GF_OBJ_HANDLE *handle, int oldSlot, int newSlot) {
  GfEvent *gfEvent = get();
  for (size_t i = 0; i < gfEvent->callbacks.size(); i++) {
    gfEvent->callbacks[i]->gevChangeBlade(handle, oldSlot, newSlot);
  }
}

void GfEvent::callPartyChange() {
  GfEvent *gfEvent = get();
  for (size_t i = 0; i < gfEvent->callbacks.size(); i++) {
    gfEvent->callbacks[i]->gevChangeParty();
  }
}

void GfEvent::callGameObjEnter(GF_OBJ_HANDLE *handle) {
  GfEvent *gfEvent = get();
  for (size_t i = 0; i < gfEvent->callbacks.size(); i++) {
    gfEvent->callbacks[i]->gevGameObjEnter(handle);
  }
}

void GfEvent::callGameObjLeave(GF_OBJ_HANDLE *handle) {
  GfEvent *gfEvent = get();
  for (size_t i = 0; i < gfEvent->callbacks.size(); i++) {
    gfEvent->callbacks[i]->gevGameObjLeave(handle);
  }
}

void GfEvent::callAchievmentRelease(const GfAchievementRelease &release) {
  GfEvent *gfEvent = get();
  for (size_t i = 0; i < gfEvent->callbacks.size(); i++) {
    gfEvent->callbacks[i]->gevReleaseAchievment(release);
  }
}

void GfEvent::callDriverActivate(u32 driver, ActivateType activateType, ActivateType oldActivateType) {
  GfEvent *gfEvent = get();
  for (size_t i = 0; i < gfEvent->callbacks.size(); i++) {
    gfEvent->callbacks[i]->gevDriverActivate(driver, activateType, oldActivateType);
  }
}

void GfEvent::callBladeActivate(u32 blade, ActivateType activateType, ActivateType oldActivateType) {
  GfEvent *gfEvent = get();
  for (size_t i = 0; i < gfEvent->callbacks.size(); i++) {
    gfEvent->callbacks[i]->gevBladeActivate(blade, activateType, oldActivateType);
  }
}

void GfEvent::callBladeUnselect(u32 blade, bool unselect) {
  GfEvent *gfEvent = get();
  for (size_t i = 0; i < gfEvent->callbacks.size(); i++) {
    gfEvent->callbacks[i]->gevBladeUnselect(blade, unselect);
  }
}

void GfEvent::callBladeEnable(u32 blade) {
  GfEvent *gfEvent = get();
  for (size_t i = 0; i < gfEvent->callbacks.size(); i++) {
    gfEvent->callbacks[i]->gevBladeEnable(blade);
  }
}

void GfEvent::callDriverLevel(u32 driver, u32 level, u32 oldLevel) {
  GfEvent *gfEvent = get();
  for (size_t i = 0; i < gfEvent->callbacks.size(); i++) {
    gfEvent->callbacks[i]->gevDriverLevel(driver, level, oldLevel);
  }
}

void GfEvent::callExecState(EXEC_STATE state) {
  GfEvent *gfEvent = get();
  for (size_t i = 0; i < gfEvent->callbacks.size(); i++) {
    gfEvent->callbacks[i]->gevExecState(state);
  }
}

void GfEvent::callMercenariesTeam(u32 team) {
  GfEvent *gfEvent = get();
  for (size_t i = 0; i < gfEvent->callbacks.size(); i++) {
    gfEvent->callbacks[i]->gevMercenariesTeam(team);
  }
}

void GfEvent::callMercenariesMissionFlag(u32 mission, u32 flag, u32 value) {
  GfEvent *gfEvent = get();
  for (size_t i = 0; i < gfEvent->callbacks.size(); i++) {
    gfEvent->callbacks[i]->gevMercenariesMissionFlag(mission, flag, value);
  }
}

void GfEvent::callItemAdd(u32 item, int count) {
  GfEvent *gfEvent = get();
  for (size_t i = 0; i < gfEvent->callbacks.size(); i++) {
    gfEvent->callbacks[i]->gevItemAdd(item, count);
  }
}

void GfEvent::callPartyMemberOK(bool isOK) {
  GfEvent *gfEvent = get();
  for (size_t i = 0; i < gfEvent->callbacks.size(); i++) {
    gfEvent->callbacks[i]->gevPartyMemberOK(isOK);
  }
}

void GfEvent::callPartyIDMemberOK(bool isOK, u32 partyId) {
  GfEvent *gfEvent = get();
  for (size_t i = 0; i < gfEvent->callbacks.size(); i++) {
    gfEvent->callbacks[i]->gevPartyIDMemberOK(isOK, partyId);
  }
}

void GfEvent::callChangeLeader(GF_OBJ_HANDLE *leader) {
  GfEvent *gfEvent = get();
  for (size_t i = 0; i < gfEvent->callbacks.size(); i++) {
    gfEvent->callbacks[i]->gevChangeLeader(leader);
  }
}

void GfEvent::callPartyDriver(GF_OBJ_HANDLE *handle, u32 partyId, bool isEnter) {
  GfEvent *gfEvent = get();
  for (size_t i = 0; i < gfEvent->callbacks.size(); i++) {
    gfEvent->callbacks[i]->gevPartyDriver(handle, partyId, isEnter);
  }
}

void GfEvent::callGameState(GF_STATE previousState, GF_STATE state) {
  GfEvent *gfEvent = get();
  for (size_t i = 0; i < gfEvent->callbacks.size(); i++) {
    gfEvent->callbacks[i]->gevGameState(previousState, state);
  }
}

void GfEvent::callControllFree(bool isFree) {
  GfEvent *gfEvent = get();
  for (size_t i = 0; i < gfEvent->callbacks.size(); i++) {
    gfEvent->callbacks[i]->gevControllFree(isFree);
  }
}

void GfEvent::callPartyReturnFieldState(u32 state) {
  GfEvent *gfEvent = get();
  for (size_t i = 0; i < gfEvent->callbacks.size(); i++) {
    gfEvent->callbacks[i]->gevPartyReturnFieldState(state);
  }
}

void GfEvent::callLoadGameTime(f32 time) {
  GfEvent *gfEvent = get();
  for (size_t i = 0; i < gfEvent->callbacks.size(); i++) {
    gfEvent->callbacks[i]->gevLoadGameTime(time);
  }
}

void GfEvent::callPlayerControl(GEV event) {
  GfEvent *gfEvent = get();
  for (size_t i = 0; i < gfEvent->callbacks.size(); i++) {
    gfEvent->callbacks[i]->gevPlayerControl(event);
  }
}

void GfEvent::callPartyMover(GF_OBJ_HANDLE *handle, bool isMover) {
  GfEvent *gfEvent = get();
  for (size_t i = 0; i < gfEvent->callbacks.size(); i++) {
    gfEvent->callbacks[i]->gevPartyMover(handle, isMover);
  }
}

void GfEvent::callExecBuy(u32 item, u32 count, u32 shop) {
  GfEvent *gfEvent = get();
  for (size_t i = 0; i < gfEvent->callbacks.size(); i++) {
    gfEvent->callbacks[i]->gevExecBuy(item, count, shop);
  }
}

void GfEvent::callGetArts(u32 driver, u32 arts, bool isNew) {
  GfEvent *gfEvent = get();
  for (size_t i = 0; i < gfEvent->callbacks.size(); i++) {
    gfEvent->callbacks[i]->gevGetArts(driver, arts, isNew);
  }
}

void GfEvent::callHikariCurrent(bool hikariCurrent) {
  GfEvent *gfEvent = get();
  for (size_t i = 0; i < gfEvent->callbacks.size(); i++) {
    gfEvent->callbacks[i]->gevSelectHikari(hikariCurrent);
  }
}

void GfEvent::callSwapFormation(u32 playerId, u32 otherPlayerId) {
  GfEvent *gfEvent = get();
  for (size_t i = 0; i < gfEvent->callbacks.size(); i++) {
    gfEvent->callbacks[i]->gevSwapFormation(playerId, otherPlayerId);
  }
}

void GfEvent::callDebugBladeAttribute(u32 blade, u8 attribute) {
  GfEvent *gfEvent = get();
  for (size_t i = 0; i < gfEvent->callbacks.size(); i++) {
    gfEvent->callbacks[i]->gevDebugBladeAttribute(blade, attribute);
  }
}

void GfEvent::callDebugWeaponTypeActivate(u32 weaponType) {
  GfEvent *gfEvent = get();
  for (size_t i = 0; i < gfEvent->callbacks.size(); i++) {
    gfEvent->callbacks[i]->gevDebugWeaponTypeActivate(weaponType);
  }
}

void GfEvent::callDebugChangeTime(u32 time, u32 oldTime) {
  GfEvent *gfEvent = get();
  for (size_t i = 0; i < gfEvent->callbacks.size(); i++) {
    gfEvent->callbacks[i]->gevDebugChangeTime(time, oldTime);
  }
}

void GfEvent::callChangeTimeRange(u32 timeRange) {
  GfEvent *gfEvent = get();
  for (size_t i = 0; i < gfEvent->callbacks.size(); i++) {
    gfEvent->callbacks[i]->gevChangeTimeRange(timeRange);
  }
}

void GfEvent::callDebugItem(u32 item, bool isAdd) {
  GfEvent *gfEvent = get();
  for (size_t i = 0; i < gfEvent->callbacks.size(); i++) {
    gfEvent->callbacks[i]->gevDebugItem(item, isAdd);
  }
}

void GfEvent::callDebugChangeFlag(u32 type, u32 flag, u32 value, u32 oldValue) {
  GfEvent *gfEvent = get();
  for (size_t i = 0; i < gfEvent->callbacks.size(); i++) {
    gfEvent->callbacks[i]->gevDebugChangeFlag(type, flag, value, oldValue);
  }
}

void GfEvent::callChangeWeather(u32 weather, u32 oldWeather) {
  GfEvent *gfEvent = get();
  for (size_t i = 0; i < gfEvent->callbacks.size(); i++) {
    gfEvent->callbacks[i]->gevChangeWeather(weather, oldWeather);
  }
}

void GfEvent::callDebugChangeLevel(u32 type, u32 id, u32 level, u32 oldLevel) {
  GfEvent *gfEvent = get();
  for (size_t i = 0; i < gfEvent->callbacks.size(); i++) {
    gfEvent->callbacks[i]->gevDebugChangeLevel(type, id, level, oldLevel);
  }
}

void GfEvent::callDebugChangeIdea(u32 type, u32 id, u32 idea, u32 value) {
  GfEvent *gfEvent = get();
  for (size_t i = 0; i < gfEvent->callbacks.size(); i++) {
    gfEvent->callbacks[i]->gevDebugChangeIdea(type, id, idea, value);
  }
}

void GfEvent::callDebugDestroyAsset(GF_ASSET_HANDLE *asset) {
  GfEvent *gfEvent = get();
  for (size_t i = 0; i < gfEvent->callbacks.size(); i++) {
    gfEvent->callbacks[i]->gevDebugDestroyAsset(asset);
  }
}

void GfEvent::callDebugMapModel(GF_OBJ_HANDLE *handle, bool isEnter) {
  GfEvent *gfEvent = get();
  for (size_t i = 0; i < gfEvent->callbacks.size(); i++) {
    gfEvent->callbacks[i]->gevDebugMapModel(handle, isEnter);
  }
}

} // namespace gf
