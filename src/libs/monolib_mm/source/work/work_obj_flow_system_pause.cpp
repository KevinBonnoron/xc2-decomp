#include "ml/work_obj_flow_system_pause.h"

namespace ml {

WorkObjFlowSystemPause::WorkObjFlowSystemPause(const char *name, WorkObj *parent) : WorkObj(name, parent, 1), unknown1b0(0), unknown1b4(0), unknown1b8(false), unknown1bc(-1) {}

WorkObjFlowSystemPause::~WorkObjFlowSystemPause() {}

f32 WorkObjFlowSystemPause::getRate() {
  WorkObjFlowSystemPause *pause = get();
  if (pause != nullptr) {
    f32 rate = (f32)(pause->unknown1b4 + 1) / 5.0f;
    if (rate > 1.0f) {
      rate = 1.0f;
    }
    return rate * 0.4f;
  }

  return 0.0f;
}

void WorkObjFlowSystemPause::releasePause() {
  WorkObjFlowSystemPause *pause = get();
  if (pause != nullptr) {
    pause->unknown1b8 = true;
  }
}

void WorkObjFlowSystemPause::wkUpdate() {
  if (!wkIsShutdown()) {
    wkSetEvent(static_cast<EVT>(0));
  }
}

} // namespace ml
