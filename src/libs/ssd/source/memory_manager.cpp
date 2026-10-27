#include <stddef.h>

#include "nn/os.h"
#include "ssd/ssd_allocator.h"
#include "ssd/ssd_behavior.h"
#include "ssd/ssd_behavior_impl.h" // IWYU pragma: keep
#include "ssd/ssd_debug.h"
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
    if (memoryManager_.unknown88 != nullptr) {
      delete[] memoryManager_.unknown88;
    }
    memoryManager_.unknown88 = nullptr;
    memoryManager_.unknown90 = 0;
    if (memoryManager_.unknown94 != 0 || memoryManager_.unknown98 != 0 || memoryManager_.unknown9c != 0) {
      if (memoryManager_.unknown94 != 0) {
        log_message(u"Assert : \"%s\", %s:%d, %s",
                    u"memoryManager_.numInstance_ == 0",
                    get_logfilename(u"D:/ssd/ssd51/ssd/sources/memory/memory_manager.cpp"),
                    0x7d,
                    u"インスタンスが残っている可能性があります。");
        abort();
      }
      if (memoryManager_.unknown98 != 0) {
        log_message(u"Assert : \"%s\", %s:%d, %s",
                    u"memoryManager_.numBuffer_ == 0",
                    get_logfilename(u"D:/ssd/ssd51/ssd/sources/memory/memory_manager.cpp"),
                    0x7e,
                    u"汎用バッファが残っている可能性があります。");
        abort();
      }
      if (memoryManager_.unknown9c != 0) {
        log_message(u"Assert : \"%s\", %s:%d, %s",
                    u"memoryManager_.numStream_ == 0",
                    get_logfilename(u"D:/ssd/ssd51/ssd/sources/memory/memory_manager.cpp"),
                    0x7f,
                    u"ストリームバッファが残っている可能性があります。");
        abort();
      }
    }
    memoryManager_.unknown94 = 0;
    memoryManager_.unknown98 = 0;
    memoryManager_.unknown9c = 0;
    if (memoryManager_.unknown08.unknown20) {
      memoryManager_.unknown08.unknown20 = false;
      memoryManager_.unknown08.unknown21 = 0;
      nn::os::FinalizeMutex(&memoryManager_.unknown08.unknown00);
    }
  }
}

Allocator::Block *MemoryManager::AllocInstance(Allocator *allocator, size_t size, size_t count, size_t alignment) {
  Allocator::Block *block = AcquireBlock(allocator, size, count, alignment);
  if (block != nullptr) {
    block->unknown10 = allocator->AllocInstance(block->unknown1c);
    if (block->unknown10 == nullptr) {
      log_message(u"Assert : \"%s\" = nullptr, %s:%d", u"block->allocAdrs_", get_logfilename(u"D:/ssd/ssd51/ssd/sources/memory/memory_manager.cpp"), 0x94);
      abort();
      if (block->unknown10 == nullptr) {
        FreeBlock(block);
        return nullptr;
      }
    }
    block->unknown08 = reinterpret_cast<void *>((alignment + reinterpret_cast<size_t>(block->unknown10) - 1) & -alignment);
    unknown94++;
  }
  return block;
}

Allocator::Block *MemoryManager::AllocBuffer(Allocator *allocator, size_t size, size_t count, size_t alignment) {
  Allocator::Block *block = AcquireBlock(allocator, size, count, alignment);
  if (block != nullptr) {
    block->unknown10 = allocator->AllocBuffer(block->unknown1c, alignment);
    if (block->unknown10 == nullptr) {
      log_message(u"Assert : \"%s\" = nullptr, %s:%d", u"block->allocAdrs_", get_logfilename(u"D:/ssd/ssd51/ssd/sources/memory/memory_manager.cpp"), 0xb9);
      abort();
      if (block->unknown10 == nullptr) {
        FreeBlock(block);
        return nullptr;
      }
    }
    block->unknown08 = reinterpret_cast<void *>((alignment + reinterpret_cast<size_t>(block->unknown10) - 1) & -alignment);
    unknown98++;
  }
  return block;
}

Allocator::Block *MemoryManager::AllocStream(Allocator *allocator, size_t size, size_t alignment) {
  Allocator::Block *block = AcquireBlock(allocator, size, 1, alignment);
  if (block != nullptr) {
    block->unknown10 = allocator->AllocStream(block->unknown1c, alignment);
    if (block->unknown10 == nullptr) {
      log_message(u"Assert : \"%s\" = nullptr, %s:%d", u"block->allocAdrs_", get_logfilename(u"D:/ssd/ssd51/ssd/sources/memory/memory_manager.cpp"), 0xe5);
      abort();
      if (block->unknown10 == nullptr) {
        FreeBlock(block);
        return nullptr;
      }
    }
    block->unknown08 = reinterpret_cast<void *>((alignment + reinterpret_cast<size_t>(block->unknown10) - 1) & -alignment);
    unknown9c++;
  }
  return block;
}

Allocator::Block *MemoryManager::GetAllocatorBlock(void *address) {
  unknown08.Lock();
  Allocator::Block *found = nullptr;
  if (address != nullptr) {
    for (BlockNode *it = unknown38.unknown002(); it != unknown38.unknown003(); it = List<BlockNode>::unknown004(it)) {
      if (it->unknown08 == address) {
        found = it;
        break;
      }
    }
  }
  unknown08.Unlock();
  if (found == nullptr) {
    log_message(u"Assert : \"%s\", %s:%d, %s", u"freeBlock != nullptr", get_logfilename(u"D:/ssd/ssd51/ssd/sources/memory/memory_manager.cpp"), 0x143, u"検索したメモリアドレスは管理外でした。");
    abort();
  }
  return found;
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
