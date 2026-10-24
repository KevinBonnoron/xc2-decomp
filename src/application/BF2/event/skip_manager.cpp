#include "event/skip_manager.h"

#include "event/cs_snd_manager.h"
#include "event/frame_manager.h"
#include "event/movie_manager.h"
#include "event/volume_manager.h"
#include "mm_mtl/singleton.h"

namespace event {

bool SkipManager::isSkip() const { return (unknown10 & FLAG_SKIP) != 0; }

void SkipManager::skip(bool isSkip, f32 frame) {
  if (isSkip) {
    if (this->isSkip() && unknown18 == frame) {
      return;
    }
    mm::mtl::Singleton<MovieManager>::getPtr()->stop();
    unknown18 = frame;
    unknown10 |= FLAG_SKIP;
  } else if (this->isSkip()) {
    unknown10 &= ~FLAG_SKIP;
  }
}

void SkipManager::setSkipVolume(bool isSkipVolume) {
  if (isSkipVolume) {
    if (this->isSkipVolume()) {
      return;
    }
    mm::mtl::Singleton<VolumeManager>::get().startSkipVolume();
    unknown10 |= FLAG_SKIP_VOLUME;
  } else if (this->isSkipVolume()) {
    mm::mtl::Singleton<VolumeManager>::get().endSkipVolume();
    mm::mtl::Singleton<CsSndManager>::getPtr()->setSyncFrame(mm::mtl::Singleton<FrameManager>::getPtr()->getFrame());
    unknown10 &= ~FLAG_SKIP_VOLUME;
  }
}

f32 SkipManager::getEndFrame() const {
  if (!isSkip()) {
    return 0.0f;
  }
  return unknown18 >= 0.0f ? unknown18 : DEFAULT_END_FRAME;
}

SkipManager::SkipManager() : unknown10(0), unknown14(0), unknown18(-1.0f) {}

SkipManager::~SkipManager() {}

void SkipManager::clear() {
  unknown10 = 0;
  unknown18 = -1.0f;
}

void SkipManager::update() {
  if (isSkip() && unknown18 >= 0.0f && unknown18 <= mm::mtl::Singleton<FrameManager>::getPtr()->getFrame()) {
    skip(false, 0.0f);
  }
}

void SkipManager::render() {}

void SkipManager::tail() {
  if (isSkip() && unknown18 >= 0.0f && unknown18 <= mm::mtl::Singleton<FrameManager>::getPtr()->getFrame()) {
    unknown10 &= ~FLAG_SKIP;
  }
}

bool SkipManager::isSkipVolume() const { return (unknown10 & FLAG_SKIP_VOLUME) != 0; }

void SkipManager::setSkipFastEnable(bool isEnable) {
  if (isEnable) {
    unknown10 |= FLAG_SKIP_FAST_ENABLE;
  } else {
    unknown10 &= ~FLAG_SKIP_FAST_ENABLE;
  }
}

} // namespace event
