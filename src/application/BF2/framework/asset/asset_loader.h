#pragma once
#include "ml/file_res_th.h"

namespace mtl {
class ALLOC_HANDLE;
} // namespace mtl

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
};

} // namespace fw
