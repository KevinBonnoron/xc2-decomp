#include "event/skip_manager.h"

#include "event/frame_manager.h"
#include "mm_mtl/singleton.h"

namespace event {

SkipManager::SkipManager() : flags(0), mSkipState(0), mSkipFrame(-1.0f) {}

SkipManager::~SkipManager() {}

void SkipManager::clear() {
  flags = 0;
  mSkipFrame = -1.0f;
}

void SkipManager::update() {
  if (isSkip() && mSkipFrame >= 0.0f && mSkipFrame <= mm::mtl::Singleton<FrameManager>::getPtr()->getFrame()) {
    if (isSkip()) {
      flags &= ~FLAG_SKIP;
    }
  }
}

void SkipManager::render() {}

void SkipManager::tail() {
  if (isSkip() && mSkipFrame >= 0.0f && mSkipFrame <= mm::mtl::Singleton<FrameManager>::getPtr()->getFrame()) {
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
