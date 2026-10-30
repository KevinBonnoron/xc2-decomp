#pragma once
#include "ssd/ssd_allocator.h"
#include "ssd/ssd_array.h"

namespace ssd {

template <typename T> Array<T>::~Array() { unknown001(); }

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

template <typename T> void Array<T>::SetSize(int size) {
  if (unknown0c <= size) {
    T *old = unknown10;
    unknown10 = SoundMemory::allocator_->unknown002<T>(size + 1);
    if (old != nullptr) {
      for (int i = 0; i < unknown0c; i++) {
        unknown10[i] = old[i];
      }
      SoundMemory::allocator_->unknown001(old);
    }
    unknown0c = size;
  }
}

} // namespace ssd
