#include "event/manager.h"

#include "event/debug_manager.h"

#include "framework/lang_util.h"
#include "gf/game/event/gf_game_event.h"
#include "ml/proc_desktop.h"
#include "mtl/alloc_handle.h"

namespace ml {
class EventView;
} // namespace ml

namespace event {

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
