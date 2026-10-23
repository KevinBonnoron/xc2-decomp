#include "event/manager.h"

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
  mm::mtl::Singleton<DebugManager>::getPtr()->playMessage("failure skip!! [%s.sb]", mEventName.c_str());
}

void Manager::finishNewGameWait() { mm::mtl::Singleton<UIManager>::getPtr()->finishNewGameWait(); }

bool Manager::isPlayCancel() const { return mm::mtl::Singleton<DebugManager>::getPtr()->isPlayCancel(); }

void Manager::clearAlways() {
  if (flags & FLAG_HIDE_INFO) {
    flags &= ~FLAG_HIDE_INFO;
  }
  flags &= ~FLAG_PLAY;
}

void Manager::clear() {
  mObjHandle = reinterpret_cast<gf::GF_OBJ_HANDLE *>(-1);
  mPlayParams[0] = 0;
  mPlayParams[1] = 0;
  mPlayParams[2] = 0;
  mPlayParams[3] = 0;
  mLanguageMode = LANGUAGE_MODE_NONE;
  flags &= ~FLAG_END_FADE_OUT;
  state = 0;
}

void Manager::execMessage(MSG_TYPE type) {
  for (u32 i = 0; i < mManagers.size(); i++) {
    mManagers[i]->OnEventProc(type);
  }
}

void Manager::render() { ml::ProcDesktop::isDispInfo(); }

void Manager::tail() {
  if (state & STATE_INIT) {
    execMessage(MSG_TYPE_TAIL);
  }
  execMessage(MSG_TYPE_TAIL_POST);
}

void Manager::post() {}

void Manager::setLanguageMode(bool isEnable, LANGUAGE_MODE mode) { mLanguageMode = isEnable ? mode : LANGUAGE_MODE_NONE; }

bool Manager::checkLanguageMode() const {
  switch (mLanguageMode) {
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

void Manager::setDebugReplaceDefaultEquip(bool isReplace, u32 slot, u32 item) {
  mm::mtl::Singleton<DebugManager>::getPtr()->setReplaceDefaultEquip(isReplace, slot, item);
}

bool Manager::isReplaceDefaultEquip(u32 slot, u32 *item) const {
  return mm::mtl::Singleton<DebugManager>::getPtr()->isReplaceDefaultEquip(slot, item);
}

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

} // namespace event
