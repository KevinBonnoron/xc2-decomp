#pragma once
#include <stddef.h>

#include "gf/data/gf_data_blade.h"
#include "gf/event/gf_event.h"
#include "gf/game/gf_game_pad.h"
#include "gf/game/quest/gf_quest_manager.h"
#include "mm_mtl/fixed_array.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace fw {
struct UpdateInfo;
}

namespace mm {
struct Col4;
struct Vec3;
} // namespace mm

namespace gf {

struct GF_OBJ_HANDLE;
struct GfSetupParam;

enum {
  OWNER_BONUS_FAVORITE_VALUE_MAX = 3,
  OWNER_BONUS_IDEA_POINT = 4,
  OWNER_BONUS_DEVELOP_POINT = 5,
  OWNER_BONUS_BOOSTER_VALUE_MAX = 13,
};

struct OwnerBonus {
  s16 values[14];
};

static_assert(sizeof(OwnerBonus) == 0x1c, "");

class GfGameManager : public mm::mtl::PtrSingleton<GfGameManager>, public IGfEvent, public IQuestEvent {
public:
  GfGameManager(const GfSetupParam &param);
  void initialize(const GfSetupParam &param);
  virtual ~GfGameManager();

  static void build(const GfSetupParam &param);
  static void destroy();
  void finalize();
  static bool isGameObjEmpty();
  static GF_STATE getState();
  static void setState(GF_STATE state, bool isForce);
  static void clear();
  static bool isInitialized();
  void gevExecBuy(u32 item, u32 count, u32 shop) override;
  void gevChangeParty() override;
  void gevGetArts(u32 driver, u32 arts, bool isPopup) override;
  void gevDriverLevel(u32 driver, u32 level, u32 oldLevel) override;
  void gevSelectHikari(bool hikariCurrent) override;
  void gevBattleStart() override;
  void gevBattleEnd() override;
  void gevPause(u32 resumeBits, u32 pauseBits) override;
  void gevChangeBlade(GF_OBJ_HANDLE *handle, int oldSlot, int newSlot) override;
  void gevMapjump(GEV event, const MapjumpCallbackInfo &info) override;
  void gevGameObjEnter(GF_OBJ_HANDLE *handle) override;
  void gevGameObjLeave(GF_OBJ_HANDLE *handle) override;
  void gevDriverActivate(u32 driver, ActivateType activateType, ActivateType oldActivateType) override;
  void gevBladeActivate(u32 blade, ActivateType activateType, ActivateType oldActivateType) override;
  void gevBladeUnselect(u32 blade, bool unselect) override;
  void gevBladeEnable(u32 blade) override;
  void gevPlayEvent(GEV event, u32 eventId) override;
  void gevItemAdd(u32 item, int count) override;
  void gevPartyMemberOK(bool isOK) override;
  void gevLayerPause(u32 layer, bool isPause) override;
  void gevPartyIDMemberOK(bool isOK, u32 partyId) override;
  void gevReloadBdat(RELOAD_BDAT reload, u32 value) override;
  void gevSalvageStateChange(u32 state) override;
  void gevChangeScenarioFlag(u32 scenarioFlag, u32 oldScenarioFlag) override;
  void gevChangeWeather(u32 weather, u32 oldWeather) override;
  void gevChangeTimeRange(u32 timeRange) override;
  void gevGameState(GF_STATE previousState, GF_STATE state) override;
  void gevControllFree(bool isFree) override;
  void gevMercenariesMissionFlag(u32 mission, u32 flag, u32 value) override;
  void qevCompleteQuest(const QuestCompleteParam &param) override;
  void qevOrderQuest(const QuestOrderParam &param) override;
  void qevCompleteChildQuest(const QuestCompleteChildParam &param) override;
  static bool isInnerState(GF_STATE state);
  static GF_OBJ_HANDLE *getPartyLeader();
  static GF_OBJ_HANDLE *getPartyLeaderDriver();
  static GF_OBJ_HANDLE *getControlMover();
  static GF_OBJ_HANDLE *getControlRider();
  static void collectPadCharList(mm::mtl::FixedArray<GF_OBJ_HANDLE *, 2> *characters);
  static bool isPlayerPause();
  static void enterBattle(bool isForce);
  static bool isBattle();
  static bool isBattleStop();
  static bool isControlMoverBattle();
  static bool isQuestCompleteUI();
  static bool isPartySelect();
  static bool isEvent(bool isIncludeSequentialPlay);
  static bool isEventWait();
  static bool isPlayEvent();
  static bool isField();
  static bool isPlaySequenceClear();
  static bool isControlFree();
  static bool isControlFree(u32 state);
  static bool isBladeChange();
  static bool isDisableBattou();
  static bool isEnableBattouWithHoodHomura(bool isCheckMenu);
  static bool isTalkOK();
  static bool isTalking();
  static bool isFullScreenMenu();
  static bool isPlayCommonMenu();
  static bool isPlayEventOK();
  static bool isMapjumpOK();
  static bool isExecTutorial();
  static bool isGmkTutorialMoverOK();
  static void setGmkTutorialMoverOK(bool isOK);
  static bool isGmkTutorialSequenceOK();
  static void setGmkTutorialSequenceOK(bool isOK);
  static bool isGmkTutorialOK();
  static bool isValidCollisionVelocity();
  static void setValidCollisionVelocity(bool isValid);
  static bool isEnablePlayerDeadSequence();
  static bool isLeaveGameForDebug();
  static bool isGameOver();
  static bool isEnemyChangeBattleOK();
  static bool isFieldLockMsgOK();
  static bool isEnableFieldAccess();
  static bool isAutoTalkOK();
  static bool isInGamePauseMenuOK();
  static bool isLandmarkUiOK();
  static bool isElevatorMoveOK(u16 elevator);
  static bool isRoom();
  static bool isWeatherSE();
  static u32 getMapJumpID();
  static u32 getMapID();
  static void setMapID(u32 mapJump, u32 map);
  static u32 getMapZoneID();
  static void setAccessTarget(GF_OBJ_HANDLE *target);
  static void setTargetUI(GF_OBJ_HANDLE *target);
  static bool isEnableFieldBattleTarget();
  static void setupGame();
  static bool isFading(u32 fade);
  static bool isFadeout();
  static void getFadeColor(u32 fade, mm::Col4 &color);
  static bool isFadeClear();
  static f32 getFadeoutAlpha();
  static bool isStopBattleSequence();
  static bool isMapjump();
  static bool isMapjumpWithSaveData();
  static bool isMapjumpBlackout();
  static bool isPlayerCameraPause();
  static u32 getDeadType();
  static void leaveGameForDebug();
  static bool isPadCameraForDebug();
  static void setInterruptPadOnForDebug(DWPAD pad);
  static bool isScenarioGame();
  static bool isAdvertize();
  static bool isPartyCreateForMapjump();
  static bool isActivateHikari(bool isCheckLeader);
  static bool isActivateHomuri(bool isCheckLeader);
  static bool isInMetJIJI();
  static const mm::Vec3 &getControlMoverPosition();
  static mm::Vec3 getControlMoverRotation();
  static OwnerBonus *getOwnerBonus();
  static f32 getFieldSpeed(const fw::UpdateInfo &info);
  static bool isPlayerFinishBattleState();
  static bool isEnableOpenMainMenuSequence();
  static bool isStartGame();
  static bool isEnableOpenMainMenu();
  static bool isStopMainMenuOpenForGimmick();
  static bool isEnableHoodHomuraScenes();
  static bool isEnableGimmickPhantomDamage();
  static bool isEnableGetFieldPrecious();
  static bool isEnableCreateBattleLock();
  static bool isPartyMover(GF_OBJ_HANDLE *handle);
  static bool isBusyBladeCreateEvent();
  static void callbackBladeActivateForGimmick();
  static bool isExistBossEnemy();
  static bool isExistBossEnemyWithHp();
  static bool isNeedResetBlade();
  static bool isStopEnemySearch();
  static bool isPlayerDeadSequence();
  static bool isForceBossBattleBgm();
  static bool isForceEventBgm();
  static bool isNight();
  static void destroyBattleEnemy();
  static bool isWaitGimmickPopForMapjump();
  static const char *getMapSePackName();
  static u32 getScenarioId();
  static bool isRexAwakening();
  static void setStartGame();
  static bool isEnableRoomForHikariLv4();
  static void setHomuriWeaponExtraMesh(bool isVisible, f32 alpha);
  static bool isClearGame();
  static bool isOpenPreciousMenu();
  static bool isStopEnemyAttack();
  static bool isPlayEnemyVoice();
  static bool isPlayVoice(GF_OBJ_HANDLE *handle);
  static bool isPartyMemberPlayVoice();
  static void setStopMainMenuOpenForGimmick(bool isStop);
  static bool isDisableJumpForRide();
  static bool isDisableAutoRun();
  static bool isHoodHomura(GF_OBJ_HANDLE *handle);
  static bool isChangeNormalHomuraForce(u32 blade);
  static bool isAssetNumberInvalid();
  void updateParam(const fw::UpdateInfo &info);
  void postUpdate(const fw::UpdateInfo &info);
  void update(const fw::UpdateInfo &info);

private:
  bool mInitialized;
  bool mIsLeaveGame;

  friend struct GfGameManagerLayout;
};

struct GfGameManagerLayout {
  static_assert(offsetof(GfGameManager, mInitialized) == 0x18, "");
  static_assert(offsetof(GfGameManager, mIsLeaveGame) == 0x19, "");
  static_assert(sizeof(GfGameManager) == 0x20, "");
};

} // namespace gf
