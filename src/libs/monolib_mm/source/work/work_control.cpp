#include "ml/work_control.h"

#include "ml/critical_section.h"
#include "ml/work_flow_shutdown_all.h"

namespace ml {

CriticalSection &WorkControl::getCriticalSection() {
  static CriticalSection sect;
  return sect;
}

void WorkControl::wkTail() {}

bool WorkControl::hasFlow() { return WorkFlowShutdownAll::get() != nullptr; }

} // namespace ml

template mm::mtl::PtrSingleton<ml::WorkControl>::~PtrSingleton();
