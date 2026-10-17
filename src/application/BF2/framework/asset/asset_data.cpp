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
    asset->handle = handle;
    if (data != nullptr && size != 0) {
      asset->data = mtl::MemManager::allocate(handle, size, 0x1000, false, "no name", 0);
      memcpy(asset->data, data, size);
      asset->size = size;
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
    asset->allocator = allocator;
    if (data != nullptr && size != 0) {
      asset->data = allocator->allocate(size, 0x1000);
      memcpy(asset->data, data, size);
      asset->size = size;
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
    asset->handle = handle;
    if (data != nullptr && size != 0) {
      asset->data = const_cast<void *>(data);
      asset->size = size;
      asset->timeStamp = timeStamp;
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
    asset->allocator = allocator;
    if (data != nullptr && size != 0) {
      asset->data = const_cast<void *>(data);
      asset->size = size;
      asset->timeStamp = timeStamp;
    }

    asset->setName(fileName.c_str());
    asset->addRef();
  }

  return asset;
}

static bool unknown001(const char *name) { // Inferred role: isNotClonable; original function name unknown.
  return strstr(name, ".arc") != nullptr || strstr(name, ".mot") != nullptr || strstr(name, ".pcefb") != nullptr ||
         strstr(name, ".wiefb") != nullptr || strstr(name, ".stp") != nullptr || strstr(name, ".ssp") != nullptr || strstr(name, "effect") != nullptr;
}

AssetData *AssetData::CreateFromCache(mtl::ALLOC_HANDLE handle, const char *name) {
  AssetData *asset = AssetManager::get()->searchAsset(name, nullptr);
  AssetData *source = nullptr;
  while (asset != nullptr) {
    if (asset->handle == handle) {
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
    if (data != nullptr && size != 0) {
      asset->data = mtl::MemManager::allocate(handle, size, 0x1000, false, "no name", 0);
      memcpy(asset->data, data, size);
      asset->size = size;
      asset->timeStamp = timeStamp;
    }

    asset->handle = handle;
    asset->copyName(name);
    asset->hash = hash;
    asset->addRef();
  }

  return asset;
}

AssetData *AssetData::CreateFromCache(mm::mtl::IAllocator *allocator, const char *name) {
  AssetData *source = nullptr;
  for (AssetData *asset = AssetManager::get()->searchAsset(name, nullptr); asset != nullptr; asset = AssetManager::get()->searchAsset(name, asset)) {
    if (asset->allocator == allocator) {
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
    if (data != nullptr && size != 0) {
      asset->data = allocator->allocate(size, 0x1000);
      memcpy(asset->data, data, size);
      asset->size = size;
      asset->timeStamp = timeStamp;
    }

    asset->allocator = allocator;
    asset->copyName(name);
    asset->hash = hash;
    asset->addRef();
  }

  return asset;
}

void *AssetData::LoadFromPacdata(mtl::ALLOC_HANDLE handle, const char *name, int &size) {
  size = 0;
  return nullptr;
}

AssetData::AssetData() : allocator(nullptr), hash(0), size(0), data(nullptr), timeStamp(0) { AssetManager::get()->addAsset(this); }

AssetData::~AssetData() {
  if (data != nullptr) {
    if (allocator != nullptr) {
      allocator->deallocate(data);
    } else {
      mtl::MemManager::deallocate(data, 0, false);
    }

    data = nullptr;
  }

  AssetManager::get()->removeAsset(this);
}

} // namespace fw
