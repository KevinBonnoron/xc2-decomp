#pragma once
#include "gf/game/quest/gf_quest_info.h"
#include "gf/menu/object/gf_menu_obj_common_text.h"
#include "gmk/gmk_manager.h"
#include "mm_mtl/intrusive_ptr.h"
#include "types.h"

namespace fw {
class Camera;
} // namespace fw

namespace gf {

struct GF_OBJ_HANDLE;
struct GfMapjumpInfo;
struct GfSequentialPlaySignal;
struct GfSetupPfTalk;
struct MenuCommonWindowParam;
struct ParamReturnTitle;
struct QuestID;

enum MAINMENU {
  MAINMENU_TOP,
  MAINMENU_SYSTEM,
  MAINMENU_SKIP_TRAVEL,
};

enum GfPlayerDead {
  PLAYER_DEAD_NONE,
  PLAYER_DEAD_GAME_OVER,
};

class GfPlayFactory {
public:
  static bool createReturnTitle(const ParamReturnTitle &param);
  static bool createOpenMenu(u32 type, GfSequentialPlaySignal *signal);
  static bool createOpenMenu2(u32 type, MAINMENU menu, GfSequentialPlaySignal *signal);
  static bool createStartTutorial(u32 tutorial, GfSequentialPlaySignal *signal);
  static void createMiniGame();
  static bool createMenuQuestList();
  static bool createMenuKizunaring(u32 blade);
  static bool createMenuObjCommonText(GfMenuObjCommonText::OpenKizunaParam &param);
  static bool createSalvage(GF_OBJ_HANDLE *handle);
  static bool createCollect(GF_OBJ_HANDLE *handle);
  static bool createMapGimmick(GF_OBJ_HANDLE *handle);
  static bool createGrave(GF_OBJ_HANDLE *handle);
  static bool createJump(GF_OBJ_HANDLE *handle);
  static bool createWarp(GF_OBJ_HANDLE *handle);
  static bool createGmkTutorial(const char *name, u32 tutorial);
  static bool createGmkCamera(mm::mtl::IntrusivePtr<fw::Camera> camera);
  static bool createPlayerDead(GfPlayerDead dead);
  static bool createGameOver();
  static bool createTalk(const GfSetupPfTalk &talk);
  static void createMapjump(const GfMapjumpInfo &info);
  static bool createEventMapjump(const GfMapjumpInfo &info);
  static bool createOneEventForGimmick(u32 event);
  static bool createOneEvent(u32 event);
  static bool createBlEvent(u32 event, u32 param0, u32 param1, GfSequentialPlaySignal *signal);
  static bool createTheaterEvent(int event);
  static bool createReserveEvent(const char *name);
  static bool createEventAfterScript(int event);
  static bool createOneEvent(const char *name);
  static bool createQuestUIOrder(QuestID quest, bool isEntry, bool isForce);
  static bool createQuestUIComplete(QuestID quest, QuestID child, QSTATE state);
  static bool createQuestUIComplete(QuestID quest);
  static bool createMenuPrecious(u32 item, bool isSequence);
  static bool createEventWait(f32 time, GF_OBJ_HANDLE *handle);
  static int createCommonMessage(u32 window);
  static int createCommonMessage(const MenuCommonWindowParam &param);
  static bool isDispCommonMessage(u32 window);
  static u32 getDispCommonMessage(u32 window);
  static void createOpenChapterSave(u32 chapter);
  static bool isDispChapterSave();
  static void createOpenZoneUI(u32 zone);
  static void createOpenChapterUI(u32 chapter);
  static void createOpenChapterEndUI(u32 chapter);
  static void createOpenDummyTutorial(u32 tutorial);
  static void createBattleStart(bool isStart);
  static void createGimmickTaskComplete(gmk::GmkType type, u32 task, f32 time);
  static bool createChainAttack();
  static bool createArtsMovie(const char *name);
  static void createSkipTravel(u32 mapjump);
  static bool createResetBladeForBattleEnd(u32 partyId, int blade, bool isPlayerStop);
  static bool createResetBladeForBladeSwitch(u32 partyId, int blade);
  static void createHomuraHikariCurrent(u32 partyId, int blade);
  static void createMoverSwitch();
  static void createHoodHomuraBattou();
};

} // namespace gf
