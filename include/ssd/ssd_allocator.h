#pragma once
#include <stddef.h>

#include <new>

#include "types.h"

namespace ssd {

class Allocator {
public:
  virtual ~Allocator() {}
  virtual void *AllocInstance(size_t size) = 0;
  virtual void FreeInstance(void *pointer) = 0;
  virtual void *AllocBuffer(size_t size, size_t alignment) = 0;
  virtual void FreeBuffer(void *pointer) = 0;
  virtual void *AllocStream(size_t size, size_t alignment) = 0;
  virtual void FreeStream(void *pointer) = 0;

  struct Block {
    Allocator *unknown00; // Inferred role: allocator; original member name unknown.
    void *unknown08;      // Inferred role: aligned address; original member name unknown.
    void *unknown10;      // Inferred role: allocated address; original member name unknown.
    u32 unknown18;        // Inferred role: requested size; original member name unknown.
    u32 unknown1c;        // Inferred role: aligned size; original member name unknown.
    u32 unknown20;        // Inferred role: element size; original member name unknown.
    u32 unknown24;        // Inferred role: element count; original member name unknown.
  };

  Block *NewInstanceImpl(size_t size, size_t count, size_t alignment);
  Block *NewBufferImpl(size_t size, size_t count, size_t alignment);
  Block *NewStreamImpl(size_t size, size_t alignment);
  Block *GetMemoryBlock(void *address);
  void DeleteInstanceImpl(Block *block);
  void DeleteBufferImpl(Block *block);
  void DeleteStreamImpl(Block *block);

  // Inferred role: destroy the elements of an allocated instance array and release it; original name unknown.
  template <typename T> void unknown001(T *instance) {
    Block *block = GetMemoryBlock(instance);
    if (block != nullptr) {
      for (u64 i = 0; i < block->unknown24; i++) {
        instance[i].~T();
      }
      DeleteInstanceImpl(block);
    }
  }

  // Inferred role: allocate an instance array and construct its elements; original name unknown.
  template <typename T> T *unknown002(size_t count) {
    Block *block = NewInstanceImpl(sizeof(T), count, 16);
    if (block == nullptr) {
      return nullptr;
    }
    T *instance = static_cast<T *>(block->unknown08);
    for (u64 i = 0; i < count; i++) {
      new (&instance[i]) T();
    }
    return instance;
  }
};

static_assert(sizeof(Allocator::Block) == 0x28, "");

class SoundMemory {
public:
  static Allocator *allocator_;
};

} // namespace ssd
