#pragma once
#include <stddef.h>

#include "types.h"

namespace ssd {

class MemoryManager {
public:
  virtual ~MemoryManager();

  static MemoryManager memoryManager_;

  u8 _08[0x58 - 0x08];
  int allocMemoryCount;
  u8 _5c[0x94 - 0x5c];
  int instanceAllocCount;
  int bufferAllocCount;
  int streamAllocCount;
};

static_assert(offsetof(MemoryManager, allocMemoryCount) == 0x58, "");
static_assert(offsetof(MemoryManager, instanceAllocCount) == 0x94, "");
static_assert(offsetof(MemoryManager, streamAllocCount) == 0x9c, "");

} // namespace ssd
