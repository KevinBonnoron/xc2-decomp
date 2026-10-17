#pragma once
#include <stddef.h>

#include "gf/data/gf_data_blade.h"
#include "gf/event/gf_event.h"
#include "gf/game/gf_game_manager.h"
#include "gf/game/sequential_play/gf_play_factory.h"
#include "mm_mtl/bitflag.h"
#include "mm_mtl/fixed_list.h"
#include "mm_mtl/fixed_vector.h"
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
struct MsgObjectNotifyDamage;

enum PLSTOP {
  PLSTOP_GMK_TUTORIAL_SEQUENCE = 1,
  PLSTOP_GMK_TUTORIAL_MOVER = 2,
  PLSTOP_EVENT = 3,
  PLSTOP_RESET_BLADE = 4,
};

class GfGameScene : public mm::mtl::PtrSingleton<GfGameScene> {
public:
  enum {
    FLAG_CAMERA_ACTIVATE_ONE_TIME = 1 << 0,
    FLAG_BATTLE = 1 << 1,
    FLAG_CAMERA_PAUSE = 1 << 2,
  };

  class EvtPlayerStop {
  public:
    enum STATE {
      STATE_NONE,
      STATE_WAIT_MOVER,
      STATE_STOP,
    };

    void startPlayerStop();
    void endPlayerStop();
    void resetState();
    void setPlayerStop(bool isStop);
    void update(const fw::UpdateInfo &info);

    u8 _00[0x08 - 0x00];
    STATE state;
    u8 _0c[0x10 - 0x0c];
  };

  struct BattleAchievement {
    void battleStart();
    void battleEnd();
    void bladeDamage(GF_OBJ_HANDLE *handle, const MsgObjectNotifyDamage &damage);

    bool isBattle;
    u32 damageCount;
    u32 maxDamage;
  };

  struct DamageCharacter {
    GF_OBJ_HANDLE *handle;
    u32 time;
  };

  void setDamageCharacter(GF_OBJ_HANDLE *handle);
  void setCameraAvtivateOneTime();
  void setRideOn(u32 partyId);
  void addMoneyLog();

  void setPlayerStopFlag(PLSTOP flag, bool isStop);
  bool isPlayerStopFlag(PLSTOP flag);
  GfGameScene(const GfSetupParam &param);
  static void build(const GfSetupParam &param);
  static void destroy();
  static bool isPlayerWalkAndRun();
  bool isInitialized() const;
  void clear();
  void setupGame();
  void refreshGimmickFlag();
  bool isPlayEvent() const;
  bool isMaskMainMenu() const;
  bool isMoverGetFieldDamage() const;
  void setEventPlayerStop(bool isStop);
  void setResetBladePlayerStop(bool isStop);
  bool isControlFree() const;
  bool isControlFreeState() const;
  void setHomuriWeaponExtraMesh(bool isVisible, f32 alpha);
  bool isEnableFieldBladeChange() const;
  bool isNeedFieldBladeChange(u32 partyId) const;
  void setForceBossBattleBgm(bool isForce);
  bool isForceBossBattleBgm() const;
  void setForceEventBgm(f32 time);
  bool isForceEventBgm() const;
  bool isPlayerTalkForce();
  void setPlayerTalkForce(bool isForce);
  void setGimmickCameraPause(bool isPause);
  void setAutoBattle(bool isAuto);
  bool isAutoBattle();
  bool isRideObj(GF_OBJ_HANDLE *handle) const;
  int createPlayerPause();
  void destroyPlayerPause(u32 pause);
  bool isPlayerPause() const;
  bool isPlayerPauseForBattle() const;
  bool isRideParty(u32 partyId) const;
  void setDeadType(GfPlayerDead dead);
  u32 getDeadType();
  bool isNeedResetBladeForBattleEndForMenuOpen() const;
  bool isDisableJumpForRide() const;
  bool isBattle() const;
  bool isResetBladePlay() const;
  void applyMapjumpForCleanup(const MapjumpCallbackInfo &info);
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
  void playEventPlayStart(u32 event);
  void gevPlayEvent(GEV event, u32 eventId);
  void gevSelectHikari(bool hikariCurrent);
  void qevCompleteQuest(const QuestCompleteParam &param);
  void updateAppendModel(const fw::UpdateInfo &info);
  void postUpdate(const fw::UpdateInfo &info);
  OwnerBonus &getOwnerBonus() const;
  GfAppendWire *getAppendControl(GF_OBJ_HANDLE *handle);
  bool isPlayerCameraPause();
  void setPlayerCameraPause(bool isPause);
  void enterBattle(bool isForce);
  bool isBattleStop();
  static void setForceBattleTime(f32 time);
  void setForceStopBattle(bool isStop);
  u32 getQuestIdForTaskLog() const;
  void updateOwnerBonus(const fw::UpdateInfo &info);
  void updateParam(const fw::UpdateInfo &info);
  void updateMaskMainMenu(const fw::UpdateInfo &info);
  void updateStopEnemyAttackForEvent(const fw::UpdateInfo &info);
  void updateAfterEventCount(const fw::UpdateInfo &info);
  void updateEventFadeVolume(const fw::UpdateInfo &info);
  void updateLog(const fw::UpdateInfo &info);
  void updateForceBattle(const fw::UpdateInfo &info);
  void updateEventBgm(const fw::UpdateInfo &info);
  void updateAutoFlag(const fw::UpdateInfo &info);
  void update(const fw::UpdateInfo &info);

  bool initialized;
  u8 _09[0x18 - 0x09];
  f32 fieldBladeChangeTime;
  u8 _1c[0x20 - 0x1c];
  DamageCharacter damageCharacters[3];
  bool isOwnerBonusDirty;
  u8 _51[0x52 - 0x51];
  mutable OwnerBonus ownerBonus;
  u8 _6e[0x70 - 0x6e];
  mm::mtl::FixedList<GfAppendWire *, 8> appendWires;
  f32 moneyLogTime;
  u32 questIdForTaskLog;
  BattleAchievement battleAchievement;
  f32 forceBattleTime;
  bool isForceStopBattle;
  bool isForceBossBattleBgmEnable;
  bool isForceBattleBgm;
  u8 _133[0x134 - 0x133];
  f32 forceEventBgmTime;
  bool isPlayerTalkForceEnable;
  bool isGimmickCameraPause;
  u8 _13a[0x13c - 0x13a];
  GfPlayerDead deadType;
  u32 playerPauseBits;
  u32 flags;
  u8 _148[0x1a8 - 0x148];
  bool isAutoBattleEnable;
  bool isRequestAutoFlag;
  u8 _1aa[0x1b8 - 0x1aa];
  mm::mtl::BitFlag<5> playerStopFlags;
  u8 _1bc[0x1c9 - 0x1bc];
  bool isStartGame;
  bool isEnableRoomForHikariLv4;
  u8 _1cb[0x1d0 - 0x1cb];
  bool isStopMainMenuOpenForGimmick;
  u8 _1d1[0x270 - 0x1d1];
  bool isValidCollisionVelocity;
  u8 _271[0x410 - 0x271];
  bool isMaskMainMenuEnable;
  bool isPlayEventEnable;
  u8 _412[0x418 - 0x412];
  mm::mtl::FixedVector<GF_OBJ_HANDLE *, 64> eventObjs;
  int stopEnemyAttackCount;
  int afterEventCount;
  EvtPlayerStop eventPlayerStop;
  EvtPlayerStop resetBladePlayerStop;
  u8 _648[0x670 - 0x648];
};

static_assert(offsetof(GfGameScene, isStartGame) == 0x1c9, "");
static_assert(offsetof(GfGameScene, isEnableRoomForHikariLv4) == 0x1ca, "");
static_assert(offsetof(GfGameScene, isStopMainMenuOpenForGimmick) == 0x1d0, "");
static_assert(offsetof(GfGameScene, isValidCollisionVelocity) == 0x270, "");
static_assert(offsetof(GfGameScene, stopEnemyAttackCount) == 0x620, "");
static_assert(offsetof(GfGameScene, fieldBladeChangeTime) == 0x18, "");
static_assert(offsetof(GfGameScene, ownerBonus) == 0x52, "");
static_assert(offsetof(GfGameScene, appendWires) == 0x70, "");
static_assert(offsetof(GfGameScene, moneyLogTime) == 0x118, "");
static_assert(offsetof(GfGameScene, battleAchievement) == 0x120, "");
static_assert(offsetof(GfGameScene, forceBattleTime) == 0x12c, "");
static_assert(offsetof(GfGameScene, deadType) == 0x13c, "");
static_assert(offsetof(GfGameScene, flags) == 0x144, "");
static_assert(offsetof(GfGameScene, isAutoBattleEnable) == 0x1a8, "");
static_assert(offsetof(GfGameScene, playerStopFlags) == 0x1b8, "");
static_assert(offsetof(GfGameScene, isMaskMainMenuEnable) == 0x410, "");
static_assert(offsetof(GfGameScene, eventObjs) == 0x418, "");
static_assert(offsetof(GfGameScene, eventPlayerStop) == 0x628, "");
static_assert(sizeof(GfGameScene) == 0x670, "");

} // namespace gf
