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

template <typename T> class IntrusivePtr {
public:
  IntrusivePtr() : mPtr(nullptr) {}

  ~IntrusivePtr() {
    if (mPtr != nullptr) {
      mPtr->release();
    }
  }

  IntrusivePtr &operator=(T *ptr) {
    if (ptr != nullptr) {
      ptr->addRef();
    }
    T *old = mPtr;
    mPtr = ptr;
    if (old != nullptr) {
      old->release();
    }
    return *this;
  }

  T *get() const { return mPtr; }

private:
  T *mPtr;
};

} // namespace mtl
} // namespace mm
