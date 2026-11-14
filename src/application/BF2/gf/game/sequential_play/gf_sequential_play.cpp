#include "gf/game/sequential_play/gf_sequential_play.h"

#include "fw/fw_camera.h"
#include "gf/field/gf_field_map_gimmick.h"
#include "gf/game/gf_game_manager.h"
#include "gf/game/gf_game_scene.h"
#include "gf/game/quest/gf_quest_id.h"
#include "gf/game/sequential_play/gf_play_command.h"
#include "gf/gf_allocator.h"
#include "gf/gf_manager.h"
#include "gf/gf_pause.h"
#include "mm_mtl/algorithm.h"
#include "mm_mtl/rtti.h"

namespace gf {

namespace {

constexpr f32 unknown030 = 0.3f; // Inferred role: battle start end wait time; original name unknown.
constexpr f32 unknown041 = 0.6f; // Inferred role: battle start end ride wait time; original name unknown.

} // namespace

GfSequentialPlay::GfSequentialPlay(const GfSetupParam &) : unknown1228(false), unknown20f0(TYPE_UNKNOWN_0), unknown20f4(true) {}

void GfSequentialPlay::initialize(const GfSetupParam &) { unknown20f4 = true; }

GfSequentialPlay::~GfSequentialPlay() {}

#line 52
void GfSequentialPlay::build(const GfSetupParam &param) { new (getAllocator(ALLOCATOR_UNKNOWN_1), __FILE__, __LINE__, 8) GfSequentialPlay(param); }

void GfSequentialPlay::destroy() {
  GfSequentialPlay *sequentialPlay = get();
  sequentialPlay->finalize();
  delete sequentialPlay;
}

void GfSequentialPlay::finalize() {
  while (isPlay()) {
    GfSleep(1);
  }
  destroyCommand();
  unknown20f4 = false;
}

bool GfSequentialPlay::isPlay() { return !get()->unknown08.empty() || !get()->unknown1850.empty(); }

void GfSequentialPlay::destroyCommand() {
  if (!isPlay()) {
    for (GfPlayCom *&command : unknown08) {
      if (command != nullptr) {
        delete command;
        command = nullptr;
      }
    }
    unknown08.clear();
    for (GfPlayCom *&command : unknown1850) {
      if (command != nullptr) {
        delete command;
        command = nullptr;
      }
    }
    unknown1850.clear();
  }
}

bool GfSequentialPlay::isInitialized() {
  if (get() != nullptr) {
    return get()->unknown20f4;
  }
  return false;
}

void GfSequentialPlay::postUpdate(const fw::UpdateInfo &info) {
  GfSequentialPlay *sequentialPlay = get();
  if (sequentialPlay == nullptr || !sequentialPlay->unknown20f4) {
    return;
  }
  if (sequentialPlay->unknown1850.size() > 0) {
    for (mm::mtl::FixedList<GfPlayCom *, 128>::iterator it = sequentialPlay->unknown1850.begin(); it != sequentialPlay->unknown1850.end(); ++it) {
      sequentialPlay->unknown08.push_front(*it);
    }
    sequentialPlay->unknown1850.clear();
  }
  while (!sequentialPlay->unknown08.empty()) {
    mm::mtl::FixedList<GfPlayCom *, 256>::iterator it = sequentialPlay->unknown08.begin();
    GfPlayCom *command = *it;
    if (command->unknown08) {
      command->unknown08 = false;
      command->start();
    }
    if (!command->update(info, GfManager::isDestroyNow())) {
      return;
    }
    command->end();
    bool isContinue = command->unknown09;
    delete command;
    sequentialPlay->unknown08.erase(it);
    if (!isContinue) {
      break;
    }
  }
}

bool GfSequentialPlay::play() {
  get()->unknown20f0 = TYPE_UNKNOWN_0;
  return true;
}

bool GfSequentialPlay::isCancel() { return get()->unknown1228; }

void GfSequentialPlay::beginCommand(TYPE type) { get()->unknown20f0 = type; }

void GfSequentialPlay::addCommand(GfPlayCom *command) {
  if (command != nullptr) {
    GfSequentialPlay *sequentialPlay = get();
    if (sequentialPlay->unknown20f0 == TYPE_UNKNOWN_1) {
      sequentialPlay->unknown1850.push_front(command);
    } else {
      sequentialPlay->unknown08.push_back(command);
    }
  }
}

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
  GfGameManager::setState(sequentialPlay->unknown1640.empty() ? GF_STATE_UNKNOWN_3 : sequentialPlay->unknown1640.back(), true);
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

void GfSequentialPlay::pushState(GF_STATE state) { addCommand(GfPlayComState::create(state, get()->unknown20f0 != TYPE_UNKNOWN_0)); }

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
    time = unknown030;
  } else {
    time = GfGameScene::get()->isRideParty(0) ? unknown041 : unknown030;
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

bool GfSequentialPlay::hasCommand(PCOMTYPE type, GfPlayCom *command) {
  GfSequentialPlay *sequentialPlay = get();
  mm::mtl::FixedList<GfPlayCom *, 256>::iterator it = mm::mtl::find(sequentialPlay->unknown08.begin(), sequentialPlay->unknown08.end(), command);
  if (sequentialPlay->unknown08.end() != it) {
    for (++it; it != sequentialPlay->unknown08.end(); ++it) {
      if ((*it)->unknown08 && (*it)->unknown0c == type) {
        return true;
      }
    }
  }
  return false;
}

bool GfSequentialPlay::isExistResetBladeParty(u32 partyId) {
  for (GfPlayCom *command : get()->unknown08) {
    if (command != nullptr && command->unknown0c == PCOMTYPE_UNKNOWN_42) {
      if (command->getRTTI()->isKindOf(&GfPlayComResetBlade::m_rtti) && static_cast<GfPlayComResetBlade *>(command)->unknown14 == partyId) {
        return true;
      }
    }
  }
  return false;
}

void GfSequentialPlay::startSignal(GfSequentialPlaySignal *signal) { addCommand(GfPlayComExecuteSignal::create(true, signal)); }

void GfSequentialPlay::endSignal(GfSequentialPlaySignal *signal) { addCommand(GfPlayComExecuteSignal::create(false, signal)); }

bool GfSequentialPlay::isInnerState(GF_STATE state) {
  GfSequentialPlay *sequentialPlay = get();
  for (GfPlayCom *command : sequentialPlay->unknown08) {
    if (sequentialPlay->isExistState(command, state)) {
      return true;
    }
  }
  for (GfPlayCom *command : sequentialPlay->unknown1850) {
    if (sequentialPlay->isExistState(command, state)) {
      return true;
    }
  }
  return sequentialPlay->unknown1640.find(state) != sequentialPlay->unknown1640.end();
}

bool GfSequentialPlay::isInnerPause(u32 pauseBits) {
  GfSequentialPlay *sequentialPlay = get();
  for (GfPlayCom *command : sequentialPlay->unknown08) {
    if (command->unknown0c == PCOMTYPE_UNKNOWN_1) {
      if (command->getRTTI()->isKindOf(&GfPlayComPause::m_rtti) && (static_cast<GfPlayComPause *>(command)->unknown10 & pauseBits) == pauseBits) {
        return true;
      }
    }
  }
  for (GfPlayCom *command : sequentialPlay->unknown1850) {
    if (command->unknown0c == PCOMTYPE_UNKNOWN_1) {
      if (command->getRTTI()->isKindOf(&GfPlayComPause::m_rtti) && (static_cast<GfPlayComPause *>(command)->unknown10 & pauseBits) == pauseBits) {
        return true;
      }
    }
  }
  return GfPause::isPause(pauseBits);
}

bool GfSequentialPlay::isExistPauseType(GfPlayCom *command, u32 pauseBits) const {
  if (command->unknown0c == PCOMTYPE_UNKNOWN_1) {
    if (command->getRTTI()->isKindOf(&GfPlayComPause::m_rtti) && (static_cast<GfPlayComPause *>(command)->unknown10 & pauseBits) == pauseBits) {
      return true;
    }
  }
  return false;
}

bool GfSequentialPlay::isExistState(GfPlayCom *command, GF_STATE state) const {
  if (command->unknown0c == PCOMTYPE_UNKNOWN_2) {
    if (command->getRTTI()->isKindOf(&GfPlayComState::m_rtti) && static_cast<GfPlayComState *>(command)->unknown10 == state) {
      return true;
    }
  }
  return false;
}

int GfSequentialPlay::getRequestEvent() const {
  for (GfPlayCom *command : unknown1850) {
    if (command != nullptr && command->unknown0c == PCOMTYPE_UNKNOWN_9) {
      if (command->getRTTI()->isKindOf(&GfPlayComEvent::m_rtti) && static_cast<GfPlayComEvent *>(command)->unknown18 != 0) {
        return static_cast<GfPlayComEvent *>(command)->unknown18;
      }
    }
  }
  for (GfPlayCom *command : unknown08) {
    if (command != nullptr && command->unknown0c == PCOMTYPE_UNKNOWN_9) {
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

template mm::mtl::PtrSingleton<gf::GfSequentialPlay>::~PtrSingleton();
template mm::mtl::FixedList<gf::GfPlayCom *, 256>::iterator mm::mtl::FixedList<gf::GfPlayCom *, 256>::erase(mm::mtl::FixedList<gf::GfPlayCom *, 256>::iterator);
