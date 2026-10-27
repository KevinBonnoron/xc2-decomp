#pragma once
#include <stddef.h>

#include "mm/mm_std_base.h"
#include "mm_mtl/allocator.h"
#include "types.h"

namespace anm {

struct SerialiseArg;

class ReferenceObject {
public:
  explicit ReferenceObject(mm::mtl::IAllocator *pAllocator) : unknown08(0), unknown0a(0xffff), m_pAllocator(pAllocator) { MM_ASSERT(pAllocator); }
  explicit ReferenceObject(const SerialiseArg &arg) {}
  virtual ~ReferenceObject() {}

  void addRef() {
    if (unknown0a) {
      unknown08++;
    }
  }

  void release() {
    if (unknown0a) {
      if (--unknown08 <= 0) {
        MM_ASSERT(m_pAllocator);
        this->~ReferenceObject();
        m_pAllocator->deallocate(this);
      }
    }
  }

  s16 unknown08; // Inferred role: ref count; original member name unknown.
  u16 unknown0a; // Inferred role: shared; original member name unknown.
  mm::mtl::IAllocator *m_pAllocator;
};

static_assert(offsetof(ReferenceObject, unknown08) == 0x08, "");
static_assert(offsetof(ReferenceObject, unknown0a) == 0x0a, "");
static_assert(offsetof(ReferenceObject, m_pAllocator) == 0x10, "");

// Inferred helper: releases a reference and clears the pointer; original name unknown.
template <typename T> void unknown001(T *&object) {
  if (object != nullptr) {
    object->release();
    object = nullptr;
  }
}

} // namespace anm
