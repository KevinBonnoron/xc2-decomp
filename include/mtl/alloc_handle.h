#pragma once
#include <stddef.h>

namespace mtl {

class ALLOC_HANDLE {
public:
  ALLOC_HANDLE() : mHandle(0) {}
  ALLOC_HANDLE(const ALLOC_HANDLE &other) : mHandle(other.mHandle) {}

  bool isValid() const { return mHandle != 0; }

  ALLOC_HANDLE &operator=(const ALLOC_HANDLE &other) {
    mHandle = other.mHandle;
    return *this;
  }

private:
  unsigned int mHandle;
};

} // namespace mtl

void *operator new(size_t size, mtl::ALLOC_HANDLE handle, const char *file, size_t line, int alignment, bool);
