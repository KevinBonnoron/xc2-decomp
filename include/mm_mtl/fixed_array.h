#pragma once
#include <stddef.h>

namespace mm {
namespace mtl {

template <typename T, size_t N> class FixedArray {
public:
  T &operator[](size_t index) { return mData[index]; }
  T *begin() { return mData; }
  T *end() { return mData + N; }
  const T &operator[](size_t index) const { return mData[index]; }
  size_t size() const { return N; }

private:
  T mData[N];
};

} // namespace mtl
} // namespace mm
