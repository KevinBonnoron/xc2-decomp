#pragma once
#include "types.h"

namespace ml {

class Thread {
public:
  virtual ~Thread();
  virtual bool isSuspended() const = 0;
  virtual bool isTerminated() = 0;
  virtual void exitThread() = 0;
  virtual void *getHandle() const = 0;
  virtual u64 getID() const = 0;
  virtual int getCPUID() const = 0;
  virtual const char *getName() const = 0;
  virtual void setSignalEvent(bool isSignal) = 0;
  virtual void waitSignalEvent() = 0;
  virtual bool isWaitingEvent() const = 0;

  void suspend();
  void resume();
};

} // namespace ml
