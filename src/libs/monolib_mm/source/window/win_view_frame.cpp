#include "ml/win_view_frame.h"

#include "ml/win_view.h"

namespace ml {

void WinViewFrame::setInfo(WinView *info) { m_info = info; }

bool WinViewFrame::evtFocusOn() { return true; }

bool WinViewFrame::evtFocusOff() {
  unknown38 = 8;
  return true;
}

bool WinViewFrame::evtMousePickOff(EventView *event) {
  if (unknown38 == 8) {
    return false;
  }
  unknown38 = 8;
  return true;
}

mm::Col4 WinViewFrame::getColorTransparency() const {
  mm::Col4 color = unknown08;
  color.a *= m_info->unknown524;
  return color;
}

mm::Pnt<int> WinViewFrame::getFrame2ViewSizeOffset() const {
  mm::Pnt<int> offset(0, 0);
  u32 frameFlags = m_info->unknown3bc;
  if ((frameFlags & 1) && (m_info->unknown3b8 & 3) == 0) {
    s16 width = unknown60;
    offset.x = width * 2;
    offset.y = offset.x;
    if (frameFlags & 2) {
      offset.y = width + offset.x + 0x16;
    }
  }
  return offset;
}

} // namespace ml
