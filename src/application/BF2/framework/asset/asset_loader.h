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

  mtl::ALLOC_HANDLE unknown100;    // Inferred role: handle; original member name unknown.
  mm::mtl::IAllocator *unknown108; // Inferred role: allocator; original member name unknown.
  u32 unknown110;                  // Inferred role: hash; original member name unknown.
  u8 _114[0x120 - 0x114];
};

static_assert(offsetof(AssetLoader, unknown100) == 0x100, "");
static_assert(offsetof(AssetLoader, unknown110) == 0x110, "");
static_assert(sizeof(AssetLoader) == 0x120, "");

} // namespace fw
