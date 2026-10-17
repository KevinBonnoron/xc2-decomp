#pragma once
#include <stddef.h>

#include "gf/data/gf_data_blade.h"
#include "gf/data/gf_data_util.h"
#include "gf/event/gf_event.h"
#include "gf/game/gf_game_manager.h"
#include "gf/game/quest/gf_quest_id.h"
#include "gf/game/sequential_play/gf_play_factory.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/bitflag.h"
#include "mm_mtl/fixed_array.h"
#include "mm_mtl/fixed_list.h"
#include "mm_mtl/fixed_queue.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace fw {
struct UpdateInfo;
}

namespace gf {

struct GF_OBJ_HANDLE;
struct GF_SE_CATEGORY_HANDLE;
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

namespace _gfgsc {

void setInvalidSavePos(mm::Vec3 &position);
bool isInvalidSavePos(const mm::Vec3 &position);
bool isPartyMemberGetFieldDamage(u32 partyId);

} // namespace _gfgsc

class GfGameScene : public mm::mtl::PtrSingleton<GfGameScene> {
public:
  enum {
    FLAG_CAMERA_ACTIVATE_ONE_TIME = 1 << 0,
    FLAG_BATTLE = 1 << 1,
    FLAG_CAMERA_PAUSE = 1 << 2,
  };

  enum MOVER_STATE {
    MOVER_STATE_NONE,
    MOVER_STATE_FIELD,
    MOVER_STATE_SWIM,
    MOVER_STATE_CLIMB,
    MOVER_STATE_JUMP,
    MOVER_STATE_BUSY,
  };

  class EvtPlayerStop {
  public:
    enum STATE {
      STATE_NONE,
      STATE_WAIT_MOVER,
      STATE_STOP,
    };

    EvtPlayerStop(GfGameScene *scene, PLSTOP flag) : scene(scene), state(STATE_NONE), flag(flag) {}

    void startPlayerStop();
    void endPlayerStop();
    void resetState();
    void setPlayerStop(bool isStop);
    void update(const fw::UpdateInfo &info);

    GfGameScene *scene;
    STATE state;
    PLSTOP flag;
  };

  struct BattleAchievement {
    BattleAchievement() : isBattle(false), damageCount(0), maxDamage(0) {}

    void battleStart();
    void battleEnd();
    void enemyDamage(GF_OBJ_HANDLE *handle, const MsgObjectNotifyDamage &damage);
    void driverDamage(GF_OBJ_HANDLE *handle, const MsgObjectNotifyDamage &damage);
    void bladeDamage(GF_OBJ_HANDLE *handle, const MsgObjectNotifyDamage &damage);
    void addDamage(GF_OBJ_HANDLE *handle, const MsgObjectNotifyDamage &damage);

    bool isBattle;
    u32 damageCount;
    u32 maxDamage;
  };

  struct DamageCharacter {
    DamageCharacter() : handle(reinterpret_cast<GF_OBJ_HANDLE *>(-1)), healTime(0.0f) {}

    GF_OBJ_HANDLE *handle;
    f32 healTime;
  };

  struct MoveAchievement {
    MoveAchievement(AMOVE moveType, u32 achievement, bool (*isMove)()) : moveType(moveType), achievement(achievement), isMove(isMove) {}

    AMOVE moveType;
    u32 achievement;
    bool (*isMove)();
  };

  struct PartyState {
    PartyState() : partyId(-1), moverState(MOVER_STATE_NONE), fieldFrames(0), isGetFieldDamage(false), isFloating(false) {}

    u32 partyId;
    MOVER_STATE moverState;
    int fieldFrames;
    bool isGetFieldDamage;
    bool isFloating;
  };

  struct SavePos {
    SavePos() : position(mm::Vec3::zero), isEnable(false) {}

    mm::Vec3 position;
    bool isEnable;
  };

  void setPlayerStopFlag(PLSTOP flag, bool isStop);
  bool isPlayerStopFlag(PLSTOP flag);
  GfGameScene(const GfSetupParam &param);
  void initialize(const GfSetupParam &param);
  ~GfGameScene();
  static void build(const GfSetupParam &param);
  static void destroy();
  void finalize();
  void clearPartyState();
  static bool isPlayerSwimOnCloud();
  static bool isPlayerWalkAndRun();
  bool isInitialized() const;
  void clear();
  void destroySepiaFilter();
  void setupGame();
  bool isPlayEvent() const;
  bool isMaskMainMenu() const;
  bool isMoverGetFieldDamage() const;
  void setEventPlayerStop(bool isStop);
  void setResetBladePlayerStop(bool isStop);
  bool isControlFree() const;
  bool isControlFreeState() const;
  void setEraseQuestEnemyForEventStart(QuestID quest);
  void setEnemyDead(GF_OBJ_HANDLE *handle);
  void setHomuriWeaponExtraMesh(bool isVisible, f32 alpha);
  bool isEnableFieldBladeChange() const;
  bool requestFieldBladeChange();
  bool isNeedFieldBladeChange(u32 partyId) const;
  void checkFieldBladeChange();
  bool isEnableRideCondition(u32 partyId) const;
  void checkFieldBladeChangeForRide();
  void setForceBossBattleBgm(bool isForce);
  bool isForceBossBattleBgm() const;
  void setForceEventBgm(f32 time);
  bool isForceEventBgm() const;
  bool isPlayerTalkForce();
  void setPlayerTalkForce(bool isForce);
  void setGimmickCameraPause(bool isPause);
  void refreshGimmickFlag();
  void setAutoBattle(bool isAuto);
  bool isAutoBattle();
  bool isRide(u32 partyId) const;
  bool isRideObj(GF_OBJ_HANDLE *handle) const;
  bool isRideParty(u32 partyId) const;
  int createPlayerPause();
  void destroyPlayerPause(u32 pause);
  bool isPlayerPause() const;
  bool isPlayerPauseForBattle() const;
  void setDeadType(GfPlayerDead dead);
  u32 getDeadType();
  void setDamageCharacter(GF_OBJ_HANDLE *handle);
  void createDriverAppendModelControl(GF_OBJ_HANDLE *handle);
  void destroyDriverAppendModelControl(GF_OBJ_HANDLE *handle);
  void enterExtraControlForHanaJS(GF_OBJ_HANDLE *handle);
  void leaveExtraControlForHanaJS(GF_OBJ_HANDLE *handle);
  GfAppendWire *getAppendControl(GF_OBJ_HANDLE *handle);
  void saveBattleHpForEnemy(GF_OBJ_HANDLE *handle);
  const mm::Vec3 &getEnableSavePos() const;
  bool isNeedResetBladeForBattleEndForMenuOpen() const;
  bool isDisableJumpForRide() const;
  bool isBattle() const;
  bool isNeedResetBladeForBattleEndForBattleEnd() const;
  bool isResetBladePlay() const;
  void applyMapjumpForCleanup(const MapjumpCallbackInfo &info);
  void applyMapjumpForStart(const MapjumpCallbackInfo &info);
  void applyMapjumpForEnd(const MapjumpCallbackInfo &info);
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
  void playEventSequenceStart(u32 event);
  void playEventSequenceEnd(u32 event);
  void playEventPlayStart(u32 event);
  void playEventPlayEnd(u32 event);
  void playEventStartFrame(u32 event);
  void createSepiaFilter();
  void updatePlayerState();
  void gevPlayEvent(GEV event, u32 eventId);
  void gevSelectHikari(bool hikariCurrent);
  void qevCompleteQuest(const QuestCompleteParam &param);
  void updateAppendModel(const fw::UpdateInfo &info);
  void postUpdate(const fw::UpdateInfo &info);
  OwnerBonus &getOwnerBonus() const;
  void setCameraAvtivateOneTime();
  bool isPlayerCameraPause();
  void setPlayerCameraPause(bool isPause);
  void enterBattle(bool isBattle);
  bool isBattleStop();
  static void setForceBattleTime(f32 time);
  void setForceStopBattle(bool isStop);
  void addDamage(GF_OBJ_HANDLE *handle, const MsgObjectNotifyDamage &damage);
  void addMoneyLog();
  QuestID getQuestIdForTaskLog() const;
  void updateOwnerBonus(const fw::UpdateInfo &info);
  void updateParam(const fw::UpdateInfo &info);
  void updatePartyMover(const fw::UpdateInfo &info);
  void updateExtraControlForHanaJS(const fw::UpdateInfo &info);
  void updatePartyBattle(const fw::UpdateInfo &info);
  void updateMaskMainMenu(const fw::UpdateInfo &info);
  void updatePlayerStopFlag(const fw::UpdateInfo &info);
  void updateStopEnemyAttackForEvent(const fw::UpdateInfo &info);
  void updatePartyObjFlag(const fw::UpdateInfo &info);
  void updateBattleMomuri(const fw::UpdateInfo &info);
  void updateHikariLv4Room(const fw::UpdateInfo &info);
  void updateStartGame(const fw::UpdateInfo &info);
  void updateAfterEventCount(const fw::UpdateInfo &info);
  void updateControlFreeEvent(const fw::UpdateInfo &info);
  void updateEventFadeVolume(const fw::UpdateInfo &info);
  bool isPartyBusy(u32 partyId);
  void updatePartyInfo(const fw::UpdateInfo &info);
  void updateBladeChangeForBattle(const fw::UpdateInfo &info);
  void updateBladeChangeInField(const fw::UpdateInfo &info);
  void updateColiPrio(const fw::UpdateInfo &info);
  void updateAutoHeal(const fw::UpdateInfo &info);
  void updateMaxHp(const fw::UpdateInfo &info);
  void updateListeningPoint(const fw::UpdateInfo &info);
  void updateLog(const fw::UpdateInfo &info);
  void updateQuestTaskLog(const fw::UpdateInfo &info);
  void updateForceBattle(const fw::UpdateInfo &info);
  void updateMoveAchievement(const fw::UpdateInfo &info);
  void updateEventBgm(const fw::UpdateInfo &info);
  void updateAutoFlag(const fw::UpdateInfo &info);
  void updateCrystalPopup(const fw::UpdateInfo &info);
  void updateEnableSavePos(const fw::UpdateInfo &info);
  void updateRideRequest(const fw::UpdateInfo &info);
  void updateSepia(const fw::UpdateInfo &info);
  void updateEnemySaveHp(const fw::UpdateInfo &info);
  void setRideOn(u32 partyId);
  void update(const fw::UpdateInfo &info);

  bool initialized;
  u32 bladeChangeRequests[3];
  f32 fieldBladeChangeTime;
  DamageCharacter damageCharacters[3];
  bool isOwnerBonusDirty;
  mutable OwnerBonus ownerBonus;
  mm::mtl::FixedList<GfAppendWire *, 8> appendWires;
  f32 moneyLogTime;
  QuestID questIdForTaskLog;
  BattleAchievement battleAchievement;
  f32 forceBattleTime;
  bool isForceStopBattle;
  bool isForceBossBattleBgmEnable;
  bool isForceBattleBgm;
  f32 forceEventBgmTime;
  bool isPlayerTalkForceEnable;
  bool isGimmickCameraPause;
  GfPlayerDead deadType;
  u32 playerPauseBits;
  u32 flags;
  u8 _148[0x150 - 0x148];
  mm::Vec3 movePosition;
  mm::mtl::FixedVector<MoveAchievement, 4> moveAchievements;
  bool isAutoBattleEnable;
  bool isRequestAutoFlag;
  u32 isWaitReturnFieldState[3];
  mm::mtl::BitFlag<5> playerStopFlags;
  bool isDispRexCrystal;
  bool isDispHomuraCrystal;
  int controlFreeFrames;
  u32 playerControl;
  u8 _1c8[0x1c9 - 0x1c8];
  bool isStartGame;
  bool isEnableRoomForHikariLv4;
  bool isBattleMomuri;
  u32 battleMomuriRequest;
  bool isStopMainMenuOpenForGimmick;
  mm::mtl::FixedQueue<u8, 64> playerStopFlagQueue;
  size_t battleStartCounts[3];
  PartyState partyStates[3];
  bool isValidCollisionVelocity;
  mm::Vec3 listeningPoint;
  mm::Vec3 requestListeningPoint;
  bool isRequestListeningPoint;
  SavePos savePositions[8];
  mm::mtl::FixedVector<GF_OBJ_HANDLE *, 8> hanaJsObjs;
  mm::mtl::FixedArray<GF_OBJ_HANDLE *, 3> partyMovers;
  bool isMaskMainMenuEnable;
  bool isPlayEventEnable;
  mm::mtl::FixedVector<GF_OBJ_HANDLE *, 64> eventObjs;
  int stopEnemyAttackCount;
  int afterEventCount;
  EvtPlayerStop eventPlayerStop;
  EvtPlayerStop resetBladePlayerStop;
  bool isBattleEvent;
  GF_SE_CATEGORY_HANDLE *eventCategoryHandle;
  GF_SE_CATEGORY_HANDLE *mapjumpCategoryHandle;
  GF_SE_CATEGORY_HANDLE *eventSequenceCategoryHandle;
  bool isRideBlade;
  bool isRequestRideOn;
  u32 sepiaEffect;
};

static_assert(offsetof(GfGameScene, bladeChangeRequests) == 0x0c, "");
static_assert(offsetof(GfGameScene, fieldBladeChangeTime) == 0x18, "");
static_assert(offsetof(GfGameScene, damageCharacters) == 0x20, "");
static_assert(offsetof(GfGameScene, isOwnerBonusDirty) == 0x50, "");
static_assert(offsetof(GfGameScene, ownerBonus) == 0x52, "");
static_assert(offsetof(GfGameScene, appendWires) == 0x70, "");
static_assert(offsetof(GfGameScene, moneyLogTime) == 0x118, "");
static_assert(offsetof(GfGameScene, questIdForTaskLog) == 0x11c, "");
static_assert(offsetof(GfGameScene, battleAchievement) == 0x120, "");
static_assert(offsetof(GfGameScene, forceBattleTime) == 0x12c, "");
static_assert(offsetof(GfGameScene, isForceStopBattle) == 0x130, "");
static_assert(offsetof(GfGameScene, forceEventBgmTime) == 0x134, "");
static_assert(offsetof(GfGameScene, deadType) == 0x13c, "");
static_assert(offsetof(GfGameScene, flags) == 0x144, "");
static_assert(offsetof(GfGameScene, movePosition) == 0x150, "");
static_assert(offsetof(GfGameScene, moveAchievements) == 0x160, "");
static_assert(offsetof(GfGameScene, isAutoBattleEnable) == 0x1a8, "");
static_assert(offsetof(GfGameScene, isWaitReturnFieldState) == 0x1ac, "");
static_assert(offsetof(GfGameScene, playerStopFlags) == 0x1b8, "");
static_assert(offsetof(GfGameScene, isDispRexCrystal) == 0x1bc, "");
static_assert(offsetof(GfGameScene, controlFreeFrames) == 0x1c0, "");
static_assert(offsetof(GfGameScene, isStartGame) == 0x1c9, "");
static_assert(offsetof(GfGameScene, battleMomuriRequest) == 0x1cc, "");
static_assert(offsetof(GfGameScene, isStopMainMenuOpenForGimmick) == 0x1d0, "");
static_assert(offsetof(GfGameScene, playerStopFlagQueue) == 0x1d8, "");
static_assert(offsetof(GfGameScene, battleStartCounts) == 0x228, "");
static_assert(offsetof(GfGameScene, partyStates) == 0x240, "");
static_assert(offsetof(GfGameScene, isValidCollisionVelocity) == 0x270, "");
static_assert(offsetof(GfGameScene, listeningPoint) == 0x280, "");
static_assert(offsetof(GfGameScene, requestListeningPoint) == 0x290, "");
static_assert(offsetof(GfGameScene, isRequestListeningPoint) == 0x2a0, "");
static_assert(offsetof(GfGameScene, savePositions) == 0x2b0, "");
static_assert(offsetof(GfGameScene, hanaJsObjs) == 0x3b0, "");
static_assert(offsetof(GfGameScene, partyMovers) == 0x3f8, "");
static_assert(offsetof(GfGameScene, isMaskMainMenuEnable) == 0x410, "");
static_assert(offsetof(GfGameScene, eventObjs) == 0x418, "");
static_assert(offsetof(GfGameScene, stopEnemyAttackCount) == 0x620, "");
static_assert(offsetof(GfGameScene, eventPlayerStop) == 0x628, "");
static_assert(offsetof(GfGameScene, resetBladePlayerStop) == 0x638, "");
static_assert(offsetof(GfGameScene, isBattleEvent) == 0x648, "");
static_assert(offsetof(GfGameScene, eventCategoryHandle) == 0x650, "");
static_assert(offsetof(GfGameScene, isRideBlade) == 0x668, "");
static_assert(offsetof(GfGameScene, sepiaEffect) == 0x66c, "");
static_assert(sizeof(GfGameScene) == 0x670, "");

} // namespace gf
