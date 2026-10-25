#include "event/cam_motion.h"

#include "event/frame_manager.h"

namespace event {

CamMotion::CamMotion(bool isFocal, bool isStreamMode) : CamBase(isFocal), unknown48(nullptr), unknown50(nullptr) { unknown40 = isStreamMode; }

void CamMotion::update(const FrameInfo &info) {
  if (unknown40 & FLAG_PLAY_EVA) {
    unknown60.update(info.unknown0c);
  }
  if (unknown40 & FLAG_PLAY_EFF) {
    unknowna0.update(info.unknown0c);
  }
}

} // namespace event
