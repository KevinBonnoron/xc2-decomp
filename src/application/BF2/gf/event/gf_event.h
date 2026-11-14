#pragma once
#include <stddef.h>

#include "gf/data/gf_data_driver.h"
#include "mm_mtl/fixed_queue.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace gf {

enum RELOAD_BDAT {
  RELOAD_BDAT_UNKNOWN_0 = 0, // Inferred role: sent before the bdat files are reloaded; original name unknown.
  RELOAD_BDAT_UNKNOWN_1 = 1, // Inferred role: reload bdat all; original name unknown.
};

enum GEV {
  GEV_UNKNOWN_1 = 1,   // Inferred role: gev mapjump start; original name unknown.
  GEV_UNKNOWN_2 = 2,   // Inferred role: gev mapjump destroy field; original name unknown.
  GEV_UNKNOWN_3 = 3,   // Inferred role: gev mapjump dispose field; original name unknown.
  GEV_UNKNOWN_4 = 4,   // Inferred role: gev mapjump change map; original name unknown.
  GEV_UNKNOWN_5 = 5,   // Inferred role: gev mapjump create field; original name unknown.
  GEV_UNKNOWN_6 = 6,   // Inferred role: gev mapjump fadein; original name unknown.
  GEV_UNKNOWN_7 = 7,   // Inferred role: gev mapjump end; original name unknown.
  GEV_UNKNOWN_8 = 8,   // Inferred role: gev event end wait; original name unknown.
  GEV_UNKNOWN_9 = 9,   // Inferred role: gev event end; original name unknown.
  GEV_UNKNOWN_10 = 10, // Inferred role: gev event play end; original name unknown.
  GEV_UNKNOWN_11 = 11, // Inferred role: gev event sequence start; original name unknown.
  GEV_UNKNOWN_12 = 12, // Inferred role: gev event sequence end; original name unknown.
  GEV_UNKNOWN_13 = 13, // Inferred role: gev event start frame; original name unknown.
  GEV_UNKNOWN_14 = 14, // Inferred role: gev player control free; original name unknown.
  GEV_UNKNOWN_15 = 15, // Inferred role: gev player control lock; original name unknown.
};

enum {
  DEBUG_UNKNOWN_4 = 4, // Inferred role: debug change idea trust; original name unknown.
};

enum GF_STATE {
  GF_STATE_UNKNOWN_0 = 0,   // Inferred role: gf state none; original name unknown.
  GF_STATE_UNKNOWN_1 = 1,   // Inferred role: gf state initialize; original name unknown.
  GF_STATE_UNKNOWN_2 = 2,   // Inferred role: gf state destroy; original name unknown.
  GF_STATE_UNKNOWN_3 = 3,   // Inferred role: gf state control; original name unknown.
  GF_STATE_UNKNOWN_4 = 4,   // Inferred role: gf state talk; original name unknown.
  GF_STATE_UNKNOWN_6 = 6,   // Inferred role: gf state menu; original name unknown.
  GF_STATE_UNKNOWN_7 = 7,   // Inferred role: gf state wait event; original name unknown.
  GF_STATE_UNKNOWN_8 = 8,   // Inferred role: gf state mapjump; original name unknown.
  GF_STATE_UNKNOWN_9 = 9,   // Inferred role: gf state mapjump skip travel; original name unknown.
  GF_STATE_UNKNOWN_10 = 10, // Inferred role: gf state player dead; original name unknown.
  GF_STATE_UNKNOWN_11 = 11, // Inferred role: gf state salvage; original name unknown.
  GF_STATE_UNKNOWN_12 = 12, // Inferred role: gf state collect; original name unknown.
  GF_STATE_UNKNOWN_13 = 13, // Inferred role: gf state field tbox; original name unknown.
  GF_STATE_UNKNOWN_14 = 14, // Inferred role: gf state map gimmick; original name unknown.
  GF_STATE_UNKNOWN_15 = 15, // Inferred role: gf state grave; original name unknown.
  GF_STATE_UNKNOWN_16 = 16, // Inferred role: gf state jump; original name unknown.
  GF_STATE_UNKNOWN_17 = 17, // Inferred role: gf state warp; original name unknown.
  GF_STATE_UNKNOWN_18 = 18, // Inferred role: gf state gmk tutorial; original name unknown.
  GF_STATE_UNKNOWN_19 = 19, // Inferred role: gf state gmk camera; original name unknown.
  GF_STATE_UNKNOWN_20 = 20, // Inferred role: gf state event; original name unknown.
  GF_STATE_UNKNOWN_21 = 21, // Inferred role: gf state gimmick task; original name unknown.
  GF_STATE_UNKNOWN_22 = 22, // Inferred role: gf state chain attack; original name unknown.
  GF_STATE_UNKNOWN_23 = 23, // Inferred role: gf state arts movie; original name unknown.
  GF_STATE_UNKNOWN_24 = 24, // Inferred role: gf state reset blade; original name unknown.
  GF_STATE_UNKNOWN_25 = 25, // Inferred role: gf state max; original name unknown.
};

enum EXEC_STATE {
  EXEC_STATE_UNKNOWN_0, // Inferred role: exec state debug; original name unknown.
  EXEC_STATE_UNKNOWN_1, // Inferred role: exec state scenario game; original name unknown.
  EXEC_STATE_UNKNOWN_2, // Inferred role: exec state advertize; original name unknown.
  EXEC_STATE_UNKNOWN_3, // Inferred role: exec state theater; original name unknown.
  EXEC_STATE_UNKNOWN_4, // Inferred role: exec state tool; original name unknown.
};

struct GF_ASSET_HANDLE;
struct GfSetupParam;
struct GF_OBJ_HANDLE;

enum {
  MAPJUMP_UNKNOWN_1 = 1, // Inferred role: mapjump type save data; original name unknown.
};

struct MapjumpCallbackInfo {
  u32 unknown00 = 0;      // Inferred role: map jump id; original member name unknown.
  u32 unknown04 = 0;      // Inferred role: map; original member name unknown.
  u32 unknown08 = 0;      // Inferred role: prev map; original member name unknown.
  bool unknown0c = false; // Inferred role: with save data; original member name unknown.
  u32 unknown10 = 0;      // Inferred role: jump type; original member name unknown.
};

static_assert(sizeof(MapjumpCallbackInfo) == 0x14, "");

struct GfAchievementRelease {
  u16 unknown00; // Inferred role: blade; original member name unknown.
  u16 unknown02; // Inferred role: level; original member name unknown.
  u32 unknown04; // Inferred role: achievement type; original member name unknown.
};

static_assert(offsetof(GfAchievementRelease, unknown02) == 0x02, "");
static_assert(offsetof(GfAchievementRelease, unknown04) == 0x04, "");
static_assert(sizeof(GfAchievementRelease) == 0x08, "");

class IGfEvent {
public:
  virtual ~IGfEvent() {}
  virtual void gevPartyMover(GF_OBJ_HANDLE *, bool) {}
  virtual void gevExecBuy(u32, u32, u32) {}
  virtual void gevGetArts(u32, u32, bool) {}
  virtual void gevSelectHikari(bool) {}
  virtual void gevPlayerControl(GEV) {}
  virtual void gevLoadGameTime(f32) {}
  virtual void gevPartyReturnFieldState(u32) {}
  virtual void gevControllFree(bool) {}
  virtual void gevGameState(GF_STATE, GF_STATE) {}
  virtual void gevPartyDriver(GF_OBJ_HANDLE *, u32, bool) {}
  virtual void gevChangeLeader(GF_OBJ_HANDLE *) {}
  virtual void gevSwapFormation(u32, u32) {}
  virtual void gevPartyIDMemberOK(bool, u32) {}
  virtual void gevPartyMemberOK(bool) {}
  virtual void gevItemAdd(u32, int) {}
  virtual void gevMercenariesMissionFlag(u32, u32, u32) {}
  virtual void gevMercenariesTeam(u32) {}
  virtual void gevDriverLevel(u32, u32, u32) {}
  virtual void gevDriverActivate(u32, ActivateType, ActivateType) {}
  virtual void gevBladeActivate(u32, ActivateType, ActivateType) {}
  virtual void gevBladeUnselect(u32, bool) {}
  virtual void gevBladeEnable(u32) {}
  virtual void gevReleaseAchievment(const GfAchievementRelease &) {}
  virtual void gevGameObjEnter(GF_OBJ_HANDLE *) {}
  virtual void gevGameObjLeave(GF_OBJ_HANDLE *) {}
  virtual void gevChangeParty() {}
  virtual void gevChangeBlade(GF_OBJ_HANDLE *, int, int) {}
  virtual void gevPlayEvent(GEV, u32) {}
  virtual void gevPause(u32, u32) {}
  virtual void gevLayerPause(u32, bool) {}
  virtual void gevCameraControl(u32) {}
  virtual void gevChangeTarget(GF_OBJ_HANDLE *) {}
  virtual void gevAccessTarget(GF_OBJ_HANDLE *) {}
  virtual void gevMapjump(GEV, const MapjumpCallbackInfo &) {}
  virtual void gevBattleStart() {}
  virtual void gevBattleEnd() {}
  virtual void gevChangeScenarioFlag(u32, u32) {}
  virtual void gevSalvageStateChange(u32) {}
  virtual void gevGameMapModel(GF_OBJ_HANDLE *, bool) {}
  virtual void gevChangeWeather(u32, u32) {}
  virtual void gevChangeTimeRange(u32) {}
  virtual void gevExecState(EXEC_STATE) {}
  virtual void gevReloadBdat(RELOAD_BDAT reload, u32 value) {}
  virtual void gevDebugBladeAttribute(u32, u8) {}
  virtual void gevDebugWeaponTypeActivate(u32) {}
  virtual void gevDebugChangeTime(u32, u32) {}
  virtual void gevDebugItem(u32, bool) {}
  virtual void gevDebugChangeFlag(u32, u32, u32, u32) {}
  virtual void gevDebugChangeIdea(u32, u32, u32, u32) {}
  virtual void gevDebugChangeLevel(u32, u32, u32, u32) {}
  virtual void gevDebugDestroyAsset(GF_ASSET_HANDLE *) {}
  virtual void gevDebugReloadObj(GF_OBJ_HANDLE *) {}
  virtual void gevDebugMapModel(GF_OBJ_HANDLE *, bool) {}
};

class GfEvent : public mm::mtl::PtrSingleton<GfEvent> {
public:
  static const u32 CALLBACK_UNKNOWN_32 = 32; // Inferred role: callback max; original name unknown.

  GfEvent(const GfSetupParam &param);
  void initialize(const GfSetupParam &param);
  ~GfEvent();
  static void build(const GfSetupParam &param);
  static void destroy();
  void finalize();
  static bool isInitialized();
  static void addEventCallback(IGfEvent *event);
  static void removeEventCallback(IGfEvent *event);
  static void callChangeScenarioFlag(u32 scenarioFlag, u32 oldScenarioFlag);
  static void callSalvageStateChange(u32 state);
  static void callBattleStart();
  static void callBattleEnd();
  static void callGameMapModel(GF_OBJ_HANDLE *handle, bool isEnter);
  static void callTargetAccess(GF_OBJ_HANDLE *target);
  static void callTargetChange(GF_OBJ_HANDLE *target);
  static void callCameraControl(int control);
  static void callEventPlay(GEV event, u32 eventId);
  static void callBladeChange(GF_OBJ_HANDLE *handle, int oldSlot, int newSlot);
  static void callPartyChange();
  static void callGameObjEnter(GF_OBJ_HANDLE *handle);
  static void callGameObjLeave(GF_OBJ_HANDLE *handle);
  static void callAchievmentRelease(const GfAchievementRelease &release);
  static void callDriverActivate(u32 driver, ActivateType activateType, ActivateType oldActivateType);
  static void callBladeActivate(u32 blade, ActivateType activateType, ActivateType oldActivateType);
  static void callBladeUnselect(u32 blade, bool unselect);
  static void callBladeEnable(u32 blade);
  static void callDriverLevel(u32 driver, u32 level, u32 oldLevel);
  static void callExecState(EXEC_STATE state);
  static void callMercenariesTeam(u32 team);
  static void callMercenariesMissionFlag(u32 mission, u32 flag, u32 value);
  static void callItemAdd(u32 item, int count);
  static void callPartyMemberOK(bool isOK);
  static void callPartyIDMemberOK(bool isOK, u32 partyId);
  static void callChangeLeader(GF_OBJ_HANDLE *leader);
  static void callPartyDriver(GF_OBJ_HANDLE *handle, u32 partyId, bool isEnter);
  static void callGameState(GF_STATE previousState, GF_STATE state);
  static void callControllFree(bool isFree);
  static void callPartyReturnFieldState(u32 state);
  static void callLoadGameTime(f32 time);
  static void callPlayerControl(GEV event);
  static void callPartyMover(GF_OBJ_HANDLE *handle, bool isMover);
  static void callExecBuy(u32 item, u32 count, u32 shop);
  static void callGetArts(u32 driver, u32 arts, bool isNew);
  static void callHikariCurrent(bool hikariCurrent);
  static void callSwapFormation(u32 playerId, u32 otherPlayerId);
  static void callDebugBladeAttribute(u32 blade, u8 attribute);
  static void callDebugWeaponTypeActivate(u32 weaponType);
  static void callDebugChangeTime(u32 time, u32 oldTime);
  static void callChangeTimeRange(u32 timeRange);
  static void callDebugItem(u32 item, bool isAdd);
  static void callDebugChangeFlag(u32 type, u32 flag, u32 value, u32 oldValue);
  static void callChangeWeather(u32 weather, u32 oldWeather);
  static void callDebugChangeLevel(u32 type, u32 id, u32 level, u32 oldLevel);
  static void callDebugChangeIdea(u32 type, u32 id, u32 idea, u32 value);
  static void callDebugDestroyAsset(GF_ASSET_HANDLE *asset);
  static void callDebugMapModel(GF_OBJ_HANDLE *handle, bool isEnter);

  static void callLayerPause(u32 layer, bool isPause) {
    GfEvent *gfEvent = get();
    for (size_t i = 0; i < gfEvent->unknown08.size(); i++) {
      gfEvent->unknown08[i]->gevLayerPause(layer, isPause);
    }
  }

  // Inferred role: calls gevPause on every callback; original name unknown.
  static void unknown001(u32 resumeBits, u32 pauseBits) {
    GfEvent *gfEvent = get();
    for (size_t i = 0; i < gfEvent->unknown08.size(); i++) {
      gfEvent->unknown08[i]->gevPause(resumeBits, pauseBits);
    }
  }

  // Inferred role: calls gevReloadBdat on every callback (SCOM_RELOAD_BDAT, SCOM_RELOAD_TEXT); original name unknown.
  void unknown002(RELOAD_BDAT reload, u32 value) {
    for (size_t i = 0; i < unknown08.size(); i++) {
      unknown08[i]->gevReloadBdat(reload, value);
    }
  }

private:
  mm::mtl::FixedQueue<IGfEvent *, CALLBACK_UNKNOWN_32> unknown08; // Inferred role: callbacks; original member name unknown.
  bool unknown118;                                                // Inferred role: initialized; original member name unknown.
};

static_assert(sizeof(GfEvent) == 0x120, "");

} // namespace gf
