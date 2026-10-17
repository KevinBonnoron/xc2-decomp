#pragma once
#include <stddef.h>

#include "framework/manager_object.h"
#include "mm_mtl/singleton.h"
#include "mm_mtl/vector.h"
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
struct UpdateInfo;

class AssetManager : public ManagerObject, public mm::mtl::PtrSingleton<AssetManager> {
public:
  static mtl::ALLOC_HANDLE getMemSYS();
  static mtl::ALLOC_HANDLE getMemTMP();
  static u32 getHash(const char *name);
  AssetManager(mm::mtl::IAllocator *allocator, u32 capacity);
  ~AssetManager() override;
  void addAsset(AssetData *asset);
  void removeAsset(AssetData *asset);
  AssetData *searchAsset(mtl::ALLOC_HANDLE handle, const char *name);
  AssetData *searchAsset(mm::mtl::IAllocator *allocator, const char *name);
  AssetData *searchAsset(const char *name, AssetData *previous);
  void addCsvb(AssetCsvb *csvb);
  void removeCsvb(AssetCsvb *csvb);
  AssetCsvb *searchCsvb(mtl::ALLOC_HANDLE handle, const char *name);
  AssetCsvb *searchCsvb(mm::mtl::IAllocator *allocator, const char *name);
  AssetCsvb *searchCsvb(const char *name, AssetCsvb *previous);
  void addLoader(AssetLoader *loader);
  void removeLoader(AssetLoader *loader);
  AssetLoader *searchLoader(mtl::ALLOC_HANDLE handle, const char *path);
  AssetLoader *searchLoader(mm::mtl::IAllocator *allocator, const char *path);
  const char *getName() const override { return "AssetManager"; }
  virtual void update(const UpdateInfo &info) {}

  mm::mtl::Vector<AssetData *> assets;
  mm::mtl::Vector<AssetCsvb *> csvbs;
  mm::mtl::Vector<AssetLoader *> loaders;
};

static_assert(offsetof(AssetManager, assets) == 0x18, "");
static_assert(offsetof(AssetManager, csvbs) == 0x40, "");
static_assert(offsetof(AssetManager, loaders) == 0x68, "");

} // namespace fw
