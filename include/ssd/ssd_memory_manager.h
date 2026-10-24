#pragma once
#include <stddef.h>

#include "types.h"

namespace ssd {

class MemoryManager {
public:
  virtual ~MemoryManager();

  static MemoryManager memoryManager_;

  u8 _08[0x58 - 0x08];
  int unknown58; // Inferred role: alloc memory count; original member name unknown.
  u8 _5c[0x94 - 0x5c];
  int unknown94; // Inferred role: instance alloc count; original member name unknown.
  int unknown98; // Inferred role: buffer alloc count; original member name unknown.
  int unknown9c; // Inferred role: stream alloc count; original member name unknown.
};

static_assert(offsetof(MemoryManager, unknown58) == 0x58, "");
static_assert(offsetof(MemoryManager, unknown94) == 0x94, "");
static_assert(offsetof(MemoryManager, unknown9c) == 0x9c, "");

} // namespace ssd
