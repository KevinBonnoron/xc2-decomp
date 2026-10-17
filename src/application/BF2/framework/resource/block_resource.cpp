#include "framework/resource/block_resource.h"

#include <string.h>

#include "framework/memory/framework_memory.h"
#include "framework/resource/common_resource.h"
#include "framework/resource/resource_manager.h"
#include "mm_mtl/fixstr.h"

namespace fw {

BlockResource *BlockResource::search(mtl::ALLOC_HANDLE handle, const char *path) {
  return static_cast<BlockResource *>(ResourceManager::get()->searchResource(6, handle, path));
}

BlockResource *BlockResource::request(mtl::ALLOC_HANDLE handle, const char *path, LOAD_PRIO priority) {
  BlockResource *resource = search(handle, path);
  if (resource != nullptr) {
    resource->addRef();
    return resource;
  }

  resource = new (ResourceManager::getMemSYS()) BlockResource(handle, priority);
  if (resource != nullptr) {
    resource->setPath(path);
    resource->addRef();
    resource->update();
  }

  return resource;
}

BlockResource::BlockResource(mtl::ALLOC_HANDLE handle, LOAD_PRIO priority)
    : ResourceObject(6, handle, priority, 0), loaded(false), resourceHandle(handle), resourcePriority(priority) {
  resourceAllocator.setMemHandle(FrameworkMemory::getMem(5));
  resources.setAllocator(&resourceAllocator);
  resources.reserve(16);
}

BlockResource::~BlockResource() {
  for (CommonResource **it = resources.begin(); it != resources.end(); ++it) {
    if (*it != nullptr) {
      (*it)->release();
    }
  }

  resources.release();
}

void BlockResource::update() {
  if (loaded) {
    return;
  }

  int count = 0;
  for (CommonResource **it = resources.begin(); it != resources.end(); ++it) {
    count += (*it)->valid();
  }

  if (count == resources.size()) {
    loaded = true;
  }
}

bool BlockResource::valid() const { return loaded; }

CommonResource *BlockResource::findLoadedResource(const char *path) const {
  if (loaded) {
    for (CommonResource *const *it = resources.begin(); it != resources.end(); ++it) {
      CommonResource *resource = *it;
      if (strcmp(resource->path.c_str(), path) == 0) {
        return resource;
      }
    }
  }

  return nullptr;
}

void *BlockResource::getAssetData(const char *path) {
  CommonResource *resource = findLoadedResource(path);
  if (resource != nullptr) {
    return resource->getAssetData();
  }

  return nullptr;
}

int BlockResource::getAssetSize(const char *path) const {
  CommonResource *resource = findLoadedResource(path);
  if (resource != nullptr) {
    return resource->getAssetSize();
  }

  return 0;
}

const char *BlockResource::getAssetName(const char *path) const {
  CommonResource *resource = findLoadedResource(path);
  if (resource != nullptr) {
    return resource->getAssetName();
  }

  return nullptr;
}

void BlockResource::addAssetFile(const char *path, bool isSafe) {
  if (findLoadedResource(path) != nullptr) {
    return;
  }

  CommonResource *resource = CommonResource::request(resourceHandle, path, resourcePriority, isSafe);
  if (resource != nullptr) {
    resources.push_back(resource);
    loaded = false;
  }
}

} // namespace fw
