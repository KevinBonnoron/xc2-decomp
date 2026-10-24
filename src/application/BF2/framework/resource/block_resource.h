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

  mm::mtl::Vector<CommonResource *> unknownb0; // Inferred role: resources; original member name unknown.
  MemHandlebaseAllocator unknownd8;            // Inferred role: resource allocator; original member name unknown.
  bool unknown128;                             // Inferred role: loaded; original member name unknown.
  mtl::ALLOC_HANDLE unknown12c;                // Inferred role: resource handle; original member name unknown.
  LOAD_PRIO unknown130;                        // Inferred role: resource priority; original member name unknown.
};

static_assert(offsetof(BlockResource, unknownb0) == 0xb0, "");
static_assert(offsetof(BlockResource, unknownd8) == 0xd8, "");
static_assert(offsetof(BlockResource, unknown128) == 0x128, "");
static_assert(offsetof(BlockResource, unknown130) == 0x130, "");
static_assert(sizeof(BlockResource) == 0x138, "");

} // namespace fw
