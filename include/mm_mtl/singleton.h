#pragma once

namespace mm {
namespace mtl {

template <typename T> class PtrSingleton {
public:
  virtual ~PtrSingleton() {}

  static T *get() { return sys(); }

  static T *&sys() {
    static T *s_instance;
    return s_instance;
  }
};

} // namespace mtl
} // namespace mm
