#pragma once
#include "gf/event/gf_event.h"
#include "gf/game/quest/gf_quest_info.h"
#include "gf/game/sequential_play/gf_play_factory.h"
#include "gmk/gmk_manager.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace fw {
struct UpdateInfo;
}

namespace gf {

struct GF_OBJ_HANDLE;
struct GfMapjumpInfo;
struct GfSetupParam;
struct GfSetupPfTalk;
struct MenuCommonWindowParam;
struct QuestID;
class GfPlayCom;
struct GfSequentialPlaySignal;
struct ParamReturnTitle;

class GfSequentialPlay : public mm::mtl::PtrSingleton<GfSequentialPlay> {
public:
  enum TYPE {
    TYPE_NORMAL,
    TYPE_SEQUENCE,
  };

  static void build(const GfSetupParam &param);
  static void destroy();
  static bool isPlay();
  static void postUpdate(const fw::UpdateInfo &info);
  static bool play();
  static void beginCommand(TYPE type);
  static void addCommand(GfPlayCom *command);
  static void pauseOn(u32 pauseBits);
  static void pauseOff();
  static void execPushState(GF_STATE state);
  static void execPopState();
  static void addWait(f32 time);
  static void addWaitEvent(f32 time, GF_OBJ_HANDLE *handle);
  static void addMapjump(const GfMapjumpInfo &info);
  static void addWaitBattleEnd(u32 battle);
  static void addEventPlayerStop(bool isStop);
  static void addResetBladePlayerStop(bool isStop);
  static void addAfterEventScript(u32 event);
  static void pushPause(u32 pauseBits);
  static void popPause();
  static void pushState(GF_STATE state);
  static void popState();
  static void addEventFade();
  static void addEvent(int event, u32 param0, u32 param1, bool isEndFadeOut);
  static void addEvent(const char *name, u32 param0, u32 param1, bool isEndFadeOut);
  static void addCallbackEventSequence(int sequence, bool isStart);
  static void addMenuKizunaring(u32 blade);
  static void addMenuPrecious(u32 item);
  static int addMenuCommon(u32 window);
  static int addMenuCommon(const MenuCommonWindowParam &param);
  static void addMenuChapterSave(u32 chapter);
  static void addMenuChapter(u32 chapter);
  static void addMenuChapterEnd(u32 chapter);
  static void addMenuZone(u32 zone);
  static void addMenuDummyTutorial(u32 tutorial);
  static void addOpenMenu(u32 type);
  static void addOpenMenu2(u32 type, MAINMENU menu);
  static void addStartTutorial(u32 tutorial);
  static void addMiniGame();
  static void addReturnTitle(const ParamReturnTitle &param);
  static void addBattleStart(bool isStart);
  static void addBattleStartEnd();
  static void addMenuQuestList();
  static void addSalvage(GF_OBJ_HANDLE *handle);
  static void addCollect(GF_OBJ_HANDLE *handle);
  static void addFieldTbox(GF_OBJ_HANDLE *handle);
  static void addMapGimmick(GF_OBJ_HANDLE *handle);
  static void addGrave(GF_OBJ_HANDLE *handle);
  static void addJump(GF_OBJ_HANDLE *handle);
  static void addWarp(GF_OBJ_HANDLE *handle);
  static void addWaitPlayerToStartGmkTuto();
  static void addGmkTutorial(const char *name, u32 tutorial);
  static void addPlayerDead(GfPlayerDead dead);
  static void addTalk(const GfSetupPfTalk &talk);
  static void addQuestUIOrder(QuestID quest, bool isForce);
  static void addQuestUIComplete(QuestID quest, QuestID child, QSTATE state);
  static void addGimmickTaskComplete(gmk::GmkType type, u32 task, f32 time);
  static void addChainAttack();
  static void addArtsMovie(const char *name);
  static void addResetBlade(u32 partyId, int blade);
  static void addMoverSwitch();
  static void addHoodHomuraBattou();
  static bool isInnerState(GF_STATE state);
  static bool isExistResetBladeParty(u32 partyId);
  static bool isSequenceSpecialAction();
  static bool isInnerPause(u32 pauseBits);
  static void startSignal(GfSequentialPlaySignal *signal);
  static void endSignal(GfSequentialPlaySignal *signal);
  bool isExistEvent(u32 event) const;
};

} // namespace gf
