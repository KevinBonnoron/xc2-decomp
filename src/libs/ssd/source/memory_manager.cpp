#include <stddef.h>

#include "ssd/ssd_allocator.h"
#include "ssd/ssd_behavior.h"
#include "ssd/ssd_behavior_impl.h" // IWYU pragma: keep
#include "ssd/ssd_debug.h"
#include "ssd/ssd_memory_manager.h"
#include "ssd/ssd_mutex.h"
#include "types.h"

namespace ssd {

MemoryManager MemoryManager::memoryManager_;

void MemoryManager::FreeBlock(Allocator::Block *block) {
  m_mutex.Lock();
  BlockNode *node = static_cast<BlockNode *>(block);
  unknown38.unknown001(node);
  node->unknown08 = nullptr;
  node->unknown10 = nullptr;
  node->m_allocator = nullptr;
  unknown60.PushBack(node);
  m_mutex.Unlock();
}

MemoryManager::MemoryManager() : unknown30(false), m_blockNode(nullptr), unknown90(0) {}

void MemoryManager::Quit() {
  if (memoryManager_.unknown30) {
    BlockNode *it = memoryManager_.unknown38.unknown002();
    while (it != memoryManager_.unknown38.unknown003()) {
      BlockNode *next = List<BlockNode>::unknown004(it);
      memoryManager_.unknown38.unknown001(it);
      it = next;
    }
    it = memoryManager_.unknown60.unknown002();
    while (it != memoryManager_.unknown60.unknown003()) {
      BlockNode *next = List<BlockNode>::unknown004(it);
      memoryManager_.unknown60.unknown001(it);
      it = next;
    }
    if (memoryManager_.m_blockNode != nullptr) {
      delete[] memoryManager_.m_blockNode;
    }
    memoryManager_.m_blockNode = nullptr;
    memoryManager_.unknown90 = 0;
    if (memoryManager_.m_instanceAllocCount != 0 || memoryManager_.m_bufferAllocCount != 0 || memoryManager_.m_streamAllocCount != 0) {
      SSD_ASSERT(memoryManager_.m_instanceAllocCount == 0,
                 u"Assert : \"%s\", %s:%d, %s",
                 u"memoryManager_.numInstance_ == 0",
                 u"D:/ssd/ssd51/ssd/sources/memory/memory_manager.cpp",
                 0x7d,
                 u"インスタンスが残っている可能性があります。");
      SSD_ASSERT(memoryManager_.m_bufferAllocCount == 0,
                 u"Assert : \"%s\", %s:%d, %s",
                 u"memoryManager_.numBuffer_ == 0",
                 u"D:/ssd/ssd51/ssd/sources/memory/memory_manager.cpp",
                 0x7e,
                 u"汎用バッファが残っている可能性があります。");
      SSD_ASSERT(memoryManager_.m_streamAllocCount == 0,
                 u"Assert : \"%s\", %s:%d, %s",
                 u"memoryManager_.numStream_ == 0",
                 u"D:/ssd/ssd51/ssd/sources/memory/memory_manager.cpp",
                 0x7f,
                 u"ストリームバッファが残っている可能性があります。");
    }
    memoryManager_.m_instanceAllocCount = 0;
    memoryManager_.m_bufferAllocCount = 0;
    memoryManager_.m_streamAllocCount = 0;
    memoryManager_.m_mutex.unknown002();
  }
}

Allocator::Block *MemoryManager::AcquireBlock(Allocator *allocator, size_t size, size_t count, size_t alignment) {
  if (memoryManager_.m_blockNode == nullptr) {
    return nullptr;
  }
  m_mutex.Lock();
  unknowna0 = unknown60.count == 0;
  if (unknowna0) {
    m_mutex.Unlock();
    log_message(u"管理領域が枯渇しました。", 0);
    abort();
    return nullptr;
  }
  BlockNode *node = unknown60.unknown002();
  unknown60.unknown001(node);
  unknown38.PushBack(node);
  m_mutex.Unlock();
  node->m_allocator = allocator;
  u32 total = static_cast<u32>(count) * static_cast<u32>(size);
  u32 align = static_cast<u32>(alignment);
  node->unknown18 = total;
  node->unknown1c = (align + total - 1) & -align;
  node->unknown20 = size;
  node->unknown24 = count;
  return node;
}

Allocator::Block *MemoryManager::AllocInstance(Allocator *allocator, size_t size, size_t count, size_t alignment) {
  Allocator::Block *block = AcquireBlock(allocator, size, count, alignment);
  if (block != nullptr) {
    block->unknown10 = allocator->AllocInstance(block->unknown1c);
    SSD_ASSERT(block->unknown10 != nullptr, u"Assert : \"%s\" = nullptr, %s:%d", u"block->allocAdrs_", u"D:/ssd/ssd51/ssd/sources/memory/memory_manager.cpp", 0x94);
    if (block->unknown10 == nullptr) {
      FreeBlock(block);
      return nullptr;
    }
    block->unknown08 = reinterpret_cast<void *>((alignment + reinterpret_cast<size_t>(block->unknown10) - 1) & -alignment);
    m_instanceAllocCount++;
  }
  return block;
}

Allocator::Block *MemoryManager::AllocBuffer(Allocator *allocator, size_t size, size_t count, size_t alignment) {
  Allocator::Block *block = AcquireBlock(allocator, size, count, alignment);
  if (block != nullptr) {
    block->unknown10 = allocator->AllocBuffer(block->unknown1c, alignment);
    SSD_ASSERT(block->unknown10 != nullptr, u"Assert : \"%s\" = nullptr, %s:%d", u"block->allocAdrs_", u"D:/ssd/ssd51/ssd/sources/memory/memory_manager.cpp", 0xb9);
    if (block->unknown10 == nullptr) {
      FreeBlock(block);
      return nullptr;
    }
    block->unknown08 = reinterpret_cast<void *>((alignment + reinterpret_cast<size_t>(block->unknown10) - 1) & -alignment);
    m_bufferAllocCount++;
  }
  return block;
}

Allocator::Block *MemoryManager::AllocStream(Allocator *allocator, size_t size, size_t alignment) {
  Allocator::Block *block = AcquireBlock(allocator, size, 1, alignment);
  if (block != nullptr) {
    block->unknown10 = allocator->AllocStream(block->unknown1c, alignment);
    SSD_ASSERT(block->unknown10 != nullptr, u"Assert : \"%s\" = nullptr, %s:%d", u"block->allocAdrs_", u"D:/ssd/ssd51/ssd/sources/memory/memory_manager.cpp", 0xe5);
    if (block->unknown10 == nullptr) {
      FreeBlock(block);
      return nullptr;
    }
    block->unknown08 = reinterpret_cast<void *>((alignment + reinterpret_cast<size_t>(block->unknown10) - 1) & -alignment);
    m_streamAllocCount++;
  }
  return block;
}

Allocator::Block *MemoryManager::GetAllocatorBlock(void *address) {
  m_mutex.Lock();
  Allocator::Block *found = nullptr;
  if (address != nullptr) {
    for (BlockNode *it = unknown38.unknown002(); it != unknown38.unknown003(); it = List<BlockNode>::unknown004(it)) {
      if (it->unknown08 == address) {
        found = it;
        break;
      }
    }
  }
  m_mutex.Unlock();
  SSD_ASSERT(found != nullptr, u"Assert : \"%s\", %s:%d, %s", u"freeBlock != nullptr", u"D:/ssd/ssd51/ssd/sources/memory/memory_manager.cpp", 0x143, u"検索したメモリアドレスは管理外でした。");
  return found;
}

void MemoryManager::FreeInstance(Allocator *allocator, Allocator::Block *block) {
  allocator->FreeInstance(block->unknown10);
  FreeBlock(block);
  m_instanceAllocCount--;
}

void MemoryManager::FreeBuffer(Allocator *allocator, Allocator::Block *block) {
  allocator->FreeBuffer(block->unknown10);
  FreeBlock(block);
  m_bufferAllocCount--;
}

void MemoryManager::FreeStream(Allocator *allocator, Allocator::Block *block) {
  allocator->FreeStream(block->unknown10);
  FreeBlock(block);
  m_streamAllocCount--;
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
