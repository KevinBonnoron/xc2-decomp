#include "ml/win_view_frame.h"

#include "ml/cache_draw.h"
#include "ml/dev_graph.h"
#include "ml/win_view.h"
#include "mm_mtl/fixstr.h"

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

void WinViewFrame::getRectClose(mm::Rect<int> &rect) const {
  mm::Rect<int> frame = m_info->getFrameRect(false);
  s16 border = unknown60;
  rect = mm::Rect<int>(border + static_cast<s16>(frame.width - border * 2) - 0x12, border + 2, 0x10, 0x12);
}

void WinViewFrame::renderTitle(DebDraw *draw) const {
  // Ruling 4: only this declaration order of the color components gives the game's registers (the gray result lands in the register of r, 0x710076918c); with the
  // three declared and initialised together in any order the gray lands in another register. Found by permuting the declarations.
  f32 b;
  f32 g;
  int width = m_info->getFrameRect(false).width;
  s16 border = unknown60;
  // The game truncates the width to 16 bits before the isCurrentChild call of hasCurrent (sxth at 0x710076912c) and keeps it across the draw calls; inline in
  // the `right` computation, after the calls, the sxth moves down and the function has 236 instructions instead of 237.
  int span = static_cast<s16>(width - border * 2);
  f32 r = unknown28.r;
  g = unknown28.g;
  b = unknown28.b;
  if (m_info->hasCurrent()) {
    f32 gray = r * 0.298912f + g * 0.586611f + b * 0.114477f;
    b = gray;
    r = gray;
    g = gray;
  }
  f32 alpha = m_info->unknown524;
  draw->begin(8, 4);
  int right = span + border;
  draw->add(right, border, mm::Col4(r, g, b, alpha));
  draw->add(border, border, mm::Col4(r * 0.5f, g * 0.5f, b * 0.5f, alpha));
  draw->add(right, border + 0x16, mm::Col4(r, g, b, alpha));
  draw->add(border, border + 0x16, mm::Col4(r * 0.5f, g * 0.5f, b * 0.5f, alpha));
  draw->end();
  if (!(m_info->unknown3bc & 0x400)) {
    int closeWidth = m_info->getFrameRect(false).width;
    s16 closeBorder = unknown60;
    int right2 = closeBorder + static_cast<s16>(closeWidth - closeBorder * 2);
    int left = right2 - 0x12;
    int top = closeBorder + 2;
    draw->setCol(mm::Col4::white);
    draw->begin(2, 2);
    draw->add(mm::Pnt<int>(left, top), mm::Pnt<int>(right2 - 2, closeBorder + 0x14));
    draw->add(mm::Pnt<int>(left, closeBorder + 0x14), mm::Pnt<int>(right2 - 2, top));
    draw->end();
  }
  m_info->fontStyle(FONT_STYLE_UNKNOWN_0);
  m_info->fontShadow(false);
  m_info->fontColor(unknown18);
  m_info->fontScale(1.0f, 1.0f);
  s16 textBorder = unknown60;
  m_info->font(textBorder, textBorder + 0xb - m_info->fontGetHeight() / 2, m_info->unknown4d0.c_str());
  m_info->fontFlush(true);
  draw->setZComp(false);
  draw->setZWrite(false);
  renderFrame(draw, mm::Rect<int>(0, 0, width, static_cast<s16>(unknown60 * 2 + 0x16)));
}

} // namespace ml
