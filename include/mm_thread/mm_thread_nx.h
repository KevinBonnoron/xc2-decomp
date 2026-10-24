#pragma once
#include <stddef.h>

#include "mm_thread/mm_thread.h"
#include "mm_thread/mm_thread_util.h"
#include "nn/os.h"
#include "types.h"

namespace mm {
namespace mtl {
class IAllocator;
} // namespace mtl

namespace threading {

enum ThreadState {
  THREAD_STATE_RUNNING = 0,
  THREAD_STATE_TERMINATED = 2,
};

class ThreadNx : public Thread {
public:
  ThreadNx(mtl::IAllocator *pAllocator, const char *name, ThreadFunc func, void *argument, u32 stackSize, CPUID cpuId, s32 threadPriority);
  static void threadCallback(void *param);
  ~ThreadNx() override;
  bool isSuspended() const override;
  bool isTerminated() override;
  s32 exitThread() override;
  const char *getName() const override;
  void setSignalEvent(bool signal) override;
  bool waitSignalEvent() override;
  bool isWaitingEvent() const override;
  static Thread *create(mtl::IAllocator *pAllocator, const char *name, ThreadFunc func, void *argument, u32 stackSize, CPUID cpuId, s32 threadPriority);
  MMTHREAD *getHandle() const override;
  u64 getID() const override;
  CPUID getCPUID() const override;

  nn::os::ThreadType *handle;
  u64 id;
  CPUID cpuId;
  nn::os::ThreadType thread;
  EventWait event;
  void *stack;
  void *argument;
  ThreadFunc func;
  ThreadState state;
};

static_assert(offsetof(ThreadNx, handle) == 0x18, "");
static_assert(offsetof(ThreadNx, cpuId) == 0x28, "");
static_assert(offsetof(ThreadNx, thread) == 0x30, "");
static_assert(offsetof(ThreadNx, event) == 0x1f0, "");
static_assert(offsetof(ThreadNx, stack) == 0x250, "");
static_assert(offsetof(ThreadNx, state) == 0x268, "");
static_assert(sizeof(ThreadNx) == 0x270, "");

} // namespace threading
} // namespace mm
