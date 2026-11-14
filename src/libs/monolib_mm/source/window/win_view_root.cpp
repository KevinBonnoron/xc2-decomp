#include "ml/win_view_root.h"

#include "ml/cache_draw.h"
#include "ml/dev_graph.h"
#include "ml/device.h"
#include "ml/lib_main.h"
#include "ml/proc_desktop.h"
#include "ml/reslist.h"
#include "ml/win_proc_root.h"
#include "ml/win_view.h"
#include "ml/work_obj_flow_system_pause.h"
#include "ml/work_root.h"
#include "ml/work_util.h"
#include "mm_math/mm_pnt.h"
#include "mm_math/mm_rect.h"
#include "mtl/alloc_handle.h"

namespace ml {

namespace {

// Inferred role: stops WinViewRoot::renderView, set by WinViewRoot::cutOff; original name unknown. Numbered after the
// unknown001 to unknown004 of the other files of the window.cpp unit.
bool unknown005;

} // namespace

WinView *WinViewRoot::getView(u32 wid) {
  if (get() == nullptr) {
    return nullptr;
  }
  WorkObj *work = WorkRootState::getWork(wid);
  if (work == nullptr) {
    return nullptr;
  }
  if (WorkRootState::getWork(get(), wid) != nullptr) {
    return static_cast<WinView *>(work);
  }
  if (WorkRootState::isEntryWork(wid, get())) {
    return static_cast<WinView *>(work);
  }
  return nullptr;
}

WinView *WinViewRoot::getCurrent() {
  WinViewRoot *root = get();
  return root != nullptr ? root->unknown1f0 : nullptr;
}

WinView *WinViewRoot::getRootView(WinView *view) {
  WinViewRoot *root = get();
  if (root == nullptr) {
    return nullptr;
  }
  WorkObj *parent = view->unknown58;
  if (root == parent) {
    return nullptr;
  }
  if (ProcDesktop::getView() == parent) {
    return view;
  }
  return getRootView(static_cast<WinView *>(parent));
}

WinView *WinViewRoot::getPointedView(const mm::Pnt<int> &pos) {
  WinView *pointed = nullptr;
  if (get() != nullptr) {
    for (reslist<WorkObj *>::Node *node = get()->wkGetChild()->begin(); node != get()->wkGetChild()->end(); node = node->getNext()) {
      WinView *view = static_cast<WinView *>(node->value);
      if (!view->wkIsWaitException() && view->wkIsActive() && !view->wkIsShutdown()) {
        WinView *child = view->getPointedView(pos);
        if (child != nullptr) {
          pointed = child;
        }
      }
    }
  }
  return pointed;
}

WinProc *WinViewRoot::getCurrentProc() {
  WinViewRoot *root = get();
  return root != nullptr ? root->unknown1f8 : nullptr;
}

void WinViewRoot::destroyProc(const WinProc *proc) {
  WinViewRoot *root = get();
  if (root != nullptr && (root->unknown200 == proc || root->unknown1f8 == proc)) {
    root->unknown1f8 = nullptr;
    root->unknown200 = nullptr;
  }
}

bool WinViewRoot::isCurrent(const WinView *view) {
  WinViewRoot *root = get();
  if (root != nullptr) {
    WinView *current = root->unknown1f0;
    return current == view && current != nullptr;
  }
  return false;
}

bool WinViewRoot::isCurrentChild(const WinView *view, const WinView *current) {
  if (current != nullptr && get() != nullptr) {
    for (reslist<WorkObj *>::Node *node = view->wkGetChild()->begin(); node != view->wkGetChild()->end(); node = node->getNext()) {
      WinView *child = static_cast<WinView *>(node->value);
      if (child == current || isCurrentChild(child, current)) {
        return true;
      }
    }
  }
  return false;
}

WinView *WinViewRoot::getView(const char *name) {
  if (get() != nullptr) {
    for (reslist<WorkObj *>::Node *node = get()->wkGetChild()->begin(); node != get()->wkGetChild()->end(); node = node->getNext()) {
      WinView *view = static_cast<WinView *>(WorkRootState::getWork(node->value, name));
      if (view != nullptr) {
        return view;
      }
    }
  }
  return nullptr;
}

WinView *WinViewRoot::getFullScreenView() {
  if (get() == nullptr) {
    return nullptr;
  }
  WinView *desktop = ProcDesktop::getView();
  if (desktop == nullptr) {
    return nullptr;
  }
  for (reslist<WorkObj *>::Node *node = desktop->wkGetChild()->begin(); node != desktop->wkGetChild()->end(); node = node->getNext()) {
    WinView *view = static_cast<WinView *>(node->value);
    if (!view->wkIsShutdown()) {
      if (view->unknown3b8 & 1) {
        return view;
      }
      mm::Rect<int> rect = view->getRect(false);
      if (!(view->unknown3b8 & 4) && rect.x == 0 && rect.y == 0 && rect.width == DevGraph::getRootWidth() && rect.height == DevGraph::getRootHeight()) {
        return view;
      }
    }
  }
  return desktop;
}

bool WinViewRoot::isInitialized() {
  WinViewRoot *root = get();
  if (root == nullptr || root->wkIsWaitException()) {
    return false;
  }

  return root->wkIsActive();
}

bool WinViewRoot::wkStandbyLogin() {
  if (!Device::isAllReady() || !LibMain::isInitialized()) {
    return false;
  }
  if (!WorkRoot::isWinDestroy() && !DevGraph::isIgnore() && DevGraph::getRootWidth() == 0) {
    return false;
  }

  return WorkObj::wkStandbyLogin();
}

bool WinViewRoot::wkStandbyLogout() {
  if (unknown60.size() == 0 && WinProcRoot::get() == nullptr) {
    return WorkObj::wkStandbyLogout();
  }

  return false;
}

WinViewRoot *WinViewRoot::create(WorkObj *parent) {
  WinViewRoot *root = new (WorkUtil::getWorkMem()) WinViewRoot("WinViewRoot", parent);
  WorkRootState::entryWork(root, parent, false);
  return root;
}

void WinViewRoot::cutOff(bool cut) { unknown005 = cut; }

void WinViewRoot::renderView() {
  WinViewRoot *root = get();
  if (root == nullptr || unknown005 || root->wkIsShutdown() || ProcDesktop::get() == nullptr) {
    return;
  }
  for (reslist<WorkObj *>::Node *node = get()->wkGetChild()->begin(); node != get()->wkGetChild()->end(); node = node->getNext()) {
    static_cast<WinView *>(node->value)->renderView();
  }
  f32 rate = WorkObjFlowSystemPause::getRate();
  if (rate != 0.0f) {
    DebDraw *draw = DebDraw::get(0xffffffff);
    draw->setOrtho();
    draw->setZComp(false);
    draw->setZWrite(false);
    draw->setCol(0.0f, 0.0f, 0.0f, rate);
    draw->renderRectFill(0, 0, DevGraph::getRootWidth(), DevGraph::getRootHeight());
  }
}

} // namespace ml

template mm::mtl::PtrSingleton<ml::WinViewRoot>::~PtrSingleton();
