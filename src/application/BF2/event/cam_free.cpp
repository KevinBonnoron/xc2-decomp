#include "event/cam_free.h"

namespace event {

CamFree::CamFree(bool isFocal) : CamBase(isFocal), flags(0), mButtonFlags(0), mCtrlMode(CTRL_MODE_NONE), mMoveSpeed(5.0f) {}

void CamFree::update(const FrameInfo &info) {}

} // namespace event
