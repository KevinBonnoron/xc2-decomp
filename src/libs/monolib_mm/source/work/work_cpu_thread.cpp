#include "ml/work_cpu_thread.h"

#include "ml/critical_section.h"
#include "ml/dev_clock.h"
#include "ml/dev_graph.h"
#include "ml/thread.h"
#include "mm_math/mm_col3.h"

namespace ml {

bool WorkCpuThread::isSuspendThread() const {
  if (m_thread == nullptr) {
    return true;
  }
  return m_thread->isSuspended();
}

CPUID WorkCpuThread::getCPUID() const { return m_cpuId; }

void WorkCpuThread::getStackInfo(unsigned long &address, unsigned long &size) {
  address = m_stackAddress;
  size = m_stackSize;
}

u64 WorkCpuThread::getThreadID() const { return m_threadId; }

f32 WorkCpuThread::getJobCost() const { return m_jobCost / DevGraph::getFrameSyncSec() * 100.0f; }

int WorkCpuThread::getJobNum() const {
  CS cs(*m_cs);
  return m_jobNum;
}

void WorkCpuThread::setEvent(bool isSignal) {
  if (m_thread != nullptr) {
    m_thread->setSignalEvent(isSignal);
  }
}

u32 WorkCpuThread::updateDirect(bool isDirect) {
  m_isDirect = isDirect;
  threadFunc(this);
  m_isDirect = false;
  return 0;
}

bool WorkCpuThread::hasWorkingJob() const {
  CS cs(*m_cs);
  return m_workingJob != nullptr;
}

u32 WorkCpuThread::getAboutJobNumC() const { return m_aboutJobNumC; }

void WorkCpuThread::beginUpdate() {
  m_jobClock = 0.0f;
  DevClock::getClockNow(m_beginClock);
  m_endClock = m_beginClock;
}

void WorkCpuThread::calcPerformance(bool isCalc) {
  if (isCalc) {
    if (m_cpuId == CPUID_CORE_0) {
      long clock = m_endClock - m_beginClock;
      m_jobCost = DevClock::getClock2Sec(clock);
    } else {
      m_jobCost = m_jobClock;
    }
  }
}

void WorkCpuThread::changeFrame() {}

bool WorkCpuThread::isStackOverFlow() const { return false; }

bool WorkCpuThread::isBeginTerm() const { return m_isBeginTerm; }

void WorkCpuThread::addJobClock(f32 clock) {
  m_jobClock += clock;
  DevClock::getClockNow(m_endClock);
}

void WorkCpuThread::terminateWorkingJob(const TJOB *job) {
  CS cs(*m_cs);
  m_workingJob = nullptr;
}

void WorkCpuThread::waitEvent() {
  if (m_thread != nullptr) {
    m_thread->waitSignalEvent();
  }
}

void WorkCpuThread::setWorkingJob(TJOB *job) {
  CS cs(*m_cs);
  m_workingJob = job;
}

void WorkCpuThread::setBackground(bool isBackground) { m_isBackground = isBackground; }

bool WorkCpuThread::isBackground() const { return m_isBackground; }

void WorkCpuThread::setStackInfo(unsigned long address, unsigned long size, void *stack) {
  m_stackAddress = address;
  m_stackSize = size;
}

void WorkCpuThread::suspendThread() {
  if (m_thread != nullptr) {
    m_thread->suspend();
  }
}

void WorkCpuThread::resumeThread() {
  if (m_thread != nullptr) {
    m_thread->resume();
  }
}

void WorkCpuThread::wkTail() {
  const mm::Col3 &color = mm::Col3::yellow;
  m_color = static_cast<u32>(color.r * 255.0f) | static_cast<u32>(color.g * 255.0f) << 8 | static_cast<u32>(color.b * 255.0f) << 16 | 0xff000000;
}

bool WorkCpuThread::wkStandbyLogin() { return WorkObj::wkStandbyLogin(); }

void WorkCpuThread::termThread() { m_isBeginTerm = true; }

bool WorkCpuThread::isTermThread() {
  if (m_thread == nullptr) {
    return true;
  }
  return m_thread->isTerminated();
}

void WorkCpuThread::exitThread() {
  if (m_thread != nullptr) {
    m_thread->exitThread();
  }
}

} // namespace ml
