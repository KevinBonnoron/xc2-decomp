#pragma once
#include <stddef.h>

#include "mm_thread/mm_thread_util.h"
#include "types.h"

namespace mm {
namespace mtl {
class IAllocator;
} // namespace mtl
namespace threading {
class Thread;
} // namespace threading
} // namespace mm

namespace anm {

class JobQueue;

struct TreadPoolInfo {
  u32 unknown00; // Inferred role: worker thread mask; original member name unknown.
  u32 unknown04; // Inferred role: thread priority; original member name unknown.
  u32 unknown08; // Inferred role: max jobs per pass; original member name unknown.
};

static_assert(sizeof(TreadPoolInfo) == 0x0c, "");

class ThreadPool {
public:
  ThreadPool(const TreadPoolInfo &info, mm::mtl::IAllocator &allocator);
  virtual ~ThreadPool();
  virtual void processAllJob(JobQueue &queue);
  virtual void waitForCompletion();
  virtual void initialize(const TreadPoolInfo &info, mm::mtl::IAllocator &allocator);
  virtual void finalize();
  static u32 threadFunc(void *argument);

  mm::threading::Thread *unknown08[3];    // Inferred role: worker threads; original member name unknown.
  mm::threading::EventWait unknown20[3];  // Inferred role: wake events of the workers; original member name unknown.
  mm::threading::SpinLock unknown140;     // Inferred role: queue lock; original member name unknown.
  s32 unknown144;                         // Inferred role: state (0 created, 1 running, 2 finalizing); original member name unknown.
  mm::threading::EventWait unknown148[3]; // Inferred role: done events of the workers; original member name unknown.
  TreadPoolInfo unknown268;               // Inferred role: info; original member name unknown.
  JobQueue *m_pJobQueue;
};

static_assert(offsetof(ThreadPool, unknown20) == 0x20, "");
static_assert(offsetof(ThreadPool, unknown140) == 0x140, "");
static_assert(offsetof(ThreadPool, unknown148) == 0x148, "");
static_assert(offsetof(ThreadPool, unknown268) == 0x268, "");
static_assert(offsetof(ThreadPool, m_pJobQueue) == 0x278, "");
static_assert(sizeof(ThreadPool) == 0x280, "");

} // namespace anm
