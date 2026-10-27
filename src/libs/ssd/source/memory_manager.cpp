#include "ssd/ssd_behavior_impl.h" // IWYU pragma: keep
#include <stddef.h>

#include "ssd/ssd_allocator.h"
#include "ssd/ssd_behavior.h"
#include "ssd/ssd_memory_manager.h"
#include "ssd/ssd_mutex.h"

namespace ssd {

void MemoryManager::FreeBlock(Allocator::Block *block) {
  unknown08.Lock();
  BlockNode *node = static_cast<BlockNode *>(block);
  unknown38.unknown001(node);
  node->unknown08 = nullptr;
  node->unknown10 = nullptr;
  node->unknown00 = nullptr;
  unknown60.PushBack(node);
  unknown08.Unlock();
}

void MemoryManager::FreeInstance(Allocator *allocator, Allocator::Block *block) {
  allocator->FreeInstance(block->unknown10);
  FreeBlock(block);
  unknown94--;
}

void MemoryManager::FreeBuffer(Allocator *allocator, Allocator::Block *block) {
  allocator->FreeBuffer(block->unknown10);
  FreeBlock(block);
  unknown98--;
}

void MemoryManager::FreeStream(Allocator *allocator, Allocator::Block *block) {
  allocator->FreeStream(block->unknown10);
  FreeBlock(block);
  unknown9c--;
}

Allocator::Block *Allocator::NewInstanceImpl(size_t size, size_t count, size_t alignment) { return MemoryManager::memoryManager_.AllocInstance(this, size, count, alignment); }

Allocator::Block *Allocator::NewBufferImpl(size_t size, size_t count, size_t alignment) { return MemoryManager::memoryManager_.AllocBuffer(this, size, count, alignment); }

Allocator::Block *Allocator::NewStreamImpl(size_t size, size_t alignment) { return MemoryManager::memoryManager_.AllocStream(this, size, alignment); }

Allocator::Block *Allocator::GetMemoryBlock(void *address) { return MemoryManager::memoryManager_.GetAllocatorBlock(address); }

void Allocator::DeleteInstanceImpl(Block *block) { MemoryManager::memoryManager_.FreeInstance(this, block); }

void Allocator::DeleteBufferImpl(Block *block) {
  if (block != nullptr) {
    MemoryManager::memoryManager_.FreeBuffer(this, block);
  }
}

void Allocator::DeleteStreamImpl(Block *block) {
  if (block != nullptr) {
    MemoryManager::memoryManager_.FreeStream(this, block);
  }
}

template List<MemoryManager::BlockNode> *List<MemoryManager::BlockNode>::Delete();
template List<MemoryManager::BlockNode>::Node::~Node();

} // namespace ssd
