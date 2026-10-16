#pragma once
#include "mm/mm_std_base.h"
#include <stddef.h>

namespace mm {
namespace mtl {

template <typename T, size_t N> class FixedVector {
public:
  FixedVector() : mSize(0) {}
  ~FixedVector() { clear(); }

  T &operator[](size_t index) {
    MM_ASSERT(index < size());
    return *reinterpret_cast<T *>(mBuffer + index * sizeof(T));
  }

  const T &operator[](size_t index) const {
    MM_ASSERT(index < size());
    return *reinterpret_cast<const T *>(mBuffer + index * sizeof(T));
  }

  size_t size() const { return mSize; }
  size_t capacity() const { return N; }
  bool empty() const { return mSize == 0; }
  T *begin() { return reinterpret_cast<T *>(mBuffer); }
  const T *begin() const { return reinterpret_cast<const T *>(mBuffer); }
  T *end() { return begin() + size(); }
  const T *end() const { return begin() + size(); }

  void clear() {
    while (mSize != 0) {
      reinterpret_cast<T *>(mBuffer + --mSize * sizeof(T))->~T();
    }
  }

  void push_back(const T &value) {
    MM_ASSERT(size() < capacity());
    *reinterpret_cast<T *>(mBuffer + mSize * sizeof(T)) = value;
    mSize++;
  }

private:
  alignas(T) unsigned char mBuffer[sizeof(T) * N];
  size_t mSize;
};

} // namespace mtl
} // namespace mm
