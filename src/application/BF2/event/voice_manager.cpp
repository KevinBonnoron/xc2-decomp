#include "event/voice_manager.h"

#include "event/extend.h"
#include "event/lipsync_manager.h"
#include "event/skip_manager.h"
#include "framework/lang_util.h"
#include "mm_mtl/fixstr.h"

namespace event {

VoiceManager::VoiceManager() : unknown10(0), unknown14(0) {}

void VoiceManager::clear() {
  unknown230.clear();
  unknown6f8.clear();
  unknown10 = 0;
}

void VoiceManager::startScene() { unknown230.clearPreload(); }

void VoiceManager::update() {
  unknown230.update();
  unknown6f8.update();
}

void VoiceManager::render() {
  if ((unknown14 & DISP_FLAG_UNKNOWN_0) != 0) {
    unknown230.draw();
  }
}

void VoiceManager::setAutoVoiceMode(bool isAutoVoiceMode, const char *directory, const char *name) {
  unknown18.create(isAutoVoiceMode, directory, name);
  setFlag(FLAG_UNKNOWN_0, isAutoVoiceMode);
}

void VoiceManager::setMultipleMode(bool isMultipleMode) { unknown230.setMultipleMode(isMultipleMode); }

// The original source repeats the statements of preload() here instead of calling it: with `preload(frame, path)`
// this function is 46 instructions against the game's 109 (0x71000fcaa4), and no call, unit grouping or flag
// gives the game's code.
void VoiceManager::preloadAuto(f32 frame, const char *name) {
  if ((unknown10 & FLAG_UNKNOWN_0) == 0) {
    return;
  }
  const char *path = unknown18.makePath(name);
  if (path == nullptr) {
    return;
  }
  unknown230.preload(frame, mm::mtl::Singleton<Extend>::getPtr()->wav(path));
}

void VoiceManager::preload(f32 frame, const char *name) {
  const char *path = mm::mtl::Singleton<Extend>::getPtr()->wav(name);
  unknown230.preload(frame, path);
}

// The original source repeats the statements of play() here instead of calling it: the game's playAuto
// (0x71000f517c, 159 instructions) holds them with Extend::wav inlined, which play() itself (0x71000fccec) calls.
// `return play(path, delay, event)` gives 26 instructions, and play() forced inline gives 123 (wav stays a call);
// both files are in the event unit, and no flag or inline threshold gives the game's code.
bool VoiceManager::playAuto(const char *name, f32 delay, IVoiceEvent *event) {
  if ((unknown10 & FLAG_UNKNOWN_0) == 0) {
    return false;
  }
  const char *path = unknown18.makePath(name);
  if (path == nullptr) {
    return false;
  }
  bool isLipsync = mm::mtl::Singleton<LipsyncManager>::getPtr()->setTarget(path);
  setFlag(FLAG_UNKNOWN_1, isLipsync);
  if (mm::mtl::Singleton<SkipManager>::getPtr()->isSkip()) {
    return isLipsync;
  }
  return unknown230.play(mm::mtl::Singleton<Extend>::getPtr()->wav(path), delay, event);
}

bool VoiceManager::play(const char *name, f32 delay, IVoiceEvent *event) {
  bool isLipsync = mm::mtl::Singleton<LipsyncManager>::getPtr()->setTarget(name);
  setFlag(FLAG_UNKNOWN_1, isLipsync);
  if (mm::mtl::Singleton<SkipManager>::getPtr()->isSkip()) {
    return isLipsync;
  }
  return unknown230.play(mm::mtl::Singleton<Extend>::getPtr()->wav(name), delay, event);
}

bool VoiceManager::playOneshot(const char *name, f32 volume) {
  mm::mtl::FixStr<64> path("/stream/");
  path += name;
  if (fw::LangUtil::getVoiceType() != 0) {
    path = mm::mtl::Singleton<Extend>::getPtr()->replaceString(name, "jp", fw::LangUtil::getVoiceFolder().c_str());
  }
  return unknown6f8.play(mm::mtl::Singleton<Extend>::getPtr()->wav(path.c_str()), volume);
}

void VoiceManager::pause(bool isPause) {
  setFlag(FLAG_UNKNOWN_2, isPause);
  unknown230.pause(isPause);
  unknown6f8.pause(isPause);
}

void VoiceManager::setDisp(bool isDisp) {
  if (isDisp) {
    unknown14 |= DISP_FLAG_UNKNOWN_0;
  } else {
    unknown14 &= ~DISP_FLAG_UNKNOWN_0;
  }
}

bool VoiceManager::isDisp() const { return (unknown14 & DISP_FLAG_UNKNOWN_0) != 0; }

void VoiceManager::OnEventProc(MSG_TYPE type) {
  switch (type) {
  case MSG_TYPE_UNKNOWN_4:
    clear();
    break;
  case MSG_TYPE_UNKNOWN_7:
  case MSG_TYPE_UNKNOWN_8:
    startScene();
    break;
  case MSG_TYPE_UNKNOWN_12:
    clear();
    break;
  case MSG_TYPE_UNKNOWN_14:
    update();
    break;
  case MSG_TYPE_UNKNOWN_16:
    render();
    break;
  default:
    break;
  }
}

} // namespace event

template event::VoiceManager *mm::mtl::Singleton<event::VoiceManager>::getPtr();
