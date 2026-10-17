#include "ml/work_cpu.h"

#include "ml/dev_clock.h"
#include "ml/thread_util.h"
#include "ml/work_cpu_thread.h"

namespace ml {

namespace _mlwcpu {

bool s_bEnableLib;
bool s_bEShop;
bool s_bStallRender;
long s_aHearBeat[3];
s32 s_cpuStall;
bool s_bBackGround;

} // namespace _mlwcpu

bool WorkCpu::s_bRenderSubCpu;

bool WorkCpu::isInitialized() {
  WorkCpu *cpu = get();
  if (cpu == nullptr) {
    return false;
  }

  for (u32 i = 0; i < cpu->m_cpuNum; i++) {
    WorkCpuThread *thread = cpu->m_cpuThreads[i];
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
    return cpu->m_mainThreadId;
  }

  return 0;
}

bool WorkCpu::checkTermThread() { return true; }

void WorkCpu::setProfiler(bool isProfiler) {}

f32 WorkCpu::getAllCostSec() {
  WorkCpu *cpu = get();
  if (cpu != nullptr) {
    return cpu->m_allCostSec;
  }

  return 0.0f;
}

void WorkCpu::setRenderSubCpu(bool isRenderSubCpu) { s_bRenderSubCpu = isRenderSubCpu; }

mtl::ALLOC_HANDLE WorkCpu::getMemWork() {
  WorkCpu *cpu = get();
  if (cpu != nullptr) {
    return cpu->m_memWork;
  }

  return mtl::ALLOC_HANDLE();
}

mtl::ALLOC_HANDLE WorkCpu::getMemStack() {
  WorkCpu *cpu = get();
  if (cpu != nullptr) {
    return cpu->m_memStack;
  }

  return mtl::ALLOC_HANDLE();
}

CPUID WorkCpu::getMainCPUID() { return CPUID_CORE_0; }

CPUID WorkCpu::getRenderCPUID() {
  if (s_bRenderSubCpu) {
    u32 cpuNum = get()->m_cpuNum;
    if (cpuNum > 2) {
      return CPUID_CORE_2;
    }

    if (cpuNum == 2) {
      return CPUID_CORE_1;
    }
  }

  return CPUID_CORE_0;
}

u32 WorkCpu::getCpuNum() { return get()->m_cpuNum; }

void WorkCpu::setThread(DO_THREAD thread) { get()->m_nextThread = thread; }

DO_THREAD WorkCpu::getThread() {
  WorkCpu *cpu = get();
  if (cpu != nullptr) {
    return cpu->m_thread;
  }

  return static_cast<DO_THREAD>(0);
}

u32 WorkCpu::getEven() { return get()->m_even; }

bool WorkCpu::isShutdown() {
  WorkCpu *cpu = get();
  if (cpu != nullptr) {
    return (cpu->m_flags & 0x2) != 0;
  }

  return false;
}

u32 WorkCpu::getFrameCountU32() { return get()->m_frameCount; }

const unsigned long &WorkCpu::getFrameCount() { return get()->m_frameCount; }

bool WorkCpu::getOdd() { return get()->m_even == 0; }

bool WorkCpu::isBackground() { return _mlwcpu::s_bBackGround; }

void WorkCpu::syncSubCpu() {}

void WorkCpu::setHeartBeatCpu(CPUID cpu) { DevClock::getClockNow(_mlwcpu::s_aHearBeat[cpu - 1]); }

u32 WorkCpu::getJobTrans() { return get()->m_jobTrans[getOdd()]; }

const long &WorkCpu::getBeginClock(bool isCurrent) {
  WorkCpu *cpu = get();
  int index = isCurrent ? 0 : 4;
  return cpu->m_beginClocks[index];
}

const long &WorkCpu::getTailStartClock() { return get()->m_tailStartClock; }

const long &WorkCpu::getTailEndClock() { return get()->m_tailEndClock; }

const long &WorkCpu::getSyncClock() { return get()->m_syncClock; }

u32 WorkCpu::getCounter() {
  WorkCpu *cpu = get();
  if (cpu != nullptr) {
    return cpu->m_counter;
  }

  return 0;
}

void WorkCpu::gotoBackground() {}

void WorkCpu::gotoForeground() {}

void WorkCpu::backgroundProcess() {}

void WorkCpu::backgroundProcess(CPUID cpu) {}

u32 WorkCpu::thForeground(void *argument, void *userData) { return 0; }

u32 WorkCpu::thBackground(void *argument, void *userData) { return 0; }

void WorkCpu::setAfterUpdateRender(bool isAfterUpdateRender) {
  WorkCpu *cpu = get();
  if (cpu != nullptr) {
    if (isAfterUpdateRender) {
      cpu->m_flags |= 0x10;
    } else {
      cpu->m_flags &= ~0x10;
    }
  }
}

bool WorkCpu::isHomeMenuEnable() { return true; }

s32 WorkCpu::getHeartBeatStall() { return _mlwcpu::s_cpuStall; }

void WorkCpu::clrHeartBeatStall() { _mlwcpu::s_cpuStall = 0; }

} // namespace ml
