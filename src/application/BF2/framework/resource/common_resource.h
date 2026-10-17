#pragma once
#include <stddef.h>

#include "framework/resource/resource_object.h"
#include "types.h"

namespace mtl {
class ALLOC_HANDLE;
} // namespace mtl

namespace mm {
namespace mtl {
class IAllocator;
} // namespace mtl
} // namespace mm

namespace fw {

class AssetData;
class AssetLoader;

class CommonResource : public ResourceObject {
public:
  enum State {
    STATE_NONE = 0,
    STATE_LOADING = 1,
    STATE_LOADED = 2,
  };

  static CommonResource *search(mtl::ALLOC_HANDLE handle, const char *path);
  static CommonResource *search(mm::mtl::IAllocator *allocator, const char *path);
  static CommonResource *request_detail(mtl::ALLOC_HANDLE handle, const char *path, int priority, bool isSafe, bool isBlock);
  void updateBlock();
  static CommonResource *request_detail(mm::mtl::IAllocator *allocator, const char *path, int priority, bool isSafe, bool isBlock);
  static CommonResource *request(mtl::ALLOC_HANDLE handle, const char *path, int priority, bool isSafe);
  static CommonResource *request(mm::mtl::IAllocator *allocator, const char *path, int priority, bool isSafe);
  static CommonResource *blockRequest(mtl::ALLOC_HANDLE handle, const char *path, bool isSafe);
  static CommonResource *blockRequest(mm::mtl::IAllocator *allocator, const char *path, bool isSafe);
  CommonResource(mtl::ALLOC_HANDLE handle, LOAD_PRIO priority, u32 type, int option);
  CommonResource(mm::mtl::IAllocator *allocator, LOAD_PRIO priority, u32 type, int option);
  ~CommonResource() override;
  void update() override;
  const char *getMemName();
  bool valid() const override;
  void *getAssetData();
  int getAssetSize() const;
  virtual const char *getAssetName() const;
  u64 getAssetTimeStamp() const;

  State state;
  bool isSafe;
  AssetLoader *loader;
  AssetData *asset;
};

static_assert(offsetof(CommonResource, state) == 0xb0, "");
static_assert(offsetof(CommonResource, loader) == 0xb8, "");
static_assert(sizeof(CommonResource) == 0xc8, "");

} // namespace fw
