#pragma once
#include <stddef.h>

#include "types.h"

namespace mtl {
class ALLOC_HANDLE;
} // namespace mtl

namespace ml {

class DataWrite {
public:
  void init(mtl::ALLOC_HANDLE handle, u64 capacity);
  void *write(const void *data, u64 size);
  void *writeFormat(const char *format, ...);
  void align(u64 alignment);
  int writeFile(const char *path);

  u8 _00[0x08 - 0x00];
  u8 *m_buffer;
  u64 m_size;
  u64 m_capacity;
};

static_assert(offsetof(DataWrite, m_buffer) == 0x08, "");
static_assert(offsetof(DataWrite, m_capacity) == 0x18, "");

} // namespace ml
