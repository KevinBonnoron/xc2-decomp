#include "gf/game/sequential_play/gf_play_command.h"

#include "bdat.h"
#include "fw/fw_update_info.h"
#include "gf/data/gf_bdat_id.h"
#include "gf/data/gf_data_bdat.h"
#include "gf/data/gf_data_event.h"
#include "gf/data/gf_data_util.h"
#include "gf/game/event/gf_game_event.h"
#include "gf/game/gf_game_manager.h"
#include "gf/game/gf_game_scene.h"
#include "gf/game/gf_game_state.h"
#include "gf/game/quest/gf_quest_task.h"
#include "gf/game/sequential_play/gf_play_factory.h"
#include "gf/game/sequential_play/gf_sequential_play.h"
#include "gf/gf_allocator.h"
#include "gf/menu/gf_menu_fade.h"
#include "gf/menu/gf_menu_kizunaring.h"
#include "gf/menu/gf_menu_manager.h"
#include "gf/request/gf_req_scom.h"
#include "gf/scom/gf_scom_script.h"
#include "gf/script/gf_script_manager.h"
#include "gmk/gmk_manager.h"
#include "mm_math/mm_col4.h"

namespace gf {

void GfPlayComPause::start() {
  if (pauseBits != 0) {
    GfSequentialPlay::pauseOn(pauseBits);
  } else {
    GfSequentialPlay::pauseOff();
  }
}

void GfPlayComPause::end() {}

bool GfPlayComPause::update(const fw::UpdateInfo &, bool) { return true; }

GfPlayComPause *GfPlayComPause::create(u32 pauseBits) {
  // __LINE__ must be 243 as in the original file: its value changes the instruction order.
#line 243
  return new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) GfPlayComPause(pauseBits);
}

void GfPlayComState::start() {
  if (state != 0) {
    GfSequentialPlay::execPushState(state);
  } else {
    GfSequentialPlay::execPopState();
  }
}

void GfPlayComState::end() {}

bool GfPlayComState::update(const fw::UpdateInfo &, bool) { return true; }

GfPlayComState *GfPlayComState::create(GF_STATE state, bool isSequence) {
  // __LINE__ must be 285 as in the original file: its value changes the instruction order.
#line 285
  GfPlayComState *command = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) GfPlayComState(state, isSequence);
  if (!isSequence || GfGameState::getStateReserve() == GF_STATE_CONTROL) {
    GfGameState::setStateReserve(state);
  }
  return command;
}

void GfPlayComWait::start() {}

void GfPlayComWait::end() {}

bool GfPlayComWait::update(const fw::UpdateInfo &info, bool isCancel) {
  if (isCancel) {
    return true;
  }
  time -= info.frameTime;
  return time <= 0.0f;
}

GfPlayComWait *GfPlayComWait::create(f32 time) {
  // __LINE__ must be 327 as in the original file: its value changes the instruction order.
#line 327
  return new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) GfPlayComWait(time);
}

GfPlayComEventPlayerStop::GfPlayComEventPlayerStop(bool isStop) : GfPlayCom(PCOMTYPE_PLAYER_STOP, true), isStop(isStop) {
  if (isStop && GfGameScene::get() != nullptr) {
    GfGameScene::get()->setEventPlayerStop(true);
  }
}

void GfPlayComEventPlayerStop::start() {
  if (!isStop && GfGameScene::get() != nullptr) {
    GfGameScene::get()->setEventPlayerStop(false);
  }
}

GfPlayComEventPlayerStop *GfPlayComEventPlayerStop::create(bool isStop) {
  // __LINE__ must be 548 as in the original file: its value changes the instruction order.
#line 548
  return new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) GfPlayComEventPlayerStop(isStop);
}

GfPlayComResetBladePlayerStop::GfPlayComResetBladePlayerStop(bool isStop) : GfPlayCom(PCOMTYPE_PLAYER_STOP, true), isStop(isStop) {
  if (isStop && GfGameScene::get() != nullptr) {
    GfGameScene::get()->setResetBladePlayerStop(true);
  }
}

void GfPlayComResetBladePlayerStop::start() {
  if (!isStop && GfGameScene::get() != nullptr) {
    GfGameScene::get()->setResetBladePlayerStop(false);
  }
}

GfPlayComResetBladePlayerStop *GfPlayComResetBladePlayerStop::create(bool isStop) {
  // __LINE__ must be 578 as in the original file: its value changes the instruction order.
#line 578
  return new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) GfPlayComResetBladePlayerStop(isStop);
}

int GfPlayComAfterEventScript::s_activate;

GfPlayComAfterEventScript::GfPlayComAfterEventScript(u32 event)
    : GfPlayCom(PCOMTYPE_AFTER_EVENT_SCRIPT, false), state(0), event(event), handle(reinterpret_cast<GF_SCOM_HANDLE *>(-1)) {
  s_activate++;
}

GfPlayComAfterEventScript::~GfPlayComAfterEventScript() { s_activate--; }

void GfPlayComAfterEventScript::start() {
  int startID = GfDataEvent::getEventAfterScriptStartID(event);
  const char *name = GfDataEvent::getEventAfterScriptName(event);
  if (name != nullptr && name[0] != '\0') {
    GfGameEvent::setAfterEventStartID(startID);
    handle = SCOM_SCRIPT::create(SCRIPT_SLOT_AFTER_EVENT, name, true);
  }
}

void GfPlayComAfterEventScript::end() { GfGameEvent::setAfterEventStartID(0); }

bool GfPlayComAfterEventScript::update(const fw::UpdateInfo &, bool isCancel) {
  if (isCancel) {
    SCOM_SCRIPT::create(SCRIPT_SLOT_AFTER_EVENT, nullptr, false);
    return true;
  }
  return !GfReqSmallCom::get()->isValid(handle);
}

GfPlayComAfterEventScript *GfPlayComAfterEventScript::create(u32 event) {
  if (GfGameManager::isAdvertize()) {
    GfMenuFade::setFade(1, 0, mm::Col4::black);
  }
  // __LINE__ must be 655 as in the original file: its value changes the instruction order.
#line 655
  return new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) GfPlayComAfterEventScript(event);
}

void GfPlayComCallbackEventSequence::start() { GfEvent::callEventPlay(isStart ? GEV_EVENT_SEQUENCE_START : GEV_EVENT_SEQUENCE_END, sequence); }

void GfPlayComCallbackEventSequence::end() {}

bool GfPlayComCallbackEventSequence::update(const fw::UpdateInfo &, bool) { return true; }

GfPlayComCallbackEventSequence *GfPlayComCallbackEventSequence::create(int sequence, bool isStart) {
  // __LINE__ must be 790 as in the original file: its value changes the instruction order.
#line 790
  return new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) GfPlayComCallbackEventSequence(sequence, isStart);
}

int GfPlayComOpenMenu::s_active;

GfPlayComOpenMenu::GfPlayComOpenMenu() : GfPlayCom(PCOMTYPE_OPEN_MENU, false) { s_active++; }

GfPlayComOpenMenu::~GfPlayComOpenMenu() { s_active--; }

void GfPlayComOpenMenu::start() { GfMenuManager::openMenu(menu); }

void GfPlayComOpenMenu::end() {}

bool GfPlayComOpenMenu::update(const fw::UpdateInfo &, bool isCancel) {
  bool isEnd = false;
  if (!GfMenuManager::isOpenFullScreen()) {
    isEnd = true;
  }
  if (isCancel && !isEnd) {
    GfMenuManager::closeFullScreen(true, true);
    isEnd = false;
  }
  return isEnd;
}

GfPlayComOpenMenu *GfPlayComOpenMenu::create(u32 menu) {
  // __LINE__ must be 845 as in the original file: its value changes the instruction order.
#line 845
  GfPlayComOpenMenu *command = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) GfPlayComOpenMenu();
  command->menu = menu;
  return command;
}

void GfPlayComOpenMenu2::start() { waitCount = 3; }

void GfPlayComOpenMenu2::end() {
  if (gmk::GmkManager::get() != nullptr) {
    gmk::GmkManager::get()->updateImmediate();
  }
}

bool GfPlayComOpenMenu2::update(const fw::UpdateInfo &, bool isCancel) {
  switch (state) {
  case 0:
    if (--waitCount <= 0) {
      if (GfSequentialPlay::isSequenceSpecialAction()) {
        return true;
      }
      switch (menu) {
      case MAINMENU_SYSTEM:
        GfMenuManager::setMainmenuOpenSystem();
        break;
      case MAINMENU_SKIP_TRAVEL:
        GfMenuManager::setMainmenuOpenMap();
        break;
      default:
        break;
      }
      GfMenuManager::openFullScreen(1, true, true);
      state = 1;
      return false;
    }
    break;
  case 1:
    bool isEnd = false;
    if (!GfMenuManager::isOpenFullScreen()) {
      isEnd = true;
    }
    if (isCancel && !isEnd) {
      GfMenuManager::closeFullScreen(true, true);
      isEnd = false;
    }
    return isEnd;
  }
  return false;
}

GfPlayComOpenMenu2 *GfPlayComOpenMenu2::create(u32 type, MAINMENU menu) {
  // __LINE__ must be 921 as in the original file: its value changes the instruction order.
#line 921
  return new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) GfPlayComOpenMenu2(type, menu);
}

int GfPlayComStartTutorial::s_activateCount;

void GfPlayComStartTutorial::start() {
  u8 *bdat = GfDataBdat::getFP(BDAT_MNU_TUTORIAL);
  if (bdat != nullptr && static_cast<int>(tutorial) >= Bdat::getIdTop(bdat) &&
      static_cast<int>(tutorial) - Bdat::getIdTop(bdat) < Bdat::getIdCount(bdat)) {
    GfScriptManager::loadScript(SCRIPT_SLOT_TUTORIAL, Bdat::getVal(bdat, "script_file", tutorial).valueString);
    GfScriptManager::startScript(SCRIPT_SLOT_TUTORIAL);
    s_activateCount++;
  }
}

void GfPlayComStartTutorial::end() { s_activateCount--; }

bool GfPlayComStartTutorial::update(const fw::UpdateInfo &, bool) { return GfScriptManager::isScriptFinish(SCRIPT_SLOT_TUTORIAL); }

GfPlayComStartTutorial *GfPlayComStartTutorial::create(u32 tutorial) {
  // __LINE__ must be 973 as in the original file: its value changes the instruction order.
#line 973
  return new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) GfPlayComStartTutorial(tutorial);
}

void GfPlayComMiniGame::start() { GfMenuManager::openFullScreen(4, true, true); }

void GfPlayComMiniGame::end() {}

bool GfPlayComMiniGame::update(const fw::UpdateInfo &, bool isCancel) {
  bool isEnd = false;
  if (!GfMenuManager::isOpenFullScreen()) {
    isEnd = true;
  }
  if (isCancel && !isEnd) {
    GfMenuManager::closeFullScreen(true, true);
    isEnd = false;
  }
  return isEnd;
}

GfPlayComMiniGame *GfPlayComMiniGame::create() {
  // __LINE__ must be 1016 as in the original file: its value changes the instruction order.
#line 1016
  return new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) GfPlayComMiniGame();
}

bool GfPlayComMenuChapterSave::s_bExist;

void GfPlayComMenuChapterSave::start() {
  GfDataUtil::setChapterSave(chapter, GfDataUtil::getScenarioFlag());
  isOpen = false;
}

void GfPlayComMenuChapterSave::end() {
  GfPlayFactory::createOneEvent(chapter);
  s_bExist = false;
}

bool GfPlayComMenuChapterSave::update(const fw::UpdateInfo &, bool) {
  if (!isOpen) {
    GfMenuManager::openSave();
    isOpen = true;
    return false;
  }
  return !GfMenuManager::isOpenFullScreen();
}

bool GfPlayComMenuChapterSave::isDisp() { return s_bExist; }

GfPlayComMenuChapterSave *GfPlayComMenuChapterSave::create(u32 chapter) {
  // __LINE__ must be 1100 as in the original file: its value changes the instruction order.
#line 1100
  GfPlayComMenuChapterSave *command = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) GfPlayComMenuChapterSave(chapter);
  s_bExist = true;
  return command;
}

int GfPlayComMenuChapter::s_activate;

GfPlayComMenuChapter::GfPlayComMenuChapter(u32 chapter) : GfPlayCom(PCOMTYPE_MENU_CHAPTER, false), chapter(chapter) { s_activate++; }

GfPlayComMenuChapter::~GfPlayComMenuChapter() { s_activate--; }

void GfPlayComMenuChapter::start() { GfMenuManager::openChapterTelop(chapter); }

void GfPlayComMenuChapter::end() {}

bool GfPlayComMenuChapter::update(const fw::UpdateInfo &, bool) { return !GfMenuManager::isOpenChapterTelop(); }

GfPlayComMenuChapter *GfPlayComMenuChapter::create(u32 chapter) {
  // __LINE__ must be 1149 as in the original file: its value changes the instruction order.
#line 1149
  return new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) GfPlayComMenuChapter(chapter);
}

int GfPlayComMenuChapterEnd::s_activate;

GfPlayComMenuChapterEnd::GfPlayComMenuChapterEnd(u32 chapter) : GfPlayCom(PCOMTYPE_MENU_CHAPTER_END, false), chapter(chapter) { s_activate++; }

GfPlayComMenuChapterEnd::~GfPlayComMenuChapterEnd() { s_activate--; }

void GfPlayComMenuChapterEnd::start() { GfMenuManager::openChapterEndTelop(chapter); }

void GfPlayComMenuChapterEnd::end() {}

bool GfPlayComMenuChapterEnd::update(const fw::UpdateInfo &, bool) { return !GfMenuManager::isOpenChapterTelop(); }

GfPlayComMenuChapterEnd *GfPlayComMenuChapterEnd::create(u32 chapter) {
  // __LINE__ must be 1197 as in the original file: its value changes the instruction order.
#line 1197
  return new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) GfPlayComMenuChapterEnd(chapter);
}

int GfPlayComMenuZone::s_activate;

GfPlayComMenuZone::GfPlayComMenuZone(u32 zone) : GfPlayCom(PCOMTYPE_MENU_ZONE, false), zone(zone) { s_activate++; }

GfPlayComMenuZone::~GfPlayComMenuZone() { s_activate--; }

void GfPlayComMenuZone::start() {
  GfMenuManager::openZoneTelop(zone);
  time = 10.0f;
}

void GfPlayComMenuZone::end() {}

bool GfPlayComMenuZone::update(const fw::UpdateInfo &info, bool) {
  time -= info.deltaTime;
  if (time <= 0.0f) {
    return true;
  }
  return !GfMenuManager::isOpenZoneTelop();
}

GfPlayComMenuZone *GfPlayComMenuZone::create(u32 zone) {
  // __LINE__ must be 1253 as in the original file: its value changes the instruction order.
#line 1253
  return new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) GfPlayComMenuZone(zone);
}

int GfPlayComMenuDummyTutorial::s_activate;

GfPlayComMenuDummyTutorial::GfPlayComMenuDummyTutorial(u32 tutorial) : GfPlayCom(PCOMTYPE_MENU_DUMMY_TUTORIAL, false), tutorial(tutorial) {
  s_activate++;
}

GfPlayComMenuDummyTutorial::~GfPlayComMenuDummyTutorial() { s_activate--; }

void GfPlayComMenuDummyTutorial::start() { GfMenuManager::openDummyTutorial(tutorial); }

void GfPlayComMenuDummyTutorial::end() {}

bool GfPlayComMenuDummyTutorial::update(const fw::UpdateInfo &, bool) { return !GfMenuManager::isOpenDummyTutorial(); }

GfPlayComMenuDummyTutorial *GfPlayComMenuDummyTutorial::create(u32 tutorial) {
  // __LINE__ must be 1297 as in the original file: its value changes the instruction order.
#line 1297
  return new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) GfPlayComMenuDummyTutorial(tutorial);
}

void GfPlayComMenuQuestList::start() { GfMenuManager::openFullScreen(1, true, true); }

void GfPlayComMenuQuestList::end() {}

bool GfPlayComMenuQuestList::update(const fw::UpdateInfo &, bool isCancel) {
  bool isEnd = false;
  if (!GfMenuManager::isOpenFullScreen()) {
    isEnd = true;
  }
  if (isCancel && !isEnd) {
    GfMenuManager::closeFullScreen(true, true);
    isEnd = false;
  }
  return isEnd;
}

GfPlayComMenuQuestList *GfPlayComMenuQuestList::create() {
  // __LINE__ must be 1337 as in the original file: its value changes the instruction order.
#line 1337
  return new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) GfPlayComMenuQuestList();
}

void GfPlayComMenuKizunaring::start() { GfMenuKizunaring::openMenu(blade); }

void GfPlayComMenuKizunaring::end() {}

bool GfPlayComMenuKizunaring::update(const fw::UpdateInfo &, bool isCancel) {
  bool isEnd = false;
  if (!GfMenuKizunaring::isOpenMenu()) {
    isEnd = true;
  }
  if (isCancel && !isEnd) {
    GfMenuKizunaring::closeMenu();
    isEnd = true;
  }
  return isEnd;
}

GfPlayComMenuKizunaring *GfPlayComMenuKizunaring::create(u32 blade) {
  // __LINE__ must be 1378 as in the original file: its value changes the instruction order.
#line 1378
  return new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) GfPlayComMenuKizunaring(blade);
}

int GfPlayComMenuPrecious::s_activate;

GfPlayComMenuPrecious::GfPlayComMenuPrecious(u32 item) : GfPlayCom(PCOMTYPE_MENU_PRECIOUS, false), item(item) { s_activate++; }

GfPlayComMenuPrecious::~GfPlayComMenuPrecious() { s_activate--; }

void GfPlayComMenuPrecious::start() { GfMenuManager::openPreciousWindow(item); }

void GfPlayComMenuPrecious::end() {}

bool GfPlayComMenuPrecious::update(const fw::UpdateInfo &, bool) { return !GfMenuManager::isOpenPreciousWindow(); }

GfPlayComMenuPrecious *GfPlayComMenuPrecious::create(u32 item) {
  // __LINE__ must be 1428 as in the original file: its value changes the instruction order.
#line 1428
  return new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) GfPlayComMenuPrecious(item);
}

bool GfPlayComWaitPlayerToStartGmkTuto::update(const fw::UpdateInfo &info, bool isCancel) {
  if (isCancel) {
    return true;
  }
  time += info.deltaTime;
  if (GfGameManager::isGmkTutorialMoverOK()) {
    return true;
  }
  return time > 10.0f;
}

GfPlayComWaitPlayerToStartGmkTuto *GfPlayComWaitPlayerToStartGmkTuto::create() {
  // __LINE__ must be 2009 as in the original file: its value changes the instruction order.
#line 2009
  return new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) GfPlayComWaitPlayerToStartGmkTuto();
}

GfPlayComGimmickTaskComplete::GfPlayComGimmickTaskComplete(gmk::GmkType gmkType, u32 gimmick, f32 time)
    : GfPlayCom(PCOMTYPE_QUEST_COMPLETE_UI, false), gmkType(gmkType), gimmick(gimmick), time(time) {}

bool GfPlayComGimmickTaskComplete::update(const fw::UpdateInfo &info, bool) {
  time -= info.deltaTime;
  if (time > 0.0f) {
    return false;
  }
  GfQuestTask::completeGimmickTask(gmkType, gimmick);
  return true;
}

GfPlayComGimmickTaskComplete *GfPlayComGimmickTaskComplete::create(gmk::GmkType gmkType, u32 gimmick, f32 time) {
  // __LINE__ must be 2596 as in the original file: its value changes the instruction order.
#line 2596
  return new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) GfPlayComGimmickTaskComplete(gmkType, gimmick, time);
}

GfPlayComExecuteSignal::GfPlayComExecuteSignal(bool isStart, GfSequentialPlaySignal *signal)
    : GfPlayCom(PCOMTYPE_EXECUTE_SIGNAL, true), isStart(isStart), signal(signal) {
  if (isStart) {
    signal->isActive = true;
  }
}

void GfPlayComExecuteSignal::start() {
  if (!isStart) {
    signal->isActive = false;
  }
}

GfPlayComExecuteSignal *GfPlayComExecuteSignal::create(bool isStart, GfSequentialPlaySignal *signal) {
  if (signal == nullptr) {
    return nullptr;
  }
  // __LINE__ must be 2722 as in the original file: its value changes the instruction order.
#line 2722
  return new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) GfPlayComExecuteSignal(isStart, signal);
}

} // namespace gf
