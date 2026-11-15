#pragma once
#include <new>

#include "mm/mm_std_base.h"
#include "mm_mtl/allocator.h"
#include "mm_mtl/intrusive_list.h"

namespace wnd {

// Element pool of the broad phase octree; m_freeList and m_useList are named by the assertions of unknown002.
template <typename T> class PoolObjectMemory {
public:
  ~PoolObjectMemory();

  T *alloc();
  void unknown002(mm::mtl::IAllocator *allocator);

  mm::mtl::IAllocator *unknown00;
  mm::mtl::IntrusiveList<T> m_useList;
  mm::mtl::IntrusiveList<T> m_freeList;
};

static_assert(sizeof(PoolObjectMemory<void>) == 0x38, "");

// Inferred role: sets the allocator of an empty pool; original name unknown. Not a constructor. The asserts sit in the
// BroadPhazeOctree constructor (0x71009866d0) at 0x71009868ec (line 102) and 0x7100986910 (line 103), after its octree
// setup (setAABB at 0x71009868a4). The form with the asserts as a constructor body does not match (157 instructions).
// __LINE__ must be 102 and 103 as in the original header: they are the line arguments of the asserts.
#line 101
template <typename T> inline void PoolObjectMemory<T>::unknown002(mm::mtl::IAllocator *allocator) {
  MM_ASSERT(m_freeList.empty());
  MM_ASSERT(m_useList.empty());
  unknown00 = allocator;
}

// Reuses a node of the free list, else allocates a new one; returns nullptr when the pool has no allocator.
template <typename T> T *PoolObjectMemory<T>::alloc() {
  if (!m_freeList.empty()) {
    T *object = m_freeList.begin().get();
    m_freeList.erase(object);
    m_useList.push_back(object);
    return object;
  }
  if (unknown00 == nullptr) {
    return nullptr;
  }
  T *object = new (unknown00->allocate(sizeof(T), 16)) T();
  m_useList.push_back(object);
  return object;
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
