#pragma once
#include "mm/mm_std_base.h"
#include "mm_mtl/allocator.h"
#include "types.h"

namespace mm {

namespace threading {

class ReferenceObject {
public:
  ReferenceObject(mtl::IAllocator *allocator) : unknown08(0), m_allocator(allocator) { MM_ASSERT(allocator); }
  virtual ~ReferenceObject() {}

  void addRef() { unknown08++; }

  void release() {
    if ((--unknown08 & 0xffff) == 0) {
      MM_ASSERT(m_allocator);
      this->~ReferenceObject();
      m_allocator->deallocate(this);
    }
  }
  s32 getRefCount() const { return unknown08; }

  s32 unknown08; // Inferred role: ref count; original member name unknown.
  mtl::IAllocator *m_allocator;
};

} // namespace threading
} // namespace mm
