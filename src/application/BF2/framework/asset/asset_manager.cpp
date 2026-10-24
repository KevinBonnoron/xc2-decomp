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

AssetManager::AssetManager(mm::mtl::IAllocator *allocator, u32 capacity) : unknown18(allocator), unknown40(allocator), unknown68(allocator) {
  unknown18.reserve(capacity);
  unknown40.reserve(capacity);
  unknown68.reserve(capacity);
}

AssetManager::~AssetManager() {
  while (unknown18.size() != 0) {
    if (unknown18[unknown18.size() - 1] != nullptr) {
      unknown18[unknown18.size() - 1]->release();
      unknown18[unknown18.size() - 1] = nullptr;
    }
  }
  unknown18.clear();

  while (unknown40.size() != 0) {
    if (unknown40[unknown40.size() - 1] != nullptr) {
      unknown40[unknown40.size() - 1]->release();
      unknown40[unknown40.size() - 1] = nullptr;
    }
  }
  unknown40.clear();

  while (unknown68.size() != 0) {
    if (unknown68[unknown68.size() - 1] != nullptr) {
      unknown68[unknown68.size() - 1]->release();
      unknown68[unknown68.size() - 1] = nullptr;
    }
  }
  unknown68.clear();
}

void AssetManager::addAsset(AssetData *asset) { unknown18.push_back(asset); }

void AssetManager::removeAsset(AssetData *asset) {
  AssetData **it = mm::mtl::find(unknown18.begin(), unknown18.end(), asset);
  if (it != unknown18.end()) {
    unknown18.erase(it);
  }
}

AssetData *AssetManager::searchAsset(mtl::ALLOC_HANDLE handle, const char *name) {
  if (unknown18.size() == 0) {
    return nullptr;
  }

  mm::mtl::FixStr<256> fileName;
  ml::DevFileTh::normalizeDvdFileName(fileName, name);
  u32 hash = getHash(fileName.c_str());
  for (u32 i = 0; i < unknown18.size(); i++) {
    AssetData *item = unknown18[i];
    if (item != nullptr && item->unknown0c == handle && item->unknown18 == hash && strcmp(item->unknown30.c_str(), fileName.c_str()) == 0) {
      return item;
    }
  }

  return nullptr;
}

AssetData *AssetManager::searchAsset(mm::mtl::IAllocator *allocator, const char *name) {
  if (unknown18.size() == 0) {
    return nullptr;
  }

  mm::mtl::FixStr<256> fileName;
  ml::DevFileTh::normalizeDvdFileName(fileName, name);
  u32 hash = getHash(fileName.c_str());
  for (u32 i = 0; i < unknown18.size(); i++) {
    AssetData *item = unknown18[i];
    if (item != nullptr && item->unknown10 == allocator && item->unknown18 == hash && strcmp(item->unknown30.c_str(), fileName.c_str()) == 0) {
      return item;
    }
  }

  return nullptr;
}

AssetData *AssetManager::searchAsset(const char *name, AssetData *previous) {
  if (unknown18.size() == 0) {
    return nullptr;
  }

  mm::mtl::FixStr<256> fileName;
  ml::DevFileTh::normalizeDvdFileName(fileName, name);
  u32 hash = getHash(fileName.c_str());
  AssetData **it = unknown18.begin();
  if (previous != nullptr) {
    it = mm::mtl::find(unknown18.begin(), unknown18.end(), previous);
    if (it != unknown18.end()) {
      ++it;
    }
  }

  for (; it != unknown18.end(); ++it) {
    AssetData *item = *it;
    if (item != nullptr && item->unknown18 == hash && strcmp(item->unknown30.c_str(), fileName.c_str()) == 0) {
      return item;
    }
  }

  return nullptr;
}

void AssetManager::addCsvb(AssetCsvb *csvb) { unknown40.push_back(csvb); }

void AssetManager::removeCsvb(AssetCsvb *csvb) {
  AssetCsvb **it = mm::mtl::find(unknown40.begin(), unknown40.end(), csvb);
  if (it != unknown40.end()) {
    unknown40.erase(it);
  }
}

AssetCsvb *AssetManager::searchCsvb(mtl::ALLOC_HANDLE handle, const char *name) {
  if (unknown40.size() == 0) {
    return nullptr;
  }

  mm::mtl::FixStr<256> fileName;
  ml::DevFileTh::normalizeDvdFileName(fileName, name);
  u32 hash = getHash(fileName.c_str());
  for (u32 i = 0; i < unknown18.size(); i++) {
    AssetCsvb *item = unknown40[i];
    if (item != nullptr && item->unknown0c == handle && item->unknown18 == hash && strcmp(item->unknown28.c_str(), fileName.c_str()) == 0) {
      return item;
    }
  }

  return nullptr;
}

AssetCsvb *AssetManager::searchCsvb(mm::mtl::IAllocator *allocator, const char *name) {
  if (unknown40.size() == 0) {
    return nullptr;
  }

  mm::mtl::FixStr<256> fileName;
  ml::DevFileTh::normalizeDvdFileName(fileName, name);
  u32 hash = getHash(fileName.c_str());
  for (u32 i = 0; i < unknown18.size(); i++) {
    AssetCsvb *item = unknown40[i];
    if (item != nullptr && item->unknown10 == allocator && item->unknown18 == hash && strcmp(item->unknown28.c_str(), fileName.c_str()) == 0) {
      return item;
    }
  }

  return nullptr;
}

AssetCsvb *AssetManager::searchCsvb(const char *name, AssetCsvb *previous) {
  if (unknown18.size() == 0) {
    return nullptr;
  }

  mm::mtl::FixStr<256> fileName;
  ml::DevFileTh::normalizeDvdFileName(fileName, name);
  u32 hash = getHash(fileName.c_str());
  AssetCsvb **it = unknown40.begin();
  if (previous != nullptr) {
    it = mm::mtl::find(unknown40.begin(), unknown40.end(), previous);
    if (it != unknown40.end()) {
      ++it;
    }
  }

  for (; it != unknown40.end(); ++it) {
    AssetCsvb *item = *it;
    if (item != nullptr && item->unknown18 == hash && strcmp(item->unknown28.c_str(), fileName.c_str()) == 0) {
      return item;
    }
  }

  return nullptr;
}

void AssetManager::addLoader(AssetLoader *loader) { unknown68.push_back(loader); }

void AssetManager::removeLoader(AssetLoader *loader) {
  AssetLoader **it = mm::mtl::find(unknown68.begin(), unknown68.end(), loader);
  if (it != unknown68.end()) {
    unknown68.erase(it);
  }
}

AssetLoader *AssetManager::searchLoader(mtl::ALLOC_HANDLE handle, const char *path) {
  u32 hash = getHash(path);
  for (u32 i = 0; i < unknown68.size(); i++) {
    AssetLoader *item = unknown68[i];
    if (item != nullptr && item->unknown100 == handle && item->unknown110 == hash && strcmp(item->name.c_str(), path) == 0) {
      return item;
    }
  }

  return nullptr;
}

AssetLoader *AssetManager::searchLoader(mm::mtl::IAllocator *allocator, const char *path) {
  u32 hash = getHash(path);
  for (u32 i = 0; i < unknown68.size(); i++) {
    AssetLoader *item = unknown68[i];
    if (item != nullptr && item->unknown108 == allocator && item->unknown110 == hash && strcmp(item->name.c_str(), path) == 0) {
      return item;
    }
  }

  return nullptr;
}

} // namespace fw
