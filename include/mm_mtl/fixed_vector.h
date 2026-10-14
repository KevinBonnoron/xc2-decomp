#pragma once
#include "mm/mm_std_base.h"
#include <stddef.h>

namespace mm {
namespace mtl {

template <typename T, size_t N> class FixedVector {
public:
  T &operator[](size_t index) { return mData[index]; }
  const T &operator[](size_t index) const { return mData[index]; }
  size_t size() const { return mSize; }
  size_t capacity() const { return N; }
  bool empty() const { return mSize == 0; }

  void push_back(const T &value) {
    MM_ASSERT(size() < capacity());
    mData[mSize] = value;
    mSize++;
  }

private:
  T mData[N];
  size_t mSize;
};

} // namespace mtl
} // namespace mm
