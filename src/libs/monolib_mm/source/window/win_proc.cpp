#include "ml/win_proc.h"

#include "ml/proc_desktop.h"
#include "ml/win_proc_root.h"
#include "ml/win_view.h"
#include "ml/win_view_root.h"
#include "ml/work_root.h"

namespace ml {

bool WinProc::wkStandbyLogin() { return WorkObj::wkStandbyLogin(); }

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

const WinView *WinProc::pssGetView(u32 wid) const {
  if (wid != 0xffffffff) {
    return static_cast<WinView *>(WorkRootState::getWork(wid));
  }
  if (unknown1a8.size() == 0) {
    return nullptr;
  }
  return static_cast<WinView *>(WorkRootState::getWork(unknown1a8.begin()->value));
}

} // namespace ml
