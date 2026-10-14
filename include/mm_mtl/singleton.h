#pragma once
#include "mm/mm_std_base.h"

namespace mm {
namespace mtl {

template <typename T> class PtrSingleton {
public:
  PtrSingleton() {
    MM_ASSERT(get() == 0);
    sys() = static_cast<T *>(this);
  }

  virtual ~PtrSingleton() { sys() = nullptr; }

  static T *get() { return sys(); }

  static T *&sys() {
    static T *s_instance;
    return s_instance;
  }
};

} // namespace mtl
} // namespace mm
