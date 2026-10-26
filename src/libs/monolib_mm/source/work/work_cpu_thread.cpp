#include "ml/work_cpu_thread.h"

#include "ml/critical_section.h"
#include "ml/dev_clock.h"
#include "ml/dev_graph.h"
#include "ml/thread.h"
#include "mm_math/mm_col3.h"

namespace ml {

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
  return unknown648;
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

void WorkCpuThread::wkTail() {
  const mm::Col3 &color = mm::Col3::yellow;
  unknown658 = static_cast<u32>(color.r * 255.0f) | static_cast<u32>(color.g * 255.0f) << 8 | static_cast<u32>(color.b * 255.0f) << 16 | 0xff000000;
}

bool WorkCpuThread::wkStandbyLogin() { return WorkObj::wkStandbyLogin(); }

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
