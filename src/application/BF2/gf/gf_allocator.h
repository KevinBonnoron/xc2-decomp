#pragma once
#include "mm_mtl/allocator.h"
#include "mtl/alloc_handle.h"
#include <stddef.h>

namespace gf {

class GfAllocator : public mm::mtl::IAllocator {
public:
  virtual void *allocate(size_t size, size_t alignment);
  virtual void deallocate(void *pointer);
  virtual const char *getName() const;
  mtl::ALLOC_HANDLE getMemHandle() const;
};

enum ALLOCATOR {
  ALLOCATOR_DEFAULT = 0,
  ALLOCATOR_SYSTEM = 1,
  ALLOCATOR_BDAT = 4,
  ALLOCATOR_DEBUG = 10,
};

GfAllocator *getAllocator(ALLOCATOR allocator);

} // namespace gf

void *operator new(size_t size, gf::GfAllocator *allocator, const char *file, size_t line, int alignment);
