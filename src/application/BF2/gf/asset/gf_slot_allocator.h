#pragma once
#include <stddef.h>

#include "gf/asset/gf_size_alloc.h"
#include "mm_mtl/allocator.h"
#include "mm_mtl/fixstr.h"
#include "types.h"

namespace gf {

constexpr size_t SLOT_ALIGNMENT = 0x2000;

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

  mm::mtl::IAllocator *unknown08; // Inferred role: parent; original member name unknown.
  void *unknown10;                // Inferred role: buffer; original member name unknown.
  GfSizeAlloc unknown18;          // Inferred role: size alloc; original member name unknown.
  mm::mtl::FixStr<64> m_name;
  bool unknown2ec; // Inferred role: use debug memory; original member name unknown.
};

static_assert(offsetof(GfSlotAllocator, unknown08) == 0x08, "");
static_assert(offsetof(GfSlotAllocator, unknown10) == 0x10, "");
static_assert(offsetof(GfSlotAllocator, unknown18) == 0x18, "");
static_assert(offsetof(GfSlotAllocator, m_name) == 0x2a8, "");
static_assert(offsetof(GfSlotAllocator, unknown2ec) == 0x2ec, "");
static_assert(sizeof(GfSlotAllocator) == 0x2f0, "");

} // namespace gf
