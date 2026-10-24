#pragma once
#include <stddef.h>

#include "ml/work_cpu.h"
#include "types.h"

namespace ml {

struct MLTHREAD;

typedef u32 (*ThreadFunc)(void *argument);

class Thread {
public:
  Thread();
  virtual ~Thread();
  s32 suspend();
  void resume();
  static Thread *create(const char *name, bool isStart, ThreadFunc func, void *argument, u32 stackSize, CPUID cpuId, int priority);
  static bool create(Thread **thread, const char *name, bool isStart, ThreadFunc func, void *argument, u32 stackSize, CPUID cpuId, int priority);

  virtual bool isSuspended() const = 0;
  virtual bool isTerminated() = 0;
  virtual s32 exitThread() = 0;
  virtual MLTHREAD *getHandle() const = 0;
  virtual u64 getID() const = 0;
  virtual CPUID getCPUID() const = 0;
  virtual const char *getName() const = 0;
  virtual void setSignalEvent(bool isSignal) = 0;
  virtual bool waitSignalEvent() = 0;
  virtual bool isWaitingEvent() const = 0;

  s32 unknown08; // Inferred role: ref count; original member name unknown.
};

static_assert(offsetof(Thread, unknown08) == 0x08, "");

} // namespace ml
