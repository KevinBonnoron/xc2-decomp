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

// Inferred role: thread state; original type name unknown.
enum unknown130 {
  unknown130_0 = 0, // Inferred role: running; original name unknown.
  unknown130_2 = 2, // Inferred role: terminated; original name unknown.
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

  nn::os::ThreadType *m_handle;
  u64 m_ID;
  CPUID m_CPUID;
  nn::os::ThreadType unknown30; // Inferred role: thread; original member name unknown.
  EventWait unknown1f0;         // Inferred role: event; original member name unknown.
  void *unknown250;             // Inferred role: stack; original member name unknown.
  void *unknown258;             // Inferred role: argument; original member name unknown.
  ThreadFunc unknown260;        // Inferred role: func; original member name unknown.
  unknown130 unknown268;        // Inferred role: state; original member name unknown.
};

static_assert(offsetof(ThreadNx, m_handle) == 0x18, "");
static_assert(offsetof(ThreadNx, m_CPUID) == 0x28, "");
static_assert(offsetof(ThreadNx, unknown30) == 0x30, "");
static_assert(offsetof(ThreadNx, unknown1f0) == 0x1f0, "");
static_assert(offsetof(ThreadNx, unknown250) == 0x250, "");
static_assert(offsetof(ThreadNx, unknown268) == 0x268, "");
static_assert(sizeof(ThreadNx) == 0x270, "");

} // namespace threading
} // namespace mm
