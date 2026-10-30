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

    EvtPlayerStop(GfGameScene *scene, PLSTOP flag) : unknown00(scene), unknown08(STATE_NONE), unknown0c(flag) {}

    void startPlayerStop();
    void endPlayerStop();
    void resetState();
    void setPlayerStop(bool isStop);
    void update(const fw::UpdateInfo &info);

    GfGameScene *unknown00; // Inferred role: scene; original member name unknown.
    STATE unknown08;        // Inferred role: state; original member name unknown.
    PLSTOP unknown0c;       // Inferred role: flag; original member name unknown.
  };

  struct BattleAchievement {
    BattleAchievement() : unknown00(false), unknown04(0), unknown08(0) {}

    void battleStart();
    void battleEnd();
    void enemyDamage(GF_OBJ_HANDLE *handle, const MsgObjectNotifyDamage &damage);
    void driverDamage(GF_OBJ_HANDLE *handle, const MsgObjectNotifyDamage &damage);
    void bladeDamage(GF_OBJ_HANDLE *handle, const MsgObjectNotifyDamage &damage);
    void addDamage(GF_OBJ_HANDLE *handle, const MsgObjectNotifyDamage &damage);

    bool unknown00; // Inferred role: battle; original member name unknown.
    u32 unknown04;  // Inferred role: damage count; original member name unknown.
    u32 unknown08;  // Inferred role: max damage; original member name unknown.
  };

  // Inferred role: damage character; original type name unknown.
  struct unknown004 {
    unknown004() : unknown00(reinterpret_cast<GF_OBJ_HANDLE *>(-1)), unknown08(0.0f) {}

    GF_OBJ_HANDLE *unknown00; // Inferred role: handle; original member name unknown.
    f32 unknown08;            // Inferred role: heal time; original member name unknown.
  };

  // Inferred role: move achievement; original type name unknown.
  struct unknown005 {
    unknown005(AMOVE moveType, u32 achievement, bool (*isMove)()) : unknown00(moveType), unknown04(achievement), unknown08(isMove) {}

    AMOVE unknown00;     // Inferred role: move type; original member name unknown.
    u32 unknown04;       // Inferred role: achievement; original member name unknown.
    bool (*unknown08)(); // Inferred role: is move; original member name unknown.
  };

  // Inferred role: party state; original type name unknown.
  struct unknown006 {
    unknown006() : unknown00(-1), unknown04(MOVER_STATE_NONE), unknown08(0), unknown0c(false), unknown0d(false) {}

    u32 unknown00;         // Inferred role: party id; original member name unknown.
    MOVER_STATE unknown04; // Inferred role: mover state; original member name unknown.
    int unknown08;         // Inferred role: field frames; original member name unknown.
    bool unknown0c;        // Inferred role: get field damage; original member name unknown.
    bool unknown0d;        // Inferred role: floating; original member name unknown.
  };

  // Inferred role: save pos; original type name unknown.
  struct unknown007 {
    unknown007() : unknown00(mm::Vec3::zero), unknown10(false) {}

    mm::Vec3 unknown00; // Inferred role: position; original member name unknown.
    bool unknown10;     // Inferred role: enable; original member name unknown.
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

  bool m_initialized;
  u32 unknown0c[3];        // Inferred role: blade change requests; original member name unknown.
  f32 unknown18;           // Inferred role: field blade change time; original member name unknown.
  unknown004 unknown20[3]; // Inferred role: damage characters; original member name unknown.
  bool unknown50;          // Inferred role: owner bonus dirty; original member name unknown.
  mutable OwnerBonus m_ownerBonus;
  mm::mtl::FixedList<GfAppendWire *, 8> unknown70; // Inferred role: append wires; original member name unknown.
  f32 unknown118;                                  // Inferred role: money log time; original member name unknown.
  QuestID m_questIdForTaskLog;
  BattleAchievement unknown120; // Inferred role: battle achievement; original member name unknown.
  f32 unknown12c;               // Inferred role: force battle time; original member name unknown.
  bool unknown130;              // Inferred role: force stop battle; original member name unknown.
  bool m_forceBossBattleBgm;
  bool unknown132; // Inferred role: force battle bgm; original member name unknown.
  f32 m_forceEventBgm;
  bool unknown138; // Inferred role: player talk force enable; original member name unknown.
  bool unknown139; // Inferred role: gimmick camera pause; original member name unknown.
  GfPlayerDead m_deadType;
  u32 unknown140; // Inferred role: player pause bits; original member name unknown.
  u32 unknown144; // Inferred role: flags; original member name unknown.
  u8 _148[0x150 - 0x148];
  mm::Vec3 unknown150;                            // Inferred role: move position; original member name unknown.
  mm::mtl::FixedVector<unknown005, 4> unknown160; // Inferred role: move achievements; original member name unknown.
  bool m_autoBattle;
  bool unknown1a9;                   // Inferred role: request auto flag; original member name unknown.
  u32 unknown1ac[3];                 // Inferred role: wait return field state; original member name unknown.
  mm::mtl::unknown027<5> unknown1b8; // Inferred role: player stop flags; original member name unknown.
  bool unknown1bc;                   // Inferred role: display rex crystal; original member name unknown.
  bool unknown1bd;                   // Inferred role: display homura crystal; original member name unknown.
  int unknown1c0;                    // Inferred role: control free frames; original member name unknown.
  u32 unknown1c4;                    // Inferred role: player control; original member name unknown.
  u8 _1c8[0x1c9 - 0x1c8];
  bool unknown1c9;                                     // Inferred role: start game; original member name unknown.
  bool unknown1ca;                                     // Inferred role: enable room for hikari lv4; original member name unknown.
  bool unknown1cb;                                     // Inferred role: battle momuri; original member name unknown.
  u32 unknown1cc;                                      // Inferred role: battle momuri request; original member name unknown.
  bool unknown1d0;                                     // Inferred role: stop main menu open for gimmick; original member name unknown.
  mm::mtl::FixedQueue<u8, 64> unknown1d8;              // Inferred role: player stop flag queue; original member name unknown.
  size_t unknown228[3];                                // Inferred role: battle start counts; original member name unknown.
  unknown006 unknown240[3];                            // Inferred role: party states; original member name unknown.
  bool unknown270;                                     // Inferred role: valid collision velocity; original member name unknown.
  mm::Vec3 unknown280;                                 // Inferred role: listening point; original member name unknown.
  mm::Vec3 unknown290;                                 // Inferred role: request listening point; original member name unknown.
  bool unknown2a0;                                     // Inferred role: request listening point flag; original member name unknown.
  unknown007 unknown2b0[8];                            // Inferred role: save positions; original member name unknown.
  mm::mtl::FixedVector<GF_OBJ_HANDLE *, 8> unknown3b0; // Inferred role: hana js objects; original member name unknown.
  mm::mtl::FixedArray<GF_OBJ_HANDLE *, 3> unknown3f8;  // Inferred role: party movers; original member name unknown.
  bool m_maskMainMenu;
  bool m_playEvent;
  mm::mtl::FixedVector<GF_OBJ_HANDLE *, 64> unknown418; // Inferred role: event objects; original member name unknown.
  int unknown620;                                       // Inferred role: stop enemy attack count; original member name unknown.
  int unknown624;                                       // Inferred role: after event count; original member name unknown.
  EvtPlayerStop unknown628;                             // Inferred role: event player stop; original member name unknown.
  EvtPlayerStop unknown638;                             // Inferred role: reset blade player stop; original member name unknown.
  bool unknown648;                                      // Inferred role: battle event; original member name unknown.
  GF_SE_CATEGORY_HANDLE *unknown650;                    // Inferred role: event category handle; original member name unknown.
  GF_SE_CATEGORY_HANDLE *unknown658;                    // Inferred role: map jump category handle; original member name unknown.
  GF_SE_CATEGORY_HANDLE *unknown660;                    // Inferred role: event sequence category handle; original member name unknown.
  bool unknown668;                                      // Inferred role: ride blade; original member name unknown.
  bool unknown669;                                      // Inferred role: request ride on; original member name unknown.
  u32 unknown66c;                                       // Inferred role: sepia effect; original member name unknown.
};

static_assert(offsetof(GfGameScene, unknown0c) == 0x0c, "");
static_assert(offsetof(GfGameScene, unknown18) == 0x18, "");
static_assert(offsetof(GfGameScene, unknown20) == 0x20, "");
static_assert(offsetof(GfGameScene, unknown50) == 0x50, "");
static_assert(offsetof(GfGameScene, m_ownerBonus) == 0x52, "");
static_assert(offsetof(GfGameScene, unknown70) == 0x70, "");
static_assert(offsetof(GfGameScene, unknown118) == 0x118, "");
static_assert(offsetof(GfGameScene, m_questIdForTaskLog) == 0x11c, "");
static_assert(offsetof(GfGameScene, unknown120) == 0x120, "");
static_assert(offsetof(GfGameScene, unknown12c) == 0x12c, "");
static_assert(offsetof(GfGameScene, unknown130) == 0x130, "");
static_assert(offsetof(GfGameScene, m_forceEventBgm) == 0x134, "");
static_assert(offsetof(GfGameScene, m_deadType) == 0x13c, "");
static_assert(offsetof(GfGameScene, unknown144) == 0x144, "");
static_assert(offsetof(GfGameScene, unknown150) == 0x150, "");
static_assert(offsetof(GfGameScene, unknown160) == 0x160, "");
static_assert(offsetof(GfGameScene, m_autoBattle) == 0x1a8, "");
static_assert(offsetof(GfGameScene, unknown1ac) == 0x1ac, "");
static_assert(offsetof(GfGameScene, unknown1b8) == 0x1b8, "");
static_assert(offsetof(GfGameScene, unknown1bc) == 0x1bc, "");
static_assert(offsetof(GfGameScene, unknown1c0) == 0x1c0, "");
static_assert(offsetof(GfGameScene, unknown1c9) == 0x1c9, "");
static_assert(offsetof(GfGameScene, unknown1cc) == 0x1cc, "");
static_assert(offsetof(GfGameScene, unknown1d0) == 0x1d0, "");
static_assert(offsetof(GfGameScene, unknown1d8) == 0x1d8, "");
static_assert(offsetof(GfGameScene, unknown228) == 0x228, "");
static_assert(offsetof(GfGameScene, unknown240) == 0x240, "");
static_assert(offsetof(GfGameScene, unknown270) == 0x270, "");
static_assert(offsetof(GfGameScene, unknown280) == 0x280, "");
static_assert(offsetof(GfGameScene, unknown290) == 0x290, "");
static_assert(offsetof(GfGameScene, unknown2a0) == 0x2a0, "");
static_assert(offsetof(GfGameScene, unknown2b0) == 0x2b0, "");
static_assert(offsetof(GfGameScene, unknown3b0) == 0x3b0, "");
static_assert(offsetof(GfGameScene, unknown3f8) == 0x3f8, "");
static_assert(offsetof(GfGameScene, m_maskMainMenu) == 0x410, "");
static_assert(offsetof(GfGameScene, unknown418) == 0x418, "");
static_assert(offsetof(GfGameScene, unknown620) == 0x620, "");
static_assert(offsetof(GfGameScene, unknown628) == 0x628, "");
static_assert(offsetof(GfGameScene, unknown638) == 0x638, "");
static_assert(offsetof(GfGameScene, unknown648) == 0x648, "");
static_assert(offsetof(GfGameScene, unknown650) == 0x650, "");
static_assert(offsetof(GfGameScene, unknown668) == 0x668, "");
static_assert(offsetof(GfGameScene, unknown66c) == 0x66c, "");
static_assert(sizeof(GfGameScene) == 0x670, "");

} // namespace gf
