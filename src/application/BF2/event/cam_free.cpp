#include "event/cam_free.h"

#include "ml/event_view.h"

namespace event {

CamFree::CamFree(bool isFocal) : CamBase(isFocal), unknown48(0), unknown4c(0), unknown50(CTRL_MODE_NONE), unknown54(5.0f) {}

void CamFree::update(const FrameInfo &info) {}

bool CamFree::OnKeyUp(ml::EventView *view) {
  if ((view->unknown28 & 1) == 0) {
    return false;
  }
  unknown4c &= ~8;
  unknown50 = CTRL_MODE_NONE;
  return true;
}

} // namespace event
