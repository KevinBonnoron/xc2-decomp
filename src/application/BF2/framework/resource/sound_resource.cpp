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
    resource->unknownd0 = info;
    resource->addRef();
    resource->update();
  }

  return resource;
}

SoundResource::SoundResource(mm::mtl::IAllocator *allocator, LOAD_PRIO priority)
    : ResourceObject(5, allocator, priority, 0x1000), unknownb0(STATE_NONE), unknownb8(nullptr), unknownc0(nullptr), m_soundPack(nullptr) {}

SoundResource::~SoundResource() {
  if (unknownb8 != nullptr) {
    unknownb8->Release();
    unknownb8 = nullptr;
  }

  mm::mtl::safeRelease(m_soundPack);
  if (unknownc0 != nullptr) {
    ResourceManager::get()->removeSafeObject(unknownc0);
    mm::mtl::safeRelease(unknownc0);
  }
}

void SoundResource::update() {
  while (unknownb0 != STATE_LOADED) {
    switch (unknownb0) {
    case STATE_NONE: {
      mm::mtl::FixStr<256> fileName;
      ml::DevFileTh::normalizeDvdFileName(fileName, unknown2c.c_str());
      unknownc0 = AssetData::CreateFromCache(unknown18, fileName.c_str());
      if (unknownc0 != nullptr) {
        SoundPack::SetupInfo info;
        info.unknown00 = unknownc0->unknown30.c_str();
        info.unknown84 = unknownd0.unknown00;
        info.unknown88 = unknownd0.unknown04;
        info.unknowna4 = unknownd0.unknown08;
        info.unknown90 = unknownc0->unknown30.c_str();
        info.unknown98 = unknownc0->unknown20;
        info.unknowna0 = unknownc0->unknown1c;
        m_soundPack = SoundPack::createFromStream(unknown18, info);
        ResourceManager::get()->addSafeObject(unknownc0, static_cast<eResourceType>(5));
        unknownb0 = STATE_LOADED;
      } else {
        unknownb8 = AssetLoader::Create(unknown18, fileName.c_str(), unknown28, unknown24);
        unknownb0 = static_cast<State>(unknownb0 + 1);
      }
      break;
    }
    case STATE_LOADING:
      if (unknownb8 == nullptr) {
        unknownb0 = STATE_LOADED;
        break;
      }

      if (unknownb8->unknownc0 != nullptr) {
        return;
      }

      if (unknownb8->unknownd0 == -2) {
        unknownb8->Release();
        unknownb8 = nullptr;
        break;
      }

      if (unknownb8->isExist()) {
        unknownb8->unknownf0 = false;
        unknownc0 = AssetData::AssignFromMemory(unknown18, unknownb8->unknownc8, unknownb8->unknownd0, unknownb8->unknown0c.c_str(), 0);
        SoundPack::SetupInfo info;
        info.unknown00 = unknownc0->unknown30.c_str();
        info.unknown84 = unknownd0.unknown00;
        info.unknown88 = unknownd0.unknown04;
        info.unknowna4 = unknownd0.unknown08;
        info.unknown90 = unknownc0->unknown30.c_str();
        info.unknown98 = unknownc0->unknown20;
        info.unknowna0 = unknownc0->unknown1c;
        m_soundPack = SoundPack::createFromStream(unknown18, info);
        ResourceManager::get()->addSafeObject(unknownc0, static_cast<eResourceType>(5));
      }

      if (unknownb8 != nullptr) {
        unknownb8->Release();
        unknownb8 = nullptr;
      }
      break;
    default:
      break;
    }
  }
}

const char *SoundResource::getMemName() {
  if (unknown18 != nullptr) {
    return unknown18->getName();
  }

  return "undifine memory";
}

bool SoundResource::valid() const { return unknownb0 == STATE_LOADED; }

void *SoundResource::getAssetData() {
  if (unknownc0 != nullptr) {
    return unknownc0->unknown20;
  }

  return nullptr;
}

int SoundResource::getAssetSize() const {
  if (unknownc0 != nullptr) {
    return unknownc0->unknown1c;
  }

  return 0;
}

const char *SoundResource::getAssetName() const { return unknownc0 != nullptr ? unknownc0->unknown30.c_str() : nullptr; }

SoundPack *SoundResource::getSoundPack() { return m_soundPack; }

} // namespace fw
