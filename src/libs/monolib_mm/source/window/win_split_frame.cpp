#include "ml/win_split_frame.h"

#include "ml/dev_graph.h"
#include "ml/threadval.h"
#include "ml/win_view.h"
#include "ml/win_view_root.h"
#include "mm_math/mm_pnt.h"

namespace ml {

WinSplitFrame::~WinSplitFrame() {}

s16 WinSplitFrame::getSplitLine() const { return unknown08 ? unknown10 : unknown0c; }

void WinSplitFrame::setSplitLine(s16 line) {
  if (unknown08) {
    unknown10 = line;
  } else {
    unknown0c = line;
  }
  limit();
}

WinView *WinSplitFrame::getView1() { return WinViewRoot::getView(unknown14); }

WinView *WinSplitFrame::getView2() { return WinViewRoot::getView(unknown18); }

const WinView *WinSplitFrame::getView1() const { return WinViewRoot::getView(unknown14); }

const WinView *WinSplitFrame::getView2() const { return WinViewRoot::getView(unknown18); }

mm::Rect<int> WinSplitFrame::getWorkRect1(bool isBack) const {
  const WinView::RENDER_INFO *info = isBack ? unknown00->unknown1b8.m_back : unknown00->unknown1b8.m_front;
  mm::Pnt<int> pos = mm::Pnt<int>::zero;
  mm::Pnt<int> size = info->m_workSize;
  mm::Rect<int> rect(pos.x, pos.y, size.x, size.y);
  if (unknown08) {
    rect.height = unknown10;
  } else {
    rect.width = unknown0c;
  }
  return rect;
}

bool WinSplitFrame::isActive() const {
  const WinView *view1 = getView1();
  const WinView *view2 = getView2();
  return view1 != nullptr || view2 != nullptr;
}

mm::Rect<int> WinSplitFrame::getScissorRect1() const {
  mm::Pnt<int> screen = unknown00->unknown1b8.m_front->unknown00;
  if (unknown00->unknown3b8 & 1) {
    screen = mm::Pnt<int>(DevGraph::getRootWidth(), DevGraph::getRootHeight());
  }
  return unknown001(getWorkRect1(false), screen);
}

} // namespace ml
