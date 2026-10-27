#include "gf/game/sequential_play/gf_sequential_play.h"

#include "fw/fw_camera.h"
#include "gf/field/gf_field_map_gimmick.h"
#include "gf/game/gf_game_manager.h"
#include "gf/game/gf_game_scene.h"
#include "gf/game/quest/gf_quest_id.h"
#include "gf/game/sequential_play/gf_play_command.h"
#include "gf/gf_pause.h"
#include "mm_mtl/rtti.h"

namespace gf {

namespace {

constexpr f32 BATTLE_START_END_WAIT_TIME = 0.3f;
constexpr f32 BATTLE_START_END_RIDE_WAIT_TIME = 0.6f;

} // namespace

bool GfSequentialPlay::isPlay() { return !get()->unknown08.empty() || !get()->unknown1850.empty(); }

void GfSequentialPlay::initialize(const GfSetupParam &) { unknown20f4 = true; }

bool GfSequentialPlay::isInitialized() {
  if (get() != nullptr) {
    return get()->unknown20f4;
  }
  return false;
}

bool GfSequentialPlay::play() {
  get()->unknown20f0 = TYPE_NORMAL;
  return true;
}

bool GfSequentialPlay::isCancel() { return get()->unknown1228; }

void GfSequentialPlay::beginCommand(TYPE type) { get()->unknown20f0 = type; }

void GfSequentialPlay::pauseOn(u32 pauseBits) {
  GfSequentialPlay *sequentialPlay = get();
  sequentialPlay->unknown1230.push(GfPause::reqPause(pauseBits));
}

void GfSequentialPlay::pauseOff() { GfPause::destroyHandle(get()->unknown1230.pop_back()); }

GF_STATE GfSequentialPlay::execPushState(GF_STATE state) {
  GfSequentialPlay *sequentialPlay = get();
  GF_STATE previousState = GfGameManager::getState();
  sequentialPlay->unknown1640.push(state);
  GfGameManager::setState(state, false);
  return previousState;
}

GF_STATE GfSequentialPlay::execPopState() {
  GfSequentialPlay *sequentialPlay = get();
  GF_STATE state = sequentialPlay->unknown1640.pop_back();
  GfGameManager::setState(sequentialPlay->unknown1640.empty() ? GF_STATE_CONTROL : sequentialPlay->unknown1640.back(), true);
  return state;
}

void GfSequentialPlay::addWait(f32 time) { addCommand(GfPlayComWait::create(time)); }

void GfSequentialPlay::addWaitEvent(f32 time, GF_OBJ_HANDLE *handle) { addCommand(GfPlayComWaitEvent::create(time, handle)); }

void GfSequentialPlay::addMapjump(const GfMapjumpInfo &info) { addCommand(GfPlayComMapjump::create(info)); }

void GfSequentialPlay::addWaitBattleEnd(u32 battle) { addCommand(GfPlayComWaitBattleEnd::create(battle)); }

void GfSequentialPlay::addEventPlayerStop(bool isStop) { addCommand(GfPlayComEventPlayerStop::create(isStop)); }

void GfSequentialPlay::addResetBladePlayerStop(bool isStop) { addCommand(GfPlayComResetBladePlayerStop::create(isStop)); }

void GfSequentialPlay::addAfterEventScript(u32 event) { addCommand(GfPlayComAfterEventScript::create(event)); }

void GfSequentialPlay::pushPause(u32 pauseBits) { addCommand(GfPlayComPause::create(pauseBits)); }

void GfSequentialPlay::popPause() { addCommand(GfPlayComPause::create(0)); }

void GfSequentialPlay::pushState(GF_STATE state) { addCommand(GfPlayComState::create(state, get()->unknown20f0 != TYPE_NORMAL)); }

void GfSequentialPlay::popState() { addCommand(GfPlayComState::create(GF_STATE(0), false)); }

void GfSequentialPlay::addEventFade() { addCommand(GfPlayComEventFade::create()); }

void GfSequentialPlay::addEvent(int event, u32 param0, u32 param1, bool isEndFadeOut) { addCommand(GfPlayComEvent::create(event, param0, param1, isEndFadeOut)); }

void GfSequentialPlay::addEvent(const char *name, u32 param0, u32 param1, bool isEndFadeOut) { addCommand(GfPlayComEvent::create(name, param0, param1, isEndFadeOut)); }

void GfSequentialPlay::addCallbackEventSequence(int sequence, bool isStart) { addCommand(GfPlayComCallbackEventSequence::create(sequence, isStart)); }

void GfSequentialPlay::addMenuKizunaring(u32 blade) { addCommand(GfPlayComMenuKizunaring::create(blade)); }

void GfSequentialPlay::addMenuPrecious(u32 item) { addCommand(GfPlayComMenuPrecious::create(item)); }

void GfSequentialPlay::addMenuObjCommonText(GfMenuObjCommonText::OpenKizunaParam &param) { addCommand(GfPlayComMenuObjCommonText::create(param)); }

int GfSequentialPlay::addMenuCommon(u32 window) {
  GfPlayComMenuCommon *command = GfPlayComMenuCommon::create(window);
  addCommand(command);
  return command->unknown14;
}

int GfSequentialPlay::addMenuCommon(const MenuCommonWindowParam &param) {
  GfPlayComMenuCommonFromParam *command = GfPlayComMenuCommonFromParam::create(param);
  addCommand(command);
  return command->unknown60;
}

void GfSequentialPlay::addMenuChapterSave(u32 chapter) { addCommand(GfPlayComMenuChapterSave::create(chapter)); }

void GfSequentialPlay::addMenuChapter(u32 chapter) { addCommand(GfPlayComMenuChapter::create(chapter)); }

void GfSequentialPlay::addMenuChapterEnd(u32 chapter) { addCommand(GfPlayComMenuChapterEnd::create(chapter)); }

void GfSequentialPlay::addMenuZone(u32 zone) { addCommand(GfPlayComMenuZone::create(zone)); }

void GfSequentialPlay::addMenuDummyTutorial(u32 tutorial) { addCommand(GfPlayComMenuDummyTutorial::create(tutorial)); }

void GfSequentialPlay::addOpenMenu(u32 type) { addCommand(GfPlayComOpenMenu::create(type)); }

void GfSequentialPlay::addOpenMenu2(u32 type, MAINMENU menu) { addCommand(GfPlayComOpenMenu2::create(type, menu)); }

void GfSequentialPlay::addStartTutorial(u32 tutorial) { addCommand(GfPlayComStartTutorial::create(tutorial)); }

void GfSequentialPlay::addMiniGame() { addCommand(GfPlayComMiniGame::create()); }

void GfSequentialPlay::addReturnTitle(const ParamReturnTitle &param) { addCommand(GfPlayComReturnTitle::create(param)); }

void GfSequentialPlay::addBattleStart(bool isStart) { addCommand(GfPlayComBattleStart::create(isStart)); }

void GfSequentialPlay::addBattleStartEnd() {
  if (GfPlayComBattleStart::get() == nullptr) {
    return;
  }
  f32 time;
  if (GfGameScene::get() == nullptr) {
    time = BATTLE_START_END_WAIT_TIME;
  } else {
    time = GfGameScene::get()->isRideParty(0) ? BATTLE_START_END_RIDE_WAIT_TIME : BATTLE_START_END_WAIT_TIME;
  }
  addCommand(GfPlayComWait::create(time));
}

void GfSequentialPlay::addMenuQuestList() { addCommand(GfPlayComMenuQuestList::create()); }

void GfSequentialPlay::addSalvage(GF_OBJ_HANDLE *handle) { addCommand(GfPlayComSalvage::create(handle)); }

void GfSequentialPlay::addCollect(GF_OBJ_HANDLE *handle) { addCommand(GfPlayComCollect::create(handle)); }

void GfSequentialPlay::addFieldTbox(GF_OBJ_HANDLE *handle) { addCommand(GfPlayComFieldTbox::create(handle)); }

void GfSequentialPlay::addMapGimmick(GF_OBJ_HANDLE *handle) { addCommand(GfPlayComFieldSeq::create(GfFieldMapGimmick::get(), handle)); }

void GfSequentialPlay::addGrave(GF_OBJ_HANDLE *handle) { addCommand(GfPlayComFieldSeq::create(GfFieldGrave::get(), handle)); }

void GfSequentialPlay::addJump(GF_OBJ_HANDLE *handle) { addCommand(GfPlayComFieldSeq::create(GfFieldJump::get(), handle)); }

void GfSequentialPlay::addWarp(GF_OBJ_HANDLE *handle) { addCommand(GfPlayComFieldSeq::create(GfFieldWarp::get(), handle)); }

void GfSequentialPlay::addWaitPlayerToStartGmkTuto() { addCommand(GfPlayComWaitPlayerToStartGmkTuto::create()); }

void GfSequentialPlay::addGmkTutorial(const char *name, u32 tutorial) { addCommand(GfPlayComGmkTutorialSeq::create(name, tutorial)); }

void GfSequentialPlay::addWaitGmkCameraEnd(mm::mtl::IntrusivePtr<fw::Camera> camera) { addCommand(GfPlayComGmkCameraSeq::create(camera)); }

void GfSequentialPlay::addPlayerDead(GfPlayerDead dead) { addCommand(GfPlayComPlayerDead::create(dead)); }

void GfSequentialPlay::addTalk(const GfSetupPfTalk &talk) { addCommand(GfPlayComTalk::create(talk)); }

void GfSequentialPlay::addQuestUIOrder(QuestID quest, bool isForce) { addCommand(GfPlayComQuestOrderUI::create(quest, isForce)); }

void GfSequentialPlay::addQuestUIComplete(QuestID quest, QuestID child, QSTATE state) { addCommand(GfPlayComQuestCompleteUI::create(quest, child, state)); }

void GfSequentialPlay::addGimmickTaskComplete(gmk::GmkType type, u32 task, f32 time) { addCommand(GfPlayComGimmickTaskComplete::create(type, task, time)); }

void GfSequentialPlay::addChainAttack() { addCommand(GfPlayComChainAttack::create()); }

void GfSequentialPlay::addArtsMovie(const char *name) { addCommand(GfPlayComArtsMovie::create(name)); }

void GfSequentialPlay::addResetBlade(u32 partyId, int blade) { addCommand(GfPlayComResetBlade::create(partyId, blade)); }

void GfSequentialPlay::addMoverSwitch() { addCommand(GfPlayComMoverSwitch::create()); }

void GfSequentialPlay::addHoodHomuraBattou() { addCommand(GfPlayComHoodHomuraBattou::create()); }

void GfSequentialPlay::startSignal(GfSequentialPlaySignal *signal) { addCommand(GfPlayComExecuteSignal::create(true, signal)); }

void GfSequentialPlay::endSignal(GfSequentialPlaySignal *signal) { addCommand(GfPlayComExecuteSignal::create(false, signal)); }

bool GfSequentialPlay::isInnerPause(u32 pauseBits) {
  GfSequentialPlay *sequentialPlay = get();
  for (GfPlayCom *command : sequentialPlay->unknown08) {
    if (command->unknown0c == PCOMTYPE_PAUSE) {
      if (command->getRTTI()->isKindOf(&GfPlayComPause::m_rtti) && (static_cast<GfPlayComPause *>(command)->unknown10 & pauseBits) == pauseBits) {
        return true;
      }
    }
  }
  for (GfPlayCom *command : sequentialPlay->unknown1850) {
    if (command->unknown0c == PCOMTYPE_PAUSE) {
      if (command->getRTTI()->isKindOf(&GfPlayComPause::m_rtti) && (static_cast<GfPlayComPause *>(command)->unknown10 & pauseBits) == pauseBits) {
        return true;
      }
    }
  }
  return GfPause::isPause(pauseBits);
}

bool GfSequentialPlay::isExistPauseType(GfPlayCom *command, u32 pauseBits) const {
  if (command->unknown0c == PCOMTYPE_PAUSE) {
    if (command->getRTTI()->isKindOf(&GfPlayComPause::m_rtti) && (static_cast<GfPlayComPause *>(command)->unknown10 & pauseBits) == pauseBits) {
      return true;
    }
  }
  return false;
}

bool GfSequentialPlay::isExistState(GfPlayCom *command, GF_STATE state) const {
  if (command->unknown0c == PCOMTYPE_STATE) {
    if (command->getRTTI()->isKindOf(&GfPlayComState::m_rtti) && static_cast<GfPlayComState *>(command)->unknown10 == state) {
      return true;
    }
  }
  return false;
}

int GfSequentialPlay::getRequestEvent() const {
  for (GfPlayCom *command : unknown1850) {
    if (command != nullptr && command->unknown0c == PCOMTYPE_EVENT) {
      if (command->getRTTI()->isKindOf(&GfPlayComEvent::m_rtti) && static_cast<GfPlayComEvent *>(command)->unknown18 != 0) {
        return static_cast<GfPlayComEvent *>(command)->unknown18;
      }
    }
  }
  for (GfPlayCom *command : unknown08) {
    if (command != nullptr && command->unknown0c == PCOMTYPE_EVENT) {
      if (command->getRTTI()->isKindOf(&GfPlayComEvent::m_rtti) && static_cast<GfPlayComEvent *>(command)->unknown18 != 0) {
        return static_cast<GfPlayComEvent *>(command)->unknown18;
      }
    }
  }
  return 0;
}

const char *GfSequentialPlay::getFuncName() {
  GfSequentialPlay *sequentialPlay = get();
  if (sequentialPlay != nullptr && !sequentialPlay->unknown08.empty()) {
    return sequentialPlay->unknown08.front()->getFuncName();
  }
  return "";
}

} // namespace gf
