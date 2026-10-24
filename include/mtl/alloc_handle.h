#pragma once
#include <stddef.h>

namespace mtl {

class ALLOC_HANDLE {
public:
  ALLOC_HANDLE() : unknown00(0) {}
  ALLOC_HANDLE(const ALLOC_HANDLE &other) : unknown00(other.unknown00) {}

  bool isValid() const { return unknown00 != 0; }
  bool operator==(const ALLOC_HANDLE &other) const { return unknown00 == other.unknown00; }

  ALLOC_HANDLE &operator=(const ALLOC_HANDLE &other) {
    unknown00 = other.unknown00;
    return *this;
  }

private:
  unsigned int unknown00; // Inferred role: handle; original member name unknown.
};

} // namespace mtl

void *operator new(size_t size, mtl::ALLOC_HANDLE handle, const char *file = nullptr, size_t line = 0, int alignment = 4, bool = false);
void *operator new[](size_t size, mtl::ALLOC_HANDLE handle, const char *file = nullptr, size_t line = 0, int alignment = 4, bool = false);
