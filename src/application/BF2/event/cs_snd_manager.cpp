#include "event/cs_snd_manager.h"

#include "event/extend.h"
#include "event/frame_manager.h"
#include "framework/sound/sound_manager.h"

namespace fw {
enum SoundCategory : int;
} // namespace fw

namespace event {

CsSndManager::CsSndManager() : unknown10(0), unknown14(0), unknown18(0), unknown1c(0), unknown238(0), m_syncFrameOffset(0.0f) {}

void CsSndManager::clear() {
  stop();
  unknown10 = 0;
}

void CsSndManager::stop() {
  if ((unknown10 & FLAG_PRELOAD) != 0) {
    stopPreload();
  }
  if ((unknown10 & FLAG_PLAY) != 0) {
    stopPlay();
  }
}

void CsSndManager::update() {
  if ((unknown10 & FLAG_PLAY) == 0) {
    return;
  }
  if (!fw::SoundManager::get()->isPlaying(unknown1c)) {
    unknown1c = 0;
    unknown10 &= ~(FLAG_PLAY | FLAG_STALL);
  }
  if ((unknown10 & FLAG_PAUSE) != 0 || !fw::SoundManager::get()->isPlaying(unknown1c)) {
    return;
  }
  f32 time = 0.0f;
  if (!fw::SoundManager::get()->getPlayTime(unknown1c, time)) {
    return;
  }
  if (unknown228 != time) {
    unknown22c = 0;
    unknown228 = time;
    return;
  }
  int count = unknown22c++;
  if (count == 18) {
    fw::SoundManager::get()->pause(unknown1c, true, 0.0f);
  } else if (count == 19) {
    unknown22c = 0;
    unknown230++;
    fw::SoundManager::get()->pause(unknown1c, false, 0.0f);
  }
}

f32 CsSndManager::getPlayFrame() const {
  if (isPlay()) {
    f32 time;
    if (fw::SoundManager::get()->getPlayTime(unknown1c, time)) {
      return time * 30.0f;
    }
  }
  return 0.0f;
}

f32 CsSndManager::getTotalFrame() const {
  if (isPlay()) {
    f32 time;
    if (fw::SoundManager::get()->getTotalTime(unknown1c, time)) {
      return time * 30.0f;
    }
  }
  return 0.0f;
}

void CsSndManager::preloadAuto(const char *name) {
  mm::mtl::FixStr<256> path;
  makePath(path, name);
  preload(path.c_str());
}

void CsSndManager::preload(const char *path) {}

bool CsSndManager::isLoading() const {
  if ((unknown10 & FLAG_PRELOAD) != 0 && fw::SoundManager::get()->isPreparing(unknown18)) {
    return true;
  }
  return false;
}

void CsSndManager::playAuto(const char *name) {
  mm::mtl::FixStr<256> path;
  makePath(path, name);
  play(path.c_str());
}

void CsSndManager::play(const char *path) {
  if ((unknown10 & FLAG_PRELOAD) == 0 && __builtin_strcmp(unknown20.c_str(), path) != 0) {
    if ((unknown10 & FLAG_PLAY) != 0) {
      stopPlay();
    }
    const char *file = mm::mtl::Singleton<Extend>::getPtr()->wav(path);
    u32 handle = fw::SoundManager::get()->playBgm(file, 1.0f, false, -1, static_cast<fw::SoundCategory>(9));
    fw::SoundManager::get()->pause(handle, false, 0.0f);
    unknown1c = handle;
    m_syncFrameOffset = 0.0f;
    m_startedTotalFrame = mm::mtl::Singleton<FrameManager>::getPtr()->getTotalFrame();
    if (unknown1c == 0) {
      return;
    }
  } else {
    unknown1c = unknown18;
    fw::SoundManager::get()->startBgm(unknown18);
    unknown18 = 0;
    unknown20 = "";
    unknown10 &= ~FLAG_PRELOAD;
  }
  unknown124 = path;
  unknown228 = -1.0f;
  unknown22c = 0;
  unknown230 = 0;
  unknown10 |= FLAG_PLAY;
}

u32 CsSndManager::playBgm(const char *path, f32 volume, bool isPause) {
  u32 handle = fw::SoundManager::get()->playBgm(path, volume, isPause, -1, static_cast<fw::SoundCategory>(9));
  if (!isPause) {
    fw::SoundManager::get()->pause(handle, false, 0.0f);
  }
  return handle;
}

bool CsSndManager::isPlay() const { return (unknown10 & FLAG_PLAY) != 0; }

void CsSndManager::setDisp(bool isDisp) {
  if (isDisp) {
    unknown14 |= DISP_FLAG_DISP;
  } else {
    unknown14 &= ~DISP_FLAG_DISP;
  }
}

bool CsSndManager::isDisp() const { return (unknown14 & DISP_FLAG_DISP) != 0; }

f32 CsSndManager::getSyncFrame() const {
  f32 frame = 0.0f;
  f32 time;
  if (isPlay() && fw::SoundManager::get()->getPlayTime(unknown1c, time)) {
    frame = time * 30.0f - m_syncFrameOffset;
    frame = frame > 0.0f ? frame : 0.0f;
  }
  return frame;
}

void CsSndManager::setSyncFrame(f32 frame) {
  if (!isPlay()) {
    return;
  }
  f32 time = (frame + m_syncFrameOffset) / 30.0f;
  fw::SoundManager::get()->setPlayTime(unknown1c, time);
}

f32 CsSndManager::getStartedTotalFrame() const { return m_startedTotalFrame; }

void CsSndManager::setSyncFrameOffset(f32 offset) { m_syncFrameOffset = offset; }

void CsSndManager::OnEventProc(MSG_TYPE type) {
  switch (type) {
  case MSG_TYPE_INIT:
    clear();
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
