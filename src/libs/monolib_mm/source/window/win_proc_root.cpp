#include "ml/win_proc_root.h"

#include "ml/reslist.h"
#include "ml/work_root.h"
#include "ml/work_util.h"
#include "mtl/alloc_handle.h"

namespace ml {

WinProcRoot::WinProcRoot(const char *name, WorkObj *parent) : WorkObj(name, parent, 32) {}

WinProcRoot::~WinProcRoot() {}

bool WinProcRoot::isInitialized() {
  WinProcRoot *root = get();
  if (root->wkIsWaitException()) {
    return false;
  }

  return root->wkIsActive();
}

bool WinProcRoot::wkStandbyLogout() {
  if (unknown60.size() != 0) {
    return false;
  }

  return WorkObj::wkStandbyLogout();
}

WinProcRoot *WinProcRoot::create(WorkObj *parent) {
  WinProcRoot *root = new (WorkUtil::getWorkMem()) WinProcRoot("WinProcRoot", parent);
  WorkRootState::entryWork(root, parent, false);
  return root;
}

} // namespace ml
