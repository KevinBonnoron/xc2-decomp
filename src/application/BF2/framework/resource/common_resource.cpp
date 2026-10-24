#include "framework/resource/common_resource.h"

#include "framework/asset/asset_data.h"
#include "framework/asset/asset_loader.h"
#include "framework/resource/resource_manager.h"
#include "ml/dev_file_th.h"
#include "mm_mtl/allocator.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/reference_object.h"
#include "mtl/alloc_handle.h"
#include "mtl/mem_manager.h"

namespace fw {
enum eResourceType : int;

CommonResource *CommonResource::search(mtl::ALLOC_HANDLE handle, const char *path) { return static_cast<CommonResource *>(ResourceManager::get()->searchResource(0, handle, path)); }

CommonResource *CommonResource::search(mm::mtl::IAllocator *allocator, const char *path) { return static_cast<CommonResource *>(ResourceManager::get()->searchResource(0, allocator, path)); }

CommonResource *CommonResource::request_detail(mtl::ALLOC_HANDLE handle, const char *path, int priority, bool isSafe, bool isBlock) {
  CommonResource *resource = search(handle, path);
  if (resource != nullptr) {
    resource->addRef();
    return resource;
  }

  resource = new (ResourceManager::getMemSYS()) CommonResource(handle, static_cast<LOAD_PRIO>(priority), 0, 0);
  if (resource != nullptr) {
    resource->setPath(path);
    resource->addRef();
    if (isSafe) {
      resource->unknownb4 = true;
    } else {
      resource->unknownb4 = ResourceManager::isDelayReleaseExtention(path);
    }

    if (resource->unknownb4) {
      resource->unknown24 = 0x1000;
    }

    if (isBlock) {
      resource->updateBlock();
    } else {
      resource->update();
    }
  }

  return resource;
}

CommonResource *CommonResource::request_detail(mm::mtl::IAllocator *allocator, const char *path, int priority, bool isSafe, bool isBlock) {
  CommonResource *resource = search(allocator, path);
  if (resource != nullptr) {
    resource->addRef();
    return resource;
  }

  resource = new (ResourceManager::getMemSYS()) CommonResource(allocator, static_cast<LOAD_PRIO>(priority), 0, 0);
  if (resource != nullptr) {
    resource->setPath(path);
    resource->addRef();
    if (isSafe) {
      resource->unknownb4 = true;
    } else {
      resource->unknownb4 = ResourceManager::isDelayReleaseExtention(path);
    }

    if (resource->unknownb4) {
      resource->unknown24 = 0x1000;
    }

    if (isBlock) {
      resource->updateBlock();
    } else {
      resource->update();
    }
  }

  return resource;
}

CommonResource *CommonResource::request(mtl::ALLOC_HANDLE handle, const char *path, int priority, bool isSafe) { return request_detail(handle, path, priority, isSafe, false); }

CommonResource *CommonResource::request(mm::mtl::IAllocator *allocator, const char *path, int priority, bool isSafe) { return request_detail(allocator, path, priority, isSafe, false); }

CommonResource *CommonResource::blockRequest(mtl::ALLOC_HANDLE handle, const char *path, bool isSafe) { return request_detail(handle, path, 10, isSafe, true); }

CommonResource *CommonResource::blockRequest(mm::mtl::IAllocator *allocator, const char *path, bool isSafe) { return request_detail(allocator, path, 10, isSafe, true); }

CommonResource::CommonResource(mtl::ALLOC_HANDLE handle, LOAD_PRIO priority, u32 type, int option)
    : ResourceObject(type, handle, priority, option), unknownb0(STATE_NONE), unknownb4(false), unknownb8(nullptr), unknownc0(nullptr) {}

CommonResource::CommonResource(mm::mtl::IAllocator *allocator, LOAD_PRIO priority, u32 type, int option)
    : ResourceObject(type, allocator, priority, option), unknownb0(STATE_NONE), unknownb4(false), unknownb8(nullptr), unknownc0(nullptr) {}

CommonResource::~CommonResource() {
  if (unknownb8 != nullptr) {
    unknownb8->Release();
    unknownb8 = nullptr;
  }

  if (unknownc0 != nullptr) {
    if (unknownb4) {
      ResourceManager::get()->removeSafeObject(unknownc0);
    }

    mm::mtl::safeRelease(unknownc0);
  }
}

void CommonResource::update() {
  while (unknownb0 != STATE_LOADED) {
    switch (unknownb0) {
    case STATE_NONE:
      if (unknown10.isValid()) {
        unknownc0 = AssetData::CreateFromCache(unknown10, unknown2c.c_str());
      } else if (unknown18 != nullptr) {
        unknownc0 = AssetData::CreateFromCache(unknown18, unknown2c.c_str());
      }

      if (unknownc0 != nullptr) {
        if (unknownb4) {
          ResourceManager::get()->addSafeObject(unknownc0, static_cast<eResourceType>(0));
        }

        unknownb0 = STATE_LOADED;
      } else {
        mm::mtl::FixStr<256> fileName;
        ml::DevFileTh::normalizeDvdFileName(fileName, unknown2c.c_str());
        if (unknown10.isValid()) {
          unknownb8 = AssetLoader::Create(unknown10, fileName.c_str(), unknown28, unknown24);
        } else if (unknown18 != nullptr) {
          unknownb8 = AssetLoader::Create(unknown18, fileName.c_str(), unknown28, unknown24);
        }

        unknownb0 = static_cast<State>(unknownb0 + 1);
      }
      break;
    case STATE_LOADING:
      if (unknownb8 == nullptr) {
        unknownb0 = STATE_LOADED;
        break;
      }

      if (unknownb8->fileHandle != nullptr) {
        return;
      }

      if (unknownb8->size != -2 && unknownb8->isExist()) {
        unknownb8->isBufferOwner = false;
        if (unknown10.isValid()) {
          unknownc0 = AssetData::AssignFromMemory(unknown10, unknownb8->buffer, unknownb8->size, unknownb8->name.c_str(), unknownb8->timeStamp);
        } else if (unknown18 != nullptr) {
          unknownc0 = AssetData::AssignFromMemory(unknown18, unknownb8->buffer, unknownb8->size, unknownb8->name.c_str(), unknownb8->timeStamp);
        }

        if (unknownb4) {
          ResourceManager::get()->addSafeObject(unknownc0, static_cast<eResourceType>(0));
        }
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

const char *CommonResource::getMemName() {
  if (unknown10.isValid()) {
    return mtl::MemManager::getName(unknown10);
  }

  if (unknown18 != nullptr) {
    return unknown18->getName();
  }

  return "undifine memory";
}

bool CommonResource::valid() const { return unknownb0 == STATE_LOADED; }

void *CommonResource::getAssetData() {
  if (unknownc0 != nullptr) {
    return unknownc0->unknown20;
  }

  return nullptr;
}

int CommonResource::getAssetSize() const {
  if (unknownc0 != nullptr) {
    return unknownc0->unknown1c;
  }

  return 0;
}

const char *CommonResource::getAssetName() const { return unknownc0 != nullptr ? unknownc0->unknown30.c_str() : nullptr; }

u64 CommonResource::getAssetTimeStamp() const {
  if (unknownc0 != nullptr) {
    return unknownc0->unknown28;
  }

  return 0;
}

} // namespace fw
