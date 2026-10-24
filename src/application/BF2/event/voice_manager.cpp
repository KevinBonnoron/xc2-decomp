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
  if ((unknown14 & DISP_FLAG_DISP) != 0) {
    unknown230.draw();
  }
}

void VoiceManager::setAutoVoiceMode(bool isAutoVoiceMode, const char *directory, const char *name) {
  unknown18.create(isAutoVoiceMode, directory, name);
  setFlag(FLAG_AUTO_VOICE_MODE, isAutoVoiceMode);
}

void VoiceManager::setMultipleMode(bool isMultipleMode) { unknown230.setMultipleMode(isMultipleMode); }

void VoiceManager::preloadAuto(f32 frame, const char *name) {
  if ((unknown10 & FLAG_AUTO_VOICE_MODE) == 0) {
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

bool VoiceManager::play(const char *name, f32 delay, IVoiceEvent *event) {
  bool isLipsync = mm::mtl::Singleton<LipsyncManager>::getPtr()->setTarget(name);
  setFlag(FLAG_LIPSYNC, isLipsync);
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
  setFlag(FLAG_PAUSE, isPause);
  unknown230.pause(isPause);
  unknown6f8.pause(isPause);
}

void VoiceManager::setDisp(bool isDisp) {
  if (isDisp) {
    unknown14 |= DISP_FLAG_DISP;
  } else {
    unknown14 &= ~DISP_FLAG_DISP;
  }
}

bool VoiceManager::isDisp() const { return (unknown14 & DISP_FLAG_DISP) != 0; }

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
