#pragma once
#include <stddef.h>

#include "mm_mtl/fixed_list.h"
#include "types.h"

namespace mm {
namespace mtl {
class IAllocator;
} // namespace mtl
} // namespace mm

namespace gf {

class GfSizeAlloc {
public:
  static const u32 FREE_BLOCK_MAX = 64;

  GfSizeAlloc() : buffer(nullptr), bufferSize(0), blockTable(nullptr), allocs(0), blockSize(0), allocator(nullptr) {}
  virtual ~GfSizeAlloc() { destroy(); }
  void setup(mm::mtl::IAllocator *allocator, u32 blockSize, void *buffer, size_t size);
  void destroy();
  void resize(size_t size);
  void *alloc(size_t size, bool isTail);
  bool free(void *pointer);
  void logFreeBlock();

  void *buffer;
  size_t bufferSize;
  u32 *blockTable;
  u32 allocs;
  u32 blockCount;
  size_t blockSize;
  mm::mtl::FixedList<u32, FREE_BLOCK_MAX> freeBlocks;
  mm::mtl::IAllocator *allocator;
};

static_assert(offsetof(GfSizeAlloc, buffer) == 0x08, "");
static_assert(offsetof(GfSizeAlloc, bufferSize) == 0x10, "");
static_assert(offsetof(GfSizeAlloc, blockTable) == 0x18, "");
static_assert(offsetof(GfSizeAlloc, allocs) == 0x20, "");
static_assert(offsetof(GfSizeAlloc, blockCount) == 0x24, "");
static_assert(offsetof(GfSizeAlloc, blockSize) == 0x28, "");
static_assert(offsetof(GfSizeAlloc, freeBlocks) == 0x30, "");
static_assert(offsetof(GfSizeAlloc, allocator) == 0x288, "");
static_assert(sizeof(GfSizeAlloc) == 0x290, "");

} // namespace gf
