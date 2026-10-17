#include "framework/asset/asset_manager.h"

#include <string.h>

#include "framework/asset/asset_csvb.h"
#include "framework/asset/asset_data.h"
#include "framework/asset/asset_loader.h"
#include "ml/dev_file_th.h"
#include "mm_mtl/algorithm.h"
#include "mm_mtl/fixstr.h"

#include "framework/framework.h"
#include "framework/memory/framework_memory.h"
#include "mm_mtl/hash.h"

namespace fw {

mtl::ALLOC_HANDLE AssetManager::getMemSYS() { return Framework::getMemHandle(); }

mtl::ALLOC_HANDLE AssetManager::getMemTMP() { return FrameworkMemory::getMem(3); }

u32 AssetManager::getHash(const char *name) { return mm::mtl::hashStrCrc(name); }

AssetManager::AssetManager(mm::mtl::IAllocator *allocator, u32 capacity) : assets(allocator), csvbs(allocator), loaders(allocator) {
  assets.reserve(capacity);
  csvbs.reserve(capacity);
  loaders.reserve(capacity);
}

AssetManager::~AssetManager() {
  while (assets.size() != 0) {
    if (assets[assets.size() - 1] != nullptr) {
      assets[assets.size() - 1]->release();
      assets[assets.size() - 1] = nullptr;
    }
  }
  assets.clear();

  while (csvbs.size() != 0) {
    if (csvbs[csvbs.size() - 1] != nullptr) {
      csvbs[csvbs.size() - 1]->release();
      csvbs[csvbs.size() - 1] = nullptr;
    }
  }
  csvbs.clear();

  while (loaders.size() != 0) {
    if (loaders[loaders.size() - 1] != nullptr) {
      loaders[loaders.size() - 1]->release();
      loaders[loaders.size() - 1] = nullptr;
    }
  }
  loaders.clear();
}

void AssetManager::addAsset(AssetData *asset) { assets.push_back(asset); }

void AssetManager::removeAsset(AssetData *asset) {
  AssetData **it = mm::mtl::find(assets.begin(), assets.end(), asset);
  if (it != assets.end()) {
    assets.erase(it);
  }
}

AssetData *AssetManager::searchAsset(mtl::ALLOC_HANDLE handle, const char *name) {
  if (assets.size() == 0) {
    return nullptr;
  }

  mm::mtl::FixStr<256> fileName;
  ml::DevFileTh::normalizeDvdFileName(fileName, name);
  u32 hash = getHash(fileName.c_str());
  for (u32 i = 0; i < assets.size(); i++) {
    AssetData *item = assets[i];
    if (item != nullptr && item->handle == handle && item->hash == hash && strcmp(item->name.c_str(), fileName.c_str()) == 0) {
      return item;
    }
  }

  return nullptr;
}

AssetData *AssetManager::searchAsset(mm::mtl::IAllocator *allocator, const char *name) {
  if (assets.size() == 0) {
    return nullptr;
  }

  mm::mtl::FixStr<256> fileName;
  ml::DevFileTh::normalizeDvdFileName(fileName, name);
  u32 hash = getHash(fileName.c_str());
  for (u32 i = 0; i < assets.size(); i++) {
    AssetData *item = assets[i];
    if (item != nullptr && item->allocator == allocator && item->hash == hash && strcmp(item->name.c_str(), fileName.c_str()) == 0) {
      return item;
    }
  }

  return nullptr;
}

AssetData *AssetManager::searchAsset(const char *name, AssetData *previous) {
  if (assets.size() == 0) {
    return nullptr;
  }

  mm::mtl::FixStr<256> fileName;
  ml::DevFileTh::normalizeDvdFileName(fileName, name);
  u32 hash = getHash(fileName.c_str());
  AssetData **it = assets.begin();
  if (previous != nullptr) {
    it = mm::mtl::find(assets.begin(), assets.end(), previous);
    if (it != assets.end()) {
      ++it;
    }
  }

  for (; it != assets.end(); ++it) {
    AssetData *item = *it;
    if (item != nullptr && item->hash == hash && strcmp(item->name.c_str(), fileName.c_str()) == 0) {
      return item;
    }
  }

  return nullptr;
}

void AssetManager::addCsvb(AssetCsvb *csvb) { csvbs.push_back(csvb); }

void AssetManager::removeCsvb(AssetCsvb *csvb) {
  AssetCsvb **it = mm::mtl::find(csvbs.begin(), csvbs.end(), csvb);
  if (it != csvbs.end()) {
    csvbs.erase(it);
  }
}

AssetCsvb *AssetManager::searchCsvb(mtl::ALLOC_HANDLE handle, const char *name) {
  if (csvbs.size() == 0) {
    return nullptr;
  }

  mm::mtl::FixStr<256> fileName;
  ml::DevFileTh::normalizeDvdFileName(fileName, name);
  u32 hash = getHash(fileName.c_str());
  for (u32 i = 0; i < assets.size(); i++) {
    AssetCsvb *item = csvbs[i];
    if (item != nullptr && item->handle == handle && item->hash == hash && strcmp(item->name.c_str(), fileName.c_str()) == 0) {
      return item;
    }
  }

  return nullptr;
}

AssetCsvb *AssetManager::searchCsvb(mm::mtl::IAllocator *allocator, const char *name) {
  if (csvbs.size() == 0) {
    return nullptr;
  }

  mm::mtl::FixStr<256> fileName;
  ml::DevFileTh::normalizeDvdFileName(fileName, name);
  u32 hash = getHash(fileName.c_str());
  for (u32 i = 0; i < assets.size(); i++) {
    AssetCsvb *item = csvbs[i];
    if (item != nullptr && item->allocator == allocator && item->hash == hash && strcmp(item->name.c_str(), fileName.c_str()) == 0) {
      return item;
    }
  }

  return nullptr;
}

AssetCsvb *AssetManager::searchCsvb(const char *name, AssetCsvb *previous) {
  if (assets.size() == 0) {
    return nullptr;
  }

  mm::mtl::FixStr<256> fileName;
  ml::DevFileTh::normalizeDvdFileName(fileName, name);
  u32 hash = getHash(fileName.c_str());
  AssetCsvb **it = csvbs.begin();
  if (previous != nullptr) {
    it = mm::mtl::find(csvbs.begin(), csvbs.end(), previous);
    if (it != csvbs.end()) {
      ++it;
    }
  }

  for (; it != csvbs.end(); ++it) {
    AssetCsvb *item = *it;
    if (item != nullptr && item->hash == hash && strcmp(item->name.c_str(), fileName.c_str()) == 0) {
      return item;
    }
  }

  return nullptr;
}

void AssetManager::addLoader(AssetLoader *loader) { loaders.push_back(loader); }

void AssetManager::removeLoader(AssetLoader *loader) {
  AssetLoader **it = mm::mtl::find(loaders.begin(), loaders.end(), loader);
  if (it != loaders.end()) {
    loaders.erase(it);
  }
}

AssetLoader *AssetManager::searchLoader(mtl::ALLOC_HANDLE handle, const char *path) {
  u32 hash = getHash(path);
  for (u32 i = 0; i < loaders.size(); i++) {
    AssetLoader *item = loaders[i];
    if (item != nullptr && item->handle == handle && item->hash == hash && strcmp(item->name.c_str(), path) == 0) {
      return item;
    }
  }

  return nullptr;
}

AssetLoader *AssetManager::searchLoader(mm::mtl::IAllocator *allocator, const char *path) {
  u32 hash = getHash(path);
  for (u32 i = 0; i < loaders.size(); i++) {
    AssetLoader *item = loaders[i];
    if (item != nullptr && item->allocator == allocator && item->hash == hash && strcmp(item->name.c_str(), path) == 0) {
      return item;
    }
  }

  return nullptr;
}

} // namespace fw
