#include "ml/win_view_root.h"

#include "ml/dev_graph.h"
#include "ml/device.h"
#include "ml/lib_main.h"
#include "ml/reslist.h"
#include "ml/win_proc_root.h"
#include "ml/win_view.h"
#include "ml/work_root.h"
#include "ml/work_util.h"
#include "mtl/alloc_handle.h"

namespace ml {

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

bool WinViewRoot::isInitialized() {
  WinViewRoot *root = get();
  if (root == nullptr || root->wkIsWaitException()) {
    return false;
  }

  return root->wkIsActive();
}

bool WinViewRoot::wkStandbyLogin() {
  if (!Device::isAllReady() || !LibMain::isInitialized() || WorkRoot::isWinDestroy() || DevGraph::isIgnore() || DevGraph::getRootWidth() == 0) {
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

} // namespace ml

template mm::mtl::PtrSingleton<ml::WinViewRoot>::~PtrSingleton();
