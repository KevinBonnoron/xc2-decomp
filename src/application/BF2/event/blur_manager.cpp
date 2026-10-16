#include "event/blur_manager.h"

namespace event {

BlurManager::BlurManager() : dispFlags(0), flags(0) {}

void BlurManager::clear() {}

void BlurManager::stop() {}

void BlurManager::update() {}

void BlurManager::render() {}

void BlurManager::play() {}

void BlurManager::setDisp(bool isDisp) {
  if (isDisp) {
    dispFlags |= DISP_FLAG_DISP;
  } else {
    dispFlags &= ~DISP_FLAG_DISP;
  }
}

bool BlurManager::isDisp() const { return (dispFlags & DISP_FLAG_DISP) != 0; }

void BlurManager::OnEventProc(MSG_TYPE type) {}

} // namespace event
