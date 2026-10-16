#include "mm_thread/mm_thread_util.h"

#include "mm/mm_std_base.h"
#include "nn/time_span.h"

namespace mm {
namespace threading {

s32 ThreadUtil::getCpuNum() { return 3; }

u32 ThreadUtil::getCpuMask() { return nn::os::GetThreadAvailableCoreMask(); }

void ThreadUtil::setCpuThread(MMTHREAD *thread, CPUID cpuId) {
  if (cpuId == CPUID_ANY) {
    return;
  }

  s32 coreID = convertCoreID(cpuId);
  MM_ASSERT(coreID >= 0);
  MM_ASSERT((1U << coreID) & ThreadUtil::getCpuMask());
  nn::os::SetThreadCoreMask(thread, coreID, 1UL << coreID);
}

s32 ThreadUtil::convertCoreID(CPUID cpuId) { return cpuId > CPUID_ANY ? cpuId - 1 : -1; }

u64 ThreadUtil::getID(MMTHREAD *thread) { return reinterpret_cast<u64>(thread); }

const char *ThreadUtil::getThreadName(u64 id) { return nn::os::GetThreadNamePointer(reinterpret_cast<nn::os::ThreadType *>(id)); }

s32 ThreadUtil::suspendThread(MMTHREAD *thread) {
  MM_ASSERT(false && "can't implement!!");
  return 0;
}

void ThreadUtil::resumeThread(MMTHREAD *thread) { nn::os::StartThread(thread); }

CPUID ThreadUtil::getCurrentCPUID() { return static_cast<CPUID>(nn::os::GetCurrentCoreNumber() + 1); }

u64 ThreadUtil::getCurrentID() { return reinterpret_cast<u64>(nn::os::GetCurrentThread()); }

MMTHREAD *ThreadUtil::getCurrentHandle() { return static_cast<MMTHREAD *>(nn::os::GetCurrentThread()); }

EventWait::EventWait(bool manualClear, bool initiallySignaled) {
  CS lock(sect);
  nn::os::InitializeEvent(&event, initiallySignaled, manualClear ? nn::os::EventClearMode_ManualClear : nn::os::EventClearMode_AutoClear);
  initialized = true;
}

EventWait::~EventWait() { finalize(); }

void EventWait::finalize() {
  if (initialized) {
    nn::os::FinalizeEvent(&event);
    initialized = false;
  }
}

void EventWait::setSignal(bool signal) {
  if (signal) {
    nn::os::SignalEvent(&event);
  } else {
    CS lock(sect);
    nn::os::ClearEvent(&event);
  }
}

bool EventWait::waitSignal(u32 milliSeconds) {
  if (milliSeconds != 0) {
    nn::TimeSpan timeout = nn::TimeSpan::FromMilliSeconds(milliSeconds);
    return nn::os::TimedWaitEvent(&event, timeout);
  }

  nn::os::WaitEvent(&event);
  return true;
}

bool EventWait::isSignal() const { return nn::os::TimedWaitEvent(const_cast<nn::os::EventType *>(&event), nn::TimeSpan::FromNanoSeconds(0)); }

SpinLock::SpinLock() : locked(0) {}

} // namespace threading
} // namespace mm
