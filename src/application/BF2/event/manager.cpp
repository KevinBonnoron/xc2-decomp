#include "event/manager.h"

#include "event/cmd_queue.h"
#include "event/cpu_manager.h"
#include "event/debug_manager.h"
#include "event/frame_manager.h"
#include "event/memory_manager.h"
#include "event/object_camera.h"
#include "event/object_manager.h"
#include "event/sche_manager.h"
#include "event/seq_info.h"
#include "event/seq_manager.h"
#include "event/shake_manager.h"
#include "event/ui_manager.h"
#include "fw/fw_debug.h"
#include "ml/dev_graph.h"
#include "mm_math/mm_col4.h"

#include "framework/lang_util.h"
#include "gf/game/event/gf_game_event.h"
#include "ml/proc_desktop.h"
#include "ml/scn.h"
#include "ml/win_view.h"
#include "ml/work_cpu.h"
#include "mtl/alloc_handle.h"

namespace ml {
class EventView;
} // namespace ml

namespace event {

// Inferred role: names of the sequence categories drawn by drawInfo; original name unknown.
static const char *const unknown033[] = {"      ", "[TALK]", " [FEV]", " [SEV]", "  [CS]", " [MOV]"};

void Manager::failureSkip() {
  mm::mtl::Singleton<DebugManager>::getPtr()->failureSkip();
  mm::mtl::Singleton<DebugManager>::getPtr()->setDisp(true);
  mm::mtl::Singleton<DebugManager>::getPtr()->playMessage("failure skip!! [%s.sb]", unknown230.c_str());
}

Manager::~Manager() {
  mm::mtl::Singleton<ScheManager>::getPtr()->destroy();
  mm::mtl::Singleton<ShakeManager>::get().destroy();
  mm::mtl::Singleton<MemoryManager>::getPtr()->destroy();
  ml::WorkCpu::removeBackgroundListener(this);
  unknown228->getView(-1)->detachWorkEvent(this);
  unknown20.clear();
}

void Manager::play(const char *name, gf::GF_OBJ_HANDLE *handle, u32 param0, u32 param1, u32 param2, u32 param3, bool isEndFadeOut) {
  m_languageMode = LANGUAGE_MODE_UNKNOWN_0;
  unknown280 = handle;
  unknown288[0] = param0;
  unknown288[1] = param1;
  unknown288[2] = param2;
  unknown288[3] = param3;
  unknown18.set(FLAG_UNKNOWN_2, isEndFadeOut);
  if (!isPlay()) {
    mm::mtl::Singleton<SeqManager>::getPtr()->play(name);
  }
  unknown18.unknown004(FLAG_UNKNOWN_0);
  unknown18.unknown004(FLAG_UNKNOWN_1);
  unknown18.set(FLAG_UNKNOWN_0);
}

bool Manager::end() {
  if (isPlay()) {
    if (!unknown1c.test(STATE_UNKNOWN_5)) {
      execMessage(MSG_TYPE_UNKNOWN_11);
      unknown1c.set(STATE_UNKNOWN_5);
    }
    if (unknown1c.test(STATE_UNKNOWN_0)) {
      return false;
    }
    unknown1c.unknown004(STATE_UNKNOWN_5);
  }
  return true;
}

void Manager::stop() {
  if (isPlay()) {
    mm::mtl::Singleton<DebugManager>::getPtr()->setPlayCancel(true);
    end();
  }
}

void Manager::update() {
  if (unknown1c.test(STATE_UNKNOWN_0)) {
    execMessage(MSG_TYPE_UNKNOWN_14);
  }
  execMessage(MSG_TYPE_UNKNOWN_15);
  if (unknown1c.test(STATE_UNKNOWN_0)) {
    SeqManager *seq = mm::mtl::Singleton<SeqManager>::getPtr();
    if (!seq->unknown200.isEmpty() && seq->unknown200.unknown001() == &seq->m_end_wait) {
      execMessage(MSG_TYPE_UNKNOWN_12);
      execMessage(MSG_TYPE_UNKNOWN_13);
      clear();
    }
  }
  if (isPlay()) {
    if (mm::mtl::Singleton<SeqManager>::getPtr()->unknown170 & SeqManager::FLAG_UNKNOWN_0) {
      execMessage(MSG_TYPE_UNKNOWN_2);
      clear();
      clearAlways();
      unknown18.unknown004(FLAG_UNKNOWN_0);
      unknown18.unknown004(FLAG_UNKNOWN_1);
      unknown18.set(FLAG_UNKNOWN_1);
    }
    if (mm::mtl::Singleton<SeqManager>::getPtr()->unknown170 & SeqManager::FLAG_UNKNOWN_1) {
      execMessage(MSG_TYPE_UNKNOWN_2);
      clearAlways();
    }
  }
}

bool Manager::init(const char *name) {
  if (!unknown1c.test(STATE_UNKNOWN_0)) {
    unknown1c.clear();
    unknown230 = name;
    unknown254 = name;
    SeqManager *seq = mm::mtl::Singleton<SeqManager>::getPtr();
    if (seq->unknown200.isEmpty() || seq->unknown200.unknown001() != &seq->m_play_next) {
      if (!ml::ProcDesktop::isDispInfo()) {
        unknown18.set(FLAG_UNKNOWN_10);
      }
      execMessage(MSG_TYPE_UNKNOWN_1);
    }
    execMessage(MSG_TYPE_UNKNOWN_3);
    execMessage(MSG_TYPE_UNKNOWN_4);
    unknown18.set(FLAG_UNKNOWN_0);
    unknown1c.set(STATE_UNKNOWN_0);
  }
  SeqManager *seq = mm::mtl::Singleton<SeqManager>::getPtr();
  return !seq->unknown200.isExist(&seq->m_start_areajump);
}

bool Manager::startScene(const char *name, int pageID) {
  if (!unknown1c.test(STATE_UNKNOWN_2)) {
    unknown254 = name;
    unknown278 = pageID;
    execMessage(MSG_TYPE_UNKNOWN_7);
    unknown1c.set(STATE_UNKNOWN_2);
  }
  SeqManager *seq = mm::mtl::Singleton<SeqManager>::getPtr();
  if (seq->unknown200.isExist(&seq->m_start_form) || seq->unknown200.isExist(&seq->m_start_change) || seq->unknown200.isExist(&seq->m_start_env_seam) ||
      seq->unknown200.isExist(&seq->m_start_weather) || seq->unknown200.isExist(&seq->m_start_streaming0) || seq->unknown200.isExist(&seq->m_start_capture_wait)) {
    return false;
  }
  unknown1c.unknown004(STATE_UNKNOWN_2);
  return true;
}

bool Manager::startPage(const char *name, int pageID, f32 maxFrame) {
  if (!unknown1c.test(STATE_UNKNOWN_3)) {
    execMessage(MSG_TYPE_UNKNOWN_8);
    mm::mtl::Singleton<FrameManager>::getPtr()->setInfomation(name, pageID, maxFrame);
    unknown1c.set(STATE_UNKNOWN_3);
  }
  SeqManager *seq = mm::mtl::Singleton<SeqManager>::getPtr();
  if (seq->unknown200.isExist(&seq->m_start_streaming1)) {
    return false;
  }
  unknown1c.unknown004(STATE_UNKNOWN_3);
  return true;
}

bool Manager::endScene() {
  if (!unknown1c.test(STATE_UNKNOWN_4)) {
    execMessage(MSG_TYPE_UNKNOWN_9);
    unknown1c.set(STATE_UNKNOWN_4);
  }
  SeqManager *seq = mm::mtl::Singleton<SeqManager>::getPtr();
  if (seq->unknown200.isExist(&seq->m_exec) || seq->unknown200.isExist(&seq->m_exec_fadeout) || seq->unknown200.isExist(&seq->m_exec_grass) || seq->unknown200.isExist(&seq->m_end_change)) {
    return false;
  }
  execMessage(MSG_TYPE_UNKNOWN_10);
  unknown1c.unknown004(STATE_UNKNOWN_4);
  return true;
}

bool Manager::setupSceneEnd() {
  if (!unknown1c.test(STATE_UNKNOWN_1)) {
    execMessage(MSG_TYPE_UNKNOWN_6);
    unknown1c.set(STATE_UNKNOWN_1);
  }
  if (mm::mtl::Singleton<SeqManager>::getPtr()->isSetupSceneEnd()) {
    unknown1c.unknown004(STATE_UNKNOWN_1);
    return true;
  }
  return false;
}

void Manager::nextEvent(int next) {
  if (isPlay()) {
    mm::mtl::Singleton<SeqManager>::getPtr()->nextEvent(next);
  }
}

void Manager::finishNewGameWait() { mm::mtl::Singleton<UIManager>::getPtr()->finishNewGameWait(); }

bool Manager::isPlayCancel() const { return mm::mtl::Singleton<DebugManager>::getPtr()->isPlayCancel(); }

void Manager::clearAlways() {
  if (unknown18.test(FLAG_UNKNOWN_10)) {
    unknown18.unknown004(FLAG_UNKNOWN_10);
  }
  unknown18.unknown004(FLAG_UNKNOWN_0);
}

void Manager::clear() {
  unknown280 = reinterpret_cast<gf::GF_OBJ_HANDLE *>(-1);
  unknown288[0] = 0;
  unknown288[1] = 0;
  unknown288[2] = 0;
  unknown288[3] = 0;
  m_languageMode = LANGUAGE_MODE_UNKNOWN_0;
  unknown18.unknown004(FLAG_UNKNOWN_2);
  unknown1c.clear();
}

void Manager::execMessage(MSG_TYPE type) {
  for (u32 i = 0; i < unknown20.size(); i++) {
    unknown20[i]->OnEventProc(type);
  }
}

void Manager::render() { ml::ProcDesktop::isDispInfo(); }

void Manager::drawInfo() {
  int x = ml::DevGraph::getRootWidth() >> 1;
  // The game computes x - 160 (0x710013b51c, sub w19) before the second FrameManager::getPtr call and keeps it for the
  // white and red draws; without the local the subtraction is placed at its first use (235 vs 236 instructions).
  int left = x - 160;
  const FrameInfo &info = mm::mtl::Singleton<FrameManager>::getPtr()->frameInfo();
  f32 frame = mm::mtl::Singleton<FrameManager>::getPtr()->getFrame();
  int frames = static_cast<int>(frame);
  // The game computes the three time fields (0x710013b564 to 0x710013b59c) before the SeqManager::getPtr call
  // (0x710013b5c8) of the category name; as arguments of format they would follow the call.
  int minutes = frames / 1800;
  int seconds = frames % 1800 / 30;
  int rest = frames % 30;
  mm::mtl::FixStr<64> text;
  text.format("%s %s  %02d:%02d:%02d [%.1f]", unknown033[mm::mtl::Singleton<SeqManager>::getPtr()->m_seqInfo.unknown54], unknown254.c_str(), minutes, seconds, rest, frame);
  fw::debug::drawFont(x - 159, 61, mm::Col4::black, text.c_str());
  fw::debug::drawFont(left, 60, mm::Col4::white, text.c_str());
  if (mm::mtl::Singleton<FrameManager>::getPtr()->isWaiting()) {
    fw::debug::drawFont(x - 59, 77, mm::Col4::black, "WAITING..");
    fw::debug::drawFont(x - 60, 76, mm::Col4::white, "WAITING..");
  }
  if (0.0f < info.unknown10) {
    text.format("                                     +skip%.2f", info.unknown10);
    fw::debug::drawFont(x - 159, 61, mm::Col4::black, text.c_str());
    fw::debug::drawFont(left, 60, mm::Col4::red, text.c_str());
  }
  if (mm::mtl::Singleton<ObjectManager>::getPtr()->getCameraCount() != 0) {
    const char *cutName = mm::mtl::Singleton<ObjectManager>::getPtr()->getCamera(0)->getCutName();
    if (*cutName != '\0') {
      fw::debug::drawFont(x - 69, 78, mm::Col4::black, cutName);
      fw::debug::drawFont(x - 70, 77, mm::Col4::white, cutName);
    }
  }
}

void Manager::tail() {
  if (unknown1c.test(STATE_UNKNOWN_0)) {
    execMessage(MSG_TYPE_UNKNOWN_18);
  }
  execMessage(MSG_TYPE_UNKNOWN_19);
}

void Manager::post() {}

bool Manager::setupScene(const char *name) {
  unknown254 = name;
  execMessage(MSG_TYPE_UNKNOWN_5);
  return true;
}

void Manager::setLanguageMode(bool isEnable, LANGUAGE_MODE mode) { m_languageMode = isEnable ? mode : LANGUAGE_MODE_UNKNOWN_0; }

bool Manager::checkLanguageMode() const {
  switch (m_languageMode) {
  case LANGUAGE_MODE_UNKNOWN_1:
    return fw::LangUtil::getVoiceType() == 0;
  case LANGUAGE_MODE_UNKNOWN_2:
    return fw::LangUtil::getVoiceType() == 1;
  default:
    return true;
  }
}

void Manager::setDebugPlayOnetime(bool isPlayOnetime) { mm::mtl::Singleton<DebugManager>::getPtr()->setPlayOnetime(isPlayOnetime); }

bool Manager::isDebugPlayOnetime() const { return mm::mtl::Singleton<DebugManager>::getPtr()->isPlayOnetime(); }

void Manager::setDebugFastSkipDisable(bool isDisable) { mm::mtl::Singleton<DebugManager>::getPtr()->setFastSkipDisable(isDisable); }

void Manager::setDebugAgeingSkipEnable(bool isEnable) { mm::mtl::Singleton<DebugManager>::getPtr()->setAgeingSkipEnable(isEnable); }

void Manager::setDebugDisableBgm(bool isDisable) { mm::mtl::Singleton<DebugManager>::getPtr()->setDisableBgm(isDisable); }

void Manager::setDebugReplaceDefaultEquip(bool isReplace, u32 slot, u32 item) { mm::mtl::Singleton<DebugManager>::getPtr()->setReplaceDefaultEquip(isReplace, slot, item); }

bool Manager::isReplaceDefaultEquip(u32 slot, u32 *item) const { return mm::mtl::Singleton<DebugManager>::getPtr()->isReplaceDefaultEquip(slot, item); }

void Manager::setDebugReplaceMaximumEquip(bool isReplace) { mm::mtl::Singleton<DebugManager>::getPtr()->setReplaceMaximumEquip(isReplace); }

bool Manager::isDebugReplaceMaximumEquip() const { return mm::mtl::Singleton<DebugManager>::getPtr()->isReplaceMaximumEquip(); }

void Manager::setDebugReplaceMaximumBlade(bool isReplace) { mm::mtl::Singleton<DebugManager>::getPtr()->setReplaceMaximumBlade(isReplace); }

bool Manager::isDebugReplaceMaximumBlade() const { return mm::mtl::Singleton<DebugManager>::getPtr()->isReplaceMaximumBlade(); }

void Manager::setSyncFreeCam(bool isSync, bool isOneTime) { mm::mtl::Singleton<DebugManager>::getPtr()->setSyncFreeCam(isSync, isOneTime); }

Manager *Manager::create(ml::Scn *scn) {
  destroy();
  mtl::ALLOC_HANDLE handle = gf::GfGameEvent::getEventMem();
  return new (handle, nullptr, 0, 4, false) Manager(scn);
}

void Manager::destroy() {
  if (get()) {
    delete get();
  }
}

bool Manager::OnKeyDown(ml::EventView *view) { return false; }

void Manager::bkgHomeMenu(bool isOpen) {
  mm::mtl::Singleton<CpuManager>::getPtr()->pauseHome(true);
  if (!isOpen) {
    mm::mtl::Singleton<CpuManager>::getPtr()->pauseHome(false);
  }
}

} // namespace event

template mm::mtl::PtrSingleton<event::Manager>::~PtrSingleton();
