#include "gf/game/sequential_play/gf_play_factory.h"

#include "gf/data/gf_data_event.h"
#include "gf/event/gf_event.h"
#include "gf/game/gf_game_manager.h"
#include "gf/game/gf_game_party.h"
#include "gf/game/gf_game_scene.h"
#include "gf/game/quest/gf_quest_id.h"
#include "gf/game/sequential_play/gf_play_command.h"
#include "gf/game/sequential_play/gf_sequential_play.h"
#include "gf/game/talk/gf_game_talk.h"
#include "gf/gf_manager.h"
#include "gf/gf_pause.h"
#include "gf/object/gf_obj_acc.h"
#include "gf/request/gf_req_command.h"

namespace gf {

namespace {

constexpr u32 PAUSE_BITS_MENU = PAUSE_BIT_SYSTEM | PAUSE_BIT_GAME_SOUND | PAUSE_BIT_FIELD_TIME | PAUSE_BIT_MAIN_MENU;
constexpr u32 PAUSE_BITS_SYSTEM_MENU = PAUSE_BIT_SYSTEM | PAUSE_BIT_FIELD_TIME;

constexpr int EVENT_CATEGORY_STOP_FIELD_TIME = 2;
constexpr u32 EVENT_ALWAYS_PLAYABLE = 10001;

constexpr f32 EVENT_END_WAIT_TIME = 0.5f;

u32 getEventPauseBits(u32 event) {
  if (GfDataEvent::getEventType(event) == EVENT_CATEGORY_STOP_FIELD_TIME) {
    return PAUSE_BIT_EVENT | PAUSE_BIT_FIELD_TIME;
  }
  return PAUSE_BIT_EVENT;
}

} // namespace

bool GfPlayFactory::createReturnTitle(const ParamReturnTitle &param) {
  if (GfPlayComReturnTitle::get() != nullptr) {
    return false;
  }
  GfSequentialPlay::beginCommand(GfSequentialPlay::TYPE_NORMAL);
  GfSequentialPlay::pushState(GF_STATE_MENU);
  GfSequentialPlay::addReturnTitle(param);
  GfSequentialPlay::popState();
  GfSequentialPlay::play();
  return true;
}

bool GfPlayFactory::createOpenMenu(u32 type, GfSequentialPlaySignal *signal) {
  if (GfGameManager::isLeaveGameForDebug()) {
    return false;
  }
  if (GfSequentialPlay::isInnerState(GF_STATE_MAPJUMP_SKIP_TRAVEL)) {
    return false;
  }
  GfSequentialPlay::beginCommand(GfSequentialPlay::TYPE_SEQUENCE);
  GfSequentialPlay::startSignal(signal);
  GfSequentialPlay::pushState(GF_STATE_MENU);
  GfSequentialPlay::addWaitBattleEnd(0);
  GfSequentialPlay::pushPause(PAUSE_BITS_MENU);
  GfSequentialPlay::endSignal(signal);
  GfSequentialPlay::addOpenMenu(type);
  GfSequentialPlay::popPause();
  GfSequentialPlay::popState();
  GfSequentialPlay::play();
  return true;
}

bool GfPlayFactory::createOpenMenu2(u32 type, MAINMENU menu, GfSequentialPlaySignal *signal) {
  if (GfGameManager::isLeaveGameForDebug()) {
    return false;
  }
  if (GfGameManager::isEvent(false) || GfSequentialPlay::isInnerState(GF_STATE_EVENT) || GfSequentialPlay::isInnerState(GF_STATE_TALK) ||
      GfSequentialPlay::isInnerState(GF_STATE_MAPJUMP_SKIP_TRAVEL) || GfSequentialPlay::isInnerPause(PAUSE_BITS_SYSTEM_MENU)) {
    return false;
  }
  GfSequentialPlay::beginCommand(GfSequentialPlay::TYPE_SEQUENCE);
  GfSequentialPlay::startSignal(signal);
  GfSequentialPlay::pushState(GF_STATE_MENU);
  GfSequentialPlay::pushPause(PAUSE_BITS_MENU);
  GfSequentialPlay::endSignal(signal);
  GfSequentialPlay::addOpenMenu2(type, menu);
  GfSequentialPlay::popPause();
  GfSequentialPlay::popState();
  GfSequentialPlay::play();
  return true;
}

bool GfPlayFactory::createStartTutorial(u32 tutorial, GfSequentialPlaySignal *signal) {
  if (GfGameManager::isLeaveGameForDebug()) {
    return false;
  }
  if (GfSequentialPlay::isInnerState(GF_STATE_MAPJUMP_SKIP_TRAVEL)) {
    return false;
  }
  GfSequentialPlay::beginCommand(GfSequentialPlay::TYPE_SEQUENCE);
  GfSequentialPlay::startSignal(signal);
  GfSequentialPlay::addBattleStartEnd();
  GfSequentialPlay::pushPause(PAUSE_BIT_SYSTEM);
  GfSequentialPlay::addStartTutorial(tutorial);
  GfSequentialPlay::popPause();
  GfSequentialPlay::endSignal(signal);
  GfSequentialPlay::play();
  return true;
}

void GfPlayFactory::createMiniGame() {
  if (!GfGameManager::isLeaveGameForDebug() && !GfSequentialPlay::isInnerState(GF_STATE_MAPJUMP_SKIP_TRAVEL)) {
    GfSequentialPlay::beginCommand(GfSequentialPlay::TYPE_SEQUENCE);
    GfSequentialPlay::pushState(GF_STATE_MENU);
    GfSequentialPlay::addWaitBattleEnd(0);
    GfSequentialPlay::pushPause(PAUSE_BITS_MENU);
    GfSequentialPlay::addMiniGame();
    GfSequentialPlay::popPause();
    GfSequentialPlay::popState();
    GfSequentialPlay::play();
  }
}

bool GfPlayFactory::createMenuQuestList() {
  if (GfGameManager::isLeaveGameForDebug()) {
    return false;
  }
  if (GfGameManager::isInGamePauseMenuOK()) {
    GfSequentialPlay::beginCommand(GfSequentialPlay::TYPE_NORMAL);
    GfSequentialPlay::pushPause(PAUSE_BITS_SYSTEM_MENU);
    GfSequentialPlay::pushState(GF_STATE_MENU);
    GfSequentialPlay::addMenuQuestList();
    GfSequentialPlay::popState();
    GfSequentialPlay::popPause();
    GfSequentialPlay::play();
    return true;
  }
  return false;
}

bool GfPlayFactory::createMenuKizunaring(u32 blade) {
  if (!GfGameManager::isLeaveGameForDebug() && GfGameManager::isInGamePauseMenuOK()) {
    GfSequentialPlay::beginCommand(GfSequentialPlay::TYPE_NORMAL);
    GfSequentialPlay::pushState(GF_STATE_MENU);
    GfSequentialPlay::addWaitBattleEnd(0);
    GfSequentialPlay::pushPause(PAUSE_BITS_SYSTEM_MENU);
    GfSequentialPlay::addMenuKizunaring(blade);
    GfSequentialPlay::popPause();
    GfSequentialPlay::popState();
    GfSequentialPlay::play();
    return true;
  }
  return false;
}

bool GfPlayFactory::createSalvage(GF_OBJ_HANDLE *handle) {
  if (!GfGameManager::isLeaveGameForDebug() && !GfSequentialPlay::isInnerState(GF_STATE_MAPJUMP_SKIP_TRAVEL) &&
      !GfSequentialPlay::isInnerState(GF_STATE_RESET_BLADE) && GfGameManager::isControlFree()) {
    GfSequentialPlay::beginCommand(GfSequentialPlay::TYPE_NORMAL);
    GfSequentialPlay::pushState(GF_STATE_SALVAGE);
    GfSequentialPlay::addWaitBattleEnd(0);
    GfSequentialPlay::pushPause(PAUSE_BIT_FIELD_TIME);
    GfSequentialPlay::addSalvage(handle);
    GfSequentialPlay::popPause();
    GfSequentialPlay::popState();
    GfSequentialPlay::play();
    return true;
  }
  return false;
}

bool GfPlayFactory::createCollect(GF_OBJ_HANDLE *handle) {
  if (GfGameManager::isLeaveGameForDebug()) {
    return false;
  }
  if (GfSequentialPlay::isInnerState(GF_STATE_MAPJUMP_SKIP_TRAVEL)) {
    return false;
  }
  if (GfSequentialPlay::isInnerState(GF_STATE_EVENT)) {
    return false;
  }
  GfSequentialPlay::beginCommand(GfSequentialPlay::TYPE_NORMAL);
  GfSequentialPlay::pushState(GF_STATE_COLLECT);
  GfSequentialPlay::addWaitBattleEnd(0);
  GfSequentialPlay::pushPause(PAUSE_BIT_FIELD_TIME);
  GfSequentialPlay::addCollect(handle);
  GfSequentialPlay::popPause();
  GfSequentialPlay::popState();
  GfSequentialPlay::play();
  return true;
}

bool GfPlayFactory::createMapGimmick(GF_OBJ_HANDLE *handle) {
  if (GfGameManager::isLeaveGameForDebug()) {
    return false;
  }
  if (GfSequentialPlay::isInnerState(GF_STATE_MAPJUMP_SKIP_TRAVEL)) {
    return false;
  }
  GfSequentialPlay::beginCommand(GfSequentialPlay::TYPE_NORMAL);
  GfSequentialPlay::pushState(GF_STATE_MAP_GIMMICK);
  GfSequentialPlay::addWaitBattleEnd(0);
  GfSequentialPlay::pushPause(PAUSE_BIT_FIELD_TIME);
  GfSequentialPlay::addMapGimmick(handle);
  GfSequentialPlay::popPause();
  GfSequentialPlay::popState();
  GfSequentialPlay::play();
  return true;
}

bool GfPlayFactory::createGrave(GF_OBJ_HANDLE *handle) {
  if (GfGameManager::isLeaveGameForDebug()) {
    return false;
  }
  if (GfSequentialPlay::isInnerState(GF_STATE_MAPJUMP_SKIP_TRAVEL)) {
    return false;
  }
  GfSequentialPlay::beginCommand(GfSequentialPlay::TYPE_NORMAL);
  GfSequentialPlay::pushState(GF_STATE_GRAVE);
  GfSequentialPlay::addWaitBattleEnd(0);
  GfSequentialPlay::pushPause(PAUSE_BIT_FIELD_TIME);
  GfSequentialPlay::addGrave(handle);
  GfSequentialPlay::popPause();
  GfSequentialPlay::popState();
  GfSequentialPlay::play();
  return true;
}

bool GfPlayFactory::createJump(GF_OBJ_HANDLE *handle) {
  if (GfGameManager::isLeaveGameForDebug()) {
    return false;
  }
  if (GfSequentialPlay::isInnerState(GF_STATE_MAPJUMP_SKIP_TRAVEL)) {
    return false;
  }
  GfSequentialPlay::beginCommand(GfSequentialPlay::TYPE_NORMAL);
  GfSequentialPlay::pushState(GF_STATE_JUMP);
  GfSequentialPlay::addWaitBattleEnd(0);
  GfSequentialPlay::pushPause(PAUSE_BIT_FIELD_TIME);
  GfSequentialPlay::addJump(handle);
  GfSequentialPlay::popPause();
  GfSequentialPlay::popState();
  GfSequentialPlay::play();
  return true;
}

bool GfPlayFactory::createWarp(GF_OBJ_HANDLE *handle) {
  if (GfGameManager::isLeaveGameForDebug()) {
    return false;
  }
  if (GfSequentialPlay::isInnerState(GF_STATE_MAPJUMP_SKIP_TRAVEL)) {
    return false;
  }
  GfSequentialPlay::beginCommand(GfSequentialPlay::TYPE_NORMAL);
  GfSequentialPlay::pushState(GF_STATE_WARP);
  GfSequentialPlay::addWaitBattleEnd(0);
  GfSequentialPlay::pushPause(PAUSE_BIT_FIELD_TIME);
  GfSequentialPlay::addWarp(handle);
  GfSequentialPlay::popPause();
  GfSequentialPlay::popState();
  GfSequentialPlay::play();
  return true;
}

bool GfPlayFactory::createGmkTutorial(const char *name, u32 tutorial) {
  if (GfGameManager::isLeaveGameForDebug()) {
    return false;
  }
  if (!GfGameManager::isGmkTutorialOK() || GfSequentialPlay::isInnerState(GF_STATE_MAPJUMP_SKIP_TRAVEL)) {
    return false;
  }
  GfGameManager::setGmkTutorialSequenceOK(true);
  GfSequentialPlay::beginCommand(GfSequentialPlay::TYPE_NORMAL);
  GfSequentialPlay::pushState(GF_STATE_GMK_TUTORIAL);
  GfSequentialPlay::addWaitBattleEnd(0);
  GfSequentialPlay::addWaitPlayerToStartGmkTuto();
  GfSequentialPlay::pushPause(PAUSE_BIT_FIELD_TIME);
  GfSequentialPlay::addGmkTutorial(name, tutorial);
  GfSequentialPlay::popPause();
  GfSequentialPlay::popState();
  GfSequentialPlay::play();
  return true;
}

bool GfPlayFactory::createPlayerDead(GfPlayerDead dead) {
  if (!GfPlayComPlayerDead::replaceDeadType(dead)) {
    if (!GfGameManager::isEnablePlayerDeadSequence()) {
      return false;
    }
    if (GfGameManager::isGameOver()) {
      return createGameOver();
    }
    GfSequentialPlay::beginCommand(GfSequentialPlay::TYPE_NORMAL);
    GfSequentialPlay::pushState(GF_STATE_PLAYER_DEAD);
    GfSequentialPlay::addPlayerDead(dead);
    GfSequentialPlay::popState();
    GfSequentialPlay::play();
  }
  return true;
}

bool GfPlayFactory::createGameOver() {
  if (!GfGameManager::isEnablePlayerDeadSequence()) {
    return false;
  }
  GfGameScene *scene = GfGameScene::get();
  if (scene != nullptr) {
    if (scene->getDeadType() != PLAYER_DEAD_NONE) {
      return false;
    }
    scene->setDeadType(PLAYER_DEAD_GAME_OVER);
  }
  ParamReturnTitle param;
  param.isWaitVoice = true;
  param.isGameClear = false;
  return createReturnTitle(param);
}

bool GfPlayFactory::createTalk(const GfSetupPfTalk &talk) {
  if (GfGameManager::isLeaveGameForDebug() || GfSequentialPlay::isInnerState(GF_STATE_MAPJUMP_SKIP_TRAVEL) || !GfGameManager::isTalkOK()) {
    return false;
  }
  GfSequentialPlay::beginCommand(GfSequentialPlay::TYPE_NORMAL);
  GfSequentialPlay::addCallbackEventSequence(talk.event, true);
  GfSequentialPlay::pushState(GF_STATE_TALK);
  GfSequentialPlay::addWaitBattleEnd(0);
  GfSequentialPlay::addEventPlayerStop(true);
  GfSequentialPlay::pushPause(PAUSE_BIT_FIELD_TIME);
  GfSequentialPlay::addTalk(talk);
  GfSequentialPlay::popPause();
  GfSequentialPlay::popState();
  GfSequentialPlay::addEventFade();
  GfSequentialPlay::addWait(EVENT_END_WAIT_TIME);
  GfSequentialPlay::addCallbackEventSequence(talk.event, false);
  GfSequentialPlay::play();
  GfSequentialPlay::addEventPlayerStop(false);
  return true;
}

void GfPlayFactory::createMapjump(const GfMapjumpInfo &info) {
  GfSequentialPlay::beginCommand(GfSequentialPlay::TYPE_NORMAL);
  if (info.isSkipTravel) {
    GfSequentialPlay::addEventPlayerStop(true);
  }
  GfSequentialPlay::pushState(info.isSkipTravel ? GF_STATE_MAPJUMP_SKIP_TRAVEL : GF_STATE_MAPJUMP);
  GfSequentialPlay::addWaitBattleEnd(0);
  GfSequentialPlay::addMapjump(info);
  GfSequentialPlay::popState();
  if (info.isSkipTravel) {
    GfSequentialPlay::addEventPlayerStop(false);
  }
  GfSequentialPlay::play();
}

bool GfPlayFactory::createEventMapjump(const GfMapjumpInfo &info) {
  GfSequentialPlay::beginCommand(GfSequentialPlay::TYPE_NORMAL);
  GfSequentialPlay::pushState(GF_STATE_EVENT);
  GfSequentialPlay::pushState(GF_STATE_MAPJUMP);
  GfSequentialPlay::addCallbackEventSequence(0, true);
  GfSequentialPlay::addWaitBattleEnd(0);
  GfSequentialPlay::addMapjump(info);
  GfSequentialPlay::addCallbackEventSequence(0, false);
  GfSequentialPlay::popState();
  GfSequentialPlay::popState();
  GfSequentialPlay::play();
  return true;
}

bool GfPlayFactory::createOneEventForGimmick(u32 event) {
  if (GfSequentialPlay::isInnerState(GF_STATE_MENU) || GfSequentialPlay::isInnerState(GF_STATE_COLLECT)) {
    return false;
  }
  return createOneEvent(event);
}

bool GfPlayFactory::createOneEvent(u32 event) {
  if (event == 0) {
    return true;
  }
  if (GfGameManager::isLeaveGameForDebug()) {
    return false;
  }
  if (GfSequentialPlay::isInnerState(GF_STATE_MAPJUMP_SKIP_TRAVEL)) {
    return false;
  }
  if (GfSequentialPlay::get() != nullptr && GfSequentialPlay::get()->isExistEvent(event) && event != EVENT_ALWAYS_PLAYABLE) {
    return true;
  }
  GfSequentialPlay::beginCommand(GfSequentialPlay::TYPE_NORMAL);
  GfSequentialPlay::pushState(GF_STATE_EVENT);
  GfSequentialPlay::addCallbackEventSequence(event, true);
  GfSequentialPlay::addWaitBattleEnd(event);
  GfSequentialPlay::addEventPlayerStop(true);
  GfSequentialPlay::pushPause(getEventPauseBits(event));
  GfSequentialPlay::addEvent(event, 0, 0, false);
  GfSequentialPlay::popPause();
  GfSequentialPlay::addEventFade();
  GfSequentialPlay::addCallbackEventSequence(event, false);
  GfSequentialPlay::popState();
  GfSequentialPlay::addEventPlayerStop(false);
  GfSequentialPlay::play();
  return true;
}

bool GfPlayFactory::createBlEvent(u32 event, u32 param0, u32 param1, GfSequentialPlaySignal *signal) {
  if (GfGameManager::isLeaveGameForDebug()) {
    return false;
  }
  GfSequentialPlay::beginCommand(GfSequentialPlay::TYPE_SEQUENCE);
  GfSequentialPlay::startSignal(signal);
  GfSequentialPlay::pushState(GF_STATE_EVENT);
  GfSequentialPlay::addCallbackEventSequence(event, true);
  GfSequentialPlay::pushPause(getEventPauseBits(event));
  GfSequentialPlay::addEvent(event, param0, param1, false);
  GfSequentialPlay::popPause();
  GfSequentialPlay::addEventFade();
  GfSequentialPlay::addCallbackEventSequence(event, false);
  GfSequentialPlay::popState();
  GfSequentialPlay::endSignal(signal);
  GfSequentialPlay::play();
  return true;
}

bool GfPlayFactory::createTheaterEvent(int event) {
  if (event == 0) {
    return true;
  }
  if (GfGameManager::isLeaveGameForDebug()) {
    return false;
  }
  if (GfSequentialPlay::get() != nullptr && GfSequentialPlay::get()->isExistEvent(event) && event != EVENT_ALWAYS_PLAYABLE) {
    return true;
  }
  u32 isBladeCreate = GfDataEvent::isBladeCreateEvent(event);
  GfSequentialPlay::beginCommand(GfSequentialPlay::TYPE_NORMAL);
  GfSequentialPlay::pushState(GF_STATE_EVENT);
  GfSequentialPlay::addCallbackEventSequence(event, true);
  GfSequentialPlay::addWaitBattleEnd(0);
  GfSequentialPlay::pushPause(getEventPauseBits(event));
  GfSequentialPlay::addEvent(event, isBladeCreate, 0, true);
  GfSequentialPlay::popPause();
  GfSequentialPlay::addEventFade();
  GfSequentialPlay::addCallbackEventSequence(event, false);
  GfSequentialPlay::popState();
  GfSequentialPlay::play();
  return true;
}

bool GfPlayFactory::createReserveEvent(const char *name) {
  u32 event = GfDataEvent::getEventID(name);
  if (event == 0) {
    return false;
  }
  GfSequentialPlay::beginCommand(GfSequentialPlay::TYPE_NORMAL);
  GfSequentialPlay::pushState(GF_STATE_EVENT);
  GfSequentialPlay::addEventPlayerStop(true);
  GfSequentialPlay::pushPause(getEventPauseBits(event));
  GfSequentialPlay::addEvent(event, 0, 0, false);
  GfSequentialPlay::popPause();
  GfSequentialPlay::addEventFade();
  GfSequentialPlay::popState();
  GfSequentialPlay::addEventPlayerStop(false);
  GfSequentialPlay::play();
  return true;
}

bool GfPlayFactory::createEventAfterScript(int event) {
  if (!GfGameManager::isScenarioGame() || GfGameManager::isLeaveGameForDebug()) {
    return false;
  }
  GfSequentialPlay::beginCommand(GfSequentialPlay::TYPE_SEQUENCE);
  GfSequentialPlay::pushPause(PAUSE_BITS_SYSTEM_MENU);
  GfSequentialPlay::pushState(GF_STATE_MENU);
  GfSequentialPlay::addAfterEventScript(event);
  GfSequentialPlay::popState();
  GfSequentialPlay::popPause();
  GfSequentialPlay::play();
  return true;
}

bool GfPlayFactory::createOneEvent(const char *name) { return createOneEvent(GfDataEvent::getEventID(name)); }

bool GfPlayFactory::createQuestUIOrder(QuestID quest, bool isEntry, bool isForce) {
  if (GfGameManager::isLeaveGameForDebug()) {
    return false;
  }
  GfSequentialPlay::beginCommand(static_cast<GfSequentialPlay::TYPE>(isEntry));
  GfSequentialPlay::pushPause(PAUSE_BITS_SYSTEM_MENU);
  GfSequentialPlay::pushState(GF_STATE_MENU);
  GfSequentialPlay::addQuestUIOrder(quest, isForce);
  GfSequentialPlay::popState();
  GfSequentialPlay::popPause();
  GfSequentialPlay::play();
  return true;
}

bool GfPlayFactory::createQuestUIComplete(QuestID quest, QuestID child, QSTATE state) {
  if (GfGameManager::isLeaveGameForDebug()) {
    return false;
  }
  GfSequentialPlay::beginCommand(GfSequentialPlay::TYPE_NORMAL);
  GfSequentialPlay::pushPause(PAUSE_BITS_SYSTEM_MENU);
  GfSequentialPlay::pushState(GF_STATE_MENU);
  GfSequentialPlay::addQuestUIComplete(quest, child, state);
  GfSequentialPlay::popState();
  GfSequentialPlay::popPause();
  GfSequentialPlay::play();
  return true;
}

bool GfPlayFactory::createQuestUIComplete(QuestID quest) {
  if (!GfGameManager::isScenarioGame() || GfGameManager::isLeaveGameForDebug()) {
    return false;
  }
  GfSequentialPlay::beginCommand(GfSequentialPlay::TYPE_SEQUENCE);
  GfSequentialPlay::addQuestUIComplete(quest, toQuestID(0), QSTATE_NOT_ORDER);
  GfSequentialPlay::play();
  return true;
}

bool GfPlayFactory::createMenuPrecious(u32 item, bool isSequence) {
  if (GfGameManager::isLeaveGameForDebug()) {
    return false;
  }
  GfSequentialPlay::beginCommand(static_cast<GfSequentialPlay::TYPE>(isSequence));
  GfSequentialPlay::pushPause(PAUSE_BITS_SYSTEM_MENU);
  GfSequentialPlay::pushState(GF_STATE_MENU);
  GfSequentialPlay::addMenuPrecious(item);
  GfSequentialPlay::popState();
  GfSequentialPlay::popPause();
  GfSequentialPlay::play();
  return true;
}

bool GfPlayFactory::createEventWait(f32 time, GF_OBJ_HANDLE *handle) {
  if (GfGameManager::isLeaveGameForDebug()) {
    return false;
  }
  GfSequentialPlay::beginCommand(GfSequentialPlay::TYPE_NORMAL);
  GfSequentialPlay::pushState(GF_STATE_WAIT_EVENT);
  GfSequentialPlay::addWaitEvent(time, handle);
  GfSequentialPlay::popState();
  GfSequentialPlay::play();
  return true;
}

int GfPlayFactory::createCommonMessage(u32 window) {
  int result = -1;
  if ((GfGameManager::isScenarioGame() || GfManager::isExecModeDebug()) && !GfGameManager::isLeaveGameForDebug()) {
    if (!GfGameManager::isControlFree()) {
      GfSequentialPlay::beginCommand(GfSequentialPlay::TYPE_SEQUENCE);
      GfSequentialPlay::pushPause(PAUSE_BITS_SYSTEM_MENU);
      GfSequentialPlay::pushState(GF_STATE_MENU);
      GfSequentialPlay::addEventFade();
      result = GfSequentialPlay::addMenuCommon(window);
      GfSequentialPlay::popState();
      GfSequentialPlay::popPause();
      GfSequentialPlay::play();
    } else if (!GfSequentialPlay::isPlay()) {
      GfSequentialPlay::beginCommand(GfSequentialPlay::TYPE_SEQUENCE);
      GfSequentialPlay::pushState(GF_STATE_MENU);
      GfSequentialPlay::pushPause(PAUSE_BITS_SYSTEM_MENU);
      GfSequentialPlay::addEventFade();
      result = GfSequentialPlay::addMenuCommon(window);
      GfSequentialPlay::popPause();
      GfSequentialPlay::popState();
      GfSequentialPlay::addWait(EVENT_END_WAIT_TIME);
      GfSequentialPlay::play();
    }
  }
  return result;
}

int GfPlayFactory::createCommonMessage(const MenuCommonWindowParam &param) {
  int result = -1;
  if ((GfGameManager::isScenarioGame() || GfManager::isExecModeDebug()) && !GfGameManager::isLeaveGameForDebug()) {
    if (!GfGameManager::isControlFree()) {
      GfSequentialPlay::beginCommand(GfSequentialPlay::TYPE_SEQUENCE);
      GfSequentialPlay::pushPause(PAUSE_BITS_SYSTEM_MENU);
      GfSequentialPlay::pushState(GF_STATE_MENU);
      GfSequentialPlay::addEventFade();
      result = GfSequentialPlay::addMenuCommon(param);
      GfSequentialPlay::popState();
      GfSequentialPlay::popPause();
      GfSequentialPlay::play();
    } else if (!GfSequentialPlay::isPlay()) {
      GfSequentialPlay::beginCommand(GfSequentialPlay::TYPE_SEQUENCE);
      GfSequentialPlay::pushState(GF_STATE_MENU);
      GfSequentialPlay::pushPause(PAUSE_BITS_SYSTEM_MENU);
      GfSequentialPlay::addEventFade();
      result = GfSequentialPlay::addMenuCommon(param);
      GfSequentialPlay::popPause();
      GfSequentialPlay::popState();
      GfSequentialPlay::addWait(EVENT_END_WAIT_TIME);
      GfSequentialPlay::play();
    }
  }
  return result;
}

bool GfPlayFactory::isDispCommonMessage(u32 window) { return GfPlayComMenuCommon::isDisp(window); }

u32 GfPlayFactory::getDispCommonMessage(u32 window) { return GfPlayComMenuCommon::getResult(window); }

void GfPlayFactory::createOpenChapterSave(u32 chapter) {
  if (GfGameManager::isScenarioGame() && !GfGameManager::isLeaveGameForDebug()) {
    GfSequentialPlay::beginCommand(GfSequentialPlay::TYPE_SEQUENCE);
    GfSequentialPlay::pushPause(PAUSE_BITS_SYSTEM_MENU);
    GfSequentialPlay::pushState(GF_STATE_MENU);
    GfSequentialPlay::addMenuChapterSave(chapter);
    GfSequentialPlay::popState();
    GfSequentialPlay::popPause();
    GfSequentialPlay::play();
  }
}

bool GfPlayFactory::isDispChapterSave() { return GfPlayComMenuChapterSave::isDisp(); }

void GfPlayFactory::createOpenZoneUI(u32 zone) {
  if (GfGameManager::isLeaveGameForDebug()) {
    return;
  }
  GfSequentialPlay::beginCommand(GfSequentialPlay::TYPE_NORMAL);
  GfSequentialPlay::addEventFade();
  GfSequentialPlay::addMenuZone(zone);
  GfSequentialPlay::play();
}

void GfPlayFactory::createOpenChapterUI(u32 chapter) {
  if (GfGameManager::isLeaveGameForDebug()) {
    return;
  }
  GfSequentialPlay::beginCommand(GfSequentialPlay::TYPE_SEQUENCE);
  GfSequentialPlay::addEventFade();
  GfSequentialPlay::addMenuChapter(chapter);
  GfSequentialPlay::play();
}

void GfPlayFactory::createOpenChapterEndUI(u32 chapter) {
  if (GfGameManager::isLeaveGameForDebug()) {
    return;
  }
  GfSequentialPlay::beginCommand(GfSequentialPlay::TYPE_SEQUENCE);
  GfSequentialPlay::addMenuChapterEnd(chapter);
  GfSequentialPlay::play();
}

void GfPlayFactory::createOpenDummyTutorial(u32 tutorial) {
  if (GfGameManager::isLeaveGameForDebug()) {
    return;
  }
  GfSequentialPlay::beginCommand(GfSequentialPlay::TYPE_SEQUENCE);
  GfSequentialPlay::addMenuDummyTutorial(tutorial);
  GfSequentialPlay::play();
}

void GfPlayFactory::createBattleStart(bool isStart) {
  if (GfGameManager::isLeaveGameForDebug()) {
    return;
  }
  GfSequentialPlay::beginCommand(GfSequentialPlay::TYPE_NORMAL);
  GfSequentialPlay::addBattleStart(isStart);
  GfSequentialPlay::play();
}

void GfPlayFactory::createGimmickTaskComplete(gmk::GmkType type, u32 task, f32 time) {
  if (GfGameManager::isLeaveGameForDebug()) {
    return;
  }
  GfSequentialPlay::beginCommand(GfSequentialPlay::TYPE_SEQUENCE);
  GfSequentialPlay::pushState(GF_STATE_GIMMICK_TASK);
  GfSequentialPlay::addGimmickTaskComplete(type, task, time);
  GfSequentialPlay::popState();
  GfSequentialPlay::play();
}

bool GfPlayFactory::createChainAttack() {
  if (GfGameManager::isLeaveGameForDebug()) {
    return false;
  }
  if (GfGameManager::isControlFree()) {
    GfSequentialPlay::beginCommand(GfSequentialPlay::TYPE_NORMAL);
    GfSequentialPlay::pushPause(PAUSE_BITS_SYSTEM_MENU);
    GfSequentialPlay::pushState(GF_STATE_CHAIN_ATTACK);
    GfSequentialPlay::addChainAttack();
    GfSequentialPlay::popState();
    GfSequentialPlay::popPause();
    GfSequentialPlay::play();
    return true;
  }
  return false;
}

bool GfPlayFactory::createArtsMovie(const char *name) {
  if (!GfGameManager::isLeaveGameForDebug() && GfGameManager::isControlFree()) {
    GfSequentialPlay::beginCommand(GfSequentialPlay::TYPE_NORMAL);
    GfSequentialPlay::pushPause(PAUSE_BITS_SYSTEM_MENU);
    GfSequentialPlay::pushState(GF_STATE_ARTS_MOVIE);
    GfSequentialPlay::addArtsMovie(name);
    GfSequentialPlay::popState();
    GfSequentialPlay::popPause();
    GfSequentialPlay::play();
    return true;
  }
  return false;
}

void GfPlayFactory::createSkipTravel(u32 mapjump) {
  if (!GfGameManager::isLeaveGameForDebug()) {
    GfMapjumpInfo info(mapjump);
    info.isSkipTravel = true;
    createMapjump(info);
  }
}

bool GfPlayFactory::createResetBladeForBattleEnd(u32 partyId, int blade, bool isPlayerStop) {
  if (GfPlayComResetBlade::isPlaying(partyId)) {
    return false;
  }
  GfObjAcc driver(GfGameParty::getHandleDriver(partyId));
  if (driver.isBattle()) {
    return false;
  }
  if (GfPlayComWaitBattleEnd::s_activate > 0) {
    GfReqCommand::reqChangeBladeWithSetId(partyId, blade, true);
    return true;
  }
  if (GfSequentialPlay::isInnerState(GF_STATE_EVENT) || GfSequentialPlay::isSequenceSpecialAction() ||
      GfSequentialPlay::isExistResetBladeParty(partyId)) {
    return false;
  }
  GfSequentialPlay::beginCommand(GfSequentialPlay::TYPE_NORMAL);
  if (isPlayerStop) {
    GfSequentialPlay::addResetBladePlayerStop(true);
    GfSequentialPlay::pushState(GF_STATE_RESET_BLADE);
    GfSequentialPlay::addResetBlade(partyId, blade);
    GfSequentialPlay::popState();
    GfSequentialPlay::addResetBladePlayerStop(false);
  } else {
    GfSequentialPlay::pushState(GF_STATE_RESET_BLADE);
    GfSequentialPlay::addResetBlade(partyId, blade);
    GfSequentialPlay::popState();
  }
  GfSequentialPlay::play();
  return true;
}

bool GfPlayFactory::createResetBladeForBladeSwitch(u32 partyId, int blade) {
  if (GfPlayComResetBlade::isPlaying(partyId)) {
    return false;
  }
  GfObjAcc driver(GfGameParty::getHandleDriver(partyId));
  if (driver.isBattle()) {
    return false;
  }
  if (GfPlayComWaitBattleEnd::s_activate > 0) {
    GfReqCommand::reqChangeBladeWithSetId(partyId, blade, true);
    return true;
  }
  if (GfSequentialPlay::isInnerState(GF_STATE_EVENT) || GfSequentialPlay::isSequenceSpecialAction() ||
      GfSequentialPlay::isExistResetBladeParty(partyId)) {
    return false;
  }
  GfSequentialPlay::beginCommand(GfSequentialPlay::TYPE_NORMAL);
  GfSequentialPlay::pushState(GF_STATE_RESET_BLADE);
  GfSequentialPlay::addResetBlade(partyId, blade);
  GfSequentialPlay::popState();
  GfSequentialPlay::play();
  return true;
}

void GfPlayFactory::createHomuraHikariCurrent(u32 partyId, int blade) {
  if (GfPlayComResetBlade::isPlaying(partyId)) {
    return;
  }
  GfSequentialPlay::beginCommand(GfSequentialPlay::TYPE_SEQUENCE);
  GfSequentialPlay::pushState(GF_STATE_RESET_BLADE);
  GfSequentialPlay::addResetBlade(partyId, blade);
  GfSequentialPlay::popState();
  GfSequentialPlay::play();
}

void GfPlayFactory::createMoverSwitch() {
  GfObjAcc leader(GfGameManager::getPartyLeaderDriver());
  if (!leader.isBattle() && !GfSequentialPlay::isInnerState(GF_STATE_EVENT)) {
    GfSequentialPlay::beginCommand(GfSequentialPlay::TYPE_NORMAL);
    GfSequentialPlay::pushState(GF_STATE_RESET_BLADE);
    GfSequentialPlay::addMoverSwitch();
    GfSequentialPlay::popState();
    GfSequentialPlay::play();
  }
}

void GfPlayFactory::createHoodHomuraBattou() {
  GfSequentialPlay::beginCommand(GfSequentialPlay::TYPE_NORMAL);
  GfSequentialPlay::pushState(GF_STATE_RESET_BLADE);
  GfSequentialPlay::addHoodHomuraBattou();
  GfSequentialPlay::popState();
  GfSequentialPlay::play();
}

} // namespace gf
