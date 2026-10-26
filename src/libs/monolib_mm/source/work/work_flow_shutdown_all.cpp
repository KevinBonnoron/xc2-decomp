#include "ml/work_flow_shutdown_all.h"

namespace ml {

void WorkFlowShutdownAll::wkUpdate() {
  if (!wkIsShutdown()) {
    wkSetEvent(static_cast<EVT>(0));
  }
}

} // namespace ml
