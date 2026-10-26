#pragma once
#include "mm_mtl/allocator.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/singleton.h"
#include "mtl/alloc_handle.h"
#include <stddef.h>

namespace gf {

struct GfSetupParam;

class GfAllocator : public mm::mtl::IAllocator {
public:
  GfAllocator();
  GfAllocator(mtl::ALLOC_HANDLE handle);
  ~GfAllocator() {}
  void setMemHandle(mtl::ALLOC_HANDLE handle);
  mtl::ALLOC_HANDLE getMemHandle() const;
  void *allocate(size_t size, size_t alignment) override;
  void *allocateProgLarge(size_t size, size_t alignment);
  void deallocate(void *pointer) override;
  bool deallocateProgLarge(void *pointer);
  const char *getName() const override;

  mtl::ALLOC_HANDLE unknown08;   // Inferred role: handle; original member name unknown.
  mm::mtl::FixStr<64> unknown0c; // Inferred role: name; original member name unknown.
};

static_assert(offsetof(GfAllocator, unknown08) == 0x08, "");
static_assert(offsetof(GfAllocator, unknown0c) == 0x0c, "");
static_assert(sizeof(GfAllocator) == 0x50, "");

enum ALLOCATOR {
  ALLOCATOR_DEFAULT = 0,
  ALLOCATOR_SYSTEM = 1,
  ALLOCATOR_SCRIPT = 2,
  ALLOCATOR_ASSET = 3,
  ALLOCATOR_BDAT = 4,
  ALLOCATOR_ANIMATION = 7,
  ALLOCATOR_DEBUG = 10,
  ALLOCATOR_UNKNOWN0B = 11, // Inferred role: slot allocator; original name unknown.
  ALLOCATOR_MAX = 12,
};

class GfAllocatorManager : public mm::mtl::PtrSingleton<GfAllocatorManager> {
public:
  GfAllocatorManager();
  ~GfAllocatorManager();
  void initialize(const GfSetupParam &param);
  void finalize();
  static GfAllocator *getAllocator(ALLOCATOR allocator);
  void buildAllocator(ALLOCATOR allocator, mtl::ALLOC_HANDLE handle);
  void destroyAllocator(ALLOCATOR allocator, mtl::ALLOC_HANDLE handle);

  bool unknown08;                       // Inferred role: initialized; original member name unknown.
  GfAllocator unknown10[ALLOCATOR_MAX]; // Inferred role: allocators; original member name unknown.
};

static_assert(offsetof(GfAllocatorManager, unknown08) == 0x08, "");
static_assert(offsetof(GfAllocatorManager, unknown10) == 0x10, "");
static_assert(sizeof(GfAllocatorManager) == 0x3d0, "");

GfAllocator *getAllocator(ALLOCATOR allocator);

} // namespace gf

void *operator new(size_t size, gf::GfAllocator *allocator, const char *file, size_t line, int alignment);
void *operator new[](size_t size, gf::GfAllocator *allocator, const char *file, size_t line, int alignment);
