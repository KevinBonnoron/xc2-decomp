#pragma once

#include "nn/os.h"
#include "types.h"

namespace ssd {

class Event {
public:
  void Init(const char16_t *name);
  void Quit();
  int Wait();
  int Wait(f32 timeout);
  void Signal();

  nn::os::EventType unknown00; // Inferred role: event; original member name unknown.
};

} // namespace ssd
