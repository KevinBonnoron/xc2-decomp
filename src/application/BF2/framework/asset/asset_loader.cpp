#include "framework/asset/asset_loader.h"

#include "dr/dr_man.h"
#include "framework/asset/asset_manager.h"

namespace fw {

AssetLoader *AssetLoader::Create(mtl::ALLOC_HANDLE handle, const char *path, int priority, int option) {
  AssetLoader *loader = AssetManager::get()->searchLoader(handle, path);
  if (loader != nullptr) {
    loader->AddRef();
    return loader;
  }

  loader = new (AssetManager::getMemSYS()) AssetLoader();
  if (loader != nullptr) {
    loader->load(handle, path, option, static_cast<ml::FILE_PRIO>(priority));
    loader->unknown100 = handle;
    loader->SetName(path);
    loader->unknown110 = AssetManager::getHash(path);
  }

  return loader;
}

AssetLoader *AssetLoader::Create(mm::mtl::IAllocator *allocator, const char *path, int priority, int option) {
  AssetLoader *loader = AssetManager::get()->searchLoader(allocator, path);
  if (loader != nullptr) {
    loader->AddRef();
    return loader;
  }

  loader = new (AssetManager::getMemSYS()) AssetLoader();
  if (loader != nullptr) {
    loader->load(allocator, path, option, static_cast<ml::FILE_PRIO>(priority));
    loader->unknown108 = allocator;
    loader->SetName(path);
    loader->unknown110 = AssetManager::getHash(path);
  }

  return loader;
}

AssetLoader::AssetLoader() : unknown108(nullptr), unknown110(0) { AssetManager::get()->addLoader(this); }

AssetLoader::~AssetLoader() { AssetManager::get()->removeLoader(this); }

} // namespace fw
