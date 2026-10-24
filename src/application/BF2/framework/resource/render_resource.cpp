#include "framework/resource/common_resource.h"
#include "framework/resource/resource_manager.h"
#include "fw/fw_render_resource.h"
#include "mtl/alloc_handle.h"

namespace mm {
namespace mtl {
class IAllocator;
} // namespace mtl
} // namespace mm

namespace fw {
enum LOAD_PRIO : int;

RenderResource *RenderResource::search(mtl::ALLOC_HANDLE handle, const char *path) { return static_cast<RenderResource *>(ResourceManager::get()->searchResource(1, handle, path)); }

RenderResource *RenderResource::search(mm::mtl::IAllocator *allocator, const char *path) { return static_cast<RenderResource *>(ResourceManager::get()->searchResource(1, allocator, path)); }

RenderResource *RenderResource::request(mtl::ALLOC_HANDLE handle, const char *path, int priority) {
  RenderResource *resource = search(handle, path);
  if (resource != nullptr) {
    resource->addRef();
    return resource;
  }

  resource = new (ResourceManager::getMemSYS()) RenderResource(handle, static_cast<LOAD_PRIO>(priority));
  if (resource != nullptr) {
    resource->setPath(path);
    resource->addRef();
    resource->update();
  }

  return resource;
}

RenderResource *RenderResource::request(mm::mtl::IAllocator *allocator, const char *path, int priority) {
  RenderResource *resource = search(allocator, path);
  if (resource != nullptr) {
    resource->addRef();
    return resource;
  }

  resource = new (ResourceManager::getMemSYS()) RenderResource(allocator, static_cast<LOAD_PRIO>(priority));
  if (resource != nullptr) {
    resource->setPath(path);
    resource->addRef();
    resource->update();
  }

  return resource;
}

RenderResource::RenderResource(mtl::ALLOC_HANDLE handle, LOAD_PRIO priority) : CommonResource(handle, priority, 1, 0x1000) { unknownb4 = true; }

RenderResource::RenderResource(mm::mtl::IAllocator *allocator, LOAD_PRIO priority) : CommonResource(allocator, priority, 1, 0x1000) { unknownb4 = true; }

RenderResource::~RenderResource() {}

} // namespace fw
