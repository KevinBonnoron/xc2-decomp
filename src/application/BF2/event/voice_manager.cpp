#include "event/voice_manager.h"

#include "event/extend.h"
#include "event/lipsync_manager.h"
#include "event/skip_manager.h"
#include "framework/lang_util.h"
#include "mm_mtl/fixstr.h"

namespace event {

VoiceManager::VoiceManager() : flags(0), dispFlags(0) {}

void VoiceManager::clear() {
  player.clear();
  oneShoter.clear();
  flags = 0;
}

void VoiceManager::startScene() { player.clearPreload(); }

void VoiceManager::update() {
  player.update();
  oneShoter.update();
}

void VoiceManager::render() {
  if ((dispFlags & DISP_FLAG_DISP) != 0) {
    player.draw();
  }
}

void VoiceManager::setAutoVoiceMode(bool isAutoVoiceMode, const char *directory, const char *name) {
  maker.create(isAutoVoiceMode, directory, name);
  setFlag(FLAG_AUTO_VOICE_MODE, isAutoVoiceMode);
}

void VoiceManager::setMultipleMode(bool isMultipleMode) { player.setMultipleMode(isMultipleMode); }

void VoiceManager::preloadAuto(f32 frame, const char *name) {
  if ((flags & FLAG_AUTO_VOICE_MODE) == 0) {
    return;
  }
  const char *path = maker.makePath(name);
  if (path == nullptr) {
    return;
  }
  player.preload(frame, mm::mtl::Singleton<Extend>::getPtr()->wav(path));
}

void VoiceManager::preload(f32 frame, const char *name) {
  const char *path = mm::mtl::Singleton<Extend>::getPtr()->wav(name);
  player.preload(frame, path);
}

bool VoiceManager::play(const char *name, f32 delay, IVoiceEvent *event) {
  bool isLipsync = mm::mtl::Singleton<LipsyncManager>::getPtr()->setTarget(name);
  setFlag(FLAG_LIPSYNC, isLipsync);
  if (mm::mtl::Singleton<SkipManager>::getPtr()->isSkip()) {
    return isLipsync;
  }
  return player.play(mm::mtl::Singleton<Extend>::getPtr()->wav(name), delay, event);
}

bool VoiceManager::playOneshot(const char *name, f32 volume) {
  mm::mtl::FixStr<64> path("/stream/");
  path += name;
  if (fw::LangUtil::getVoiceType() != 0) {
    path = mm::mtl::Singleton<Extend>::getPtr()->replaceString(name, "jp", fw::LangUtil::getVoiceFolder().c_str());
  }
  return oneShoter.play(mm::mtl::Singleton<Extend>::getPtr()->wav(path.c_str()), volume);
}

void VoiceManager::pause(bool isPause) {
  setFlag(FLAG_PAUSE, isPause);
  player.pause(isPause);
  oneShoter.pause(isPause);
}

void VoiceManager::setDisp(bool isDisp) {
  if (isDisp) {
    dispFlags |= DISP_FLAG_DISP;
  } else {
    dispFlags &= ~DISP_FLAG_DISP;
  }
}

bool VoiceManager::isDisp() const { return (dispFlags & DISP_FLAG_DISP) != 0; }

void VoiceManager::OnEventProc(MSG_TYPE type) {
  switch (type) {
  case MSG_TYPE_INIT:
    clear();
    break;
  case MSG_TYPE_START_SCENE:
  case MSG_TYPE_START_PAGE:
    startScene();
    break;
  case MSG_TYPE_CLEAR:
    clear();
    break;
  case MSG_TYPE_UPDATE:
    update();
    break;
  case MSG_TYPE_RENDER:
    render();
    break;
  default:
    break;
  }
}

} // namespace event
