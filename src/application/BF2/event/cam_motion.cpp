#include "event/cam_motion.h"

namespace event {

CamMotion::CamMotion(bool isFocal, bool isStreamMode) : CamBase(isFocal), mEvaData(nullptr), mEffData(nullptr) { flags = isStreamMode; }

} // namespace event
