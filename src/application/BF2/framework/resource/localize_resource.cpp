#include "framework/resource/localize_resource.h"

#include "framework/resource/resource_manager.h"
#include "mtl/alloc_handle.h"

namespace fw {
enum LOAD_PRIO : int;

LocalizeResource::LocalizeResource(mtl::ALLOC_HANDLE handle, LOAD_PRIO priority) : CommonResource(handle, priority, 0, 0), checkState(0) {}

LocalizeResource::LocalizeResource(mm::mtl::IAllocator *allocator, LOAD_PRIO priority) : CommonResource(allocator, priority, 0, 0), checkState(0) {}

LocalizeResource::~LocalizeResource() { ; }

LocalizeResource *LocalizeResource::request(mtl::ALLOC_HANDLE handle, const char *path, int priority, bool isSafe) {
  LocalizeResource *resource = static_cast<LocalizeResource *>(CommonResource::search(handle, path));
  if (resource != nullptr) {
    resource->addRef();
    return resource;
  }

  resource = new (ResourceManager::getMemSYS()) LocalizeResource(handle, static_cast<LOAD_PRIO>(priority));
  if (resource != nullptr) {
    resource->localizedPath = path;
    resource->setPath(path);
    resource->addRef();
    resource->update();
  }

  return resource;
}

LocalizeResource *LocalizeResource::request(mm::mtl::IAllocator *allocator, const char *path, int priority, bool isSafe) {
  LocalizeResource *resource = static_cast<LocalizeResource *>(CommonResource::search(allocator, path));
  if (resource != nullptr) {
    resource->addRef();
    return resource;
  }

  resource = new (ResourceManager::getMemSYS()) LocalizeResource(allocator, static_cast<LOAD_PRIO>(priority));
  if (resource != nullptr) {
    resource->localizedPath = path;
    resource->setPath(path);
    resource->addRef();
    resource->update();
  }

  return resource;
}

const char *LocalizeResource::getAssetName() const { return localizedPath.empty() ? nullptr : localizedPath.c_str(); }

} // namespace fw
