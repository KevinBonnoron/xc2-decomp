#pragma once
#include <stddef.h>

#include "mtl/alloc_handle.h"
#include "mtl/mem_manager.h"

namespace ml {

template <typename T> class StlCustomAllocator {
public:
  typedef T value_type;

  StlCustomAllocator(mtl::ALLOC_HANDLE handle) : m_handle(handle) {}
  template <typename U> StlCustomAllocator(const StlCustomAllocator<U> &other) : m_handle(other.m_handle) {}

  T *allocate(size_t count) { return static_cast<T *>(mtl::MemManager::allocate(m_handle, count * sizeof(T), 8, false, "no name", 0)); }
  void deallocate(T *pointer, size_t) { mtl::MemManager::deallocate(pointer, 0, false); }

  mtl::ALLOC_HANDLE m_handle;
};

} // namespace ml
