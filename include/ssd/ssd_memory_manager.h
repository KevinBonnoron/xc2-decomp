#pragma once
#include <stddef.h>

#include "ssd/ssd_allocator.h"
#include "ssd/ssd_behavior.h"
#include "ssd/ssd_mutex.h"
#include "types.h"

namespace ssd {

class MemoryManager {
public:
  class BlockNode : public List<BlockNode>::Node, public Allocator::Block {};

  virtual ~MemoryManager();
  Allocator::Block *AllocInstance(Allocator *allocator, size_t size, size_t count, size_t alignment);
  Allocator::Block *AllocBuffer(Allocator *allocator, size_t size, size_t count, size_t alignment);
  Allocator::Block *AllocStream(Allocator *allocator, size_t size, size_t alignment);
  Allocator::Block *GetAllocatorBlock(void *address);
  void FreeBlock(Allocator::Block *block);
  void FreeInstance(Allocator *allocator, Allocator::Block *block);
  void FreeBuffer(Allocator *allocator, Allocator::Block *block);
  void FreeStream(Allocator *allocator, Allocator::Block *block);

  static MemoryManager memoryManager_;

  Mutex unknown08;           // Inferred role: block lists mutex; original member name unknown.
  bool unknown30;            // Inferred role: initialized; original member name unknown.
  List<BlockNode> unknown38; // Inferred role: used blocks; original member name unknown.
  List<BlockNode> unknown60; // Inferred role: free blocks; original member name unknown.
  u8 _88[0x94 - 0x88];
  int unknown94; // Inferred role: instance alloc count; original member name unknown.
  int unknown98; // Inferred role: buffer alloc count; original member name unknown.
  int unknown9c; // Inferred role: stream alloc count; original member name unknown.
};

static_assert(offsetof(MemoryManager, unknown08) == 0x8, "");
static_assert(offsetof(MemoryManager, unknown30) == 0x30, "");
static_assert(offsetof(MemoryManager, unknown38) == 0x38, "");
static_assert(offsetof(MemoryManager, unknown60) == 0x60, "");
static_assert(offsetof(MemoryManager, unknown94) == 0x94, "");
static_assert(offsetof(MemoryManager, unknown9c) == 0x9c, "");

} // namespace ssd
