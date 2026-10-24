#include "framework/asset/asset_data.h"

#include <string.h>

#include "framework/asset/asset_manager.h"
#include "ml/dev_file_th.h"
#include "mm_mtl/allocator.h"
#include "mtl/mem_manager.h"

namespace fw {

AssetData *AssetData::CreateFromMemory(mtl::ALLOC_HANDLE handle, const void *data, u32 size, const char *name) {
  mm::mtl::FixStr<256> fileName;
  ml::DevFileTh::normalizeDvdFileName(fileName, name);
  AssetData *asset = new (AssetManager::getMemSYS()) AssetData();
  if (asset != nullptr) {
    asset->unknown0c = handle;
    if (data != nullptr && size != 0) {
      asset->unknown20 = mtl::MemManager::allocate(handle, size, 0x1000, false, "no name", 0);
      memcpy(asset->unknown20, data, size);
      asset->unknown1c = size;
    }

    asset->setName(fileName.c_str());
    asset->addRef();
  }

  return asset;
}

AssetData *AssetData::CreateFromMemory(mm::mtl::IAllocator *allocator, const void *data, u32 size, const char *name) {
  mm::mtl::FixStr<256> fileName;
  ml::DevFileTh::normalizeDvdFileName(fileName, name);
  AssetData *asset = new (AssetManager::getMemSYS()) AssetData();
  if (asset != nullptr) {
    asset->unknown10 = allocator;
    if (data != nullptr && size != 0) {
      asset->unknown20 = allocator->allocate(size, 0x1000);
      memcpy(asset->unknown20, data, size);
      asset->unknown1c = size;
    }

    asset->setName(fileName.c_str());
    asset->addRef();
  }

  return asset;
}

AssetData *AssetData::AssignFromMemory(mtl::ALLOC_HANDLE handle, const void *data, u32 size, const char *name, u64 timeStamp) {
  mm::mtl::FixStr<256> fileName;
  ml::DevFileTh::normalizeDvdFileName(fileName, name);
  AssetData *asset = new (AssetManager::getMemSYS()) AssetData();
  if (asset != nullptr) {
    asset->unknown0c = handle;
    if (data != nullptr && size != 0) {
      asset->unknown20 = const_cast<void *>(data);
      asset->unknown1c = size;
      asset->unknown28 = timeStamp;
    }

    asset->setName(fileName.c_str());
    asset->addRef();
  }

  return asset;
}

AssetData *AssetData::AssignFromMemory(mm::mtl::IAllocator *allocator, const void *data, u32 size, const char *name, u64 timeStamp) {
  mm::mtl::FixStr<256> fileName;
  ml::DevFileTh::normalizeDvdFileName(fileName, name);
  AssetData *asset = new (AssetManager::getMemSYS()) AssetData();
  if (asset != nullptr) {
    asset->unknown10 = allocator;
    if (data != nullptr && size != 0) {
      asset->unknown20 = const_cast<void *>(data);
      asset->unknown1c = size;
      asset->unknown28 = timeStamp;
    }

    asset->setName(fileName.c_str());
    asset->addRef();
  }

  return asset;
}

static bool unknown001(const char *name) { // Inferred role: isNotClonable; original function name unknown.
  return strstr(name, ".arc") != nullptr || strstr(name, ".mot") != nullptr || strstr(name, ".pcefb") != nullptr || strstr(name, ".wiefb") != nullptr || strstr(name, ".stp") != nullptr ||
         strstr(name, ".ssp") != nullptr || strstr(name, "effect") != nullptr;
}

AssetData *AssetData::CreateFromCache(mtl::ALLOC_HANDLE handle, const char *name) {
  AssetData *asset = AssetManager::get()->searchAsset(name, nullptr);
  AssetData *source = nullptr;
  while (asset != nullptr) {
    if (asset->unknown0c == handle) {
      asset->addRef();
      return asset;
    }

    if (!unknown001(name)) {
      source = asset;
    }

    asset = AssetManager::get()->searchAsset(name, asset);
  }

  if (source != nullptr) {
    return source->Clone(handle);
  }

  return nullptr;
}

AssetData *AssetData::Clone(mtl::ALLOC_HANDLE handle) const {
  AssetData *asset = new (AssetManager::getMemSYS()) AssetData();
  if (asset != nullptr) {
    if (unknown20 != nullptr && unknown1c != 0) {
      asset->unknown20 = mtl::MemManager::allocate(handle, unknown1c, 0x1000, false, "no name", 0);
      memcpy(asset->unknown20, unknown20, unknown1c);
      asset->unknown1c = unknown1c;
      asset->unknown28 = unknown28;
    }

    asset->unknown0c = handle;
    asset->copyName(unknown30);
    asset->unknown18 = unknown18;
    asset->addRef();
  }

  return asset;
}

AssetData *AssetData::CreateFromCache(mm::mtl::IAllocator *allocator, const char *name) {
  AssetData *source = nullptr;
  for (AssetData *asset = AssetManager::get()->searchAsset(name, nullptr); asset != nullptr; asset = AssetManager::get()->searchAsset(name, asset)) {
    if (asset->unknown10 == allocator) {
      asset->addRef();
      return asset;
    }

    if (!unknown001(name)) {
      source = asset;
    }
  }

  if (source != nullptr) {
    return source->Clone(allocator);
  }

  return nullptr;
}

AssetData *AssetData::Clone(mm::mtl::IAllocator *allocator) const {
  AssetData *asset = new (AssetManager::getMemSYS()) AssetData();
  if (asset != nullptr) {
    if (unknown20 != nullptr && unknown1c != 0) {
      asset->unknown20 = allocator->allocate(unknown1c, 0x1000);
      memcpy(asset->unknown20, unknown20, unknown1c);
      asset->unknown1c = unknown1c;
      asset->unknown28 = unknown28;
    }

    asset->unknown10 = allocator;
    asset->copyName(unknown30);
    asset->unknown18 = unknown18;
    asset->addRef();
  }

  return asset;
}

void *AssetData::LoadFromPacdata(mtl::ALLOC_HANDLE handle, const char *name, int &size) {
  size = 0;
  return nullptr;
}

AssetData::AssetData() : unknown10(nullptr), unknown18(0), unknown1c(0), unknown20(nullptr), unknown28(0) { AssetManager::get()->addAsset(this); }

AssetData::~AssetData() {
  if (unknown20 != nullptr) {
    if (unknown10 != nullptr) {
      unknown10->deallocate(unknown20);
    } else {
      mtl::MemManager::deallocate(unknown20, 0, false);
    }

    unknown20 = nullptr;
  }

  AssetManager::get()->removeAsset(this);
}

} // namespace fw
