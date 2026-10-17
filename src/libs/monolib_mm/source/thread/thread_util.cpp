#include "ml/thread_util.h"

namespace ml {

u64 ThreadUtil::getCurrentID() { return reinterpret_cast<u64>(nn::os::GetCurrentThread()); }

s32 ThreadUtil::suspendThread(MLTHREAD *thread) { return 0; }

void ThreadUtil::resumeThread(MLTHREAD *thread) { nn::os::StartThread(thread); }

s32 ThreadUtil::getCpuNum() { return 3; }

u32 ThreadUtil::getCpuMask() { return nn::os::GetThreadAvailableCoreMask(); }

void ThreadUtil::setCpuThread(MLTHREAD *thread, CPUID cpuId) {
  if (cpuId == CPUID_ANY) {
    return;
  }
  s32 coreID = convertCoreID(cpuId);
  nn::os::SetThreadCoreMask(thread, coreID, 1UL << coreID);
}

s32 ThreadUtil::convertCoreID(CPUID cpuId) { return cpuId > CPUID_ANY ? cpuId - 1 : -1; }

u64 ThreadUtil::getID(MLTHREAD *thread) { return reinterpret_cast<u64>(thread); }

const char *ThreadUtil::getThreadName(u64 id) { return nn::os::GetThreadNamePointer(reinterpret_cast<nn::os::ThreadType *>(id)); }

CPUID ThreadUtil::getCurrentCPUID() { return static_cast<CPUID>(nn::os::GetCurrentCoreNumber() + 1); }

MLTHREAD *ThreadUtil::getCurrentHandle() { return static_cast<MLTHREAD *>(nn::os::GetCurrentThread()); }

} // namespace ml
