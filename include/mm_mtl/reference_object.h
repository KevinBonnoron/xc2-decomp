#pragma once
#include "mm/mm_std_base.h"

namespace mm {
namespace mtl {

class ReferenceObject {
public:
  ReferenceObject() : m_RefCount(0) {}
  virtual ~ReferenceObject() {}

  void addRef() { m_RefCount++; }

  void release() {
    MM_ASSERT(m_RefCount > 0);
    if (--m_RefCount == 0) {
      delete this;
    }
  }

private:
  int m_RefCount;
};

} // namespace mtl
} // namespace mm
