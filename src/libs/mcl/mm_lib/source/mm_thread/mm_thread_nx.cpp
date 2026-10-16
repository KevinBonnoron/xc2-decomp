#include "mm_thread/mm_thread_nx.h"

#include <new>

#include "mm/mm_std_base.h"
#include "mm_mtl/allocator.h"
#include "mm_mtl/fixstr.h"
#include "nn/result.h"

namespace mm {
namespace threading {

ThreadNx::ThreadNx(mtl::IAllocator *pAllocator, const char *name, ThreadFunc func, void *argument, u32 stackSize, CPUID cpuId, s32 threadPriority)
    : Thread(pAllocator), cpuId(cpuId), event(false, false), stack(nullptr), argument(argument), func(func), state(THREAD_STATE_RUNNING) {
  MM_ASSERT(pAllocator);
  if (stackSize == 0) {
    stackSize = 0x28000;
  }
  void *threadStack = pAllocator->allocate(stackSize, 0x1000);
  s32 priority = nn::os::DefaultThreadPriority - threadPriority;
  MM_ASSERT(nn::os::HighestThreadPriority <= priority && priority <= nn::os::LowestThreadPriority);
  s32 coreID = cpuId - 1;
  nn::Result result = coreID >= 0 ? nn::os::CreateThread(&thread, threadCallback, this, threadStack, stackSize, priority, coreID)
                                  : nn::os::CreateThread(&thread, threadCallback, this, threadStack, stackSize, priority);
  MM_ASSERT(result.IsSuccess() && "Cannot create Thread\n");
  handle = &thread;
  id = reinterpret_cast<u64>(&thread);
  stack = threadStack;

  mtl::FixStr<32> defaultName;
  if (name == nullptr) {
    defaultName.format("%p", this);
    name = defaultName.c_str();
  }
  nn::os::SetThreadName(&thread, name);
}

void ThreadNx::threadCallback(void *param) {
  ThreadNx *pThread = static_cast<ThreadNx *>(param);
  MM_ASSERT(pThread);
  pThread->state = THREAD_STATE_RUNNING;
  if (pThread->func != nullptr) {
    pThread->func(pThread->argument);
  }
  pThread->state = THREAD_STATE_TERMINATED;
}

ThreadNx::~ThreadNx() {
  event.finalize();
  ThreadNx::exitThread();
  if (stack != nullptr && m_allocator != nullptr) {
    m_allocator->deallocate(stack);
    stack = nullptr;
  }
}

bool ThreadNx::isSuspended() const { return false; }

bool ThreadNx::isTerminated() {
  if (handle == nullptr) {
    return true;
  }

  return state == THREAD_STATE_TERMINATED;
}

s32 ThreadNx::exitThread() {
  if (handle != nullptr) {
    nn::os::DestroyThread(handle);
    handle = nullptr;
  }

  return 0;
}

const char *ThreadNx::getName() const { return nn::os::GetThreadNamePointer(&thread); }

void ThreadNx::setSignalEvent(bool signal) { event.setSignal(signal); }

bool ThreadNx::waitSignalEvent() { return event.waitSignal(0); }

bool ThreadNx::isWaitingEvent() const { return !event.isSignal(); }

Thread *ThreadNx::create(mtl::IAllocator *pAllocator, const char *name, ThreadFunc func, void *argument, u32 stackSize, CPUID cpuId,
                         s32 threadPriority) {
  MM_ASSERT(pAllocator != 0);
  Thread *thread = static_cast<Thread *>(pAllocator->allocate(sizeof(ThreadNx), 8));
  if (thread != nullptr) {
    new (thread) ThreadNx(pAllocator, name, func, argument, stackSize, cpuId, threadPriority);
  }
  thread->addRef();
  return thread;
}

MMTHREAD *ThreadNx::getHandle() const { return static_cast<MMTHREAD *>(handle); }

u64 ThreadNx::getID() const { return id; }

CPUID ThreadNx::getCPUID() const { return cpuId; }

} // namespace threading
} // namespace mm
