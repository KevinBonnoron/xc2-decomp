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
    loader->handle = handle;
    loader->SetName(path);
    loader->hash = AssetManager::getHash(path);
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
    loader->allocator = allocator;
    loader->SetName(path);
    loader->hash = AssetManager::getHash(path);
  }

  return loader;
}

AssetLoader::AssetLoader() : allocator(nullptr), hash(0) { AssetManager::get()->addLoader(this); }

AssetLoader::~AssetLoader() { AssetManager::get()->removeLoader(this); }

} // namespace fw
