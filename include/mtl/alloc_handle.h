#pragma once

namespace mtl {

class ALLOC_HANDLE {
public:
  ALLOC_HANDLE() : mHandle(0) {}
  ALLOC_HANDLE(const ALLOC_HANDLE &other) : mHandle(other.mHandle) {}

  ALLOC_HANDLE &operator=(const ALLOC_HANDLE &other) {
    mHandle = other.mHandle;
    return *this;
  }

private:
  unsigned int mHandle;
};

} // namespace mtl
