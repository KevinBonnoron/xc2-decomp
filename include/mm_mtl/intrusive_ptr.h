#pragma once
#include "mm/mm_std_base.h"

namespace mm {
namespace mtl {

template <typename T> class IntrusivePtr {
public:
  IntrusivePtr() : mPtr(nullptr) {}

  IntrusivePtr(T *ptr) : mPtr(ptr) {
    if (mPtr != nullptr) {
      mPtr->addRef();
    }
  }

  ~IntrusivePtr() {
    if (mPtr != nullptr) {
      mPtr->release();
    }
  }

  IntrusivePtr &operator=(T *ptr) {
    IntrusivePtr(ptr).swap(*this);
    return *this;
  }

  void swap(IntrusivePtr &other) {
    T *ptr = mPtr;
    mPtr = other.mPtr;
    other.mPtr = ptr;
  }

  T *operator->() const {
    if (mPtr == 0) {
      mm::MMStdBase::mmAssert("_ptr != 0", __FILE__, __LINE__);
    }

    return mPtr;
  }

  T *get() const { return mPtr; }

private:
  T *mPtr;
};

} // namespace mtl
} // namespace mm
