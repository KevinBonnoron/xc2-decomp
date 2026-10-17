#include "framework/resource/common_resource.h"

#include "framework/asset/asset_data.h"
#include "framework/asset/asset_loader.h"
#include "framework/resource/resource_manager.h"
#include "mm_mtl/allocator.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/reference_object.h"
#include "mtl/alloc_handle.h"
#include "mtl/mem_manager.h"

namespace fw {

CommonResource *CommonResource::search(mtl::ALLOC_HANDLE handle, const char *path) {
  return static_cast<CommonResource *>(ResourceManager::get()->searchResource(0, handle, path));
}

CommonResource *CommonResource::search(mm::mtl::IAllocator *allocator, const char *path) {
  return static_cast<CommonResource *>(ResourceManager::get()->searchResource(0, allocator, path));
}

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
      resource->isSafe = true;
    } else {
      resource->isSafe = ResourceManager::isDelayReleaseExtention(path);
    }

    if (resource->isSafe) {
      resource->option = 0x1000;
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
      resource->isSafe = true;
    } else {
      resource->isSafe = ResourceManager::isDelayReleaseExtention(path);
    }

    if (resource->isSafe) {
      resource->option = 0x1000;
    }

    if (isBlock) {
      resource->updateBlock();
    } else {
      resource->update();
    }
  }

  return resource;
}

CommonResource *CommonResource::request(mtl::ALLOC_HANDLE handle, const char *path, int priority, bool isSafe) {
  return request_detail(handle, path, priority, isSafe, false);
}

CommonResource *CommonResource::request(mm::mtl::IAllocator *allocator, const char *path, int priority, bool isSafe) {
  return request_detail(allocator, path, priority, isSafe, false);
}

CommonResource *CommonResource::blockRequest(mtl::ALLOC_HANDLE handle, const char *path, bool isSafe) {
  return request_detail(handle, path, 10, isSafe, true);
}

CommonResource *CommonResource::blockRequest(mm::mtl::IAllocator *allocator, const char *path, bool isSafe) {
  return request_detail(allocator, path, 10, isSafe, true);
}

CommonResource::CommonResource(mtl::ALLOC_HANDLE handle, LOAD_PRIO priority, u32 type, int option)
    : ResourceObject(type, handle, priority, option), state(STATE_NONE), isSafe(false), loader(nullptr), asset(nullptr) {}

CommonResource::CommonResource(mm::mtl::IAllocator *allocator, LOAD_PRIO priority, u32 type, int option)
    : ResourceObject(type, allocator, priority, option), state(STATE_NONE), isSafe(false), loader(nullptr), asset(nullptr) {}

CommonResource::~CommonResource() {
  if (loader != nullptr) {
    loader->Release();
    loader = nullptr;
  }

  if (asset != nullptr) {
    if (isSafe) {
      ResourceManager::get()->removeSafeObject(asset);
    }

    mm::mtl::safeRelease(asset);
  }
}

const char *CommonResource::getMemName() {
  if (handle.isValid()) {
    return mtl::MemManager::getName(handle);
  }

  if (allocator != nullptr) {
    return allocator->getName();
  }

  return "undifine memory";
}

bool CommonResource::valid() const { return state == STATE_LOADED; }

void *CommonResource::getAssetData() {
  if (asset != nullptr) {
    return asset->data;
  }

  return nullptr;
}

int CommonResource::getAssetSize() const {
  if (asset != nullptr) {
    return asset->size;
  }

  return 0;
}

const char *CommonResource::getAssetName() const { return asset != nullptr ? asset->name.c_str() : nullptr; }

u64 CommonResource::getAssetTimeStamp() const {
  if (asset != nullptr) {
    return asset->timeStamp;
  }

  return 0;
}

} // namespace fw
