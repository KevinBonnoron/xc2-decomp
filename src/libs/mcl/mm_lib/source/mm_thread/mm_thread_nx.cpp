#include "mm_thread/mm_thread_nx.h"

#include <new>

#include "mm/mm_std_base.h"
#include "mm_mtl/allocator.h"
#include "mm_mtl/fixstr.h"
#include "nn/result.h"

namespace mm {
namespace threading {

ThreadNx::ThreadNx(mtl::IAllocator *pAllocator, const char *name, ThreadFunc func, void *argument, u32 stackSize, CPUID cpuId, s32 threadPriority)
    : Thread(pAllocator), m_CPUID(cpuId), unknown1f0(false, false), unknown250(nullptr), unknown258(argument), unknown260(func), unknown268(unknown130_0) {
  MM_ASSERT(pAllocator);
  if (stackSize == 0) {
    stackSize = 0x28000;
  }
  void *threadStack = pAllocator->allocate(stackSize, 0x1000);
  s32 priority = nn::os::DefaultThreadPriority - threadPriority;
  MM_ASSERT(nn::os::HighestThreadPriority <= priority && priority <= nn::os::LowestThreadPriority);
  s32 coreID = cpuId - 1;
  nn::Result result = coreID >= 0 ? nn::os::CreateThread(&unknown30, threadCallback, this, threadStack, stackSize, priority, coreID)
                                  : nn::os::CreateThread(&unknown30, threadCallback, this, threadStack, stackSize, priority);
  MM_ASSERT(result.IsSuccess() && "Cannot create Thread\n");
  m_handle = &unknown30;
  m_ID = reinterpret_cast<u64>(&unknown30);
  unknown250 = threadStack;

  mtl::FixStr<32> defaultName;
  if (name == nullptr) {
    defaultName.format("%p", this);
    name = defaultName.c_str();
  }
  nn::os::SetThreadName(&unknown30, name);
}

void ThreadNx::threadCallback(void *param) {
  ThreadNx *pThread = static_cast<ThreadNx *>(param);
  MM_ASSERT(pThread);
  pThread->unknown268 = unknown130_0;
  if (pThread->unknown260 != nullptr) {
    pThread->unknown260(pThread->unknown258);
  }
  pThread->unknown268 = unknown130_2;
}

ThreadNx::~ThreadNx() {
  unknown1f0.finalize();
  ThreadNx::exitThread();
  if (unknown250 != nullptr && m_allocator != nullptr) {
    m_allocator->deallocate(unknown250);
    unknown250 = nullptr;
  }
}

bool ThreadNx::isSuspended() const { return false; }

bool ThreadNx::isTerminated() {
  if (m_handle == nullptr) {
    return true;
  }

  return unknown268 == unknown130_2;
}

s32 ThreadNx::exitThread() {
  if (m_handle != nullptr) {
    nn::os::DestroyThread(m_handle);
    m_handle = nullptr;
  }

  return 0;
}

const char *ThreadNx::getName() const { return nn::os::GetThreadNamePointer(&unknown30); }

void ThreadNx::setSignalEvent(bool signal) { unknown1f0.setSignal(signal); }

bool ThreadNx::waitSignalEvent() { return unknown1f0.waitSignal(0); }

bool ThreadNx::isWaitingEvent() const { return !unknown1f0.isSignal(); }

Thread *ThreadNx::create(mtl::IAllocator *pAllocator, const char *name, ThreadFunc func, void *argument, u32 stackSize, CPUID cpuId, s32 threadPriority) {
  MM_ASSERT(pAllocator != 0);
  Thread *thread = static_cast<Thread *>(pAllocator->allocate(sizeof(ThreadNx), 8));
  if (thread != nullptr) {
    new (thread) ThreadNx(pAllocator, name, func, argument, stackSize, cpuId, threadPriority);
    thread->addRef();
  }
  return thread;
}

MMTHREAD *ThreadNx::getHandle() const { return static_cast<MMTHREAD *>(m_handle); }

u64 ThreadNx::getID() const { return m_ID; }

CPUID ThreadNx::getCPUID() const { return m_CPUID; }

} // namespace threading
} // namespace mm
