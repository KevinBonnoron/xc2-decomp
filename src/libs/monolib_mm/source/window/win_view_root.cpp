#include "ml/win_view_root.h"

#include "ml/dev_graph.h"
#include "ml/device.h"
#include "ml/lib_main.h"
#include "ml/reslist.h"
#include "ml/win_proc_root.h"
#include "ml/work_root.h"
#include "ml/work_util.h"
#include "mtl/alloc_handle.h"

namespace ml {

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
  if (m_children.size() == 0 && WinProcRoot::get() == nullptr) {
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
