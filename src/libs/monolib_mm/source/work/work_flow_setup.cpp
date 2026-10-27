#include "ml/work_flow_setup.h"

#include "ml/lib_main.h"
#include "ml/reslist.h"

namespace ml {

WorkFlowSetup::WorkFlowSetup(const char *name, WorkObj *parent) : WorkObj(name, parent, 0), unknown1b0(0) {}

WorkFlowSetup::~WorkFlowSetup() {}

bool WorkFlowSetup::wkStandbyLogin() {
  if (!LibMain::isInitialized()) {
    return false;
  }

  wkSetEvent(static_cast<EVT>(0));
  return WorkObj::wkStandbyLogin();
}

bool WorkFlowSetup::wkStandbyLogout() {
  if (unknown60.size() != 0) {
    return false;
  }

  return WorkObj::wkStandbyLogout();
}

} // namespace ml
