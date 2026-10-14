#pragma once
#include "gf/data/gf_data_blade.h"
#include "types.h"

namespace gf {

enum RELOAD_BDAT {
  RELOAD_BDAT_ALL = 1,
};

enum GEV {};
enum GF_STATE {
  GF_STATE_INITIALIZE = 1,
  GF_STATE_DESTROY = 2,
  GF_STATE_CONTROL = 3,
  GF_STATE_TALK = 4,
  GF_STATE_MENU = 6,
  GF_STATE_WAIT_EVENT = 7,
  GF_STATE_MAPJUMP = 8,
  GF_STATE_MAPJUMP_SKIP_TRAVEL = 9,
  GF_STATE_PLAYER_DEAD = 10,
  GF_STATE_SALVAGE = 11,
  GF_STATE_COLLECT = 12,
  GF_STATE_FIELD_TBOX = 13,
  GF_STATE_MAP_GIMMICK = 14,
  GF_STATE_GRAVE = 15,
  GF_STATE_JUMP = 16,
  GF_STATE_WARP = 17,
  GF_STATE_GMK_TUTORIAL = 18,
  GF_STATE_GMK_CAMERA = 19,
  GF_STATE_EVENT = 20,
  GF_STATE_GIMMICK_TASK = 21,
  GF_STATE_CHAIN_ATTACK = 22,
  GF_STATE_ARTS_MOVIE = 23,
  GF_STATE_RESET_BLADE = 24,
};
enum EXEC_STATE {};

struct GF_ASSET_HANDLE;
struct GF_OBJ_HANDLE;
struct GfAchievementRelease;

struct MapjumpCallbackInfo {
  u8 _00[0x04 - 0x00];
  u32 map;
  u32 prevMap;
  u8 _0c[0x14 - 0x0c];
};

static_assert(sizeof(MapjumpCallbackInfo) == 0x14, "");

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

class GfEvent {
public:
  static void addEventCallback(IGfEvent *event);
  static void removeEventCallback(IGfEvent *event);
  static void callChangeScenarioFlag(u32 scenarioFlag, u32 oldScenarioFlag);
  static void callTargetAccess(GF_OBJ_HANDLE *target);
  static void callTargetChange(GF_OBJ_HANDLE *target);
  static void callBladeUnselect(u32 blade, bool unselect);
  static void callHikariCurrent(bool hikariCurrent);
  static void callDebugChangeIdea(u32 type, u32 id, u32 idea, u32 value);
  static void callBladeActivate(u32 blade, ActivateType activateType, ActivateType oldActivateType);
  static void callItemAdd(u32 item, int count);
  static void callBladeChange(GF_OBJ_HANDLE *handle, int oldSlot, int newSlot);
  static void callPartyMemberOK(bool isOK);
  static void callChangeLeader(GF_OBJ_HANDLE *leader);
  static void callPartyIDMemberOK(bool isOK, u32 partyId);
  static void callPartyDriver(GF_OBJ_HANDLE *handle, u32 partyId, bool isEnter);
  static void callExecBuy(u32 item, u32 count, u32 shop);
  static void callPartyChange();
  static void callSwapFormation(u32 playerId, u32 otherPlayerId);
};

} // namespace gf
