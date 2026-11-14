#include "ml/win_view.h"

#include <algorithm>
#include <string.h>

#include "ml/cache_draw.h"
#include "ml/dev_graph.h"
#include "ml/lib_main.h"
#include "ml/win_proc.h"
#include "ml/win_proc_root.h"
#include "ml/win_view_root.h"
#include "ml/work_root.h"
#include "mm_math/mm_mat44.h"
#include "window/window.h"

namespace ml {

namespace {

// Inferred role: view being rendered, set by WinView::renderView and returned by WinView::getView; original name
// unknown. Numbered after unknown001 of proc_mouse.cpp, which shares the window.cpp unit.
WinView *unknown002;

} // namespace

WinView::~WinView() {}

bool WinView::evtFocusOn() { return true; }

bool WinView::evtFocusOff() { return unknown1b8.m_back->unknown48.evtFocusOff(); }

void WinView::setRect(const mm::Rect<int> &rect) {
  updateViewPort(rect);
  if (unknown53c) {
    memcpy(unknown1b8.m_front, unknown1b8.m_back, sizeof(RENDER_INFO));
  }
}

void WinView::setTitle(const char *title) {
  unknown4d0 = title;
  WorkObj::unknown08 = title;
}

void WinView::setSplitLine(int line) {
  unknown1b8.m_back->unknown28.setSplitLine(line);
  applyRect();
}

void WinView::createSplitView(bool isHorizontal, WinView *view1, WinView *view2) {
  unknown1b8.m_back->unknown28.setup(this, isHorizontal, view1, view2);
  unknown3bc |= isHorizontal ? 0x18 : 0x28;
  memcpy(unknown1b8.m_front, unknown1b8.m_back, sizeof(RENDER_INFO));
}

mm::Rect<int> WinView::getSplitRect(const WinView *view, bool isBack) const {
  const RENDER_INFO *info = isBack ? unknown1b8.m_back : unknown1b8.m_front;
  if (getSplitView1() != view) {
    return info->unknown28.getScissorRect2();
  }
  return info->unknown28.getScissorRect1();
}

// The game body is identical to getSplitRect: it calls WinSplitFrame::getScissorRect1/2 here too, not the client variants.
mm::Rect<int> WinView::getClientSplitRect(const WinView *view, bool isBack) const {
  const RENDER_INFO *info = isBack ? unknown1b8.m_back : unknown1b8.m_front;
  if (getSplitView1() != view) {
    return info->unknown28.getScissorRect2();
  }
  return info->unknown28.getScissorRect1();
}

mm::Rect<int> WinView::getScissorRect(bool isBack) const {
  const WinView *parent = getParentView();
  if (parent == nullptr || !parent->isSplit(isBack)) {
    return getRect(isBack);
  }
  return parent->getSplitRect(this, isBack);
}

mm::Rect<int> WinView::getFrameRect(bool isBack) const {
  const RENDER_INFO *info = isBack ? unknown1b8.m_back : unknown1b8.m_front;
  return info->unknown48.unknown001(isBack);
}

mm::Rect<int> WinView::getFrameAbsRect(bool isBack) const {
  const RENDER_INFO *info = isBack ? unknown1b8.m_back : unknown1b8.m_front;
  mm::Pnt<int> pos = getFrameAbsPos(isBack);
  mm::Rect<int> rect = info->unknown48.unknown001(isBack);
  return mm::Rect<int>(pos.x, pos.y, rect.width, rect.height);
}

void WinView::setSize(int width, int height) {
  mm::Rect<int> rect = getFrameRect(true);
  rect.width = width;
  rect.height = height;
  updateViewPort(rect);
}

void WinView::setDefaultFrameColor(const mm::Col4 &color) { unknown004.m_defaultFrameColor = color; }

void WinView::setInitialBackCol(const mm::Col4 &color) { unknown004.m_initialBackCol = color; }

const mm::Col4 &WinView::getDefaultTitleBarColor() { return unknown004.m_defaultTitleBarColor; }

WinView *WinView::getView(bool isResetShadow) {
  if (unknown002 != nullptr && isResetShadow) {
    unknown002->fontShadow(false);
  }
  return unknown002;
}

const mm::Pnt<int> &WinView::getFramePos(bool isBack) const {
  const RENDER_INFO *info = isBack ? unknown1b8.m_back : unknown1b8.m_front;
  return info->unknown48.unknown58;
}

void WinView::addFramePos(const mm::Pnt<int> &pos) {
  RENDER_INFO *info = unknown1b8.m_back;
  info->unknown48.unknown58.x += pos.x;
  info->unknown48.unknown58.y += pos.y;
}

void WinView::addScroll(const mm::Pnt<int> &scroll) { unknown1b8.m_back->addScroll(scroll); }

bool WinView::isSplitHolizon() const { return unknown1b8.m_back->unknown28.unknown08; }

s32 WinView::getSplitLine(bool isBack) const {
  const RENDER_INFO *info = isBack ? unknown1b8.m_back : unknown1b8.m_front;
  return info->unknown28.getSplitLine();
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

void WinView::getViewOfs(mm::Rect<int> &rect, bool isBack) {
  CS lock(unknown540);
  rect = mm::Rect<int>(0, 0, 0, 0);
}

void WinView::destroyCtrlMemory() {
  for (reslist<WorkObj *>::Node *node = wkGetChild()->begin(); node != wkGetChild()->end(); node = node->getNext()) {
    static_cast<WinView *>(node->value)->destroyCtrlMemory();
  }
}

bool WinView::isCurrent() const {
  WinViewRoot *root = WinViewRoot::get();
  if (root != nullptr) {
    WinView *current = root->unknown1f0;
    return current == this && current != nullptr;
  }
  return false;
}

bool WinView::isSplit(bool isBack) const {
  const RENDER_INFO *info = isBack ? unknown1b8.m_back : unknown1b8.m_front;
  return WinViewRoot::getView(info->unknown28.unknown14) != nullptr && WinViewRoot::getView(info->unknown28.unknown18) != nullptr;
}

mm::Rect<int> WinView::getClientScissorAbsRect(bool isBack) const {
  mm::Rect<int> absRect = getClientAbsRect(isBack);
  mm::Rect<int> scissor = getClientScissorRect(isBack);
  mm::Rect<int> rect(absRect.x, absRect.y, scissor.width, scissor.height);
  if (rect.x + rect.width >= DevGraph::getRootWidth()) {
    rect.width = DevGraph::getRootWidth() - rect.x;
  }
  if (rect.width < 0) {
    rect.width = 0;
  }
  if (rect.y + rect.height >= DevGraph::getRootHeight()) {
    rect.height = DevGraph::getRootHeight() - rect.y;
  }
  if (rect.height < 0) {
    rect.height = 0;
  }
  return rect;
}

WinView *WinView::getSplitView1() { return WinViewRoot::getView(unknown1b8.m_back->unknown28.unknown14); }

WinView *WinView::getSplitView2() { return WinViewRoot::getView(unknown1b8.m_back->unknown28.unknown18); }

const WinView *WinView::getSplitView1() const { return WinViewRoot::getView(unknown1b8.m_back->unknown28.unknown14); }

const WinView *WinView::getSplitView2() const { return WinViewRoot::getView(unknown1b8.m_back->unknown28.unknown18); }

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

void WinView::setCurrent() { unknown3c0.add(7); }

void WinView::setFullScreen() {
  if (!(unknown3b8 & 1)) {
    unknown52c = getRect(false);
    unknown3b8 |= 1;
    setRect(mm::Rect<int>(0, 0, DevGraph::getRootWidth(), DevGraph::getRootHeight()));
  } else {
    unknown3b8 &= ~1u;
    setRect(unknown52c);
  }
}

mm::Pnt<int> WinViewFrame::getFrame2ViewOffset() const {
  mm::Pnt<int> offset(0, 0);
  u32 frameFlags = m_info->unknown3bc;
  if ((frameFlags & 1) && (m_info->unknown3b8 & 3) == 0) {
    s16 width = unknown60;
    offset.x = width;
    offset.y = offset.x;
    if (frameFlags & 2) {
      offset.y = width + offset.x + 0x16;
    }
  }
  return offset;
}

void WinView::deleteSplitView() {
  wkSetEventChild(static_cast<EVT>(0));
  unknown3bc &= ~0x38u;
}

void WinView::initializeClientScreen(bool isSkipClear) {
  if (!isSkipClear) {
    DebDraw *draw = DebDraw::get(0xffffffff);
    draw->setZComp(false);
    draw->setZWrite(true);
    draw->unknown14c = 1.0f;
    draw->setDoubleSide(true);
    draw->setCol(mm::Col4(unknown514.r, unknown514.g, unknown514.b, unknown514.a * unknown524));
    draw->begin(9, 1);
    draw->add(getRect(false));
    draw->end();
  }
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

WinView *WinView::getPointedView(const mm::Pnt<int> &pos) {
  if (!(unknown3b8 & 0x48) && !wkIsWaitException() && wkIsActive() && !wkIsShutdown()) {
    mm::Rect<int> rect = getFrameAbsRect(false);
    WinView *pointed = nullptr;
    if (pos.x >= rect.x && pos.x < rect.x + rect.width) {
      pointed = this;
      if (pos.y < rect.y || pos.y >= rect.y + rect.height) {
        pointed = nullptr;
      }
    }
    for (reslist<WorkObj *>::Node *node = wkGetChild()->begin(); node != wkGetChild()->end(); node = node->getNext()) {
      WinView *child = static_cast<WinView *>(node->value)->getPointedView(pos);
      if (child != nullptr) {
        pointed = child;
      }
    }
    return pointed;
  }
  return nullptr;
}

void WinView::wkTail() {
  applyRect();
  updateMsg();
  if (unknown60.size() == 0 && unknown338.size() == 0 && !isSplit(true)) {
    wkSetEvent(static_cast<EVT>(0));
  }
  applyPrio();
}

void WinView::renderView() {
  if (unknown3b8 & 0x40) {
    return;
  }
  WinView *fullScreen = WinViewRoot::getFullScreenView();
  bool isHide = false;
  if (!(fullScreen->unknown3b8 & 2) && fullScreen != this) {
    if (unknown338.size() != 0 && fullScreen->unknown338.size() != 0) {
      WinProc *fullScreenRoot = WinProc::pssGetRoot(static_cast<WinProc *>(WorkRootState::getWork(fullScreen->unknown338.begin()->value)));
      WinProc *root = WinProc::pssGetRoot(static_cast<WinProc *>(WorkRootState::getWork(unknown338.begin()->value)));
      isHide = root != nullptr && fullScreenRoot != root && unknown528 >= fullScreen->unknown528;
    }
  }
  bool isSkip = isHide;
  if (WorkRoot::isErrorLog()) {
    isSkip = !(unknown3b8 & 0x100);
  }
  mm::Rect<int> rect = getRealAbsRect(false);
  if (fullScreen == this) {
    DevGraph::grSetClearCol(mm::Col4(unknown524 * unknown514.r, unknown524 * unknown514.g, unknown524 * unknown514.b, unknown514.a));
  }
  mm::Pnt<int> size = getSize(false);
  bool isEmpty = true;
  if (size.x > 0 && size.y > 0 && rect.width > 0 && rect.height > 0) {
    const WinViewPort *port = unknown1b8.m_front;
    isEmpty = port->m_workSize.x <= 0 && port->m_workSize.y <= 0;
  }
  if (!isSkip) {
    if (!isSplit(false) && !(unknown3b8 & 1) && !isEmpty) {
      initializeClientScreen((unknown3b8 & 4) != 0);
    }
    mm::Rect<int> scissor = getClientScissorAbsRect(false);
    normalizeAbsRect(scissor, false);
    mm::Rect<int> viewport = getClientAbsRect(false);
    // The viewport part of the render info, picking for each axis the larger of the view size and the work size.
    const WinViewPort *port = unknown1b8.m_front;
    const mm::Pnt<int> &widthSrc = port->unknown00.x > port->m_workSize.x ? port->unknown00 : port->m_workSize;
    const mm::Pnt<int> &heightSrc = port->unknown00.y > port->m_workSize.y ? port->unknown00 : port->m_workSize;
    mm::Rect<int> renderRect;
    renderRect.x = port->unknown10.x;
    renderRect.y = port->unknown10.y;
    renderRect.width = widthSrc.x;
    renderRect.height = heightSrc.y;
    DevGraph::pushRect(viewport, scissor, renderRect, true);
    unknown002 = this;
    if (!isEmpty) {
      wkRender();
    }
    for (reslist<u32>::Node *node = unknown338.begin(); node != unknown338.end(); node = node->getNext()) {
      WorkObj *work = WorkRootState::getWork(node->value);
      if (work != nullptr) {
        unknown002 = this;
        if (!isEmpty && work != this) {
          work->wkRender();
        }
      }
    }
    if (DebDraw::getCacheDrawWID() == unknown50) {
      DevGraph::cmdOpenDisplayList(0);
      DebDraw::flushPrio(-1, mm::Mat44::identity, mm::Mat44::identity);
      DevGraph::cmdCloseDisplayList();
    }
    DevGraph::grInitContext();
    fontFlush(true);
  }
  if (!isEmpty) {
    for (reslist<WorkObj *>::Node *node = wkGetChild()->begin(); node != wkGetChild()->end(); node = node->getNext()) {
      static_cast<WinView *>(node->value)->renderView();
    }
    for (reslist<u32>::Node *node = unknown338.begin(); node != unknown338.end(); node = node->getNext()) {
      WorkObj *work = WorkRootState::getWork(node->value);
      if (work != nullptr) {
        unknown002 = this;
        if (work != this) {
          work->wkRenderAfter();
        }
      }
    }
  }
  unknown002 = nullptr;
  DevGraph::grInitContext();
  fontFlush(true);
  if (!isSkip) {
    DevGraph::popRect();
  }
  unknown002 = this;
  if (!isSkip) {
    unknown1b8.m_front->unknown48.render(getParentView());
  }
  unknown002 = nullptr;
}

bool WinView::wkStandbyLogin() {
  if (LibMain::isInitialized() && WinViewRoot::isInitialized()) {
    unknown53c = false;
    if (!(unknown3b8 & 0x208)) {
      setCurrent();
    }
    return WorkObj::wkStandbyLogin();
  }
  return false;
}

bool WinView::wkStandbyLogout() {
  wkCheckTimeout(30000, unknown60.size() == 0 && unknown338.size() == 0 && !isSplit(true), "ログアウトに失敗しました");
  if (unknown60.size() != 0 || (unknown338.size() != 0 && !(unknown3b8 & 0x80))) {
    return false;
  }
  while (unknown338.begin() != unknown338.end()) {
    reslist<u32>::Node *node = unknown338.begin();
    u32 wid = node->value;
    unknown338.erase(node);
    WinProc *proc = static_cast<WinProc *>(WorkRootState::getWork(WinProcRoot::get(), wid));
    if (proc != nullptr) {
      proc->pssDetachView(unknown50);
    }
  }
  WinViewRoot::invalidCurrent(this);
  return WorkObj::wkStandbyLogout();
}

// The u32 reads of the message data follow WorkObj::wkStandby; the pointer is read back the way MsgParam::set(const void *) wrote it (memcpy).
// The message data is read through the queue entry each time (the game recomputes the entry address from the queue front after every call).
// The three lookups (0x7100765c74, 0x7100765cfc, 0x7100765d84) keep the list ends in locals read before the value: with the value as a reference
// into the queue, or with the value read first, the find loop is rotated or the registers differ. The node is compared with the end node as
// base pointers, as in ScnPoolObj::release (0x7100740b58).
void WinView::updateMsg() {
  CS lock(unknown540);
  while (unknown3c0.size() != 0) {
    switch (unknown3c0.get(0).msg) {
    case 0: {
      WorkObj *work = WorkRootState::getWork(*reinterpret_cast<u32 *>(unknown3c0.get(0).data));
      if (work != nullptr && !work->wkIsShutdown()) {
        reslist<u32>::iterator first = unknown338.begin();
        reslist<u32>::iterator last = unknown338.end();
        u32 wid = *reinterpret_cast<u32 *>(unknown3c0.get(0).data);
        reslist<u32>::iterator found = std::find<reslist<u32>::iterator, u32>(first, last, wid);
        if (found.unknown00 == unknown338.m_end) {
          unknown338.insert(found, wid);
        }
        if (getParentView() != nullptr) {
          WorkObj *attach = WorkRootState::getWork(*reinterpret_cast<u32 *>(unknown3c0.get(0).data));
          for (reslist<WorkObj *>::iterator it = wkGetChild()->begin(); it != wkGetChild()->end(); ++it) {
            if (*it != nullptr) {
              static_cast<WinView *>(*it)->attachRenderWork(attach);
            }
          }
        }
      }
      break;
    }
    case 1: {
      CS eventLock(unknown568);
      reslist<IWorkEvent *>::iterator first = unknown378.begin();
      reslist<IWorkEvent *>::iterator last = unknown378.end();
      IWorkEvent *event;
      memcpy(&event, unknown3c0.get(0).data, sizeof(event));
      reslist<IWorkEvent *>::iterator found = std::find<reslist<IWorkEvent *>::iterator, IWorkEvent *>(first, last, event);
      if (found.unknown00 == unknown378.m_end) {
        unknown378.insert(found, event);
      }
      break;
    }
    case 2: {
      CS eventLock(unknown568);
      reslist<IWorkEvent *>::iterator first = unknown378.begin();
      reslist<IWorkEvent *>::iterator last = unknown378.end();
      IWorkEvent *event;
      memcpy(&event, unknown3c0.get(0).data, sizeof(event));
      reslist<IWorkEvent *>::iterator found = std::find<reslist<IWorkEvent *>::iterator, IWorkEvent *>(first, last, event);
      if (found.unknown00 == unknown378.m_end) {
        unknown378.insert(unknown378.begin(), event);
      }
      break;
    }
    case 3:
      unknown338.remove(*reinterpret_cast<u32 *>(unknown3c0.get(0).data));
      break;
    case 4:
      unknown3b8 |= 3;
      break;
    case 5:
      unknown3b8 |= 4;
      break;
    case 6:
      unknown3b8 &= ~4u;
      break;
    case 7:
      WinViewRoot::setCurrent(this);
      break;
    case 8:
      if (*reinterpret_cast<u32 *>(unknown3c0.get(0).data) == 0) {
        unknown3b8 |= 0x20;
      } else {
        unknown3b8 &= ~0x20u;
      }
      break;
    case 9:
      for (reslist<u32>::iterator it = unknown338.begin(); it != unknown338.end(); ++it) {
        WorkObj *work = WorkRootState::getWork(*it);
        if (work != nullptr) {
          work->wkSetEvent(static_cast<EVT>(0));
        }
      }
      break;
    }
    unknown3c0.pop();
  }
}

bool WinView::attachRenderWork(const WorkObj *work) {
  unknown3c0.add(0);
  u32 wid = work->unknown50;
  unknown3c0.set(wid);
  unknown3c0.add(1);
  unknown3c0.set(work);
  return true;
}

bool WinView::detachRenderWork(const WorkObj *work) {
  unknown338.remove(work->unknown50);
  if (getSplitView1() != nullptr) {
    getSplitView1()->detachRenderWork(work);
  }
  if (getSplitView2() != nullptr) {
    getSplitView2()->detachRenderWork(work);
  }
  detachWorkEvent(work);
  return true;
}

bool WinView::attachWorkEvent(IWorkEvent *event, bool isFront) {
  CS lock(unknown540);
  if (isFront) {
    unknown3c0.add(2);
    unknown3c0.set(event);
  } else {
    unknown3c0.add(1);
    unknown3c0.set(event);
  }
  return true;
}

bool WinView::detachWorkEvent(const IWorkEvent *event) {
  CS lock(unknown568);
  unknown378.remove(event);
  if (getSplitView1() != nullptr) {
    getSplitView1()->detachWorkEvent(event);
  }
  if (getSplitView2() != nullptr) {
    getSplitView2()->detachWorkEvent(event);
  }
  return true;
}

template class threadval<WinView::RENDER_INFO>;

template MsgParam<10>::~MsgParam();

} // namespace ml
