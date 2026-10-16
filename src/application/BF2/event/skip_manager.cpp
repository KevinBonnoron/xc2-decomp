#include "event/skip_manager.h"

#include "event/cs_snd_manager.h"
#include "event/frame_manager.h"
#include "event/movie_manager.h"
#include "event/volume_manager.h"
#include "mm_mtl/singleton.h"

namespace event {

bool SkipManager::isSkip() const { return (flags & FLAG_SKIP) != 0; }

void SkipManager::skip(bool isSkip, f32 frame) {
  if (isSkip) {
    if (this->isSkip() && skipFrame == frame) {
      return;
    }
    mm::mtl::Singleton<MovieManager>::getPtr()->stop();
    skipFrame = frame;
    flags |= FLAG_SKIP;
  } else if (this->isSkip()) {
    flags &= ~FLAG_SKIP;
  }
}

void SkipManager::setSkipVolume(bool isSkipVolume) {
  if (isSkipVolume) {
    if (this->isSkipVolume()) {
      return;
    }
    mm::mtl::Singleton<VolumeManager>::get().startSkipVolume();
    flags |= FLAG_SKIP_VOLUME;
  } else if (this->isSkipVolume()) {
    mm::mtl::Singleton<VolumeManager>::get().endSkipVolume();
    mm::mtl::Singleton<CsSndManager>::getPtr()->setSyncFrame(mm::mtl::Singleton<FrameManager>::getPtr()->getFrame());
    flags &= ~FLAG_SKIP_VOLUME;
  }
}

f32 SkipManager::getEndFrame() const {
  if (!isSkip()) {
    return 0.0f;
  }
  return skipFrame >= 0.0f ? skipFrame : DEFAULT_END_FRAME;
}

SkipManager::SkipManager() : flags(0), skipState(0), skipFrame(-1.0f) {}

SkipManager::~SkipManager() {}

void SkipManager::clear() {
  flags = 0;
  skipFrame = -1.0f;
}

void SkipManager::update() {
  if (isSkip() && skipFrame >= 0.0f && skipFrame <= mm::mtl::Singleton<FrameManager>::getPtr()->getFrame()) {
    skip(false, 0.0f);
  }
}

void SkipManager::render() {}

void SkipManager::tail() {
  if (isSkip() && skipFrame >= 0.0f && skipFrame <= mm::mtl::Singleton<FrameManager>::getPtr()->getFrame()) {
    flags &= ~FLAG_SKIP;
  }
}

bool SkipManager::isSkipVolume() const { return (flags & FLAG_SKIP_VOLUME) != 0; }

void SkipManager::setSkipFastEnable(bool isEnable) {
  if (isEnable) {
    flags |= FLAG_SKIP_FAST_ENABLE;
  } else {
    flags &= ~FLAG_SKIP_FAST_ENABLE;
  }
}

} // namespace event
