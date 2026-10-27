#pragma once
#include "ssd/ssd_allocator.h"
#include "ssd/ssd_behavior.h"

namespace ssd {

template <typename T> List<T>::~List() {
  if (count != 0) {
    Delete();
  }
}

template <typename T> List<T> *List<T>::Delete() {
  T *it = unknown002();
  while (it != unknown003()) {
    T *element = it;
    it = unknown004(it);
    unknown001(element);
    SoundMemory::allocator_->unknown001(element);
  }
  return this;
}

} // namespace ssd
