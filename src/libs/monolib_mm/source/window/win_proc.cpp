#include "ml/win_proc.h"

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

} // namespace ml
