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
  ReferenceObject(mtl::IAllocator *allocator) : unknown08(0), m_allocator(allocator) { MM_ASSERT(allocator); }
  virtual ~ReferenceObject() {}

  void addRef() { unknown08++; }
  s32 getRefCount() const { return unknown08; }

  s32 unknown08; // Inferred role: ref count; original member name unknown.
  mtl::IAllocator *m_allocator;
};

} // namespace threading
} // namespace mm
