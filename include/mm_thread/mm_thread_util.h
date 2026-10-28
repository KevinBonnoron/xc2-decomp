#pragma once
#include <stddef.h>

#include "mm_thread/mm_thread_csection.h"
#include "nn/os.h"
#include "types.h"

namespace mm {
namespace threading {

struct MMTHREAD : nn::os::ThreadType {};

enum CPUID {
  CPUID_ANY,
  CPUID_CORE_0,
  CPUID_CORE_1,
  CPUID_CORE_2,
};

class ThreadUtil {
public:
  static s32 getCpuNum();
  static u32 getCpuMask();
  static void setCpuThread(MMTHREAD *thread, CPUID cpuId);
  static s32 convertCoreID(CPUID cpuId);
  static u64 getID(MMTHREAD *thread);
  static const char *getThreadName(u64 id);
  static s32 suspendThread(MMTHREAD *thread);
  static void resumeThread(MMTHREAD *thread);
  static CPUID getCurrentCPUID();
  static u64 getCurrentID();
  static MMTHREAD *getCurrentHandle();
};

class EventWait {
public:
  EventWait(bool manualClear, bool initiallySignaled);
  virtual ~EventWait();
  void finalize();
  void setSignal(bool signal);
  bool waitSignal(u32 milliSeconds);
  bool isSignal() const;

  nn::os::EventType unknown08; // Inferred role: event; original member name unknown.
  CriticalSection unknown30;   // Inferred role: sect; original member name unknown.
  bool unknown58;              // Inferred role: initialized; original member name unknown.
};

static_assert(offsetof(EventWait, unknown08) == 0x08, "");
static_assert(offsetof(EventWait, unknown30) == 0x30, "");
static_assert(offsetof(EventWait, unknown58) == 0x58, "");

class SpinLock {
public:
  SpinLock();
  void lock(f32 timeout);
  void unlock() { __atomic_store_n(&locked, 0, __ATOMIC_RELEASE); }

  s32 locked;
};

} // namespace threading
} // namespace mm
