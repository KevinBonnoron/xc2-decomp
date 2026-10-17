#pragma once
#include "ml/work_cpu.h"
#include "nn/os.h"
#include "types.h"

namespace ml {

struct MLTHREAD : nn::os::ThreadType {};

class ThreadUtil {
public:
  static u64 getCurrentID();
  static s32 suspendThread(MLTHREAD *thread);
  static void resumeThread(MLTHREAD *thread);
  static s32 getCpuNum();
  static u32 getCpuMask();
  static void setCpuThread(MLTHREAD *thread, CPUID cpuId);
  static s32 convertCoreID(CPUID cpuId);
  static u64 getID(MLTHREAD *thread);
  static const char *getThreadName(u64 id);
  static CPUID getCurrentCPUID();
  static MLTHREAD *getCurrentHandle();
};

} // namespace ml
