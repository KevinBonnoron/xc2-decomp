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

  GfSizeAlloc() : unknown08(nullptr), unknown10(0), unknown18(nullptr), unknown20(0), unknown28(0), unknown288(nullptr) {}
  virtual ~GfSizeAlloc() { destroy(); }
  void setup(mm::mtl::IAllocator *allocator, u32 blockSize, void *buffer, size_t size);
  void destroy();
  void resize(size_t size);
  void *alloc(size_t size, bool isTail);
  bool free(void *pointer);
  void logFreeBlock();

  void *unknown08;                                   // Inferred role: buffer; original member name unknown.
  size_t unknown10;                                  // Inferred role: buffer size; original member name unknown.
  u32 *unknown18;                                    // Inferred role: block table; original member name unknown.
  u32 unknown20;                                     // Inferred role: allocs; original member name unknown.
  u32 unknown24;                                     // Inferred role: block count; original member name unknown.
  size_t unknown28;                                  // Inferred role: block size; original member name unknown.
  mm::mtl::FixedList<u32, FREE_BLOCK_MAX> unknown30; // Inferred role: free blocks; original member name unknown.
  mm::mtl::IAllocator *unknown288;                   // Inferred role: allocator; original member name unknown.
};

static_assert(offsetof(GfSizeAlloc, unknown08) == 0x08, "");
static_assert(offsetof(GfSizeAlloc, unknown10) == 0x10, "");
static_assert(offsetof(GfSizeAlloc, unknown18) == 0x18, "");
static_assert(offsetof(GfSizeAlloc, unknown20) == 0x20, "");
static_assert(offsetof(GfSizeAlloc, unknown24) == 0x24, "");
static_assert(offsetof(GfSizeAlloc, unknown28) == 0x28, "");
static_assert(offsetof(GfSizeAlloc, unknown30) == 0x30, "");
static_assert(offsetof(GfSizeAlloc, unknown288) == 0x288, "");
static_assert(sizeof(GfSizeAlloc) == 0x290, "");

} // namespace gf
