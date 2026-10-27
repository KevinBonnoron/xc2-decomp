#pragma once
#include <stddef.h>

namespace ssd {

class Allocator;

class MemoryBuffer {
public:
  virtual ~MemoryBuffer() { Free(); }
  void Alloc(size_t size, size_t alignment, Allocator *allocator);
  void Free();

  void *unknown08;      // Inferred role: buffer; original member name unknown.
  size_t unknown10;     // Inferred role: size; original member name unknown.
  Allocator *unknown18; // Inferred role: allocator; original member name unknown.
};

static_assert(offsetof(MemoryBuffer, unknown08) == 0x8, "");
static_assert(offsetof(MemoryBuffer, unknown18) == 0x18, "");
static_assert(sizeof(MemoryBuffer) == 0x20, "");

} // namespace ssd
