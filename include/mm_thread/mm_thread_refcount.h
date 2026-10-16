#pragma once
#include "mm/mm_std_base.h"
#include "types.h"

namespace mm {
namespace mtl {
class IAllocator;
} // namespace mtl

namespace threading {

class ReferenceObject {
public:
  ReferenceObject(mtl::IAllocator *allocator) : m_refCount(0), m_allocator(allocator) { MM_ASSERT(allocator); }
  virtual ~ReferenceObject() {}

  void addRef() { m_refCount++; }
  s32 getRefCount() const { return m_refCount; }

  s32 m_refCount;
  mtl::IAllocator *m_allocator;
};

} // namespace threading
} // namespace mm
