#pragma once
#include <stddef.h>

#include "gf/asset/gf_size_alloc.h"
#include "mm_mtl/allocator.h"
#include "mm_mtl/fixstr.h"
#include "types.h"

namespace gf {

class GfSlotAllocator : public mm::mtl::IAllocator {
public:
  GfSlotAllocator();
  ~GfSlotAllocator() override;
  void destroy();
  size_t getBlockSize() const;
  void setupSizeAlloc(const char *name, mm::mtl::IAllocator *allocator, size_t size, size_t alignment, bool useDebugMemory);
  void setup(const char *name, GfSlotAllocator *allocator, size_t size, size_t alignment, bool useDebugMemory);
  void resize(size_t size);
  void *allocate(size_t size, size_t alignment) override;
  void deallocate(void *pointer) override;
  bool empty() const;
  u32 getAllocs() const;
  void *getBuffer();
  size_t getBufferSize() const;
  const char *getName() const override;

  mm::mtl::IAllocator *parent;
  void *buffer;
  GfSizeAlloc sizeAlloc;
  mm::mtl::FixStr<64> name;
  bool useDebugMemory;
};

static_assert(offsetof(GfSlotAllocator, parent) == 0x08, "");
static_assert(offsetof(GfSlotAllocator, buffer) == 0x10, "");
static_assert(offsetof(GfSlotAllocator, sizeAlloc) == 0x18, "");
static_assert(offsetof(GfSlotAllocator, name) == 0x2a8, "");
static_assert(offsetof(GfSlotAllocator, useDebugMemory) == 0x2ec, "");
static_assert(sizeof(GfSlotAllocator) == 0x2f0, "");

} // namespace gf
