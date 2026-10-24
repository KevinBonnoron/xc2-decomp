#include "framework/resource/sound_resource.h"

#include "framework/asset/asset_data.h"
#include "framework/asset/asset_loader.h"
#include "framework/resource/resource_manager.h"
#include "framework/sound/sound_pack.h"
#include "ml/dev_file_th.h"
#include "mm_mtl/allocator.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/reference_object.h"
#include "mtl/alloc_handle.h"

namespace fw {
enum eResourceType : int;

SoundResource *SoundResource::search(mm::mtl::IAllocator *allocator, const char *path) { return static_cast<SoundResource *>(ResourceManager::get()->searchResource(5, allocator, path)); }

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

void SoundResource::update() {
  while (state != STATE_LOADED) {
    switch (state) {
    case STATE_NONE: {
      mm::mtl::FixStr<256> fileName;
      ml::DevFileTh::normalizeDvdFileName(fileName, path.c_str());
      asset = AssetData::CreateFromCache(allocator, fileName.c_str());
      if (asset != nullptr) {
        SoundPack::SetupInfo info;
        info.name = asset->name.c_str();
        info.category = setupInfo.category;
        info.priority = setupInfo.priority;
        info.maxSound = setupInfo.maxSound;
        info.assetName = asset->name.c_str();
        info.data = asset->data;
        info.size = asset->size;
        soundPack = SoundPack::createFromStream(allocator, info);
        ResourceManager::get()->addSafeObject(asset, static_cast<eResourceType>(5));
        state = STATE_LOADED;
      } else {
        loader = AssetLoader::Create(allocator, fileName.c_str(), priority, option);
        state = static_cast<State>(state + 1);
      }
      break;
    }
    case STATE_LOADING:
      if (loader == nullptr) {
        state = STATE_LOADED;
        break;
      }

      if (loader->fileHandle != nullptr) {
        return;
      }

      if (loader->size != -2 && loader->isExist()) {
        loader->isBufferOwner = false;
        asset = AssetData::AssignFromMemory(allocator, loader->buffer, loader->size, loader->name.c_str(), 0);
        SoundPack::SetupInfo info;
        info.name = asset->name.c_str();
        info.category = setupInfo.category;
        info.priority = setupInfo.priority;
        info.maxSound = setupInfo.maxSound;
        info.assetName = asset->name.c_str();
        info.data = asset->data;
        info.size = asset->size;
        soundPack = SoundPack::createFromStream(allocator, info);
        ResourceManager::get()->addSafeObject(asset, static_cast<eResourceType>(5));
      }

      if (loader != nullptr) {
        loader->Release();
        loader = nullptr;
      }
      break;
    default:
      break;
    }
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
