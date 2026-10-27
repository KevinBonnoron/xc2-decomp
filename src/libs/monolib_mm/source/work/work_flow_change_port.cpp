#include "ml/work_flow_change_port.h"

#include "ml/reslist.h"

namespace ml {

WorkFlowChangePort::WorkFlowChangePort(const char *name, WorkObj *parent) : WorkObj(name, parent, 1), unknown1b0(0) { wkSetEvent(static_cast<EVT>(0)); }

WorkFlowChangePort::~WorkFlowChangePort() {}

void WorkFlowChangePort::setup(const char *name) { unknown1b4 = name; }

bool WorkFlowChangePort::wkStandbyLogout() {
  if (unknown60.size() != 0) {
    return false;
  }

  return WorkObj::wkStandbyLogout();
}

} // namespace ml
