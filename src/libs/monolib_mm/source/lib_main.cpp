#include "ml/lib_main.h"

#include "ml/dev_file_th.h"
#include "ml/reslist.h"
#include "ml/work_control.h"
#include "ml/work_cpu.h"
#include "ml/work_root.h"
#include "ml/work_system.h"
#include "ml/work_util.h"
#include "mtl/alloc_handle.h"

namespace ml {

LibMain::LibMain(const char *name, WorkObj *parent) : WorkObj(name, parent, 8) {}

LibMain::~LibMain() {}

bool LibMain::isInitialized() {
  LibMain *main = get();
  if (main == nullptr || main->wkIsWaitException()) {
    return false;
  }

  return main->wkIsActive();
}

bool LibMain::wkStandbyLogin() {
  if (mm::mtl::PtrSingleton<DevFileTh>::get() == nullptr || !DevFileTh::isInitialized() || !WorkCpu::isInitialized()) {
    return false;
  }

  return WorkObj::wkStandbyLogin();
}

bool LibMain::wkStandbyLogout() {
  int childNum = unknown60.size();
  wkCheckTimeout(30000, WorkSystem::get() == nullptr && childNum == 0, "ログアウトに失敗しました");
  if (unknown60.size() != 0 || WorkSystem::get() != nullptr) {
    return false;
  }

  return WorkObj::wkStandbyLogout();
}

LibMain *LibMain::create() {
  WorkControl *control = WorkControl::get();
  LibMain *main = new (WorkUtil::getWorkMem()) LibMain("LibMain", control);
  WorkRootState::entryWork(main, control, false);
  return main;
}

} // namespace ml
