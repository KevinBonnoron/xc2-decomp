#include "ml/win_split_frame.h"

#include "ml/dev_graph.h"
#include "ml/threadval.h"
#include "ml/win_view.h"
#include "ml/win_view_frame.h"
#include "ml/win_view_root.h"
#include "mm_math/mm_pnt.h"

namespace ml {

WinSplitFrame::~WinSplitFrame() {}

s16 WinSplitFrame::getSplitLine() const { return m_splitHolizon ? unknown10 : unknown0c; }

void WinSplitFrame::setSplitLine(s16 line) {
  if (m_splitHolizon) {
    unknown10 = line;
  } else {
    unknown0c = line;
  }
  limit();
}

void WinSplitFrame::apply() {
  if (WinViewRoot::get() != nullptr) {
    WinView *view1 = getView1();
    WinView *view2 = getView2();
    if (view1 != nullptr) {
      view1->setRect(getWorkRect1(true));
      view1->applyRect();
    }
    if (view2 != nullptr) {
      view2->setRect(getWorkRect2(true));
      view2->applyRect();
    }
  }
}

WinView *WinSplitFrame::getView1() { return WinViewRoot::getView(unknown14); }

WinView *WinSplitFrame::getView2() { return WinViewRoot::getView(unknown18); }

const WinView *WinSplitFrame::getView1() const { return WinViewRoot::getView(unknown14); }

const WinView *WinSplitFrame::getView2() const { return WinViewRoot::getView(unknown18); }

mm::Rect<int> WinSplitFrame::getWorkRect1(bool isBack) const {
  const WinView::RENDER_INFO *info = isBack ? m_winView->unknown1b8.m_back : m_winView->unknown1b8.m_front;
  mm::Pnt<int> pos = mm::Pnt<int>::zero;
  mm::Pnt<int> size = info->m_workSize;
  mm::Rect<int> rect(pos.x, pos.y, size.x, size.y);
  if (m_splitHolizon) {
    rect.height = unknown10;
  } else {
    rect.width = unknown0c;
  }
  return rect;
}

mm::Rect<int> WinSplitFrame::getWorkRect2(bool isBack) const {
  const WinView::RENDER_INFO *info = isBack ? m_winView->unknown1b8.m_back : m_winView->unknown1b8.m_front;
  mm::Rect<int> rect(mm::Pnt<int>::zero, info->m_workSize);
  if (m_splitHolizon) {
    // The game loads the front frame again in each branch after the stores to the rect (ldr x9, [x9] at 1.0.0: 0x71007632cc
    // and 0x71007632f0). The border is a 16 bit value added to the split line and truncated to s16 (ldrh, add, sxth).
    rect.y = static_cast<s16>(unknown10 + m_winView->unknown1b8.m_front->m_winViewFrame.unknown60);
    rect.height -= rect.y;
  } else {
    rect.x = static_cast<s16>(unknown0c + m_winView->unknown1b8.m_front->m_winViewFrame.unknown60);
    rect.width -= rect.x;
  }
  return rect;
}

bool WinSplitFrame::isActive() const {
  const WinView *view1 = getView1();
  const WinView *view2 = getView2();
  return view1 != nullptr || view2 != nullptr;
}

mm::Rect<int> WinSplitFrame::getScissorRect1() const {
  mm::Pnt<int> screen = m_winView->unknown1b8.m_front->unknown00;
  if (m_winView->unknown3b8 & 1) {
    screen = mm::Pnt<int>(DevGraph::getRootWidth(), DevGraph::getRootHeight());
  }
  return unknown001(getWorkRect1(false), screen);
}

mm::Rect<int> WinSplitFrame::getClientScissorRect1() const {
  mm::Pnt<int> screen;
  if (!(m_winView->unknown3b8 & 1)) {
    const WinView::RENDER_INFO *info = m_winView->unknown1b8.m_front;
    // WinView::getClientSize written out again: its call, inlined in this unit (window.cpp), gives the same code except
    // the order of two loads. The game loads the client position first (ldp w8, w9, [x10, #0x18] at 1.0.0:
    // 0x71007638b4) and the size after it (ldp w11, w12, [x10] at 0x71007638b8); the call form loads the size first. The
    // copy of the position places that load.
    mm::Pnt<int> pos = info->unknown18;
    screen.x = info->unknown00.x - pos.x - info->unknown20.x;
    screen.y = info->unknown00.y - pos.y - info->unknown20.y;
  } else {
    screen.x = DevGraph::getRootWidth();
    screen.y = DevGraph::getRootHeight();
  }
  return unknown001(getWorkRect1(false), screen);
}

} // namespace ml
