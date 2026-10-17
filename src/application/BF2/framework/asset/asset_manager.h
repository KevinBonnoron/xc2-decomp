#pragma once
#include "framework/manager_object.h"
#include "mm_mtl/singleton.h"
#include "mtl/alloc_handle.h"
#include "types.h"

namespace mm {
namespace mtl {
class IAllocator;
} // namespace mtl
} // namespace mm

namespace fw {

class AssetCsvb;
class AssetData;
class AssetLoader;

class AssetManager : public ManagerObject, public mm::mtl::PtrSingleton<AssetManager> {
public:
  static mtl::ALLOC_HANDLE getMemSYS();
  static mtl::ALLOC_HANDLE getMemTMP();
  static u32 getHash(const char *name);
  void addAsset(AssetData *asset);
  void removeAsset(AssetData *asset);
  AssetData *searchAsset(const char *name, AssetData *previous);
  void addCsvb(AssetCsvb *csvb);
  void removeCsvb(AssetCsvb *csvb);
  AssetCsvb *searchCsvb(const char *name, AssetCsvb *previous);
  void addLoader(AssetLoader *loader);
  void removeLoader(AssetLoader *loader);
  AssetLoader *searchLoader(mtl::ALLOC_HANDLE handle, const char *path);
  AssetLoader *searchLoader(mm::mtl::IAllocator *allocator, const char *path);
};

} // namespace fw
