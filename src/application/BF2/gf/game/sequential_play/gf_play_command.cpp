#include "gf/game/sequential_play/gf_play_command.h"

#include "bdat.h"
#include "fw/fw_camera.h"
#include "fw/fw_update_info.h"
#include "gf/data/gf_bdat_id.h"
#include "gf/data/gf_bdat_quest.h"
#include "gf/data/gf_data_bdat.h"
#include "gf/data/gf_data_event.h"
#include "gf/data/gf_data_param_acc.h"
#include "gf/data/gf_data_util.h"
#include "gf/field/gf_field_collect.h"
#include "gf/field/gf_field_map_gimmick.h"
#include "gf/field/gf_field_tbox.h"
#include "gf/game/achiev/gf_achiev_manager.h"
#include "gf/game/event/gf_game_event.h"
#include "gf/game/gf_game_arts_movie.h"
#include "gf/game/gf_game_chain_attack.h"
#include "gf/game/gf_game_manager.h"
#include "gf/game/gf_game_obj.h"
#include "gf/game/gf_game_party.h"
#include "gf/game/gf_game_scene.h"
#include "gf/game/gf_game_speed.h"
#include "gf/game/gf_game_state.h"
#include "gf/game/gf_game_util.h"
#include "gf/game/gf_game_voice.h"
#include "gf/game/quest/gf_quest_event.h"
#include "gf/game/quest/gf_quest_info.h"
#include "gf/game/quest/gf_quest_manager.h"
#include "gf/game/quest/gf_quest_task.h"
#include "gf/game/quest/gf_quest_util.h"
#include "gf/game/salvage/gf_game_salvage.h"
#include "gf/game/sequential_play/gf_play_factory.h"
#include "gf/game/sequential_play/gf_sequential_play.h"
#include "gf/gf_allocator.h"
#include "gf/gf_pause.h"
#include "gf/menu/call/gf_menu_call_context.h"
#include "gf/menu/gf_menu_fade.h"
#include "gf/menu/gf_menu_kizunaring.h"
#include "gf/menu/gf_menu_manager.h"
#include "gf/menu/object/gf_menu_obj_popup.h"
#include "gf/menu/object/gf_menu_obj_quest_log.h"
#include "gf/object/gf_obj_acc.h"
#include "gf/object/gf_obj_handle.h"
#include "gf/object/gf_obj_setup.h"
#include "gf/object/gf_obj_util.h"
#include "gf/request/gf_req_manager.h"
#include "gf/request/gf_req_scom.h"
#include "gf/scom/gf_scom_fade.h"
#include "gf/scom/gf_scom_script.h"
#include "gf/script/gf_script_manager.h"
#include "gmk/gmk_manager.h"
#include "mm_math/mm_col4.h"
#include "mm_mtl/fixed_queue.h"
#include "mm_mtl/reference_object.h"

namespace gf {

const mm::mtl::RTTI *GfPlayCom::getRTTI() const { return &m_rtti; }

void GfPlayCom::start() {}

void GfPlayComPause::start() {
  if (unknown10 != 0) {
    GfSequentialPlay::pauseOn(unknown10);
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
  if (unknown10 != 0) {
    GfSequentialPlay::execPushState(unknown10);
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
  unknown10 -= info.unknown00;
  return unknown10 <= 0.0f;
}

GfPlayComWait *GfPlayComWait::create(f32 time) {
  // __LINE__ must be 327 as in the original file: its value changes the instruction order.
#line 327
  return new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) GfPlayComWait(time);
}

void GfPlayComWaitEvent::start() { unknown20 = GfReqCommand::reqWaitEvent(unknown10, unknown18); }

bool GfPlayComWaitEvent::update(const fw::UpdateInfo &, bool isCancel) {
  for (u32 partyId = 0; partyId < 3; partyId++) {
    DataParamAcc acc(GfGameParty::getHandleDriver(partyId));
    if (acc.isValid() && acc.getHp() == 0) {
      GfGameUtil::setHp(acc.unknown10, 1);
    }
  }
  return !GfReqManager::isValid(unknown20);
}

GfPlayComWaitEvent *GfPlayComWaitEvent::create(f32 time, GF_OBJ_HANDLE *handle) {
  // __LINE__ must be 385 as in the original file: its value changes the instruction order.
#line 385
  return new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) GfPlayComWaitEvent(time, handle);
}

int GfPlayComWaitBattleEnd::s_activate;

void GfPlayComWaitBattleEnd::start() {
  if (GfGameScene::get() != nullptr) {
    GfGameScene::get()->setForceStopBattle(true);
  }
  unknown14 = 0.0f;
  s_activate++;
}

void GfPlayComWaitBattleEnd::end() {
  if (GfGameScene::get() != nullptr) {
    GfGameScene::get()->setForceStopBattle(false);
  }
  s_activate--;
}

GfPlayComWaitBattleEnd *GfPlayComWaitBattleEnd::create(u32 battle) {
  // __LINE__ must be 518 as in the original file: its value changes the instruction order.
#line 518
  return new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) GfPlayComWaitBattleEnd(battle);
}

int GfPlayComEvent::m_activate;

GfPlayComEvent::GfPlayComEvent(u32 event, u32 param0, u32 param1, bool isEndFadeOut)
    : GfPlayCom(PCOMTYPE_EVENT, false), unknown18(event), unknown1c(param0), unknown20(param1), unknown24(isEndFadeOut), unknown25(false), unknown26(false) {
  m_activate++;
  GfObjAcc leaderAcc(GfGameManager::getPartyLeaderDriver());
  unknown26 = leaderAcc.isBattle();
  if (!unknown26) {
    unknown26 = GfGameManager::isExistBossEnemy();
  }
  if (unknown26 && GfGameScene::get() != nullptr) {
    GfGameScene::get()->unknown648 = true;
  }
}

GfPlayComEvent::~GfPlayComEvent() { m_activate--; }

void GfPlayComEvent::start() {
  GfEvent::addEventCallback(this);
  GfGameEvent::setAfterEventStartID(0);
  GfGameEvent::play(unknown18, unknown1c, unknown20, unknown24);
}

void GfPlayComEvent::end() { GfEvent::removeEventCallback(this); }

bool GfPlayComEvent::update(const fw::UpdateInfo &, bool isCancel) {
  if (isCancel) {
    return true;
  }
  if (GfGameEvent::isPlaying()) {
    if (GfPlayComPlayerDead::get() != nullptr) {
      GfPlayComPlayerDead::get()->unknown3a = true;
    }
    return false;
  }
  return true;
}

void GfPlayComEvent::gevPlayEvent(GEV event, u32) {
  if (event == GEV_EVENT_END) {
    unknown25 = true;
  }
}

GfPlayComEvent *GfPlayComEvent::create(u32 event, u32 param0, u32 param1, bool isEndFadeOut) {
  // __LINE__ must be 752 as in the original file: its value changes the instruction order.
#line 752
  return new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) GfPlayComEvent(event, param0, param1, isEndFadeOut);
}

GfPlayComEvent *GfPlayComEvent::create(const char *name, u32 param0, u32 param1, bool isEndFadeOut) { return create(GfDataEvent::getEventID(name), param0, param1, isEndFadeOut); }

GfPlayComEventPlayerStop::GfPlayComEventPlayerStop(bool isStop) : GfPlayCom(PCOMTYPE_PLAYER_STOP, true), unknown10(isStop) {
  if (unknown10 && GfGameScene::get() != nullptr) {
    GfGameScene::get()->setEventPlayerStop(true);
  }
}

void GfPlayComEventPlayerStop::start() {
  if (!unknown10 && GfGameScene::get() != nullptr) {
    GfGameScene::get()->setEventPlayerStop(false);
  }
}

GfPlayComEventPlayerStop *GfPlayComEventPlayerStop::create(bool isStop) {
  // __LINE__ must be 548 as in the original file: its value changes the instruction order.
#line 548
  return new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) GfPlayComEventPlayerStop(isStop);
}

GfPlayComResetBladePlayerStop::GfPlayComResetBladePlayerStop(bool isStop) : GfPlayCom(PCOMTYPE_PLAYER_STOP, true), unknown10(isStop) {
  if (unknown10 && GfGameScene::get() != nullptr) {
    GfGameScene::get()->setResetBladePlayerStop(true);
  }
}

void GfPlayComResetBladePlayerStop::start() {
  if (!unknown10 && GfGameScene::get() != nullptr) {
    GfGameScene::get()->setResetBladePlayerStop(false);
  }
}

GfPlayComResetBladePlayerStop *GfPlayComResetBladePlayerStop::create(bool isStop) {
  // __LINE__ must be 578 as in the original file: its value changes the instruction order.
#line 578
  return new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) GfPlayComResetBladePlayerStop(isStop);
}

int GfPlayComAfterEventScript::s_activate;

GfPlayComAfterEventScript::GfPlayComAfterEventScript(u32 event) : GfPlayCom(PCOMTYPE_AFTER_EVENT_SCRIPT, false), unknown10(0), unknown14(event), unknown18(reinterpret_cast<GF_SCOM_HANDLE *>(-1)) {
  s_activate++;
}

GfPlayComAfterEventScript::~GfPlayComAfterEventScript() { s_activate--; }

void GfPlayComAfterEventScript::start() {
  int startID = GfDataEvent::getEventAfterScriptStartID(unknown14);
  const char *name = GfDataEvent::getEventAfterScriptName(unknown14);
  if (name != nullptr && name[0] != '\0') {
    GfGameEvent::setAfterEventStartID(startID);
    unknown18 = SCOM_SCRIPT::create(SCRIPT_SLOT_AFTER_EVENT, name, true);
  }
}

void GfPlayComAfterEventScript::end() { GfGameEvent::setAfterEventStartID(0); }

bool GfPlayComAfterEventScript::update(const fw::UpdateInfo &, bool isCancel) {
  if (isCancel) {
    SCOM_SCRIPT::create(SCRIPT_SLOT_AFTER_EVENT, nullptr, false);
    return true;
  }
  return !GfReqSmallCom::get()->isValid(unknown18);
}

GfPlayComAfterEventScript *GfPlayComAfterEventScript::create(u32 event) {
  if (GfGameManager::isAdvertize()) {
    GfMenuFade::setFade(1, 0, mm::Col4::black);
  }
  // __LINE__ must be 655 as in the original file: its value changes the instruction order.
#line 655
  return new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) GfPlayComAfterEventScript(event);
}

void GfPlayComCallbackEventSequence::start() { GfEvent::callEventPlay(unknown14 ? GEV_EVENT_SEQUENCE_START : GEV_EVENT_SEQUENCE_END, unknown10); }

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

void GfPlayComOpenMenu::start() { GfMenuManager::openMenu(unknown10); }

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
  command->unknown10 = menu;
  return command;
}

void GfPlayComOpenMenu2::start() { unknown1c = 3; }

void GfPlayComOpenMenu2::end() {
  if (gmk::GmkManager::get() != nullptr) {
    gmk::GmkManager::get()->updateImmediate();
  }
}

bool GfPlayComOpenMenu2::update(const fw::UpdateInfo &, bool isCancel) {
  switch (unknown18) {
  case 0:
    if (--unknown1c <= 0) {
      if (GfSequentialPlay::isSequenceSpecialAction()) {
        return true;
      }
      switch (unknown14) {
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
      unknown18 = 1;
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
  if (bdat != nullptr && static_cast<int>(unknown10) >= Bdat::getIdTop(bdat) && static_cast<int>(unknown10) - Bdat::getIdTop(bdat) < Bdat::getIdCount(bdat)) {
    GfScriptManager::loadScript(SCRIPT_SLOT_TUTORIAL, Bdat::getVal(bdat, "script_file", unknown10).valueString);
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
  GfDataUtil::setChapterSave(unknown10, GfDataUtil::getScenarioFlag());
  unknown14 = false;
}

void GfPlayComMenuChapterSave::end() {
  GfPlayFactory::createOneEvent(unknown10);
  s_bExist = false;
}

bool GfPlayComMenuChapterSave::update(const fw::UpdateInfo &, bool) {
  if (!unknown14) {
    GfMenuManager::openSave();
    unknown14 = true;
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

GfPlayComMenuChapter::GfPlayComMenuChapter(u32 chapter) : GfPlayCom(PCOMTYPE_MENU_CHAPTER, false), unknown10(chapter) { s_activate++; }

GfPlayComMenuChapter::~GfPlayComMenuChapter() { s_activate--; }

void GfPlayComMenuChapter::start() { GfMenuManager::openChapterTelop(unknown10); }

void GfPlayComMenuChapter::end() {}

bool GfPlayComMenuChapter::update(const fw::UpdateInfo &, bool) { return !GfMenuManager::isOpenChapterTelop(); }

GfPlayComMenuChapter *GfPlayComMenuChapter::create(u32 chapter) {
  // __LINE__ must be 1149 as in the original file: its value changes the instruction order.
#line 1149
  return new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) GfPlayComMenuChapter(chapter);
}

int GfPlayComMenuChapterEnd::s_activate;

GfPlayComMenuChapterEnd::GfPlayComMenuChapterEnd(u32 chapter) : GfPlayCom(PCOMTYPE_MENU_CHAPTER_END, false), unknown10(chapter) { s_activate++; }

GfPlayComMenuChapterEnd::~GfPlayComMenuChapterEnd() { s_activate--; }

void GfPlayComMenuChapterEnd::start() { GfMenuManager::openChapterEndTelop(unknown10); }

void GfPlayComMenuChapterEnd::end() {}

bool GfPlayComMenuChapterEnd::update(const fw::UpdateInfo &, bool) { return !GfMenuManager::isOpenChapterTelop(); }

GfPlayComMenuChapterEnd *GfPlayComMenuChapterEnd::create(u32 chapter) {
  // __LINE__ must be 1197 as in the original file: its value changes the instruction order.
#line 1197
  return new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) GfPlayComMenuChapterEnd(chapter);
}

int GfPlayComMenuZone::s_activate;

GfPlayComMenuZone::GfPlayComMenuZone(u32 zone) : GfPlayCom(PCOMTYPE_MENU_ZONE, false), unknown10(zone) { s_activate++; }

GfPlayComMenuZone::~GfPlayComMenuZone() { s_activate--; }

void GfPlayComMenuZone::start() {
  GfMenuManager::openZoneTelop(unknown10);
  unknown14 = 10.0f;
}

void GfPlayComMenuZone::end() {}

bool GfPlayComMenuZone::update(const fw::UpdateInfo &info, bool) {
  unknown14 -= info.unknown04;
  if (unknown14 <= 0.0f) {
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

GfPlayComMenuDummyTutorial::GfPlayComMenuDummyTutorial(u32 tutorial) : GfPlayCom(PCOMTYPE_MENU_DUMMY_TUTORIAL, false), unknown10(tutorial) { s_activate++; }

GfPlayComMenuDummyTutorial::~GfPlayComMenuDummyTutorial() { s_activate--; }

void GfPlayComMenuDummyTutorial::start() { GfMenuManager::openDummyTutorial(unknown10); }

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

void GfPlayComMenuKizunaring::start() { GfMenuKizunaring::openMenu(unknown10); }

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

GfPlayComMenuPrecious::GfPlayComMenuPrecious(u32 item) : GfPlayCom(PCOMTYPE_MENU_PRECIOUS, false), unknown10(item) { s_activate++; }

GfPlayComMenuPrecious::~GfPlayComMenuPrecious() { s_activate--; }

void GfPlayComMenuPrecious::start() { GfMenuManager::openPreciousWindow(unknown10); }

void GfPlayComMenuPrecious::end() {}

bool GfPlayComMenuPrecious::update(const fw::UpdateInfo &, bool) { return !GfMenuManager::isOpenPreciousWindow(); }

GfPlayComMenuPrecious *GfPlayComMenuPrecious::create(u32 item) {
  // __LINE__ must be 1428 as in the original file: its value changes the instruction order.
#line 1428
  return new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) GfPlayComMenuPrecious(item);
}

mm::mtl::FixedQueue<u32, 32> GfPlayComMenuCommon::s_list;
u32 GfPlayComMenuCommon::s_gblHandle;

GfPlayComMenuCommon::GfPlayComMenuCommon(u32 window, u32 handle) : GfPlayCom(PCOMTYPE_MENU_COMMON, false), unknown10(window) {
  unknown14 = handle & 0xffffff;
  if (s_list.size() >= 32) {
    s_list.pop_front();
  }
  s_list.push(unknown14);
}

GfPlayComMenuCommon::~GfPlayComMenuCommon() {
  for (mm::mtl::FixedQueue<u32, 32>::iterator it = s_list.begin(); it != s_list.end(); ++it) {
    if ((*it & 0xffffff) == unknown14) {
      *it = ((GfMenuManager::getCommonWindowResult() + 1) << 24) | unknown14;
      break;
    }
  }
}

void GfPlayComMenuCommon::start() {
  if (!GfGameManager::isAdvertize()) {
    SCOM_FADE::create(1, 15, mm::Col4::zero);
  }
  GfMenuManager::openCommonWindow(unknown10);
}

bool GfPlayComMenuCommon::update(const fw::UpdateInfo &, bool isCancel) {
  if (!isCancel && GfMenuManager::isOpenCommonWindow()) {
    if (!GfGameManager::isLeaveGameForDebug()) {
      return false;
    }
    GfMenuManager::closeCommonWindow();
  }
  return true;
}

bool GfPlayComMenuCommon::isDisp(u32 window) {
  for (mm::mtl::FixedQueue<u32, 32>::iterator it = s_list.begin(); it != s_list.end(); ++it) {
    if ((*it >> 24) == 0 && (*it & 0xffffff) == window) {
      return true;
    }
  }
  return false;
}

u32 GfPlayComMenuCommon::getResult(u32 window) {
  for (mm::mtl::FixedQueue<u32, 32>::iterator it = s_list.begin(); it != s_list.end(); ++it) {
    if ((*it & 0xffffff) == window) {
      return *it >> 24;
    }
  }
  return 0;
}

GfPlayComMenuCommon *GfPlayComMenuCommon::create(u32 window) {
  u32 handle = s_gblHandle++;
  // __LINE__ must be 1526 as in the original file: its value changes the instruction order.
#line 1526
  return new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) GfPlayComMenuCommon(window, handle);
}

mm::mtl::FixedQueue<u32, 32> GfPlayComMenuCommonFromParam::s_list;
u32 GfPlayComMenuCommonFromParam::s_gblHandle;

GfPlayComMenuCommonFromParam::GfPlayComMenuCommonFromParam(const MenuCommonWindowParam &param, u32 handle)
    : GfPlayCom(PCOMTYPE_MENU_COMMON_FROM_PARAM, false), unknown10(param), unknown60(handle & 0xffffff) {
  if (s_list.size() >= 32) {
    s_list.pop_front();
  }
  s_list.push(unknown60);
}

GfPlayComMenuCommonFromParam::~GfPlayComMenuCommonFromParam() {
  for (mm::mtl::FixedQueue<u32, 32>::iterator it = s_list.begin(); it != s_list.end(); ++it) {
    if ((*it & 0xffffff) == unknown60) {
      *it = ((GfMenuManager::getCommonWindowResult() + 1) << 24) | unknown60;
      break;
    }
  }
}

void GfPlayComMenuCommonFromParam::start() {
  if (!GfGameManager::isAdvertize()) {
    SCOM_FADE::create(1, 15, mm::Col4::zero);
  }
  GfMenuManager::openCommonWindow(unknown10);
}

bool GfPlayComMenuCommonFromParam::update(const fw::UpdateInfo &, bool isCancel) {
  if (!isCancel && GfMenuManager::isOpenCommonWindow()) {
    if (!GfGameManager::isLeaveGameForDebug()) {
      return false;
    }
    GfMenuManager::closeCommonWindow();
  }
  return true;
}

bool GfPlayComMenuCommonFromParam::isDisp(u32 window) {
  for (mm::mtl::FixedQueue<u32, 32>::iterator it = s_list.begin(); it != s_list.end(); ++it) {
    if ((*it >> 24) == 0 && (*it & 0xffffff) == window) {
      return true;
    }
  }
  return false;
}

u32 GfPlayComMenuCommonFromParam::getResult(u32 window) {
  for (mm::mtl::FixedQueue<u32, 32>::iterator it = s_list.begin(); it != s_list.end(); ++it) {
    if ((*it & 0xffffff) == window) {
      return *it >> 24;
    }
  }
  return 0;
}

GfPlayComMenuCommonFromParam *GfPlayComMenuCommonFromParam::create(const MenuCommonWindowParam &param) {
  u32 handle = s_gblHandle++;
  // __LINE__ must be 1624 as in the original file: its value changes the instruction order.
#line 1624
  return new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) GfPlayComMenuCommonFromParam(param, handle);
}

GfPlayComSalvage::GfPlayComSalvage(GF_OBJ_HANDLE *handle) : GfPlayCom(PCOMTYPE_SALVAGE, false), unknown18(handle), unknown20(3), unknown24(STATE_WAIT) {
  if (GfGameScene::get() != nullptr) {
    unknown10 = GfGameScene::get()->createPlayerPause();
  }
}

void GfPlayComSalvage::start() {}

void GfPlayComSalvage::end() {
  if (GfGameScene::get() != nullptr) {
    GfGameScene::get()->destroyPlayerPause(unknown10);
  }
}

bool GfPlayComSalvage::updateForWait(const fw::UpdateInfo &info) {
  if (--unknown20 <= 0) {
    if (GfSequentialPlay::isSequenceSpecialAction()) {
      return true;
    }
    if (GfPause::isPause(PAUSE_BIT_MAIN_MENU)) {
      return true;
    }
    unknown24 = STATE_SALVAGE;
    GfGameSalvage::startSalvage(unknown18);
  }
  return false;
}

bool GfPlayComSalvage::updateForSalvage(const fw::UpdateInfo &info, bool isCancel) {
  if (isCancel) {
    GfGameSalvage::cancelSalvage();
  } else if (!GfGameSalvage::isStateWait()) {
    return false;
  }
  GfGameSpeed::setSalvageSpeed(1.0f);
  return true;
}

bool GfPlayComSalvage::update(const fw::UpdateInfo &info, bool isCancel) {
  switch (unknown24) {
  case STATE_WAIT:
    return updateForWait(info);
  case STATE_SALVAGE:
    return updateForSalvage(info, isCancel);
  }
  return false;
}

GfPlayComSalvage *GfPlayComSalvage::create(GF_OBJ_HANDLE *handle) {
  // __LINE__ must be 1715 as in the original file: its value changes the instruction order.
#line 1715
  return new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) GfPlayComSalvage(handle);
}

bool GfPlayComWaitPlayerToStartGmkTuto::update(const fw::UpdateInfo &info, bool isCancel) {
  if (isCancel) {
    return true;
  }
  unknown10 += info.unknown04;
  if (GfGameManager::isGmkTutorialMoverOK()) {
    return true;
  }
  return unknown10 > 10.0f;
}

GfPlayComWaitPlayerToStartGmkTuto *GfPlayComWaitPlayerToStartGmkTuto::create() {
  // __LINE__ must be 2009 as in the original file: its value changes the instruction order.
#line 2009
  return new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) GfPlayComWaitPlayerToStartGmkTuto();
}

GfPlayComGimmickTaskComplete::GfPlayComGimmickTaskComplete(gmk::GmkType gmkType, u32 gimmick, f32 time)
    : GfPlayCom(PCOMTYPE_QUEST_COMPLETE_UI, false), unknown10(gmkType), unknown14(gimmick), unknown18(time) {}

bool GfPlayComGimmickTaskComplete::update(const fw::UpdateInfo &info, bool) {
  unknown18 -= info.unknown04;
  if (unknown18 > 0.0f) {
    return false;
  }
  GfQuestTask::completeGimmickTask(unknown10, unknown14);
  return true;
}

GfPlayComGimmickTaskComplete *GfPlayComGimmickTaskComplete::create(gmk::GmkType gmkType, u32 gimmick, f32 time) {
  // __LINE__ must be 2596 as in the original file: its value changes the instruction order.
#line 2596
  return new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) GfPlayComGimmickTaskComplete(gmkType, gimmick, time);
}

u32 GfPlayComTalk::s_questTargetNpc;
u32 GfPlayComTalk::s_questTargetCondID;

u32 GfPlayComTalk::getQuestTargetNpc(u32 condId) {
  if (s_questTargetCondID == condId) {
    return s_questTargetNpc;
  }
  return 0;
}

void GfPlayComTalk::start() {
  QuestID progress = GfQuestManager::getProgressCurrentQuest(QTYPE_NONE);
  unknown3c.unknown00 = progress.unknown00;
  unknown3c.unknown02 = progress.unknown02;
  QuestID lastOrder = GfQuestManager::getLastOrder();
  unknown40.unknown00 = lastOrder.unknown00;
  unknown40.unknown02 = lastOrder.unknown02;
  GfGameTalk::play(unknown18);
  GfObjSetupNpc *setup = GfObjUtil::getObjSetup<GfObjSetupNpc>(unknown18.unknown08);
  if (setup != nullptr) {
    unknown34 = setup->unknown10;
    if (unknown34 != 0) {
      GfAchievStats::checkTalk(unknown34, unknown18.unknown08);
      u32 taskIndex;
      if (GfQuestUtil::getTalkNpcInfo(taskIndex, unknown34, unknown3c)) {
        s_questTargetNpc = unknown34;
        s_questTargetCondID = taskIndex;
      }
    }
  }
}

void GfPlayComTalk::end() {
  if (GfGameScene::get() != nullptr) {
    GfGameScene::get()->destroyPlayerPause(unknown30);
  }
  if (!GfGameEvent::isCancelFlag()) {
    QuestID quest;
    if (unknown40 == GfQuestManager::getLastOrder()) {
      quest.unknown00 = 0;
      quest.unknown02 = 0;
    } else {
      quest = GfQuestManager::getLastOrder();
    }
    GfQuestUtil::finishTalkNpc(unknown38, unknown34, quest);
  }
  s_questTargetNpc = 0;
  s_questTargetCondID = 0;
}

bool GfPlayComTalk::update(const fw::UpdateInfo &, bool isCancel) {
  if (isCancel) {
    GfGameTalk::end();
    return true;
  }
  return !GfGameTalk::isPlaying();
}

GfPlayComQuestOrderUI::GfPlayComQuestOrderUI(QuestID quest, bool isForce) : GfPlayCom(PCOMTYPE_QUEST_ORDER_UI, false), unknown10(quest), unknown14(isForce), unknown18(nullptr) {
  if (GfGameScene::get() != nullptr) {
    GfGameScene::get()->setPlayerTalkForce(true);
  }
}

GfPlayComQuestOrderUI::~GfPlayComQuestOrderUI() { mm::mtl::safeRelease(unknown18); }

void GfPlayComQuestOrderUI::start() {
  if (GfQuestInfo::isDispUI(unknown10)) {
    unknown18 = GfMenuCallContext::create();
    GfMenuObjQuestLog::order(unknown18, unknown10);
  }
}

void GfPlayComQuestOrderUI::end() {
  if (GfGameScene::get() != nullptr) {
    GfGameScene::get()->setPlayerTalkForce(false);
  }
}

bool GfPlayComQuestOrderUI::update(const fw::UpdateInfo &, bool) {
  if (unknown18 != nullptr) {
    if (!unknown18->isTerm()) {
      return false;
    }
    GfQuestEvent::clearDispUI();
  }
  return true;
}

GfPlayComQuestOrderUI *GfPlayComQuestOrderUI::create(QuestID quest, bool isForce) {
  // __LINE__ must be 2502 as in the original file: its value changes the instruction order.
#line 2502
  return new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) GfPlayComQuestOrderUI(quest, isForce);
}

bool GfPlayComBattleStart::update(const fw::UpdateInfo &info, bool) {
  if (unknown20 == 0) {
    if (!GfGameUtil::enterPlayerBattle(unknown18, reinterpret_cast<GF_OBJ_HANDLE *>(-1), false)) {
      unknown1c += info.unknown04;
      if (unknown1c < 3.0f) {
        return false;
      }
    }
    unknown1c = 0.0f;
    unknown20 = 1;
    return false;
  } else if (unknown20 == 1) {
    unknown1c += info.unknown04;
    if (unknown1c < 1.0f) {
      return false;
    }
  }
  if (GfGameScene::get() != nullptr) {
    GfGameScene::get()->setAutoBattle(false);
  }
  return true;
}

GfPlayComBattleStart *GfPlayComBattleStart::create(bool isStart) {
  // __LINE__ must be 2689 as in the original file: its value changes the instruction order.
#line 2689
  GfPlayComBattleStart *command = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) GfPlayComBattleStart(isStart);
  if (GfGameScene::get() != nullptr) {
    GfGameScene::get()->setAutoBattle(true);
  }
  return command;
}

GfPlayComExecuteSignal::GfPlayComExecuteSignal(bool isStart, GfSequentialPlaySignal *signal) : GfPlayCom(PCOMTYPE_EXECUTE_SIGNAL, true), unknown10(isStart), unknown18(signal) {
  if (unknown10) {
    unknown18->isActive = true;
  }
}

void GfPlayComExecuteSignal::start() {
  if (!unknown10) {
    unknown18->isActive = false;
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

void GfPlayComMenuObjCommonText::start() {
  unknown20 = GfMenuCallContext::create();
  GfMenuObjCommonText::openKizunaDialog(unknown20, unknown10);
}

void GfPlayComMenuObjCommonText::end() {
  if (unknown20 != nullptr) {
    GfMenuObjCommonText::close();
    mm::mtl::safeRelease(unknown20);
  }
}

bool GfPlayComMenuObjCommonText::update(const fw::UpdateInfo &, bool isCancel) {
  if (isCancel) {
    return true;
  }
  return unknown20->isTerm();
}

int GfPlayComMenuObjCommonText::s_activate;

GfPlayComMenuObjCommonText::GfPlayComMenuObjCommonText(GfMenuObjCommonText::OpenKizunaParam &param) : GfPlayCom(PCOMTYPE_MENU_COMMON, false), unknown20(nullptr) {
  this->unknown10 = param;
  s_activate++;
}

GfPlayComMenuObjCommonText::~GfPlayComMenuObjCommonText() { s_activate--; }

GfPlayComMenuObjCommonText *GfPlayComMenuObjCommonText::create(GfMenuObjCommonText::OpenKizunaParam &param) {
  // __LINE__ must be 3127 as in the original file: its value changes the instruction order.
#line 3127
  return new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) GfPlayComMenuObjCommonText(param);
}

GfPlayComChainAttack::GfPlayComChainAttack() : GfPlayCom(PCOMTYPE_CHAIN_ATTACK, true), unknown10(0), unknown14(0) {}

void GfPlayComChainAttack::start() { unknown14 = 3; }

void GfPlayComChainAttack::end() { GfChainAttack::destroy(); }

bool GfPlayComChainAttack::update(const fw::UpdateInfo &info, bool) {
  switch (unknown10) {
  case 0:
    if (--unknown14 <= 0) {
      if (GfSequentialPlay::isInnerState(GF_STATE_EVENT)) {
        return true;
      }
      if (GfChainAttack::get() != nullptr) {
        GfChainAttack::get()->startSetup();
      }
      unknown10 = 1;
    }
    return false;
  case 1:
    if (GfChainAttack::get() == nullptr) {
      return true;
    }
    GfChainAttack::get()->update(info);
    return false;
  }
  return true;
}

GfPlayComChainAttack *GfPlayComChainAttack::create() {
  // __LINE__ must be 2783 as in the original file: its value changes the instruction order.
#line 2783
  return new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) GfPlayComChainAttack();
}

GfPlayComArtsMovie::GfPlayComArtsMovie(const char *name) : GfPlayCom(PCOMTYPE_ARTS_MOVIE, true) {
  if (name != nullptr) {
    unknown10 = name;
  }
}

void GfPlayComArtsMovie::start() {
  if (GfArtsMovie::get() != nullptr) {
    GfArtsMovie::get()->startSetup(unknown10.c_str());
  }
}

void GfPlayComArtsMovie::end() { GfArtsMovie::destroy(); }

bool GfPlayComArtsMovie::update(const fw::UpdateInfo &info, bool) {
  if (GfArtsMovie::get() != nullptr) {
    GfArtsMovie::get()->update(info);
    return false;
  }
  return true;
}

GfPlayComArtsMovie *GfPlayComArtsMovie::create(const char *name) {
  // __LINE__ must be 2826 as in the original file: its value changes the instruction order.
#line 2826
  return new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) GfPlayComArtsMovie(name);
}

void GfPlayComMapjump::start() { unknown10 = GfReqCommand::reqMapjump(unknown20); }

void GfPlayComMapjump::end() {}

bool GfPlayComMapjump::update(const fw::UpdateInfo &, bool isCancel) {
  if (isCancel) {
    return true;
  }
  return !GfReqManager::isValid(unknown10);
}

GfPlayComMapjump *GfPlayComMapjump::create(const GfMapjumpInfo &info) {
  // __LINE__ must be 424 as in the original file: its value changes the instruction order.
#line 424
  return new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) GfPlayComMapjump(info);
}

int GfPlayComGmkTutorialSeq::s_activate;

GfPlayComGmkTutorialSeq::GfPlayComGmkTutorialSeq(const char *name, u32 tutorial) : GfPlayCom(PCOMTYPE_GMK_TUTORIAL_SEQ, false) {
  unknown10 = name;
  unknown54 = tutorial;
  if (GfGameScene::get() != nullptr) {
    unknown58 = GfGameScene::get()->createPlayerPause();
  }
  s_activate++;
}

GfPlayComGmkTutorialSeq::~GfPlayComGmkTutorialSeq() { s_activate--; }

void GfPlayComGmkTutorialSeq::start() { GfFieldGmkTutorial::get()->create(unknown10.c_str(), unknown54); }

void GfPlayComGmkTutorialSeq::end() {
  GfFieldGmkTutorial::get()->dispose();
  if (GfGameScene::get() != nullptr) {
    GfGameScene::get()->destroyPlayerPause(unknown58);
  }
}

bool GfPlayComGmkTutorialSeq::update(const fw::UpdateInfo &, bool isCancel) {
  if (isCancel) {
    GfFieldGmkTutorial::get()->dispose();
  } else if (!GfFieldGmkTutorial::get()->isEnd()) {
    return false;
  }
  GfGameManager::setGmkTutorialSequenceOK(false);
  GfGameManager::setGmkTutorialMoverOK(false);
  return true;
}

GfPlayComGmkTutorialSeq *GfPlayComGmkTutorialSeq::create(const char *name, u32 tutorial) {
  // __LINE__ must be 2082 as in the original file: its value changes the instruction order.
#line 2082
  return new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) GfPlayComGmkTutorialSeq(name, tutorial);
}

int GfPlayComGmkCameraSeq::s_activate;

GfPlayComGmkCameraSeq::GfPlayComGmkCameraSeq(mm::mtl::IntrusivePtr<fw::Camera> camera) : GfPlayCom(PCOMTYPE_GMK_CAMERA_SEQ, false) {
  unknown10 = camera;
  if (GfGameScene::get() != nullptr) {
    unknown18 = GfGameScene::get()->createPlayerPause();
  }
  s_activate++;
}

GfPlayComGmkCameraSeq::~GfPlayComGmkCameraSeq() { s_activate--; }

void GfPlayComGmkCameraSeq::start() {}

void GfPlayComGmkCameraSeq::end() {
  if (GfGameScene::get() != nullptr) {
    GfGameScene::get()->destroyPlayerPause(unknown18);
  }
}

bool GfPlayComGmkCameraSeq::update(const fw::UpdateInfo &, bool isCancel) {
  if (!isCancel && unknown10->unknowna0) {
    return false;
  }
  GfGameManager::setGmkTutorialSequenceOK(false);
  GfGameManager::setGmkTutorialMoverOK(false);
  return true;
}

GfPlayComGmkCameraSeq *GfPlayComGmkCameraSeq::create(mm::mtl::IntrusivePtr<fw::Camera> camera) {
#line 2139
  return new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) GfPlayComGmkCameraSeq(camera);
}

int GfPlayComQuestCompleteUI::s_active;

GfPlayComQuestCompleteUI::GfPlayComQuestCompleteUI(QuestID quest, QuestID child, QSTATE state)
    : GfPlayCom(PCOMTYPE_QUEST_COMPLETE_UI, false), unknown10(quest), unknown14(child), unknown18(state), unknown20(nullptr) {
  s_active++;
}

GfPlayComQuestCompleteUI::~GfPlayComQuestCompleteUI() {
  mm::mtl::safeRelease(unknown20);
  s_active--;
}

void GfPlayComQuestCompleteUI::start() {
  unknown20 = GfMenuCallContext::create();
  GfMenuObjQuestLog::complete(unknown20, unknown10);
}

void GfPlayComQuestCompleteUI::end() { GfQuestManager::requestRefreshQuestTaskState(); }

bool GfPlayComQuestCompleteUI::update(const fw::UpdateInfo &, bool) {
  if (unknown20->isTerm()) {
    GfQuestEvent::clearDispUI();
    return true;
  }
  return false;
}

GfPlayComQuestCompleteUI *GfPlayComQuestCompleteUI::create(QuestID quest, QuestID child, QSTATE state) {
  // __LINE__ must be 2561 as in the original file: its value changes the instruction order.
#line 2561
  GfPlayComQuestCompleteUI *command = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) GfPlayComQuestCompleteUI(quest, child, state);
  GfQuestManager::setCompleteQuest(quest, child, state);
  return command;
}

GfPlayComCollect::GfPlayComCollect(GF_OBJ_HANDLE *handle) : GfPlayCom(PCOMTYPE_COLLECT, false), unknown20(handle) {
  if (GfGameScene::get() != nullptr) {
    unknown18 = GfGameScene::get()->createPlayerPause();
  }
}

GfPlayComCollect *GfPlayComCollect::create(GF_OBJ_HANDLE *handle) {
  // __LINE__ must be 1769 as in the original file: its value changes the instruction order.
#line 1769
  return new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) GfPlayComCollect(handle);
}

void GfPlayComCollect::start() {
  GfFieldCollect::get()->start(unknown20);
  SCOM_FIELD_VOICE::create(CV_FIELD_UNKNOWN_4, CV_PRIO_UNKNOWN_1);
}

void GfPlayComCollect::end() {
  if (GfGameScene::get() != nullptr) {
    GfGameScene::get()->destroyPlayerPause(unknown18);
  }
}

void GfPlayComFieldTbox::start() {
  GfFieldTbox::get()->start(unknown20);
  SCOM_FIELD_VOICE::create(CV_FIELD_UNKNOWN_3, CV_PRIO_UNKNOWN_1);
}

void GfPlayComFieldTbox::end() {
  if (GfGameScene::get() != nullptr) {
    GfGameScene::get()->destroyPlayerPause(unknown18);
  }
}

void GfPlayComFieldSeq::start() { unknown18->create(unknown20); }

void GfPlayComFieldSeq::end() {
  unknown18->dispose();
  if (GfGameScene::get() != nullptr) {
    GfGameScene::get()->destroyPlayerPause(unknown28);
  }
}

bool GfPlayComFieldSeq::update(const fw::UpdateInfo &, bool isCancel) {
  if (isCancel) {
    return unknown18->cancel();
  }
  return unknown18->isEnd();
}

GfPlayComFieldSeq::GfPlayComFieldSeq(IFieldSeq *sequence, GF_OBJ_HANDLE *handle) : GfPlayCom(PCOMTYPE_FIELD_SEQ, false), unknown18(sequence), unknown20(handle) {
  if (GfGameScene::get() != nullptr) {
    unknown28 = GfGameScene::get()->createPlayerPause();
  }
}

GfPlayComFieldSeq *GfPlayComFieldSeq::create(IFieldSeq *sequence, GF_OBJ_HANDLE *handle) {
  // __LINE__ must be 1972 as in the original file: its value changes the instruction order.
#line 1972
  return new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) GfPlayComFieldSeq(sequence, handle);
}

void GfPlayComMoverSwitch::start() { unknown14 = 3; }

void GfPlayComMoverSwitch::end() {}

GfPlayComMoverSwitch *GfPlayComMoverSwitch::create() {
  // __LINE__ must be 2999 as in the original file: its value changes the instruction order.
#line 2999
  return new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) GfPlayComMoverSwitch();
}

void GfPlayComHoodHomuraBattou::start() {}

void GfPlayComHoodHomuraBattou::end() {}

bool GfPlayComHoodHomuraBattou::update(const fw::UpdateInfo &, bool) {
  GfObjAcc bladeAcc(GfGameParty::getHandleBlade(0, -1));
  if (!bladeAcc.isValid()) {
    return true;
  }
  if (bladeAcc.isRebuild() || !GfGameObj::isValidGameObj(bladeAcc.getHandle(), true, nullptr)) {
    return false;
  }
  if (GfGameManager::isEnableBattouWithHoodHomura(false)) {
    GfGameUtil::enterPlayerBattle(false, INVALID_HANDLE, false);
  }
  return true;
}

void GfPlayComReturnTitle::start() { GfMenuObjPopup::closeAll(); }

void GfPlayComReturnTitle::end() {}

GfPlayComReturnTitle *GfPlayComReturnTitle::create(const ParamReturnTitle &param) {
  // __LINE__ must be 2650 as in the original file: its value changes the instruction order.
#line 2650
  return new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) GfPlayComReturnTitle(param);
}

bool GfPlayComPlayerDead::isDead() { return get() != nullptr && get()->m_dead; }

void GfPlayComPlayerDead::gevMapjump(GEV event, const MapjumpCallbackInfo &) {
  if (event == GEV_MAPJUMP_CHANGE_MAP) {
    m_dead = false;
  } else if (event == GEV_MAPJUMP_FADEIN) {
    unknown39 = true;
  }
}

GfPlayComPlayerDead *GfPlayComPlayerDead::create(GfPlayerDead dead) {
  // __LINE__ must be 2329 as in the original file: its value changes the instruction order.
#line 2329
  GfPlayComPlayerDead *command = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) GfPlayComPlayerDead(dead);
  if (GfGameScene::get() != nullptr) {
    GfGameScene::get()->setDeadType(dead);
  }
  return command;
}

} // namespace gf
