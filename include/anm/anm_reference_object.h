#pragma once
#include <stddef.h>

#include "mm/mm_std_base.h"
#include "mm_mtl/allocator.h"
#include "types.h"

namespace anm {

class ReferenceObject {
public:
  explicit ReferenceObject(mm::mtl::IAllocator *pAllocator) : m_refCount(0), m_isShared(0xffff), m_pAllocator(pAllocator) { MM_ASSERT(pAllocator); }
  virtual ~ReferenceObject() {}

  void addRef() {
    if (m_isShared) {
      m_refCount++;
    }
  }

  void release() {
    if (m_isShared) {
      if (--m_refCount <= 0) {
        MM_ASSERT(m_pAllocator);
        this->~ReferenceObject();
        m_pAllocator->deallocate(this);
      }
    }
  }

  s16 m_refCount;
  u16 m_isShared;
  mm::mtl::IAllocator *m_pAllocator;
};

static_assert(offsetof(ReferenceObject, m_refCount) == 0x08, "");
static_assert(offsetof(ReferenceObject, m_isShared) == 0x0a, "");
static_assert(offsetof(ReferenceObject, m_pAllocator) == 0x10, "");

} // namespace anm
