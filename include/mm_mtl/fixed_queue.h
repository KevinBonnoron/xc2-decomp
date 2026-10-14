#pragma once
#include "mm/mm_std_base.h"
#include <stddef.h>

namespace mm {
namespace mtl {

template <typename T, size_t N> class FixedQueue {
public:
  FixedQueue() : mSize(0), mFront(0) {}

  size_t size() const { return mSize; }
  bool full() const { return mSize == N; }

  void push(const T &value) {
    MM_ASSERT(!full());
    mBuffer[(mFront + mSize) % N] = value;
    mSize++;
  }

private:
  T mBuffer[N];
  size_t mSize;
  size_t mFront;
};

} // namespace mtl
} // namespace mm
