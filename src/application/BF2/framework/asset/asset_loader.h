#pragma once
#include <stddef.h>

#include "ml/file_res_th.h"
#include "mtl/alloc_handle.h"
#include "types.h"

namespace mm {
namespace mtl {
class IAllocator;
} // namespace mtl
} // namespace mm

namespace fw {

class AssetLoader : public ml::FileResTh {
public:
  static AssetLoader *Create(mtl::ALLOC_HANDLE handle, const char *path, int priority, int option);
  static AssetLoader *Create(mm::mtl::IAllocator *allocator, const char *path, int priority, int option);
  AssetLoader();
  ~AssetLoader() override;

  mtl::ALLOC_HANDLE handle;
  mm::mtl::IAllocator *allocator;
  u32 hash;
  u8 _114[0x120 - 0x114];
};

static_assert(offsetof(AssetLoader, handle) == 0x100, "");
static_assert(offsetof(AssetLoader, hash) == 0x110, "");
static_assert(sizeof(AssetLoader) == 0x120, "");

} // namespace fw
