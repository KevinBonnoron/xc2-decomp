#include "event/cs_snd_manager.h"

namespace event {

CsSndManager::CsSndManager() : flags(0), dispFlags(0), mPreloadHandle(0), mPlayHandle(0), mUnused(0), mSyncFrameOffset(0.0f) {}

void CsSndManager::preloadAuto(const char *name) {
  mm::mtl::FixStr<256> path;
  makePath(path, name);
  preload(path.c_str());
}

void CsSndManager::preload(const char *path) {}

void CsSndManager::playAuto(const char *name) {
  mm::mtl::FixStr<256> path;
  makePath(path, name);
  play(path.c_str());
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

f32 CsSndManager::getStartedTotalFrame() const { return mStartedTotalFrame; }

void CsSndManager::setSyncFrameOffset(f32 offset) { mSyncFrameOffset = offset; }

} // namespace event
