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
  static const u32 BLOCK_UNKNOWN_64 = 64; // Inferred role: free block max; original name unknown.

  GfSizeAlloc() : m_buffer(nullptr), m_bufferSize(0), unknown18(nullptr), m_allocs(0), m_blockSize(0), unknown288(nullptr) {}
  virtual ~GfSizeAlloc() { destroy(); }
  void setup(mm::mtl::IAllocator *allocator, u32 blockSize, void *buffer, size_t size);
  void destroy();
  void resize(size_t size);
  void *alloc(size_t size, bool isTail);
  bool free(void *pointer);
  void logFreeBlock();

  void *m_buffer;                                      // Inferred role: buffer; named after the game accessor gf::GfSlotAllocator::getBuffer.
  size_t m_bufferSize;                                 // Inferred role: buffer size; named after the game accessor gf::GfSlotAllocator::getBufferSize.
  u32 *unknown18;                                      // Inferred role: block table; original member name unknown.
  u32 m_allocs;                                        // Inferred role: allocs; named after the game accessor gf::GfSlotAllocator::getAllocs.
  u32 unknown24;                                       // Inferred role: block count; original member name unknown.
  size_t m_blockSize;                                  // Inferred role: block size; named after the game accessor gf::GfSlotAllocator::getBlockSize.
  mm::mtl::FixedList<u32, BLOCK_UNKNOWN_64> unknown30; // Inferred role: free blocks; original member name unknown.
  mm::mtl::IAllocator *unknown288;                     // Inferred role: allocator; original member name unknown.
};

static_assert(offsetof(GfSizeAlloc, m_buffer) == 0x08, "");
static_assert(offsetof(GfSizeAlloc, m_bufferSize) == 0x10, "");
static_assert(offsetof(GfSizeAlloc, unknown18) == 0x18, "");
static_assert(offsetof(GfSizeAlloc, m_allocs) == 0x20, "");
static_assert(offsetof(GfSizeAlloc, unknown24) == 0x24, "");
static_assert(offsetof(GfSizeAlloc, m_blockSize) == 0x28, "");
static_assert(offsetof(GfSizeAlloc, unknown30) == 0x30, "");
static_assert(offsetof(GfSizeAlloc, unknown288) == 0x288, "");
static_assert(sizeof(GfSizeAlloc) == 0x290, "");

} // namespace gf
