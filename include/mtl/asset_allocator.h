#pragma once
#include <stddef.h>

#include "mm_mtl/fixed_list.h"
#include "mm_mtl/fixstr.h"
#include "mtl/mem_allocator.h"
#include "mtl/mem_manager.h"
#include "types.h"

namespace mtl {

// Allocator of the resource memory: the buffer is cut in blocks (getAllocSize of the memory manager rounds the sizes
// to them) and the free and used chunks are lists of runs of blocks.
template <int N> class AssetAllocator : public IMemAllocator {
public:
  struct SMemChunk {
    const char *unknown00; // Inferred role: file of the allocation; original member name unknown.
    u16 unknown08;         // Inferred role: line of the allocation; original member name unknown.
    u16 unknown0a;         // Role and original member name unknown.
    int unknown0c;         // Inferred role: index of the first block of the chunk; original member name unknown.
    int unknown10;         // Inferred role: number of blocks of the chunk; original member name unknown.

    // Evidence: allocate_tail stores 0xffffffff in unknown0c and zeros in the other fields of its chunk before the search loop
    // (0x71007855f0 to 0x7100785610 in the game); deallocate only keeps the zero stores, it sets unknown0c right away.
    SMemChunk() : unknown00(nullptr), unknown08(0), unknown0a(0), unknown0c(-1), unknown10(0) {}

    // Inferred role: chunks are the same when they start at the same block; original form unknown.
    bool operator==(const SMemChunk &other) const { return unknown0c == other.unknown0c; }

    // Inferred role: order of the free chunks, by index of the first block; original form unknown.
    bool operator<(const SMemChunk &other) const { return unknown0c < other.unknown0c; }
  };

  void create(void *buffer, size_t size, const char *name) override;
  void destroy() override;
  AllocatorType getType() const override;
  void *allocate(size_t size, size_t alignment) override;
  void *allocate(size_t size, size_t alignment, const char *file, int line) override;
  void *allocate_tail(size_t size, size_t alignment, const char *file, int line) override;
  void deallocate(void *pointer, size_t size) override;
  void *reallocate(void *pointer, size_t size) override;
  void log(MemoryInfo *info, bool isDetail) const override;
  const char *getName() const override;
  bool hasMemory(const void *pointer) const override;
  size_t getAllocSize(const void *pointer) const override;
  void memoryInfo(MemoryInfo *info) const override;
  void getMemImage(MEMIMAGE_HEAD *head) const override;
  bool getMemInfo1(MemoryInfo1 *info, u32 num) const override;
  bool empty() const override;
  bool valid() const override;
  bool dummy() const override;

  void addFreeList(const SMemChunk &chunk);
  void merge(void *pointer, const SMemChunk &chunk);

  // Inferred role: address of the block of the given index in the buffer; original name unknown.
  void *unknown001(u32 index) const { return static_cast<u8 *>(unknown11090) + index * unknown110a0; }

  // Inferred role: size in bytes of the given number of blocks; original name unknown.
  size_t unknown002(u32 blocks) const { return blocks * unknown110a0; }

  mm::mtl::FixStr<32> m_name;
  mm::mtl::FixedList<SMemChunk, N> unknown30;   // Inferred role: free chunks, by address; original member name unknown.
  mm::mtl::FixedList<SMemChunk, N> unknown8860; // Inferred role: chunks in use; original member name unknown.
  void *unknown11090;                           // Inferred role: buffer given to create; original member name unknown.
  size_t unknown11098;                          // Inferred role: size of the buffer in whole blocks; original member name unknown.
  size_t unknown110a0;                          // Inferred role: size of a block; original member name unknown.
  size_t unknown110a8;                          // Inferred role: number of blocks of the buffer; original member name unknown.
};

static_assert(sizeof(AssetAllocator<1024>::SMemChunk) == 0x18, "");
static_assert(sizeof(AssetAllocator<1024>) == 0x110b0, "");

} // namespace mtl
