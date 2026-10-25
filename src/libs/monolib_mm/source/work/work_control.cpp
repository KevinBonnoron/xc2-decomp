#include "ml/work_control.h"

#include "ml/work_flow_shutdown_all.h"

namespace ml {

void WorkControl::wkTail() {}

bool WorkControl::hasFlow() { return WorkFlowShutdownAll::get() != nullptr; }

} // namespace ml
