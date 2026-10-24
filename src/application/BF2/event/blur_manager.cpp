#include "event/blur_manager.h"

namespace event {

BlurManager::BlurManager() : unknown10(0), unknown14(0) {}

void BlurManager::clear() {}

void BlurManager::stop() {}

void BlurManager::update() {}

void BlurManager::render() {}

void BlurManager::play() {}

void BlurManager::setDisp(bool isDisp) {
  if (isDisp) {
    unknown10 |= DISP_FLAG_DISP;
  } else {
    unknown10 &= ~DISP_FLAG_DISP;
  }
}

bool BlurManager::isDisp() const { return (unknown10 & DISP_FLAG_DISP) != 0; }

void BlurManager::OnEventProc(MSG_TYPE type) {}

} // namespace event
