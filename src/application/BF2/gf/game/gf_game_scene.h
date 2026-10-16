#pragma once
#include <stddef.h>

#include "gf/data/gf_data_blade.h"
#include "gf/event/gf_event.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace fw {
struct UpdateInfo;
}

namespace gf {

struct GF_OBJ_HANDLE;
class GfAppendWire;
struct GfSetupParam;
struct QuestCompleteParam;
struct OwnerBonus;

enum PLSTOP {
  PLSTOP_GMK_TUTORIAL_SEQUENCE = 1,
  PLSTOP_GMK_TUTORIAL_MOVER = 2,
  PLSTOP_EVENT = 3,
  PLSTOP_RESET_BLADE = 4,
};

class GfGameScene : public mm::mtl::PtrSingleton<GfGameScene> {
public:
  void setDamageCharacter(GF_OBJ_HANDLE *handle);
  void setCameraAvtivateOneTime();
  void setRideOn(u32 partyId);
  void addMoneyLog();

  void setPlayerStopFlag(PLSTOP flag, bool isStop);
  bool isPlayerStopFlag(PLSTOP flag);
  static void build(const GfSetupParam &param);
  static void destroy();
  static bool isPlayerWalkAndRun();
  void clear();
  void setupGame();
  void refreshGimmickFlag();
  bool isPlayEvent() const;
  bool isMaskMainMenu() const;
  bool isMoverGetFieldDamage() const;
  void setEventPlayerStop(bool isStop);
  void setResetBladePlayerStop(bool isStop);
  bool isControlFree() const;
  void setHomuriWeaponExtraMesh(bool isVisible, f32 alpha);
  bool isNeedFieldBladeChange(u32 partyId) const;
  void setForceBossBattleBgm(bool isForce);
  bool isForceBossBattleBgm() const;
  bool isForceEventBgm() const;
  bool isPlayerTalkForce();
  bool isPlayerPause() const;
  bool isPlayerPauseForBattle() const;
  u32 getDeadType();
  bool isNeedResetBladeForBattleEndForMenuOpen() const;
  bool isDisableJumpForRide() const;
  bool isBattle() const;
  void gevExecBuy(u32 item, u32 count, u32 shop);
  void gevChangeParty();
  void gevDriverActivate(u32 driver, ActivateType activateType, ActivateType oldActivateType);
  void gevBladeActivate(u32 blade, ActivateType activateType, ActivateType oldActivateType);
  void gevBladeUnselect(u32 blade, bool unselect);
  void gevDriverLevel(u32 driver, u32 level, u32 oldLevel);
  void gevMapjump(GEV event, const MapjumpCallbackInfo &info);
  void gevChangeScenarioFlag(u32 scenarioFlag, u32 oldScenarioFlag);
  void gevItemAdd(u32 item, int count);
  void gevGameObjEnter(GF_OBJ_HANDLE *handle);
  void gevGameObjLeave(GF_OBJ_HANDLE *handle);
  void gevChangeWeather(u32 weather, u32 oldWeather);
  void gevChangeTimeRange(u32 timeRange);
  void gevControllFree(bool isFree);
  void gevBattleStart();
  void gevBattleEnd();
  void gevMercenariesMissionFlag(u32 mission, u32 flag, u32 value);
  void gevPlayEvent(GEV event, u32 eventId);
  void gevSelectHikari(bool hikariCurrent);
  void qevCompleteQuest(const QuestCompleteParam &param);
  void postUpdate(const fw::UpdateInfo &info);
  OwnerBonus &getOwnerBonus() const;
  GfAppendWire *getAppendControl(GF_OBJ_HANDLE *handle);
  bool isPlayerCameraPause();
  void enterBattle(bool isForce);
  bool isBattleStop();
  void setForceStopBattle(bool isStop);
  void updateParam(const fw::UpdateInfo &info);
  void update(const fw::UpdateInfo &info);

  u8 _08[0x1c9 - 0x08];
  bool isStartGame;
  bool isEnableRoomForHikariLv4;
  u8 _1cb[0x1d0 - 0x1cb];
  bool isStopMainMenuOpenForGimmick;
  u8 _1d1[0x270 - 0x1d1];
  bool isValidCollisionVelocity;
  u8 _271[0x620 - 0x271];
  int stopEnemyAttackCount;
};

static_assert(offsetof(GfGameScene, isStartGame) == 0x1c9, "");
static_assert(offsetof(GfGameScene, isEnableRoomForHikariLv4) == 0x1ca, "");
static_assert(offsetof(GfGameScene, isStopMainMenuOpenForGimmick) == 0x1d0, "");
static_assert(offsetof(GfGameScene, isValidCollisionVelocity) == 0x270, "");
static_assert(offsetof(GfGameScene, stopEnemyAttackCount) == 0x620, "");

} // namespace gf
