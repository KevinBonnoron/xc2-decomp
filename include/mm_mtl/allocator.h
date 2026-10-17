#pragma once
#include <stddef.h>

namespace mm {
namespace mtl {

class IAllocator {
public:
  virtual ~IAllocator() {}
  virtual void *allocate(size_t size, size_t alignment) = 0;
  virtual void deallocate(void *pointer) = 0;
  virtual const char *getName() const { return "IAllocator"; }
};

} // namespace mtl
} // namespace mm
