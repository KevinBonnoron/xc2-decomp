#pragma once
#include <stddef.h>

#include "nn/os.h"
#include "types.h"

namespace ssd {

class Mutex {
public:
  ~Mutex();

  void Lock() {
    nn::os::LockMutex(&mutex);
    lockCount++;
  }

  void Unlock() {
    lockCount--;
    nn::os::UnlockMutex(&mutex);
    nn::os::IsMutexLockedByCurrentThread(&mutex);
  }

  nn::os::MutexType mutex;
  bool isInit;
  u8 lockCount;
};

static_assert(offsetof(Mutex, isInit) == 0x20, "");

} // namespace ssd
