#include "framework/resource/resource_object.h"

#include "framework/resource/resource_manager.h"

namespace fw {

ResourceObject::ResourceObject(u32 type, mtl::ALLOC_HANDLE handle, LOAD_PRIO priority, int option)
    : type(type), handle(handle), allocator(nullptr), hash(0), option(option), priority(priority) {
  ResourceManager::get()->addResource(this);
}

ResourceObject::ResourceObject(u32 type, mm::mtl::IAllocator *allocator, LOAD_PRIO priority, int option)
    : type(type), allocator(allocator), hash(0), option(option), priority(priority) {
  ResourceManager::get()->addResource(this);
}

ResourceObject::~ResourceObject() { ResourceManager::get()->removeResource(this); }

} // namespace fw
