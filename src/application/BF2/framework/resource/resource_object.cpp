#include "framework/resource/resource_object.h"

#include "framework/resource/resource_manager.h"

namespace fw {

ResourceObject::ResourceObject(u32 type, mtl::ALLOC_HANDLE handle, LOAD_PRIO priority, int option)
    : unknown0c(type), unknown10(handle), unknown18(nullptr), unknown20(0), unknown24(option), unknown28(priority) {
  ResourceManager::get()->addResource(this);
}

ResourceObject::ResourceObject(u32 type, mm::mtl::IAllocator *allocator, LOAD_PRIO priority, int option) : unknown0c(type), unknown18(allocator), unknown20(0), unknown24(option), unknown28(priority) {
  ResourceManager::get()->addResource(this);
}

ResourceObject::~ResourceObject() { ResourceManager::get()->removeResource(this); }

} // namespace fw
