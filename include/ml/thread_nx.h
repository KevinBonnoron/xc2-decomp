#pragma once
#include <stddef.h>

#include "ml/thread.h"
#include "ml/work_cpu.h"
#include "mm_thread/mm_thread_util.h"
#include "nn/os.h"
#include "types.h"

namespace ml {

class ThreadNx : public Thread {
public:
  enum State {
    STATE_RUNNING = 0,
    STATE_TERMINATED = 2,
  };

  static void create(Thread **thread, const char *name, bool isStart, ThreadFunc func, void *argument, u32 stackSize, CPUID cpuId, int priority);
  ThreadNx(Thread **thread, const char *name, bool isStart, ThreadFunc func, void *argument, u32 stackSize, CPUID cpuId, int priority);
  static void threadCallback(void *param);
  ~ThreadNx() override;
  bool isSuspended() const override;
  bool isTerminated() override;
  s32 exitThread() override;
  const char *getName() const override;
  void setSignalEvent(bool isSignal) override;
  bool waitSignalEvent() override;
  bool isWaitingEvent() const override;
  MLTHREAD *getHandle() const override;
  u64 getID() const override;
  CPUID getCPUID() const override;

  nn::os::ThreadType *m_handle;
  u64 m_ID;
  CPUID m_CPUID;
  nn::os::ThreadType unknown28;        // Inferred role: thread; original member name unknown.
  mm::threading::EventWait unknown1e8; // Inferred role: event; original member name unknown.
  void *unknown248;                    // Inferred role: stack; original member name unknown.
  void *unknown250;                    // Inferred role: argument; original member name unknown.
  ThreadFunc unknown258;               // Inferred role: func; original member name unknown.
  State unknown260;                    // Inferred role: state; original member name unknown.
};

static_assert(offsetof(ThreadNx, m_handle) == 0x10, "");
static_assert(offsetof(ThreadNx, m_CPUID) == 0x20, "");
static_assert(offsetof(ThreadNx, unknown28) == 0x28, "");
static_assert(offsetof(ThreadNx, unknown1e8) == 0x1e8, "");
static_assert(offsetof(ThreadNx, unknown248) == 0x248, "");
static_assert(offsetof(ThreadNx, unknown260) == 0x260, "");
static_assert(sizeof(ThreadNx) == 0x268, "");

} // namespace ml
