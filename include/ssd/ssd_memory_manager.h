#pragma once
#include <stddef.h>

#include "ssd/ssd_allocator.h"
#include "ssd/ssd_behavior.h"
#include "ssd/ssd_mutex.h"

namespace ssd {

class MemoryManager {
public:
  class BlockNode : public List<BlockNode>::Node, public Allocator::Block {};

  MemoryManager();
  virtual ~MemoryManager() { Quit(); }
  static void Init(int size, Allocator *allocator);
  static void Quit();
  Allocator::Block *AcquireBlock(Allocator *allocator, size_t size, size_t count, size_t alignment);
  Allocator::Block *AllocInstance(Allocator *allocator, size_t size, size_t count, size_t alignment);
  Allocator::Block *AllocBuffer(Allocator *allocator, size_t size, size_t count, size_t alignment);
  Allocator::Block *AllocStream(Allocator *allocator, size_t size, size_t alignment);
  Allocator::Block *GetAllocatorBlock(void *address);
  void FreeBlock(Allocator::Block *block);
  void FreeInstance(Allocator *allocator, Allocator::Block *block);
  void FreeBuffer(Allocator *allocator, Allocator::Block *block);
  void FreeStream(Allocator *allocator, Allocator::Block *block);

  static MemoryManager memoryManager_;

  Mutex m_mutex;             // Inferred role: block lists mutex; original member name unknown.
  bool unknown30;            // Inferred role: initialized; original member name unknown.
  List<BlockNode> unknown38; // Inferred role: used blocks; original member name unknown.
  List<BlockNode> unknown60; // Inferred role: free blocks; original member name unknown.
  BlockNode *m_blockNode;    // Inferred role: block pool; original member name unknown.
  int unknown90;             // Inferred role: block pool size; original member name unknown.
  int m_instanceAllocCount;  // Inferred role: instance alloc count; named after the game accessor ssd::SoundCore::GetInstanceAllocCount.
  int m_bufferAllocCount;    // Inferred role: buffer alloc count; named after the game accessor ssd::SoundCore::GetBufferAllocCount.
  int m_streamAllocCount;    // Inferred role: stream alloc count; named after the game accessor ssd::SoundCore::GetStreamAllocCount.
  bool unknowna0;            // Inferred role: free blocks exhausted; original member name unknown.
};

static_assert(offsetof(MemoryManager, m_mutex) == 0x8, "");
static_assert(offsetof(MemoryManager, unknown30) == 0x30, "");
static_assert(offsetof(MemoryManager, unknown38) == 0x38, "");
static_assert(offsetof(MemoryManager, unknown60) == 0x60, "");
static_assert(offsetof(MemoryManager, m_blockNode) == 0x88, "");
static_assert(offsetof(MemoryManager, m_instanceAllocCount) == 0x94, "");
static_assert(offsetof(MemoryManager, m_streamAllocCount) == 0x9c, "");
static_assert(offsetof(MemoryManager, unknowna0) == 0xa0, "");

} // namespace ssd
