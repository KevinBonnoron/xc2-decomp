#include "ml/work_cpu.h"

#include "ml/critical_section.h"
#include "ml/dev_clock.h"
#include "ml/thread_util.h"
#include "ml/work_cpu_thread.h"

namespace ml {

WorkCpuThread *WorkCpu::getCpuThread(CPUID cpuId) {
  WorkCpu *cpu = get();
  u32 index = cpuId - CPUID_CORE_0;
  return cpu->unknown1740[index];
}

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

  for (u32 i = 0; i < cpu->unknown1bc; i++) {
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

CPUID WorkCpu::getMainCPUID() { return CPUID_CORE_0; }

CPUID WorkCpu::getRenderCPUID() {
  if (s_bRenderSubCpu) {
    u32 cpuNum = get()->unknown1bc;
    if (cpuNum > 2) {
      return CPUID_CORE_2;
    }

    if (cpuNum == 2) {
      return CPUID_CORE_1;
    }
  }

  return CPUID_CORE_0;
}

u32 WorkCpu::getCpuNum() { return get()->unknown1bc; }

void WorkCpu::setThread(DO_THREAD thread) { get()->unknown173c = thread; }

DO_THREAD WorkCpu::getThread() {
  WorkCpu *cpu = get();
  if (cpu != nullptr) {
    return cpu->unknown1738;
  }

  return static_cast<DO_THREAD>(0);
}

u32 WorkCpu::getEven() { return get()->unknown1764; }

bool WorkCpu::isShutdown() {
  WorkCpu *cpu = get();
  if (cpu != nullptr) {
    return (cpu->unknown1b0 & 0x2) != 0;
  }

  return false;
}

u32 WorkCpu::getFrameCountU32() { return get()->unknown2090; }

const unsigned long &WorkCpu::getFrameCount() { return get()->unknown2090; }

bool WorkCpu::getOdd() { return get()->unknown1764 == 0; }

bool WorkCpu::isBackground() { return _mlwcpu::s_bBackGround; }

void WorkCpu::syncSubCpu() {}

void WorkCpu::setHeartBeatCpu(CPUID cpu) { DevClock::getClockNow(_mlwcpu::s_aHearBeat[cpu - 1]); }

u32 WorkCpu::getJobTrans() { return get()->unknown2028[getOdd()]; }

const long &WorkCpu::getBeginClock(bool isCurrent) {
  WorkCpu *cpu = get();
  int index = isCurrent ? 0 : 4;
  return cpu->unknown2048[index];
}

const long &WorkCpu::getTailStartClock() { return get()->unknown2070; }

const long &WorkCpu::getTailEndClock() { return get()->unknown2078; }

const long &WorkCpu::getSyncClock() { return get()->unknown2080; }

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

bool WorkCpu::isHomeMenuEnable() { return true; }

int WorkCpu::reqHomeMenuDisable() { return 9999; }

int WorkCpu::reqImm(bool isEnable) { return 9999; }

void WorkCpu::removeHomeMenuDisable(DEFHBM *&handle) {}

void WorkCpu::removeImm(DEFIMM *&handle) {}

s32 WorkCpu::getHeartBeatStall() { return _mlwcpu::s_cpuStall; }

void WorkCpu::clrHeartBeatStall() { _mlwcpu::s_cpuStall = 0; }

} // namespace ml
