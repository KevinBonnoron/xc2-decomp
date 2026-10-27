#pragma once
#include <stddef.h>

#include "types.h"

namespace ssd {

class BufferBase {
public:
  void GetData(u64 size, u64 offset, void *buffer);
  long Read(u64 size, void *buffer);

  u8 *unknown00; // Inferred role: data; original member name unknown.
  u64 unknown08; // Inferred role: data size; original member name unknown.
  u64 unknown10; // Inferred role: read position; original member name unknown.
};

static_assert(offsetof(BufferBase, unknown10) == 0x10, "");

} // namespace ssd
