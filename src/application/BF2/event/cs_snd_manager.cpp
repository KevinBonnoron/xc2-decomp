#include "event/cs_snd_manager.h"

#include "event/extend.h"
#include "event/frame_manager.h"
#include "framework/sound/sound_manager.h"

namespace fw {
enum SoundCategory : int;
} // namespace fw

namespace event {

CsSndManager::CsSndManager() : flags(0), dispFlags(0), mPreloadHandle(0), mPlayHandle(0), mUnused(0), mSyncFrameOffset(0.0f) {}

void CsSndManager::clear() {
  stop();
  flags = 0;
}

void CsSndManager::stop() {
  if ((flags & FLAG_PRELOAD) != 0) {
    stopPreload();
  }
  if ((flags & FLAG_PLAY) != 0) {
    stopPlay();
  }
}

void CsSndManager::update() {
  if ((flags & FLAG_PLAY) == 0) {
    return;
  }
  if (!fw::SoundManager::get()->isPlaying(mPlayHandle)) {
    mPlayHandle = 0;
    flags &= ~(FLAG_PLAY | FLAG_STALL);
  }
  if ((flags & FLAG_PAUSE) != 0 || !fw::SoundManager::get()->isPlaying(mPlayHandle)) {
    return;
  }
  f32 time = 0.0f;
  if (!fw::SoundManager::get()->getPlayTime(mPlayHandle, time)) {
    return;
  }
  if (mPrevPlayTime != time) {
    mStallCount = 0;
    mPrevPlayTime = time;
    return;
  }
  int count = mStallCount++;
  if (count == 18) {
    fw::SoundManager::get()->pause(mPlayHandle, true, 0.0f);
  } else if (count == 19) {
    mStallCount = 0;
    mRestartCount++;
    fw::SoundManager::get()->pause(mPlayHandle, false, 0.0f);
  }
}

f32 CsSndManager::getPlayFrame() const {
  if (isPlay()) {
    f32 time;
    if (fw::SoundManager::get()->getPlayTime(mPlayHandle, time)) {
      return time * 30.0f;
    }
  }
  return 0.0f;
}

f32 CsSndManager::getTotalFrame() const {
  if (isPlay()) {
    f32 time;
    if (fw::SoundManager::get()->getTotalTime(mPlayHandle, time)) {
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
  if ((flags & FLAG_PRELOAD) != 0 && fw::SoundManager::get()->isPreparing(mPreloadHandle)) {
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
  if ((flags & FLAG_PRELOAD) == 0 && __builtin_strcmp(mPreloadPath.c_str(), path) != 0) {
    if ((flags & FLAG_PLAY) != 0) {
      stopPlay();
    }
    const char *file = mm::mtl::Singleton<Extend>::getPtr()->wav(path);
    u32 handle = fw::SoundManager::get()->playBgm(file, 1.0f, false, -1, static_cast<fw::SoundCategory>(9));
    fw::SoundManager::get()->pause(handle, false, 0.0f);
    mPlayHandle = handle;
    mSyncFrameOffset = 0.0f;
    mStartedTotalFrame = mm::mtl::Singleton<FrameManager>::getPtr()->getTotalFrame();
    if (mPlayHandle == 0) {
      return;
    }
  } else {
    mPlayHandle = mPreloadHandle;
    fw::SoundManager::get()->startBgm(mPreloadHandle);
    mPreloadHandle = 0;
    mPreloadPath = "";
    flags &= ~FLAG_PRELOAD;
  }
  mPlayPath = path;
  mPrevPlayTime = -1.0f;
  mStallCount = 0;
  mRestartCount = 0;
  flags |= FLAG_PLAY;
}

u32 CsSndManager::playBgm(const char *path, f32 volume, bool isPause) {
  u32 handle = fw::SoundManager::get()->playBgm(path, volume, isPause, -1, static_cast<fw::SoundCategory>(9));
  if (!isPause) {
    fw::SoundManager::get()->pause(handle, false, 0.0f);
  }
  return handle;
}

bool CsSndManager::isPlay() const { return (flags & FLAG_PLAY) != 0; }

void CsSndManager::setDisp(bool isDisp) {
  if (isDisp) {
    dispFlags |= DISP_FLAG_DISP;
  } else {
    dispFlags &= ~DISP_FLAG_DISP;
  }
}

bool CsSndManager::isDisp() const { return (dispFlags & DISP_FLAG_DISP) != 0; }

f32 CsSndManager::getSyncFrame() const {
  f32 frame = 0.0f;
  f32 time;
  if (isPlay() && fw::SoundManager::get()->getPlayTime(mPlayHandle, time)) {
    frame = time * 30.0f - mSyncFrameOffset;
    frame = frame > 0.0f ? frame : 0.0f;
  }
  return frame;
}

void CsSndManager::setSyncFrame(f32 frame) {
  if (!isPlay()) {
    return;
  }
  f32 time = (frame + mSyncFrameOffset) / 30.0f;
  fw::SoundManager::get()->setPlayTime(mPlayHandle, time);
}

f32 CsSndManager::getStartedTotalFrame() const { return mStartedTotalFrame; }

void CsSndManager::setSyncFrameOffset(f32 offset) { mSyncFrameOffset = offset; }

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
