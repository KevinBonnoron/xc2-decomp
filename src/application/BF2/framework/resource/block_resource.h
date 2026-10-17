#pragma once
#include <stddef.h>

#include "framework/memory/allocator.h"
#include "framework/resource/resource_object.h"
#include "mm_mtl/vector.h"
#include "mtl/alloc_handle.h"

namespace fw {

class CommonResource;

class BlockResource : public ResourceObject {
public:
  static BlockResource *search(mtl::ALLOC_HANDLE handle, const char *path);
  static BlockResource *request(mtl::ALLOC_HANDLE handle, const char *path, LOAD_PRIO priority);
  BlockResource(mtl::ALLOC_HANDLE handle, LOAD_PRIO priority);
  ~BlockResource() override;
  void update() override;
  bool valid() const override;
  CommonResource *findLoadedResource(const char *path) const;
  void *getAssetData(const char *path);
  int getAssetSize(const char *path) const;
  const char *getAssetName(const char *path) const;
  void addAssetFile(const char *path, bool isSafe);

  mm::mtl::Vector<CommonResource *> resources;
  MemHandlebaseAllocator resourceAllocator;
  bool loaded;
  mtl::ALLOC_HANDLE resourceHandle;
  LOAD_PRIO resourcePriority;
};

static_assert(offsetof(BlockResource, resources) == 0xb0, "");
static_assert(offsetof(BlockResource, resourceAllocator) == 0xd8, "");
static_assert(offsetof(BlockResource, loaded) == 0x128, "");
static_assert(offsetof(BlockResource, resourcePriority) == 0x130, "");
static_assert(sizeof(BlockResource) == 0x138, "");

} // namespace fw
