#pragma once
#include "mm/mm_std_base.h"

namespace mm {
namespace mtl {

template <typename T> struct UniquePtrDefaultDeleter {
  void operator()(T *ptr) const { delete ptr; }
};

template <typename T, typename Deleter = UniquePtrDefaultDeleter<T>> class UniquePtr {
  struct _safe_bool_helper {
    void safe_bool_function() const {}
  };
  typedef void (_safe_bool_helper::*safe_bool_type)() const;

public:
  UniquePtr() : _ptr(nullptr) {}
  explicit UniquePtr(T *ptr) : _ptr(ptr) {}
  ~UniquePtr() { reset(); }

  void reset() {
    if (_ptr != nullptr) {
      delete _ptr;
      _ptr = nullptr;
    }
  }

  // __LINE__ must be 132 as in the original header: it is the line argument of the assert.
#line 131
  T *operator->() const {
    MM_ASSERT(_ptr != 0);
    return _ptr;
  }

  T &operator*() const {
    MM_ASSERT(_ptr != 0);
    return *_ptr;
  }

  T *get() const { return _ptr; }

  operator safe_bool_type() const { return _ptr != nullptr ? &_safe_bool_helper::safe_bool_function : nullptr; }

private:
  T *_ptr;
};

} // namespace mtl
} // namespace mm
