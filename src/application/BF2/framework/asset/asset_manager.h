#pragma once
#include "framework/manager_object.h"
#include "mm_mtl/singleton.h"
#include "mtl/alloc_handle.h"
#include "types.h"

namespace fw {

class AssetData;

class AssetManager : public ManagerObject, public mm::mtl::PtrSingleton<AssetManager> {
public:
  static mtl::ALLOC_HANDLE getMemSYS();
  static mtl::ALLOC_HANDLE getMemTMP();
  static u32 getHash(const char *name);
  void addAsset(AssetData *asset);
  void removeAsset(AssetData *asset);
  AssetData *searchAsset(const char *name, AssetData *previous);
};

} // namespace fw
