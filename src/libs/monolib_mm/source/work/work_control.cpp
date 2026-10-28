#include "ml/work_control.h"

#include "ml/critical_section.h"
#include "ml/device.h"
#include "ml/reslist.h"
#include "ml/work_flow_change_port.h"
#include "ml/work_flow_setup.h"
#include "ml/work_flow_shutdown_all.h"
#include "ml/work_obj_flow_system_pause.h"
#include "ml/work_root.h"
#include "ml/work_util.h"
#include "mm_mtl/fixed_queue.h"
#include "mtl/alloc_handle.h"

namespace ml {

namespace _wkcnt {

mm::mtl::FixedQueue<PAUSEQ, 16> s_quePause;

} // namespace _wkcnt

s32 WorkControl::s_nPauseNum;
s32 WorkControl::s_nSysPauseNum;

CriticalSection &WorkControl::getCriticalSection() {
  static CriticalSection sect;
  return sect;
}

WorkControl::WorkControl(const char *name, WorkObj *parent) : WorkObj(name, parent, 0x20) {
  s_nPauseNum = 0;
  s_nSysPauseNum = 0;
  unknown1b0 = 0;
}

WorkControl::~WorkControl() {}

bool WorkControl::setFlowSetup() {
  if (WorkFlowSetup::get() == nullptr) {
    WorkControl *control = get();
    WorkFlowSetup *flow = new (WorkRootState::getWorkMem()) WorkFlowSetup("WorkFlowSetup", control);
    WorkRootState::entryWork(flow, control, false);
  }
  return true;
}

bool WorkControl::setFlowChangePort(const char *name) {
  if (WorkFlowChangePort::get() == nullptr) {
    WorkControl *control = get();
    WorkFlowChangePort *flow = new (WorkRootState::getWorkMem()) WorkFlowChangePort("WorkFlowChangePort", control);
    WorkRootState::entryWork(flow, control, false);
    if (flow != nullptr) {
      flow->setup(name);
      return true;
    }
  }
  return false;
}

bool WorkControl::setFlowSystemPause(u32 wid) {
  if (WorkObjFlowSystemPause::get() == nullptr) {
    WorkControl *control = get();
    WorkObjFlowSystemPause *flow = new (WorkRootState::getWorkMem()) WorkObjFlowSystemPause("WorkObjFlowSystemPause", control);
    WorkRootState::entryWork(flow, control, false);
    if (flow != nullptr) {
      flow->unknown1bc = wid;
      return true;
    }
  }
  return false;
}

bool WorkControl::setFlowShutdownAll(bool) {
  if (WorkFlowShutdownAll::get() == nullptr) {
    WorkControl *control = get();
    WorkFlowShutdownAll *flow = new (WorkRootState::getWorkMem()) WorkFlowShutdownAll("WorkFlowShutdownAll", control);
    WorkRootState::entryWork(flow, control, false);
    return true;
  }
  return false;
}

bool WorkControl::wkStandbyLogout() {
  if (unknown60.size() != 0 || Device::get() != nullptr) {
    return false;
  }
  if (s_nPauseNum > 0) {
    s_nPauseNum = 0;
  }
  return WorkObj::wkStandbyLogout();
}

void WorkControl::wkTail() {}

WorkControl *WorkControl::create(WorkObj *parent) { return WorkUtil::createWork<WorkControl>("WorkControl", parent, false); }

void WorkControl::pause(bool isPause, const char *name) {
  CS lock(getCriticalSection());
  _wkcnt::PAUSEQ request;
  request.unknown00 = isPause;
  request.unknown04 = name;
  _wkcnt::s_quePause.push(request);
}

bool WorkControl::hasFlow() { return WorkFlowShutdownAll::get() != nullptr; }

} // namespace ml

template mm::mtl::PtrSingleton<ml::WorkControl>::~PtrSingleton();
