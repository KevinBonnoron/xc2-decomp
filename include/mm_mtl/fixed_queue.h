#pragma once
#include <stddef.h>

namespace mm {
namespace mtl {

template <typename T, size_t N> class FixedQueue {
public:
  FixedQueue() : mSize(0), mFront(0) {}

  size_t size() const { return mSize; }

private:
  alignas(T) unsigned char mBuffer[sizeof(T) * N];
  size_t mSize;
  size_t mFront;
};

} // namespace mtl
} // namespace mm
