#include "ml/win_proc.h"

#include "ml/proc_desktop.h"
#include "ml/win_proc_root.h"
#include "ml/win_view.h"
#include "ml/win_view_root.h"
#include "ml/work_root.h"
#include "ml/work_util.h"
#include "mm_mtl/fixstr.h"
#include "mtl/alloc_handle.h"

namespace ml {

WinProc::WinProc(const char *name, WorkObj *parent, s16 childNum) : WorkObj(name, parent, childNum), unknown1e8(0xffffffff), unknown1ec(2) { unknown1a8.create(16, unknown54); }

WinProc::~WinProc() {}

WinView *WinProc::pssGetApplicationView() { return pssGetApplicationView(pssGetView(0xffffffff)); }

WinView *WinProc::pssGetApplicationView(WinView *view) {
  for (; view != nullptr; view = view->getParentView()) {
    if (ProcDesktop::getView() == view) {
      return view;
    }
    if (view->getParentView() == ProcDesktop::getView()) {
      return view;
    }
  }

  return nullptr;
}

bool WinProc::wkStandbyLogin() { return WorkObj::wkStandbyLogin(); }

bool WinProc::wkStandbyLogout() {
  pssDetachView();
  WinViewRoot::destroyProc(this);
  return WorkObj::wkStandbyLogout();
}

WinView *WinProc::pssCreateView(const char *name, WorkObj *parent, s16 childNum) {
  mm::mtl::FixStr<64> viewName("WinView");
  viewName += name;
  WinView *view = WorkUtil::createWork<WinView>(viewName.c_str(), parent, false);
  view->wkReplaceHasChild(childNum);
  pssAttachView(view);
  unknown1e8 = parent->unknown50;
  if (unknown58 != nullptr && unknown58 != WinProcRoot::get()) {
    view->setRect(static_cast<WinProc *>(unknown58)->pssMakeClientRect());
  }
  return view;
}

bool WinProc::pssAttachView(WinView *view) {
  view->attachRenderWork(this);
  u32 wid = view->unknown50;
  unknown1a8.push_back(wid);
  return true;
}

void WinProc::pssSetFocus() {
  WinView *view = pssGetView(0xffffffff);
  if (view != nullptr) {
    view->setDisp(true, false);
    view->setCurrent();
  }
}

WorkObj *WinProc::pssGetParentView() {
  WorkObj *parent = WorkRootState::getWork(unknown1e8);
  if (parent != nullptr) {
    return parent;
  }
  return WinViewRoot::get();
}

WinProc *WinProc::pssGetRoot(WinProc *proc) {
  if (proc != nullptr) {
    WorkObj *parent;
    do {
      parent = proc->unknown58;
      if (parent == WinProcRoot::get()) {
        return nullptr;
      }
      if (parent == ProcDesktop::get()) {
        return proc;
      }
      proc = static_cast<WinProc *>(parent);
    } while (parent != nullptr);
  }
  return nullptr;
}

WinView *WinProc::pssGetView(u32 wid) {
  if (wid != 0xffffffff) {
    return static_cast<WinView *>(WorkRootState::getWork(wid));
  }
  if (unknown1a8.size() == 0) {
    return nullptr;
  }
  return static_cast<WinView *>(WorkRootState::getWork(unknown1a8.begin()->value));
}

bool WinProc::pssDetachView() {
  for (reslist<u32>::iterator it = unknown1a8.begin(); it != unknown1a8.end(); ++it) {
    if (WinViewRoot::get() != nullptr) {
      u32 wid = *it;
      WinView *view = static_cast<WinView *>(WorkRootState::getWork(wid));
      if (view != nullptr && (WorkRootState::getWork(WinViewRoot::get(), wid) != nullptr || WorkRootState::isEntryWork(wid, WinViewRoot::get()))) {
        view->detachRenderWork(this);
      }
    }
  }
  unknown1a8.clear();
  return true;
}

const WinView *WinProc::pssGetView(u32 wid) const {
  if (wid != 0xffffffff) {
    return static_cast<WinView *>(WorkRootState::getWork(wid));
  }
  if (unknown1a8.size() == 0) {
    return nullptr;
  }
  return static_cast<WinView *>(WorkRootState::getWork(unknown1a8.begin()->value));
}

mm::Rect<int> WinProc::pssMakeClientRect() const {
  if (unknown1a8.size() == 0) {
    return mm::Rect<int>(0, 0, 0, 0);
  }
  const WinView *view = pssGetView(0xffffffff);
  int childNum = view->wkGetChild()->size();
  mm::Rect<int> rect = view->getRect(false);
  rect.x += childNum * 20;
  rect.y += childNum * 20;
  int growX = (static_cast<int>(rect.width * 0.6f) - rect.width) / 2;
  int growY = (static_cast<int>(rect.height * 0.6f) - rect.height) / 2;
  rect.width += growX * 2;
  rect.height += growY * 2;
  rect.x -= growX;
  rect.y -= growY;
  return rect;
}

} // namespace ml
