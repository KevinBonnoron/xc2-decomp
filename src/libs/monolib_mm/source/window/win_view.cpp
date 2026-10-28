#include "ml/win_view.h"

#include "ml/dev_graph.h"
#include "ml/win_view_root.h"

namespace ml {

const mm::Pnt<int> &WinView::getFramePos(bool isBack) const {
  const RENDER_INFO *info = isBack ? unknown1b8.m_back : unknown1b8.m_front;
  return info->unknown48.unknown58;
}

void WinView::addFramePos(const mm::Pnt<int> &pos) {
  RENDER_INFO *info = unknown1b8.m_back;
  info->unknown48.unknown58.x += pos.x;
  info->unknown48.unknown58.y += pos.y;
}

bool WinView::isSplitHolizon() const { return unknown1b8.m_back->unknown30; }

s32 WinView::getSplitLine(bool isBack) const {
  const RENDER_INFO *info = isBack ? unknown1b8.m_back : unknown1b8.m_front;
  return info->unknown30 ? info->unknown38 : info->unknown34;
}

mm::Pnt<int> WinView::getFrame2ViewOffset(bool isBack) const { return (isBack ? unknown1b8.m_back : unknown1b8.m_front)->unknown48.getFrame2ViewOffset(); }

mm::Pnt<int> WinView::getPos(bool isBack) const {
  if (unknown3b8 & 1) {
    return mm::Pnt<int>(0, 0);
  }
  const RENDER_INFO *info = isBack ? unknown1b8.m_back : unknown1b8.m_front;
  mm::Pnt<int> offset = getFrame2ViewOffset(isBack);
  return mm::Pnt<int>(info->unknown48.unknown58.x + offset.x, info->unknown48.unknown58.y + offset.y);
}

mm::Pnt<int> WinView::getSize(bool isBack) const {
  if (unknown3b8 & 1) {
    return mm::Pnt<int>(DevGraph::getRootWidth(), DevGraph::getRootHeight());
  }
  const RENDER_INFO *info = isBack ? unknown1b8.m_back : unknown1b8.m_front;
  return info->unknown00;
}

mm::Rect<int> WinView::getRect(bool isBack) const {
  mm::Pnt<int> offset = getFrame2ViewOffset(isBack);
  const mm::Pnt<int> &framePos = getFramePos(isBack);
  int x = framePos.x + offset.x;
  int y = framePos.y + offset.y;
  mm::Pnt<int> size = getSize(isBack);
  return mm::Rect<int>(x, y, size.x, size.y);
}

mm::Pnt<int> WinView::getClientPos(bool isBack) const {
  const RENDER_INFO *info = isBack ? unknown1b8.m_back : unknown1b8.m_front;
  int x = 0;
  int y = 0;
  if (!(unknown3b8 & 1)) {
    mm::Pnt<int> offset = getFrame2ViewOffset(isBack);
    x = info->unknown48.unknown58.x + offset.x;
    y = info->unknown48.unknown58.y + offset.y;
  }
  return mm::Pnt<int>(info->unknown18.x + x, info->unknown18.y + y);
}

mm::Pnt<int> WinView::getClientSize(bool isBack) const {
  if (unknown3b8 & 1) {
    return mm::Pnt<int>(DevGraph::getRootWidth(), DevGraph::getRootHeight());
  }
  const RENDER_INFO *info = isBack ? unknown1b8.m_back : unknown1b8.m_front;
  return mm::Pnt<int>(info->unknown00.x - info->unknown18.x - info->unknown20.x, info->unknown00.y - info->unknown18.y - info->unknown20.y);
}

WinView *WinView::getParentView() {
  if (WinViewRoot::get() != unknown58) {
    return static_cast<WinView *>(unknown58);
  }
  return nullptr;
}

const WinView *WinView::getParentView() const {
  if (WinViewRoot::get() != unknown58) {
    return static_cast<const WinView *>(unknown58);
  }
  return nullptr;
}

bool WinView::isCurrent() const {
  WinViewRoot *root = WinViewRoot::get();
  if (root != nullptr) {
    WinView *current = root->unknown1f0;
    return current == this && current != nullptr;
  }
  return false;
}

WinView *WinView::getSplitView1() { return WinViewRoot::getView(unknown1b8.m_back->unknown3c); }

WinView *WinView::getSplitView2() { return WinViewRoot::getView(unknown1b8.m_back->unknown40); }

const WinView *WinView::getSplitView1() const { return WinViewRoot::getView(unknown1b8.m_back->unknown3c); }

const WinView *WinView::getSplitView2() const { return WinViewRoot::getView(unknown1b8.m_back->unknown40); }

void WinView::setDisp(bool isDisp, bool isInvalidCurrent) {
  u32 flags = unknown3b8 & ~0x40u;
  if (!isDisp) {
    flags = unknown3b8 | 0x40;
  }
  unknown3b8 = flags;
  if (!isDisp && isInvalidCurrent) {
    WinViewRoot *root = WinViewRoot::get();
    WinView *current = root != nullptr ? root->unknown1f0 : nullptr;
    if (current == this) {
      WinViewRoot::invalidCurrent(this);
    }
  }
}

void WinView::deleteSplitView() {
  wkSetEventChild(static_cast<EVT>(0));
  unknown3bc &= ~0x38u;
}

bool WinView::hasCurrent() const {
  WinViewRoot *root = WinViewRoot::get();
  WinView *current = root != nullptr ? root->unknown1f0 : nullptr;
  if (current == this && current != nullptr) {
    return false;
  }
  return !WinViewRoot::isCurrentChild(this, current);
}

mm::Pnt<int> WinView::getFrameAbsPos(bool isBack) const {
  mm::Pnt<int> pos = getFramePos(isBack);
  for (const WinView *parent = getParentView(); parent != nullptr; parent = parent->getParentView()) {
    mm::Pnt<int> parentPos = parent->getPos(isBack);
    pos.x += parentPos.x;
    pos.y += parentPos.y;
  }
  return pos;
}

mm::Pnt<int> WinView::getAbsPos(bool isBack) const {
  if (unknown3b8 & 1) {
    return mm::Pnt<int>(0, 0);
  }
  const RENDER_INFO *info = isBack ? unknown1b8.m_back : unknown1b8.m_front;
  mm::Pnt<int> framePos = getFrameAbsPos(isBack);
  mm::Pnt<int> offset = info->unknown48.getFrame2ViewOffset();
  return mm::Pnt<int>(framePos.x + offset.x, framePos.y + offset.y);
}

mm::Rect<int> WinView::getAbsRect(bool isBack) const {
  mm::Pnt<int> pos = getAbsPos(isBack);
  mm::Pnt<int> size = getSize(isBack);
  return mm::Rect<int>(pos.x, pos.y, size.x, size.y);
}

mm::Rect<int> WinView::getRealAbsRect(bool isBack) const {
  mm::Rect<int> rect = getAbsRect(isBack);
  normalizeAbsRect(rect, isBack);
  return rect;
}

template class threadval<WinView::RENDER_INFO>;

template MsgParam<10>::~MsgParam();

} // namespace ml
