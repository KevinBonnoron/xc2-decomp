#include "ml/work_cpu.h"

#include "ml/critical_section.h"
#include "ml/dev_clock.h"
#include "ml/dev_graph.h"
#include "ml/fixed_size_alloc.h"
#include "ml/reslist.h"
#include "ml/thread_util.h"
#include "ml/threadval.h"
#include "ml/work_background.h"
#include "ml/work_control.h"
#include "ml/work_cpu_thread.h"
#include "ml/work_root.h"
#include "ml/work_util.h"
#include "mm/mm_std_base.h"
#include "mm_mtl/algorithm.h"
#include "mm_mtl/fixed_list.h" // IWYU pragma: keep

namespace ml {

WorkCpuThread *WorkCpu::getCpuThread(CPUID cpuId) {
  WorkCpu *cpu = get();
  u32 index = cpuId - CPUID_UNKNOWN_1;
  return cpu->unknown1740[index];
}

void WorkCpu::removeCpu(CPUID cpu, WorkCpuThread *) { get()->unknown1740[cpu - CPUID_UNKNOWN_1] = nullptr; }

namespace _mlwcpu {

bool s_bEnableLib;
bool s_bEShop;
bool s_bStallRender;
long s_aHearBeat[3];
s32 s_cpuStall;
bool s_bBackGround;

CriticalSection &getSwapLock() {
  static CriticalSection lock;
  return lock;
}

CriticalSection &getHeartBeatLock() {
  static CriticalSection lock;
  return lock;
}

CriticalSection &getListGrpLock() {
  static CriticalSection lock;
  return lock;
}

CriticalSection &getListenerLock() {
  static CriticalSection lock;
  return lock;
}

CriticalSection &getTermThreadLock() {
  static CriticalSection lock;
  return lock;
}

CriticalSection &getWaitingJobLock() {
  static CriticalSection lock;
  return lock;
}

} // namespace _mlwcpu

bool WorkCpu::s_bRenderSubCpu;

bool WorkCpu::isInitialized() {
  WorkCpu *cpu = get();
  if (cpu == nullptr) {
    return false;
  }

  for (u32 i = 0; i < cpu->m_cpuNum; i++) {
    WorkCpuThread *thread = cpu->unknown1740[i];
    if (thread == nullptr || thread->wkIsWaitException() || !thread->wkIsActive()) {
      return false;
    }
  }

  return true;
}

void WorkCpu::stallRender() { _mlwcpu::s_bStallRender = true; }

bool WorkCpu::isGotoEShop() { return _mlwcpu::s_bEShop; }

void WorkCpu::gotoEShop() { _mlwcpu::s_bEShop = true; }

void WorkCpu::setEnableSystem() { _mlwcpu::s_bEnableLib = true; }

bool WorkCpu::isEnableSystem() { return _mlwcpu::s_bEnableLib; }

u64 WorkCpu::getCurrentThreadId() { return ThreadUtil::getCurrentID(); }

u64 WorkCpu::getMainThreadId() {
  WorkCpu *cpu = get();
  if (cpu != nullptr) {
    return cpu->unknown2020;
  }

  return 0;
}

bool WorkCpu::checkTermThread() { return true; }

void WorkCpu::setProfiler(bool isProfiler) {}

f32 WorkCpu::getAllCostSec() {
  WorkCpu *cpu = get();
  if (cpu != nullptr) {
    return cpu->unknown2034;
  }

  return 0.0f;
}

void WorkCpu::setRenderSubCpu(bool isRenderSubCpu) { s_bRenderSubCpu = isRenderSubCpu; }

mtl::ALLOC_HANDLE WorkCpu::getMemWork() {
  WorkCpu *cpu = get();
  if (cpu != nullptr) {
    return cpu->unknown1b4;
  }

  return mtl::ALLOC_HANDLE();
}

mtl::ALLOC_HANDLE WorkCpu::getMemStack() {
  WorkCpu *cpu = get();
  if (cpu != nullptr) {
    return cpu->unknown1b8;
  }

  return mtl::ALLOC_HANDLE();
}

CPUID WorkCpu::getMainCPUID() { return CPUID_UNKNOWN_1; }

CPUID WorkCpu::getRenderCPUID() {
  if (s_bRenderSubCpu) {
    u32 cpuNum = get()->m_cpuNum;
    if (cpuNum > 2) {
      return CPUID_UNKNOWN_3;
    }

    if (cpuNum == 2) {
      return CPUID_UNKNOWN_2;
    }
  }

  return CPUID_UNKNOWN_1;
}

u32 WorkCpu::getCpuNum() { return get()->m_cpuNum; }

void WorkCpu::setThread(DO_THREAD thread) { get()->m_thread = thread; }

DO_THREAD WorkCpu::getThread() {
  WorkCpu *cpu = get();
  if (cpu != nullptr) {
    return cpu->unknown1738;
  }

  return static_cast<DO_THREAD>(0);
}

u32 WorkCpu::getEven() { return get()->m_even; }

bool WorkCpu::isShutdown() {
  WorkCpu *cpu = get();
  if (cpu != nullptr) {
    return (cpu->unknown1b0 & 0x2) != 0;
  }

  return false;
}

u32 WorkCpu::getFrameCountU32() { return get()->unknown2090; }

const unsigned long &WorkCpu::getFrameCount() { return get()->unknown2090; }

u32 WorkCpu::getOdd() { return get()->m_even == 0; }

bool WorkCpu::isBackground() { return _mlwcpu::s_bBackGround; }

void WorkCpu::syncSubCpu() {}

void WorkCpu::setHeartBeatCpu(CPUID cpu) { DevClock::getClockNow(_mlwcpu::s_aHearBeat[cpu - 1]); }

u32 WorkCpu::getJobTrans() { return get()->m_jobTrans[getOdd()]; }

const long &WorkCpu::getBeginClock(bool isCurrent) {
  WorkCpu *cpu = get();
  int index = isCurrent ? 0 : 4;
  return cpu->unknown2048[index];
}

const long &WorkCpu::getTailStartClock() { return get()->m_tailStartClock; }

const long &WorkCpu::getTailEndClock() { return get()->m_tailEndClock; }

const long &WorkCpu::getSyncClock() { return get()->m_syncClock; }

CPUID WorkCpu::getCurrentCPUID() {
  WorkCpu *cpu = get();
  if (cpu == nullptr) {
    return CPUID_UNKNOWN_0;
  }

  u64 threadId = ThreadUtil::getCurrentID();
  for (u32 i = 0; i < cpu->m_cpuNum; i++) {
    WorkCpuThread *thread = cpu->unknown1740[i];
    if (thread != nullptr && thread->getThreadID() == threadId) {
      return thread->getCPUID();
    }
  }

  return ThreadUtil::getCurrentCPUID();
}

bool WorkCpu::isStackAdr(void *address, CPUID cpuId) {
  WorkCpu *cpu = get();
  if (cpu != nullptr) {
    for (u32 i = 0; i < cpu->m_cpuNum; i++) {
      WorkCpuThread *thread = cpu->unknown1740[i];
      if (thread != nullptr && (cpuId == CPUID_UNKNOWN_0 || thread->getCPUID() == cpuId)) {
        u64 stackAddress;
        u64 stackSize;
        thread->getStackInfo(stackAddress, stackSize);
        u64 target = reinterpret_cast<u64>(address);
        if (stackAddress <= target && stackAddress + stackSize > target) {
          return true;
        }
      }
    }
  }

  return false;
}

bool WorkCpu::getStackInfo(u64 threadId, u64 &address, u64 &size) {
  WorkCpu *cpu = get();
  if (cpu == nullptr) {
    return false;
  }

  for (u32 i = 0; i < cpu->m_cpuNum; i++) {
    WorkCpuThread *thread = cpu->unknown1740[i];
    if (thread != nullptr && thread->getThreadID() == threadId) {
      thread->getStackInfo(address, size);
      return true;
    }
  }

  return true;
}

u64 WorkCpu::getThreadId(CPUID cpuId) {
  WorkCpu *cpu = get();
  if (cpu == nullptr) {
    return 0;
  }

  if (cpuId == CPUID_UNKNOWN_1) {
    return cpu->unknown2020;
  }

  for (u32 i = 1; i < cpu->m_cpuNum; i++) {
    WorkCpuThread *thread = cpu->unknown1740[i];
    if (thread == nullptr) {
      continue;
    }
    if (thread->getCPUID() == cpuId) {
      return thread->getThreadID();
    }
  }

  return 0;
}

bool WorkCpu::isStackOverFlow() {
  WorkCpu *cpu = get();
  if (cpu != nullptr) {
    u64 threadId = ThreadUtil::getCurrentID();
    for (u64 i = 0; i < cpu->m_cpuNum; i++) {
      WorkCpuThread *thread = cpu->unknown1740[i];
      if (thread != nullptr && thread->getThreadID() == threadId) {
        return thread->isStackOverFlow();
      }
    }
    ThreadUtil::getCurrentCPUID();
  }

  return false;
}

CPUID WorkCpu::getJobCPUID() {
  WorkCpu *cpu = get();
  CPUID result = CPUID_UNKNOWN_0;
  u32 minJobNum = 10000;
  for (u32 i = 0; i < cpu->m_cpuNum; i++) {
    WorkCpuThread *thread = cpu->unknown1740[i];
    if (i == 0 && cpu->unknown1738 == DO_THREAD_UNKNOWN_2) {
      continue;
    }
    u32 jobNum = thread->getJobNum();
    if (minJobNum > jobNum) {
      result = thread->getCPUID();
      minJobNum = jobNum;
    }
  }

  return result;
}

WorkCpu::GRPLIST *WorkCpu::getListGrp(int handle) {
  MM_VERIFY(_mlwcpu::getListGrpLock().isLocked());
  for (mm::mtl::FixedList<GRPLIST, 128>::iterator it = unknown280.begin(); it != unknown280.end(); ++it) {
    if (it->unknown00 == handle) {
      return &*it;
    }
  }

  return nullptr;
}

void WorkCpu::wakeup(int cpu) {
  WorkCpu *instance = get();
  if (instance == nullptr) {
    return;
  }
  WorkCpuThread *mainThread = instance->unknown1740[0];
  if (mainThread == nullptr) {
    return;
  }

  if (instance->unknown1738 == DO_THREAD_UNKNOWN_0) {
    {
      CS lock(_mlwcpu::getListGrpLock());
      for (mm::mtl::FixedList<GRPLIST, 128>::iterator it = instance->unknown280.begin(); it != instance->unknown280.end(); ++it) {
        if (cpu == -1 || it->unknown00 == cpu) {
          GRPLIST *group = instance->getListGrp(cpu);
          for (u32 i = 0; i < get()->m_cpuNum; i++) {
            mainThread->addJobThreadList(group->unknown08[i], 1);
          }
          for (u32 i = 0; i < get()->m_cpuNum; i++) {
            instance->unknown1740[i]->addJobThreadList(group->unknown08[i], 2);
          }
        }
      }
    }
    mainThread->updateDirect(false);
  } else {
    bool isAdded[16] = {};
    {
      CS lock(_mlwcpu::getListGrpLock());
      for (mm::mtl::FixedList<GRPLIST, 128>::iterator it = instance->unknown280.begin(); it != instance->unknown280.end(); ++it) {
        if (cpu == -1 || it->unknown00 == cpu) {
          GRPLIST *group = instance->getListGrp(cpu);
          for (u32 i = 0; i < get()->m_cpuNum; i++) {
            isAdded[i] = instance->unknown1740[i]->addJobThreadList(group->unknown08[i], 0);
          }
        }
      }
    }
    for (u32 i = 1; i < instance->m_cpuNum; i++) {
      if (isAdded[i]) {
        instance->unknown1740[i]->setEvent(true);
      }
    }
  }
}

f32 WorkCpu::getJobCost(CPUID cpuId) { return getCpuThread(cpuId)->getJobCost(); }

bool WorkCpu::isSuspendThread(CPUID cpuId) {
  WorkCpu *cpu = get();
  if (cpu == nullptr) {
    return false;
  }

  WorkCpuThread *thread = cpu->unknown1740[cpuId - CPUID_UNKNOWN_1];
  if (thread != nullptr) {
    return thread->isSuspendThread();
  }

  return false;
}

void WorkCpu::beginRender() {
  WorkCpu *cpu = get();
  if (cpu != nullptr && cpu->unknown1758 != -1 && !_mlwcpu::s_bStallRender && (cpu->unknown1b0 & 0x2) == 0) {
    wakeup(cpu->unknown1758);
  }
}

u32 WorkCpu::getCounter() {
  WorkCpu *cpu = get();
  if (cpu != nullptr) {
    return cpu->unknown195c;
  }

  return 0;
}

void WorkCpu::gotoBackground() {}

void WorkCpu::gotoForeground() {}

void WorkCpu::backgroundProcess() {}

void WorkCpu::backgroundProcess(CPUID cpu) {}

u32 WorkCpu::thForeground(void *argument, void *userData) { return 0; }

u32 WorkCpu::thBackground(void *argument, void *userData) { return 0; }

u32 WorkCpu::thSwap(void *argument, void *userData) {
  reslist<IThreadValue *> &list = get()->unknown1c0[reinterpret_cast<u64>(argument)];
  for (reslist<IThreadValue *>::Node *node = list.begin(); node != list.end(); node = node->getNext()) {
    node->value->tvSwap();
  }
  return 0;
}

void WorkCpu::setAfterUpdateRender(bool isAfterUpdateRender) {
  WorkCpu *cpu = get();
  if (cpu != nullptr) {
    if (isAfterUpdateRender) {
      cpu->unknown1b0 |= 0x10;
    } else {
      cpu->unknown1b0 &= ~0x10;
    }
  }
}

void WorkCpu::endUpdate() {
  WorkCpu *cpu = get();
  if (cpu != nullptr) {
    cpu->unknown1b0 |= 0x20;
    if (!WorkRootState::isThreadRender()) {
      if (cpu->unknown1758 != -1) {
        sync(cpu->unknown1758, WKCPU_SYNC_UNKNOWN_1, CPUID_UNKNOWN_0);
      }
      swapBank();
    }
  }
}

bool WorkCpu::isHomeMenuEnable() { return true; }

int WorkCpu::reqHomeMenuDisable() { return 9999; }

int WorkCpu::reqImm(bool isEnable) { return 9999; }

void WorkCpu::removeHomeMenuDisable(DEFHBM *&handle) {}

void WorkCpu::removeImm(DEFIMM *&handle) {}

void WorkCpu::attachJobCol(const mm::Col3 &color) {
  if (get()->unknown1798 != nullptr) {
    get()->unknown1798->unknown28 = unknown001(color);
  }
}

s32 WorkCpu::getHeartBeatStall() { return _mlwcpu::s_cpuStall; }

void WorkCpu::clrHeartBeatStall() { _mlwcpu::s_cpuStall = 0; }

u32 WorkCpu::thRender(void *argument, void *userData) {
  WorkCpu *cpu = static_cast<WorkCpu *>(argument);
  if ((cpu->unknown1b0 & 0x10) != 0) {
    long clock;
    DevClock::getClockNow(clock);
    f32 time;
    for (;;) {
      if ((cpu->unknown1b0 & 0x20) != 0) {
        break;
      }
      DevClock::getTimeNow(time, clock);
      if (time > 0.1f) {
        break;
      }
    }
  }
  cpu->unknown1760 = true;
  long clock;
  DevClock::getClockNow(clock);
  WorkRootState::renderWork();
  DevClock::getTimeNow(cpu->unknown2030, clock);
  cpu->unknown1760 = false;
  return 0;
}

void WorkCpu::resumeThread() {
  WorkCpu *cpu = get();
  if (cpu != nullptr && getCurrentCPUID() == CPUID_UNKNOWN_1) {
    for (u32 i = 1; i < cpu->m_cpuNum; i++) {
      cpu->unknown1740[i]->setEvent(true);
    }
  }
}

void WorkCpu::swapBank() {
  CS lock(_mlwcpu::getSwapLock());
  WorkCpu *cpu = get();
  cpu->m_even = cpu->m_even == 0;
  if (cpu->unknown175c != -1) {
    wakeup(cpu->unknown175c);
    sync(cpu->unknown175c, WKCPU_SYNC_UNKNOWN_0, CPUID_UNKNOWN_0);
  }
}

void WorkCpu::beginFrame() {
  WorkCpu *cpu = get();
  if (cpu == nullptr) {
    return;
  }
  cpu->m_jobTrans[cpu->m_even] = 0;
  if ((cpu->unknown1b0 & 0x2) == 0) {
    if (!_mlwcpu::s_bStallRender) {
      DevGraph::cmdExecDisplayList();
    }
  } else if (_mlwcpu::s_bBackGround && !_mlwcpu::s_bStallRender) {
    DevGraph::cmdExecDisplayList();
  }
  DevClock::getClockNow(cpu->unknown2048[0]);
  for (u32 i = 0; i < get()->m_cpuNum; i++) {
    WorkCpuThread *thread = cpu->unknown1740[i];
    if (thread != nullptr) {
      thread->unknown1e0 = 0.0f;
      DevClock::getClockNow(thread->unknown1d0);
      thread->unknown1d8 = thread->unknown1d0;
    }
  }
  DevGraph::cb(RCB_UNKNOWN_0);
}

void WorkCpu::beginUpdate() {
  WorkCpu *cpu = get();
  if (cpu != nullptr) {
    for (mm::mtl::FixedList<AUTO_EXEC, 32>::iterator it = cpu->unknown17a0.begin(); it != cpu->unknown17a0.end(); ++it) {
      wakeup((*it).unknown00);
    }
  }
}

void WorkCpu::endRender() {
  WorkCpu *cpu = get();
  if (cpu == nullptr) {
    return;
  }
  if (!WorkRoot::isErrorStop()) {
    if (cpu->unknown1758 != -1 && (cpu->unknown1b0 & 0x2) == 0) {
      sync(cpu->unknown1758, WKCPU_SYNC_UNKNOWN_0, CPUID_UNKNOWN_0);
    }
    if (!WorkRoot::isErrorStop()) {
      DevGraph::cb(RCB_UNKNOWN_4);
      if (!WorkRoot::isErrorStop()) {
        for (mm::mtl::FixedList<AUTO_EXEC, 32>::iterator it = cpu->unknown17a0.begin(); it != cpu->unknown17a0.end(); ++it) {
          sync((*it).unknown00, WKCPU_SYNC_UNKNOWN_0, CPUID_UNKNOWN_0);
        }
      }
    }
  }
  bool isBusy;
  do {
    isBusy = false;
    for (u32 i = 0; i < get()->m_cpuNum; i++) {
      WorkCpuThread *thread = cpu->unknown1740[i];
      if (thread != nullptr && thread->getJobNum() != 0) {
        resumeThread();
        isBusy = true;
      }
    }
  } while (isBusy);
  DevClock::getClockNow(cpu->unknown2048[1]);
}

void WorkCpu::endFrame() {
  WorkCpu *cpu = get();
  if (cpu != nullptr && DevClock::get() != nullptr) {
    DevClock::getClockNow(cpu->unknown2048[2]);
    DevClock::getTimeNow(cpu->unknown2038, cpu->unknown2048[1]);
    DevClock::getTimeNow(cpu->unknown203c, cpu->unknown2048[0]);
    for (u32 i = 0; i < get()->m_cpuNum; i++) {
      WorkCpuThread *thread = cpu->unknown1740[i];
      if (thread != nullptr) {
        thread->calcPerformance(true);
      }
    }
    if (!WorkRoot::isErrorStop()) {
      if (WorkRootState::isThreadRender()) {
        swapBank();
      }
      if (!isShutdown() && !_mlwcpu::s_bStallRender) {
        DevGraph::renderSync();
      }
    }
    cpu->unknown1b0 &= ~0x20;
    get()->unknown1738 = get()->m_thread;
    DevClock::getClockNow(cpu->unknown2048[3]);
    DevGraph::cb(RCB_UNKNOWN_3);
    WorkControl::endFrame();
    DevClock::getTimeNow(cpu->unknown2034, cpu->unknown2048[0]);
    cpu->unknown2048[4] = cpu->unknown2048[0];
    cpu->m_tailStartClock = cpu->unknown2048[1];
    cpu->m_tailEndClock = cpu->unknown2048[2];
    cpu->m_syncClock = cpu->unknown2048[3];
    cpu->unknown195c++;
    cpu->unknown2090++;
    cpu->updateMessage();
    DevClock::getClockNow(_mlwcpu::s_aHearBeat[0]);
  }
}

void WorkCpu::entrySwap(IThreadValue *value) {
  CS lock(_mlwcpu::getSwapLock());
  WorkCpu *cpu = get();
  value->tvSwap();
  u32 index = 0;
  u32 minSize = 0xfffff;
  u32 cpuNum = get()->m_cpuNum;
  for (u32 i = 0; i < cpuNum; i++) {
    u32 size = cpu->unknown1c0[i].size();
    if (minSize > size) {
      index = i;
      minSize = size;
    }
  }
  value->setCpuBank(index);
  cpu->unknown1c0[index].push_back(value);
}

u32 WorkCpu::runThread(CPUID cpu, u32 (*function)(void *, void *), void *argument, void *userData, const mm::Col3 *color, bool isDebug, WKCPU_SYNC sync) {
  WorkCpu *instance = get();
  if (instance != nullptr && (instance->unknown1b0 & 0x2) != 0 && getRenderCPUID() == cpu) {
    return 0;
  }

  CPUID current = getCurrentCPUID();
  if (current != cpu) {
    int handle = createGroupHandle(1);
    entryJobThread(handle, function, 0, argument, userData, cpu, isDebug, true);
    if (current == CPUID_UNKNOWN_0) {
      if (color != nullptr) {
        attachJobCol(*color);
      }
      wakeup(handle);
      WorkCpu::sync(handle, sync, CPUID_UNKNOWN_0);
    } else {
      if (color != nullptr) {
        attachJobCol(*color);
      }
      wakeup(handle);
      WorkCpu::sync(handle, sync, cpu);
    }
    u32 result = getResult(handle);
    releaseGroupHandle(handle);
    return result;
  }

  return function(argument, userData);
}

void WorkCpu::setBackground(bool isBackground) {
  if (_mlwcpu::s_bBackGround != isBackground) {
    _mlwcpu::s_bBackGround = isBackground;
    WorkCpu *cpu = get();
    if (cpu != nullptr) {
      CS lock(_mlwcpu::getListenerLock());
      if (isBackground) {
        for (mm::mtl::FixedList<IWorkBackground *, 32>::iterator it = cpu->unknown1ba0.begin(); it != cpu->unknown1ba0.end(); ++it) {
          (*it)->bkgHomeMenu(true);
        }
      } else {
        for (mm::mtl::FixedList<IWorkBackground *, 32>::iterator it = cpu->unknown1ba0.begin(); it != cpu->unknown1ba0.end(); ++it) {
          (*it)->bkgHomeMenu(false);
        }
      }
    }
  }
}

WorkCpu *WorkCpu::create(WorkObj *parent) { return WorkUtil::createWork<WorkCpu>("WorkCpu", parent, false); }

template class reslist<IThreadValue *>;
template class reslist<TJOB *>;
template class fixed_size_alloc<TJOB>;

} // namespace ml

template mm::mtl::FixedList<ml::IWorkBackground *, 32>::iterator mm::mtl::FixedList<ml::IWorkBackground *, 32>::erase(mm::mtl::FixedList<ml::IWorkBackground *, 32>::iterator);

template mm::mtl::FixedList<ml::IWorkEvent *, 32>::iterator mm::mtl::FixedList<ml::IWorkEvent *, 32>::erase(mm::mtl::FixedList<ml::IWorkEvent *, 32>::iterator);

template mm::mtl::FixedList<ml::IWorkInfomation *, 32>::iterator mm::mtl::FixedList<ml::IWorkInfomation *, 32>::erase(mm::mtl::FixedList<ml::IWorkInfomation *, 32>::iterator);

template mm::mtl::FixedList<ml::IErrorCB *, 32>::iterator mm::mtl::FixedList<ml::IErrorCB *, 32>::erase(mm::mtl::FixedList<ml::IErrorCB *, 32>::iterator);

template mm::mtl::FixedList<ml::TJOB *, 64>::iterator mm::mtl::FixedList<ml::TJOB *, 64>::erase(mm::mtl::FixedList<ml::TJOB *, 64>::iterator);

template mm::mtl::FixedList<ml::WorkCpu::AUTO_EXEC, 32>::iterator mm::mtl::FixedList<ml::WorkCpu::AUTO_EXEC, 32>::erase(mm::mtl::FixedList<ml::WorkCpu::AUTO_EXEC, 32>::iterator);

namespace ml {

void WorkCpu::addShutdownForceListener(IWorkEvent *listener) {
  WorkCpu *cpu = get();
  if (cpu != nullptr) {
    CriticalSection &lock = _mlwcpu::getListenerLock();
    CriticalSection::enter(lock);
    cpu->unknown1960.push_back(listener);
    CriticalSection::leave(lock);
  }
}

void WorkCpu::addBackgroundListener(IWorkBackground *listener) {
  WorkCpu *cpu = get();
  if (cpu != nullptr) {
    CriticalSection &lock = _mlwcpu::getListenerLock();
    CriticalSection::enter(lock);
    cpu->unknown1ba0.push_back(listener);
    CriticalSection::leave(lock);
  }
}

void WorkCpu::addSystemInfoListener(IWorkInfomation *listener) {
  WorkCpu *cpu = get();
  if (cpu != nullptr) {
    CriticalSection &lock = _mlwcpu::getListenerLock();
    CriticalSection::enter(lock);
    cpu->unknown1de0.push_back(listener);
    CriticalSection::leave(lock);
  }
}

void WorkCpu::removeShutdownForceListener(IWorkEvent *listener) {
  WorkCpu *cpu = get();
  if (cpu != nullptr && (cpu->unknown1b0 & 2) == 0) {
    CriticalSection &lock = _mlwcpu::getListenerLock();
    CriticalSection::enter(lock);
    mm::mtl::FixedList<IWorkEvent *, 32>::iterator it = mm::mtl::find(cpu->unknown1960.begin(), cpu->unknown1960.end(), listener);
    if (it != cpu->unknown1960.end()) {
      cpu->unknown1960.erase(it);
    }
    CriticalSection::leave(lock);
  }
}

void WorkCpu::removeBackgroundListener(IWorkBackground *listener) {
  WorkCpu *cpu = get();
  if (cpu != nullptr && (cpu->unknown1b0 & 2) == 0) {
    CriticalSection &lock = _mlwcpu::getListenerLock();
    CriticalSection::enter(lock);
    mm::mtl::FixedList<IWorkBackground *, 32>::iterator it = mm::mtl::find(cpu->unknown1ba0.begin(), cpu->unknown1ba0.end(), listener);
    if (it != cpu->unknown1ba0.end()) {
      cpu->unknown1ba0.erase(it);
    }
    CriticalSection::leave(lock);
  }
}

void WorkCpu::removeSystemInfoListener(IWorkInfomation *listener) {
  WorkCpu *cpu = get();
  if (cpu != nullptr && (cpu->unknown1b0 & 2) == 0) {
    CriticalSection &lock = _mlwcpu::getListenerLock();
    CriticalSection::enter(lock);
    mm::mtl::FixedList<IWorkInfomation *, 32>::iterator it = mm::mtl::find(cpu->unknown1de0.begin(), cpu->unknown1de0.end(), listener);
    if (it != cpu->unknown1de0.end()) {
      cpu->unknown1de0.erase(it);
    }
    CriticalSection::leave(lock);
  }
}

bool WorkCpu::unregistErrorCB(IErrorCB *callback) {
  WorkCpu *cpu = get();
  if (callback == nullptr || cpu == nullptr) {
    return false;
  }

  CSNC lock(cpu->unknown22e0);
  mm::mtl::FixedList<IErrorCB *, 32>::iterator it = mm::mtl::find(cpu->unknown20a0.begin(), cpu->unknown20a0.end(), callback);
  if (it != cpu->unknown20a0.end()) {
    cpu->unknown20a0.erase(it);
  }

  return true;
}

} // namespace ml

template mm::mtl::PtrSingleton<ml::WorkCpu>::~PtrSingleton();
