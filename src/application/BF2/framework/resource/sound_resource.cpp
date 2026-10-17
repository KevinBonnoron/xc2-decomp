#include "framework/resource/sound_resource.h"

#include "framework/asset/asset_data.h"
#include "framework/asset/asset_loader.h"
#include "framework/resource/resource_manager.h"
#include "framework/sound/sound_pack.h"
#include "mm_mtl/allocator.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/reference_object.h"
#include "mtl/alloc_handle.h"

namespace fw {

SoundResource *SoundResource::search(mm::mtl::IAllocator *allocator, const char *path) {
  return static_cast<SoundResource *>(ResourceManager::get()->searchResource(5, allocator, path));
}

SoundResource *SoundResource::request(mm::mtl::IAllocator *allocator, const char *path, const SetupInfo &info, LOAD_PRIO priority) {
  SoundResource *resource = search(allocator, path);
  if (resource != nullptr) {
    resource->addRef();
    return resource;
  }

  resource = new (ResourceManager::getMemSYS()) SoundResource(allocator, priority);
  if (resource != nullptr) {
    resource->setPath(path);
    resource->setupInfo = info;
    resource->addRef();
    resource->update();
  }

  return resource;
}

SoundResource::SoundResource(mm::mtl::IAllocator *allocator, LOAD_PRIO priority)
    : ResourceObject(5, allocator, priority, 0x1000), state(STATE_NONE), loader(nullptr), asset(nullptr), soundPack(nullptr) {}

SoundResource::~SoundResource() {
  if (loader != nullptr) {
    loader->Release();
    loader = nullptr;
  }

  mm::mtl::safeRelease(soundPack);
  if (asset != nullptr) {
    ResourceManager::get()->removeSafeObject(asset);
    mm::mtl::safeRelease(asset);
  }
}

const char *SoundResource::getMemName() {
  if (allocator != nullptr) {
    return allocator->getName();
  }

  return "undifine memory";
}

bool SoundResource::valid() const { return state == STATE_LOADED; }

void *SoundResource::getAssetData() {
  if (asset != nullptr) {
    return asset->data;
  }

  return nullptr;
}

int SoundResource::getAssetSize() const {
  if (asset != nullptr) {
    return asset->size;
  }

  return 0;
}

const char *SoundResource::getAssetName() const { return asset != nullptr ? asset->name.c_str() : nullptr; }

SoundPack *SoundResource::getSoundPack() { return soundPack; }

} // namespace fw
