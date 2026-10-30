#pragma once
#include <stddef.h>

#include "nn/os.h"
#include "types.h"

namespace ssd {

class Mutex {
public:
  Mutex() : unknown20(false), unknown21(0) {}

  ~Mutex() {
    unknown20 = false;
    unknown21 = 0;
  }

  // Inferred role: create the mutex; original name unknown.
  void unknown001() {
    nn::os::InitializeMutex(&unknown00, true, 0);
    unknown20 = true;
    unknown21 = 0;
  }

  // Inferred role: destroy the mutex if it was created; original name unknown.
  void unknown002() {
    if (unknown20) {
      unknown20 = false;
      unknown21 = 0;
      nn::os::FinalizeMutex(&unknown00);
    }
  }

  void Lock() {
    nn::os::LockMutex(&unknown00);
    unknown21++;
  }

  void Unlock() {
    unknown21--;
    nn::os::UnlockMutex(&unknown00);
    nn::os::IsMutexLockedByCurrentThread(&unknown00);
  }

  nn::os::MutexType unknown00; // Inferred role: mutex; original member name unknown.
  bool unknown20;              // Inferred role: init; original member name unknown.
  u8 unknown21;                // Inferred role: lock count; original member name unknown.
};

static_assert(offsetof(Mutex, unknown20) == 0x20, "");

} // namespace ssd
