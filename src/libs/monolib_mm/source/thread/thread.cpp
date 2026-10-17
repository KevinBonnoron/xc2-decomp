#include "ml/thread.h"

#include <string.h>

#include "ml/thread_nx.h"
#include "ml/thread_util.h"
#include "ml/work_util.h"
#include "mm_mtl/fixstr.h"
#include "mm_thread/mm_thread_util.h"
#include "mtl/alloc_handle.h"
#include "mtl/mem_manager.h"
#include "nn/os.h"

namespace ml {

u64 ThreadUtil::getCurrentID() { return reinterpret_cast<u64>(nn::os::GetCurrentThread()); }

Thread::Thread() : m_refCount(0) {}

s32 Thread::suspend() { return ThreadUtil::suspendThread(getHandle()); }

s32 ThreadUtil::suspendThread(MLTHREAD *thread) { return 0; }

void Thread::resume() { ThreadUtil::resumeThread(getHandle()); }

void ThreadUtil::resumeThread(MLTHREAD *thread) { nn::os::StartThread(thread); }

Thread *Thread::create(const char *name, bool isStart, ThreadFunc func, void *argument, u32 stackSize, CPUID cpuId, int priority) {
  Thread *thread = nullptr;
  ThreadNx::create(&thread, name, isStart, func, argument, stackSize, cpuId, priority);
  thread->m_refCount++;
  return thread;
}

void ThreadNx::create(Thread **thread, const char *name, bool isStart, ThreadFunc func, void *argument, u32 stackSize, CPUID cpuId, int priority) {
  new (WorkUtil::getWorkMem()) ThreadNx(thread, name, isStart, func, argument, stackSize, cpuId, priority);
}

bool Thread::create(Thread **thread, const char *name, bool isStart, ThreadFunc func, void *argument, u32 stackSize, CPUID cpuId, int priority) {
  new (WorkUtil::getWorkMem()) ThreadNx(thread, name, isStart, func, argument, stackSize, cpuId, priority);
  (*thread)->m_refCount++;
  return *thread != nullptr;
}

s32 ThreadUtil::getCpuNum() { return 3; }

u32 ThreadUtil::getCpuMask() { return nn::os::GetThreadAvailableCoreMask(); }

void ThreadUtil::setCpuThread(MLTHREAD *thread, CPUID cpuId) {
  if (cpuId == CPUID_ANY) {
    return;
  }
  s32 coreID = convertCoreID(cpuId);
  nn::os::SetThreadCoreMask(thread, coreID, 1UL << coreID);
}

s32 ThreadUtil::convertCoreID(CPUID cpuId) { return cpuId > CPUID_ANY ? cpuId - 1 : -1; }

u64 ThreadUtil::getID(MLTHREAD *thread) { return reinterpret_cast<u64>(thread); }

const char *ThreadUtil::getThreadName(u64 id) { return nn::os::GetThreadNamePointer(reinterpret_cast<nn::os::ThreadType *>(id)); }

CPUID ThreadUtil::getCurrentCPUID() { return static_cast<CPUID>(nn::os::GetCurrentCoreNumber() + 1); }

MLTHREAD *ThreadUtil::getCurrentHandle() { return static_cast<MLTHREAD *>(nn::os::GetCurrentThread()); }

ThreadNx::ThreadNx(Thread **thread, const char *name, bool isStart, ThreadFunc func, void *argument, u32 stackSize, CPUID cpuId, int priority)
    : m_cpuId(cpuId), m_event(false, false), m_stack(nullptr), m_argument(argument), m_func(func), m_state(STATE_RUNNING) {
  *thread = this;
  if (stackSize == 0) {
    stackSize = 0x10000;
  }
  m_stack = mtl::MemManager::allocate(WorkCpu::getMemStack(), stackSize, 0x1000, false, "no name", 0);
  memset(m_stack, 0xa5, stackSize);
  int threadPriority = nn::os::DefaultThreadPriority - priority;
  if (cpuId != CPUID_ANY) {
    nn::os::CreateThread(&m_thread, threadCallback, this, m_stack, stackSize, threadPriority, cpuId - 1);
  } else {
    nn::os::CreateThread(&m_thread, threadCallback, this, m_stack, stackSize, threadPriority);
  }
  m_handle = &m_thread;
  m_id = reinterpret_cast<u64>(&m_thread);

  mm::mtl::FixStr<32> defaultName;
  if (name == nullptr) {
    defaultName.format("%p", this);
    name = defaultName.c_str();
  }
  nn::os::SetThreadName(&m_thread, name);
  if (isStart) {
    resume();
  }
}

void ThreadNx::threadCallback(void *param) {
  ThreadNx *thread = static_cast<ThreadNx *>(param);
  thread->m_state = STATE_RUNNING;
  if (thread->m_func != nullptr) {
    thread->m_func(thread->m_argument);
  }
  thread->m_state = STATE_TERMINATED;
}

bool ThreadNx::isSuspended() const { return false; }

bool ThreadNx::isTerminated() {
  if (m_handle == nullptr) {
    return true;
  }
  return m_state == STATE_TERMINATED;
}

s32 ThreadNx::exitThread() {
  if (m_handle != nullptr) {
    nn::os::DestroyThread(m_handle);
    m_handle = nullptr;
  }
  m_state = STATE_TERMINATED;
  return 0;
}

const char *ThreadNx::getName() const { return nn::os::GetThreadNamePointer(&m_thread); }

void ThreadNx::setSignalEvent(bool isSignal) { m_event.setSignal(isSignal); }

bool ThreadNx::waitSignalEvent() { return m_event.waitSignal(0); }

bool ThreadNx::isWaitingEvent() const { return !m_event.isSignal(); }

MLTHREAD *ThreadNx::getHandle() const { return static_cast<MLTHREAD *>(m_handle); }

u64 ThreadNx::getID() const { return m_id; }

CPUID ThreadNx::getCPUID() const { return m_cpuId; }

} // namespace ml
