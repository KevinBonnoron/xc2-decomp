#include "event/manager.h"

#include "event/cpu_manager.h"
#include "event/debug_manager.h"
#include "event/ui_manager.h"

#include "framework/lang_util.h"
#include "gf/game/event/gf_game_event.h"
#include "ml/proc_desktop.h"
#include "mtl/alloc_handle.h"

namespace ml {
class EventView;
} // namespace ml

namespace event {

void Manager::failureSkip() {
  mm::mtl::Singleton<DebugManager>::getPtr()->failureSkip();
  mm::mtl::Singleton<DebugManager>::getPtr()->setDisp(true);
  mm::mtl::Singleton<DebugManager>::getPtr()->playMessage("failure skip!! [%s.sb]", unknown230.c_str());
}

void Manager::finishNewGameWait() { mm::mtl::Singleton<UIManager>::getPtr()->finishNewGameWait(); }

bool Manager::isPlayCancel() const { return mm::mtl::Singleton<DebugManager>::getPtr()->isPlayCancel(); }

void Manager::clearAlways() {
  if (unknown18 & FLAG_HIDE_INFO) {
    unknown18 &= ~FLAG_HIDE_INFO;
  }
  unknown18 &= ~FLAG_PLAY;
}

void Manager::clear() {
  unknown280 = reinterpret_cast<gf::GF_OBJ_HANDLE *>(-1);
  unknown288[0] = 0;
  unknown288[1] = 0;
  unknown288[2] = 0;
  unknown288[3] = 0;
  unknown298 = LANGUAGE_MODE_NONE;
  unknown18 &= ~FLAG_END_FADE_OUT;
  unknown1c = 0;
}

void Manager::execMessage(MSG_TYPE type) {
  for (u32 i = 0; i < unknown20.size(); i++) {
    unknown20[i]->OnEventProc(type);
  }
}

void Manager::render() { ml::ProcDesktop::isDispInfo(); }

void Manager::tail() {
  if (unknown1c & STATE_INIT) {
    execMessage(MSG_TYPE_TAIL);
  }
  execMessage(MSG_TYPE_TAIL_POST);
}

void Manager::post() {}

void Manager::setLanguageMode(bool isEnable, LANGUAGE_MODE mode) { unknown298 = isEnable ? mode : LANGUAGE_MODE_NONE; }

bool Manager::checkLanguageMode() const {
  switch (unknown298) {
  case LANGUAGE_MODE_VOICE_TYPE_0:
    return fw::LangUtil::getVoiceType() == 0;
  case LANGUAGE_MODE_VOICE_TYPE_1:
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
