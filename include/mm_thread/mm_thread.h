#pragma once
#include "mm_thread/mm_thread_refcount.h"
#include "mm_thread/mm_thread_util.h"
#include "types.h"

namespace mm {
namespace mtl {
class IAllocator;
} // namespace mtl

namespace threading {

typedef u32 (*ThreadFunc)(void *argument);

class Thread : public ReferenceObject {
public:
  Thread(mtl::IAllocator *allocator);
  ~Thread() override;
  s32 suspend();
  void resume();
  void join(s32 milliSeconds);
  static Thread *create(mtl::IAllocator *pAllocator, const char *name, ThreadFunc func, void *argument, u32 stackSize, CPUID cpuId, s32 threadPriority);

  virtual bool isSuspended() const = 0;
  virtual bool isTerminated() = 0;
  virtual s32 exitThread() = 0;
  virtual MMTHREAD *getHandle() const = 0;
  virtual u64 getID() const = 0;
  virtual CPUID getCPUID() const = 0;
  virtual const char *getName() const = 0;
  virtual void setSignalEvent(bool signal) = 0;
  virtual bool waitSignalEvent() = 0;
  virtual bool isWaitingEvent() const = 0;
};

} // namespace threading
} // namespace mm
