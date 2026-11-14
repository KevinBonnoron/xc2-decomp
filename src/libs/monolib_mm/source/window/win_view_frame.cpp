#include "ml/win_view_frame.h"

#include "ml/win_view.h"

namespace ml {

void WinViewFrame::setInfo(WinView *info) { m_info = info; }

bool WinViewFrame::evtFocusOn() { return true; }

bool WinViewFrame::evtFocusOff() {
  unknown38 = FMOVE_UNKNOWN_8;
  return true;
}

bool WinViewFrame::evtMousePickOff(EventView *event) {
  if (unknown38 == FMOVE_UNKNOWN_8) {
    return false;
  }
  unknown38 = FMOVE_UNKNOWN_8;
  return true;
}

WinViewFrame::WinViewFrame() : m_info(nullptr), unknown38(FMOVE_UNKNOWN_8), unknown3c(0.0f), unknown40(0.0f), unknown44(0.0f), unknown48(0.0f), unknown4c(0.0f), unknown60(4) {
  unknown08 = mm::Col4(0.5f, 0.5f, 0.5f, 1.0f);
  unknown18 = mm::Col4(0.8f, 0.8f, 0.8f, 1.0f);
  unknown28 = mm::Col4(0.4f, 0.5f, 0.6f, 1.0f);
  unknown50 = mm::Pnt<int>(0, 0);
  unknown58 = mm::Pnt<int>(0, 0);
}

mm::Col4 WinViewFrame::getColorTransparency() const {
  mm::Col4 color = unknown08;
  color.a *= m_info->unknown524;
  return color;
}

MCURSOR WinViewFrame::evtMouseSelect(const mm::Pnt<int> &pos) const {
  if (unknown38 == FMOVE_UNKNOWN_8) {
    return getFrameSelect(pos);
  }
  return getMove2MCursor(unknown38);
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

MCURSOR WinViewFrame::getMove2MCursor(FMOVE move) const {
  if (move == FMOVE_UNKNOWN_0 || move == FMOVE_UNKNOWN_3) {
    return MCURSOR_UNKNOWN_1;
  }
  if (move == FMOVE_UNKNOWN_1 || move == FMOVE_UNKNOWN_2) {
    return MCURSOR_UNKNOWN_2;
  }
  if (move == FMOVE_UNKNOWN_4 || move == FMOVE_UNKNOWN_5 || move == FMOVE_UNKNOWN_11) {
    return MCURSOR_UNKNOWN_3;
  }
  if (move == FMOVE_UNKNOWN_6 || move == FMOVE_UNKNOWN_7 || move == FMOVE_UNKNOWN_10) {
    return MCURSOR_UNKNOWN_4;
  }
  if (move == FMOVE_UNKNOWN_9) {
    return MCURSOR_UNKNOWN_5;
  }
  return MCURSOR_UNKNOWN_0;
}

MCURSOR WinViewFrame::getFrameSelect(const mm::Pnt<int> &pos) const { return getMove2MCursor(getFramePick(pos)); }

bool WinViewFrame::checkLTFrame(const mm::Rect<int> &rect, const mm::Pnt<int> &pos) const {
  mm::Rect<int> r(rect);
  s16 border = unknown60;
  int right = r.x + border;
  if (pos.x >= r.x && pos.x < right && pos.y >= r.y && pos.y < r.y + 0x10) {
    return true;
  }
  if (pos.x >= r.x && pos.x < r.x + 0x10) {
    if (pos.y < r.y) {
      return false;
    }
    return pos.y < border + r.y;
  }
  return false;
}

bool WinViewFrame::checkTFrame(const mm::Rect<int> &rect, const mm::Pnt<int> &pos) const {
  int top = rect.y;
  int left = static_cast<s16>(rect.x + 0x10);
  int right = left + static_cast<s16>(rect.width - 0x20);
  if (pos.x >= right || pos.x < left) {
    return false;
  }
  if (pos.y < top) {
    return false;
  }
  return pos.y < unknown60 + top;
}

bool WinViewFrame::checkBFrame(const mm::Rect<int> &rect, const mm::Pnt<int> &pos) const {
  int top = static_cast<s16>(rect.y + rect.height - unknown60);
  int left = static_cast<s16>(rect.x + 0x10);
  int right = left + static_cast<s16>(rect.width - 0x20);
  if (pos.x >= right || pos.x < left) {
    return false;
  }
  if (pos.y < top) {
    return false;
  }
  return pos.y < top + unknown60;
}

} // namespace ml
