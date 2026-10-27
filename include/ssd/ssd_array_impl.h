#pragma once
#include "ssd/ssd_allocator.h"
#include "ssd/ssd_array.h"

namespace ssd {

template <typename T> Array<T>::~Array() {
  if (unknown10 != nullptr) {
    Allocator *allocator = SoundMemory::allocator_;
    Allocator::Block *block = allocator->GetMemoryBlock(unknown10);
    if (block != nullptr) {
      allocator->DeleteInstanceImpl(block);
    }
  }
  unknown08 = 0;
  unknown0c = 0;
  unknown10 = nullptr;
}

template <typename T> void Array<T>::SetArraySize(int size) {
  if (unknown0c <= size) {
    T *old = unknown10;
    Allocator::Block *block = SoundMemory::allocator_->NewInstanceImpl(sizeof(T), size + 1, 16);
    if (block != nullptr) {
      unknown10 = static_cast<T *>(block->unknown08);
    } else {
      unknown10 = nullptr;
    }
    if (old != nullptr) {
      for (int i = 0; i < unknown0c; i++) {
        unknown10[i] = old[i];
      }
      Allocator *allocator = SoundMemory::allocator_;
      Allocator::Block *oldBlock = allocator->GetMemoryBlock(old);
      if (oldBlock != nullptr) {
        allocator->DeleteInstanceImpl(oldBlock);
      }
    }
    unknown0c = size;
  }
}

} // namespace ssd
