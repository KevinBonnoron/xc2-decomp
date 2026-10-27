#include "ml/work_flow_shutdown_all.h"

#include "ml/lib_main.h"
#include "ml/proc_desktop.h"
#include "ml/reslist.h"
#include "ml/work_flow_setup.h"
#include "ml/work_root.h"
#include "ml/work_system.h"

namespace ml {

WorkFlowShutdownAll::WorkFlowShutdownAll(const char *name, WorkObj *parent) : WorkObj(name, parent, 1), unknown1b0(0) {}

WorkFlowShutdownAll::~WorkFlowShutdownAll() {}

bool WorkFlowShutdownAll::wkStandbyLogout() {
  switch (unknown1b0) {
  case 0:
    if (WorkFlowSetup::get() == nullptr) {
      ProcDesktop *desktop = ProcDesktop::get();
      if (desktop == nullptr || desktop->wkIsWaitException()) {
        return false;
      }
      if (!desktop->wkIsActive()) {
        return false;
      }
      unknown1b0++;
    }
    return false;
  case 1:
    if (ProcDesktop::get() == nullptr) {
      unknown1b0 = 2;
    } else {
      ProcDesktop::deleteApp();
      unknown1b0++;
    }
  case 2: {
    ProcDesktop *desktop = ProcDesktop::get();
    if (desktop != nullptr && desktop->unknown60.size() != 0) {
      return false;
    }
    if (LibMain::get() != nullptr) {
      LibMain::get()->wkSetEvent(static_cast<EVT>(0));
    }
    if (WorkSystem::get() != nullptr) {
      WorkSystem::get()->wkSetEvent(static_cast<EVT>(0));
    }
    unknown1b0++;
  }
  case 3:
    if (WorkSystem::get() != nullptr || LibMain::get() != nullptr) {
      return false;
    }
    WorkRootState::shutdownAll();
    unknown1b0++;
  case 4:
    if (unknown60.size() != 0) {
      return false;
    }
    return WorkObj::wkStandbyLogout();
  default:
    return false;
  }
}

void WorkFlowShutdownAll::wkUpdate() {
  if (!wkIsShutdown()) {
    wkSetEvent(static_cast<EVT>(0));
  }
}

} // namespace ml
