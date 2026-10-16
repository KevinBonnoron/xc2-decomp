#pragma once
#include "mm/mm_std_base.h"

namespace mm {
namespace mtl {

template <typename T> class UniquePtr {
public:
  UniquePtr() : _ptr(nullptr) {}
  ~UniquePtr() { reset(); }

  void reset() {
    if (_ptr != nullptr) {
      delete _ptr;
      _ptr = nullptr;
    }
  }

  T *operator->() const {
    MM_ASSERT(_ptr != 0);
    return _ptr;
  }

  T &operator*() const {
    MM_ASSERT(_ptr != 0);
    return *_ptr;
  }

  T *get() const { return _ptr; }

private:
  T *_ptr;
};

} // namespace mtl
} // namespace mm
