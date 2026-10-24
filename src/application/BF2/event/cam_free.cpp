#include "event/cam_free.h"

namespace event {

CamFree::CamFree(bool isFocal) : CamBase(isFocal), unknown48(0), unknown4c(0), unknown50(CTRL_MODE_NONE), unknown54(5.0f) {}

void CamFree::update(const FrameInfo &info) {}

} // namespace event
