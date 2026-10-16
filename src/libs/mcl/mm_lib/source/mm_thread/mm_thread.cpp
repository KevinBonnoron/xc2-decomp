#include "mm_thread/mm_thread.h"

#include "mm/mm_std_base.h"
#include "mm_thread/mm_thread_nx.h"

namespace mm {
namespace threading {

Thread::Thread(mtl::IAllocator *allocator) : ReferenceObject(allocator) {}

Thread::~Thread() { MM_ASSERT(getRefCount() == 0); }

s32 Thread::suspend() { return ThreadUtil::suspendThread(getHandle()); }

void Thread::resume() { ThreadUtil::resumeThread(getHandle()); }

Thread *Thread::create(mtl::IAllocator *pAllocator, const char *name, ThreadFunc func, void *argument, u32 stackSize, CPUID cpuId,
                       s32 threadPriority) {
  return ThreadNx::create(pAllocator, name, func, argument, stackSize, cpuId, threadPriority);
}

} // namespace threading
} // namespace mm
