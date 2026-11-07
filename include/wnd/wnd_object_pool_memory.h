#pragma once
#include "mm/mm_std_base.h"
#include "mm_mtl/allocator.h"
#include "mm_mtl/intrusive_list.h"

namespace wnd {

// Element pool of the broad phase octree; m_freeList and m_useList are named by the constructor assertions.
template <typename T> class PoolObjectMemory {
public:
  explicit PoolObjectMemory(mm::mtl::IAllocator *allocator);
  ~PoolObjectMemory();

  T *alloc();

  mm::mtl::IAllocator *unknown00;
  mm::mtl::IntrusiveList<T> m_useList;
  mm::mtl::IntrusiveList<T> m_freeList;
};

static_assert(sizeof(PoolObjectMemory<void>) == 0x38, "");

// __LINE__ must be 102 and 103 as in the original header: they are the line arguments of the asserts.
#line 101
template <typename T> inline PoolObjectMemory<T>::PoolObjectMemory(mm::mtl::IAllocator *allocator) {
  MM_ASSERT(m_freeList.empty());
  MM_ASSERT(m_useList.empty());
  unknown00 = allocator;
}

// The game unlinks and frees the nodes of both lists, freeing-list first.
template <typename T> inline PoolObjectMemory<T>::~PoolObjectMemory() {
  if (unknown00 == nullptr) {
    return;
  }
  while (!m_freeList.empty()) {
    T *node = m_freeList.begin().get();
    m_freeList.erase(node);
    unknown00->deallocate(node);
  }
  while (!m_useList.empty()) {
    T *node = m_useList.begin().get();
    m_useList.erase(node);
    unknown00->deallocate(node);
  }
}

} // namespace wnd
