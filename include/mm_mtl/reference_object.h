#pragma once
#include "mm/mm_std_base.h"

namespace mm {
namespace mtl {

class ReferenceObject {
public:
  ReferenceObject() : m_RefCount(0) {}
  virtual ~ReferenceObject() {}

  void addRef() { m_RefCount++; }

  // __LINE__ must be 60 as in the original header: it is the line argument of the assert.
#line 59
  void release() {
    MM_ASSERT(m_RefCount > 0);
    if (--m_RefCount == 0) {
      delete this;
    }
  }

  int getRefCount() const { return m_RefCount; }

private:
  int m_RefCount;
};

template <typename T> void safeRelease(T *&object) {
  if (object != nullptr) {
    object->release();
    object = nullptr;
  }
}

} // namespace mtl
} // namespace mm
