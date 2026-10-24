#include "event/cam_motion.h"

namespace event {

CamMotion::CamMotion(bool isFocal, bool isStreamMode) : CamBase(isFocal), unknown48(nullptr), unknown50(nullptr) { unknown40 = isStreamMode; }

} // namespace event
