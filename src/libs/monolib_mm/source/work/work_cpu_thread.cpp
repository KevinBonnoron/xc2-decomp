#include "ml/work_cpu_thread.h"

#include "ml/critical_section.h"
#include "ml/dev_clock.h"
#include "ml/dev_graph.h"
#include "ml/reslist.h"
#include "ml/thread.h"
#include "ml/thread_util.h"
#include "ml/work_control.h"
#include "ml/work_root.h"
#include "mm_math/mm_col3.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/reference_object.h"
#include "mtl/alloc_handle.h"

namespace ml {

WorkCpuThread::WorkCpuThread(const char *name, WorkObj *parent)
    : WorkObj(name, parent, 0), m_CPUID(CPUID_CORE_0), m_threadID(0), unknown1b8(nullptr), unknown1c0(0), unknown1c4(0), m_aboutJobNumC(0), unknown1d0(0), unknown1d8(0), unknown1e0(0.0f),
      unknown1e4(0.0f), unknown1e8(nullptr), unknown650(nullptr), unknown658(WorkCpu::unknown001(mm::Col3::yellow)), unknown660(0), unknown668(0), m_background(false), unknown671(false),
      m_beginTerm(false) {
  unknown1e8 = new (WorkRootState::getWorkMem()) CriticalSection();
  unknown1e8->setCostIgnore(true);
}

WorkCpuThread::~WorkCpuThread() {
  if (unknown1e8 != nullptr) {
    delete unknown1e8;
    unknown1e8 = nullptr;
  }
}

bool WorkCpuThread::isSuspendThread() const {
  if (unknown1b8 == nullptr) {
    return true;
  }
  return unknown1b8->isSuspended();
}

bool WorkCpuThread::isWaitEvent() const {
  if (unknown1b8 != nullptr) {
    return unknown1b8->isWaitingEvent();
  }
  return false;
}

MLTHREAD *WorkCpuThread::getHandle() const { return unknown1b8->getHandle(); }

CPUID WorkCpuThread::getCPUID() const { return m_CPUID; }

void WorkCpuThread::getStackInfo(unsigned long &address, unsigned long &size) {
  address = unknown660;
  size = unknown668;
}

u64 WorkCpuThread::getThreadID() const { return m_threadID; }

f32 WorkCpuThread::getJobCost() const { return unknown1e4 / DevGraph::getFrameSyncSec() * 100.0f; }

int WorkCpuThread::getJobNum() const {
  CS cs(*unknown1e8);
  return unknown1f0.size();
}

void WorkCpuThread::setEvent(bool isSignal) {
  if (unknown1b8 != nullptr) {
    unknown1b8->setSignalEvent(isSignal);
  }
}

u32 WorkCpuThread::updateDirect(bool isDirect) {
  unknown671 = isDirect;
  threadFunc(this);
  unknown671 = false;
  return 0;
}

bool WorkCpuThread::hasWorkingJob() const {
  CS cs(*unknown1e8);
  return unknown650 != nullptr;
}

bool WorkCpuThread::isBusyJob(int handle) const {
  CS cs(*unknown1e8);
  if (unknown650 != nullptr && unknown650->unknown24 == handle) {
    return true;
  }
  for (mm::mtl::FixedList<TJOB *, 64>::const_iterator it = unknown1f0.begin(); it != unknown1f0.end(); ++it) {
    if ((*it)->unknown24 == handle) {
      return true;
    }
  }
  return false;
}

bool WorkCpuThread::addJobThread(TJOB *job) {
  CS cs(*unknown1e8);
  unknown1c4++;
  if (job->unknown30 == 0) {
    m_aboutJobNumC++;
  }
  unknown1f0.push_back(job);
  return true;
}

TJOB *WorkCpuThread::transferJob(WorkCpuThread *destination) {
  CS cs(*unknown1e8);
  if (unknown1f0.size() != 0) {
    for (mm::mtl::FixedList<TJOB *, 64>::iterator it = unknown1f0.begin(); it != unknown1f0.end(); ++it) {
      TJOB *job = *it;
      if (job->unknown30 == 0) {
        destination->setWorkingJob(job);
        unknown1f0.erase(it);
        unknown1c4--;
        m_aboutJobNumC--;
        return job;
      }
    }
  }
  return nullptr;
}

bool WorkCpuThread::getJobThread(TJOB *&job, bool isBackground) {
  job = nullptr;
  if (unknown1c4 == 0) {
    return false;
  }
  CS cs(*unknown1e8);
  if (unknown1f0.size() == 0) {
    return false;
  }
  if (isBackground) {
    for (mm::mtl::FixedList<TJOB *, 64>::iterator it = unknown1f0.begin(); it != unknown1f0.end(); ++it) {
      if ((*it)->unknown3c) {
        unknown650 = *it;
        job = *it;
        unknown1f0.erase(it);
        break;
      }
    }
    if (job == nullptr) {
      return false;
    }
  } else {
    unknown650 = unknown1f0.front();
    job = unknown1f0.front();
    unknown1f0.pop_front();
  }
  unknown1c4--;
  if (job->unknown30 == 0) {
    m_aboutJobNumC--;
  }
  return true;
}

u32 WorkCpuThread::getAboutJobNumC() const { return m_aboutJobNumC; }

void WorkCpuThread::beginUpdate() {
  unknown1e0 = 0.0f;
  DevClock::getClockNow(unknown1d0);
  unknown1d8 = unknown1d0;
}

void WorkCpuThread::calcPerformance(bool isCalc) {
  if (isCalc) {
    if (m_CPUID == CPUID_CORE_0) {
      long clock = unknown1d8 - unknown1d0;
      unknown1e4 = DevClock::getClock2Sec(clock);
    } else {
      unknown1e4 = unknown1e0;
    }
  }
}

void WorkCpuThread::changeFrame() {}

bool WorkCpuThread::isStackOverFlow() const { return false; }

bool WorkCpuThread::isBeginTerm() const { return m_beginTerm; }

void WorkCpuThread::addJobClock(f32 clock) {
  unknown1e0 += clock;
  DevClock::getClockNow(unknown1d8);
}

void WorkCpuThread::terminateWorkingJob(const TJOB *job) {
  CS cs(*unknown1e8);
  unknown650 = nullptr;
}

void WorkCpuThread::waitEvent() {
  if (unknown1b8 != nullptr) {
    unknown1b8->waitSignalEvent();
  }
}

void WorkCpuThread::setWorkingJob(TJOB *job) {
  CS cs(*unknown1e8);
  unknown650 = job;
}

void WorkCpuThread::setup(CPUID cpuId) {
  m_CPUID = cpuId;
  if (cpuId == CPUID_CORE_0) {
    m_threadID = ThreadUtil::getCurrentID();
    return;
  }
  Thread::create(&unknown1b8, unknown08.c_str(), false, threadFunc, this, 0x40000, cpuId, 0);
  m_threadID = unknown1b8->getID();
  unknown1b8->resume();
}

void WorkCpuThread::setBackground(bool isBackground) { m_background = isBackground; }

bool WorkCpuThread::isBackground() const { return m_background; }

void WorkCpuThread::setStackInfo(unsigned long address, unsigned long size, void *stack) {
  unknown660 = address;
  unknown668 = size;
}

void WorkCpuThread::suspendThread() {
  if (unknown1b8 != nullptr) {
    unknown1b8->suspend();
  }
}

void WorkCpuThread::resumeThread() {
  if (unknown1b8 != nullptr) {
    unknown1b8->resume();
  }
}

void WorkCpuThread::wkTail() { unknown658 = WorkCpu::unknown001(mm::Col3::yellow); }

bool WorkCpuThread::wkStandbyLogin() { return WorkObj::wkStandbyLogin(); }

bool WorkCpuThread::wkStandbyLogout() {
  if (unknown60.size() != 0 || WorkControl::get() != nullptr) {
    return false;
  }
  if (unknown1c0 == 0) {
    m_beginTerm = true;
    setEvent(true);
    unknown1c0++;
  } else if (unknown1c0 != 1) {
    return false;
  }
  if (unknown1b8 != nullptr) {
    if (!unknown1b8->isTerminated()) {
      return false;
    }
    mm::mtl::safeRelease(unknown1b8);
  }
  unknown1c0++;
  WorkCpu::removeCpu(m_CPUID, this);
  return WorkObj::wkStandbyLogout();
}

void WorkCpuThread::termThread() { m_beginTerm = true; }

bool WorkCpuThread::isTermThread() {
  if (unknown1b8 == nullptr) {
    return true;
  }
  return unknown1b8->isTerminated();
}

void WorkCpuThread::exitThread() {
  if (unknown1b8 != nullptr) {
    unknown1b8->exitThread();
  }
}

} // namespace ml
