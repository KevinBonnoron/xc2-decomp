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
    resource->m_setupInfo = info;
    resource->addRef();
    resource->update();
  }

  return resource;
}

SoundResource::SoundResource(mm::mtl::IAllocator *allocator, LOAD_PRIO priority)
    : ResourceObject(5, allocator, priority, 0x1000), unknownb0(STATE_UNKNOWN_0), m_assetLoader(nullptr), m_assetData(nullptr), m_soundPack(nullptr) {}

SoundResource::~SoundResource() {
  if (m_assetLoader != nullptr) {
    m_assetLoader->Release();
    m_assetLoader = nullptr;
  }

  mm::mtl::safeRelease(m_soundPack);
  if (m_assetData != nullptr) {
    ResourceManager::get()->removeSafeObject(m_assetData);
    mm::mtl::safeRelease(m_assetData);
  }
}

void SoundResource::update() {
  while (unknownb0 != STATE_UNKNOWN_2) {
    switch (unknownb0) {
    case STATE_UNKNOWN_0: {
      mm::mtl::FixStr<256> fileName;
      ml::DevFileTh::normalizeDvdFileName(fileName, unknown2c.c_str());
      m_assetData = AssetData::CreateFromCache(unknown18, fileName.c_str());
      if (m_assetData != nullptr) {
        SoundPack::SetupInfo info;
        info.unknown00 = m_assetData->unknown30.c_str();
        info.unknown84 = m_setupInfo.unknown00;
        info.unknown88 = m_setupInfo.unknown04;
        info.unknowna4 = m_setupInfo.unknown08;
        info.unknown90 = m_assetData->unknown30.c_str();
        info.unknown98 = m_assetData->unknown20;
        info.unknowna0 = m_assetData->unknown1c;
        m_soundPack = SoundPack::createFromStream(unknown18, info);
        ResourceManager::get()->addSafeObject(m_assetData, static_cast<eResourceType>(5));
        unknownb0 = STATE_UNKNOWN_2;
      } else {
        m_assetLoader = AssetLoader::Create(unknown18, fileName.c_str(), unknown28, unknown24);
        unknownb0 = static_cast<State>(unknownb0 + 1);
      }
      break;
    }
    case STATE_UNKNOWN_1:
      if (m_assetLoader == nullptr) {
        unknownb0 = STATE_UNKNOWN_2;
        break;
      }

      if (m_assetLoader->m_fileHandleTh != nullptr) {
        return;
      }

      if (m_assetLoader->unknownd0 == -2) {
        m_assetLoader->Release();
        m_assetLoader = nullptr;
        break;
      }

      if (m_assetLoader->isExist()) {
        m_assetLoader->unknownf0 = false;
        m_assetData = AssetData::AssignFromMemory(unknown18, m_assetLoader->m_glassBreakage, m_assetLoader->unknownd0, m_assetLoader->unknown0c.c_str(), 0);
        SoundPack::SetupInfo info;
        info.unknown00 = m_assetData->unknown30.c_str();
        info.unknown84 = m_setupInfo.unknown00;
        info.unknown88 = m_setupInfo.unknown04;
        info.unknowna4 = m_setupInfo.unknown08;
        info.unknown90 = m_assetData->unknown30.c_str();
        info.unknown98 = m_assetData->unknown20;
        info.unknowna0 = m_assetData->unknown1c;
        m_soundPack = SoundPack::createFromStream(unknown18, info);
        ResourceManager::get()->addSafeObject(m_assetData, static_cast<eResourceType>(5));
      }

      if (m_assetLoader != nullptr) {
        m_assetLoader->Release();
        m_assetLoader = nullptr;
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

bool SoundResource::valid() const { return unknownb0 == STATE_UNKNOWN_2; }

void *SoundResource::getAssetData() {
  if (m_assetData != nullptr) {
    return m_assetData->unknown20;
  }

  return nullptr;
}

int SoundResource::getAssetSize() const {
  if (m_assetData != nullptr) {
    return m_assetData->unknown1c;
  }

  return 0;
}

const char *SoundResource::getAssetName() const { return m_assetData != nullptr ? m_assetData->unknown30.c_str() : nullptr; }

SoundPack *SoundResource::getSoundPack() { return m_soundPack; }

} // namespace fw
