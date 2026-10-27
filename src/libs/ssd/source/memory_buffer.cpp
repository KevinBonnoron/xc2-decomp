#include <stddef.h>

#include "ssd/ssd_allocator.h"
#include "ssd/ssd_memory_buffer.h"

namespace ssd {

void MemoryBuffer::Alloc(size_t size, size_t alignment, Allocator *allocator) {
  Allocator *buffer = SoundMemory::allocator_;
  if (allocator != nullptr) {
    buffer = allocator;
  }
  unknown18 = buffer;
  Allocator::Block *block = buffer->NewBufferImpl(size, 1, alignment);
  void *data;
  if (block != nullptr) {
    data = block->unknown08;
  } else {
    data = nullptr;
  }
  unknown08 = data;
  unknown10 = size;
}

void MemoryBuffer::Free() {
  if (unknown08 != nullptr) {
    Allocator *allocator = unknown18;
    Allocator::Block *block = allocator->GetMemoryBlock(unknown08);
    allocator->DeleteBufferImpl(block);
    unknown10 = 0;
    unknown18 = nullptr;
    unknown08 = nullptr;
  }
}

} // namespace ssd
