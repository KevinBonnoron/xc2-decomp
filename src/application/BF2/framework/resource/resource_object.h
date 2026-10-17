#pragma once
#include <stddef.h>

#include "framework/resource/resource_manager.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/reference_object.h"
#include "mtl/alloc_handle.h"
#include "types.h"

namespace mm {
namespace mtl {
class IAllocator;
} // namespace mtl
} // namespace mm

namespace fw {

enum LOAD_PRIO : int {};

class ResourceObject : public mm::mtl::ReferenceObject {
public:
  ResourceObject(u32 type, mtl::ALLOC_HANDLE handle, LOAD_PRIO priority, int option);
  ResourceObject(u32 type, mm::mtl::IAllocator *allocator, LOAD_PRIO priority, int option);
  ~ResourceObject() override;
  virtual void update() = 0;
  virtual bool valid() const = 0;

  void setPath(const char *path) {
    this->path = path;
    hash = ResourceManager::getHash(path);
  }

  u32 type;
  mtl::ALLOC_HANDLE handle;
  mm::mtl::IAllocator *allocator;
  u32 hash;
  int option;
  LOAD_PRIO priority;
  mm::mtl::FixStr<128> path;
};

static_assert(offsetof(ResourceObject, type) == 0x0c, "");
static_assert(offsetof(ResourceObject, allocator) == 0x18, "");
static_assert(offsetof(ResourceObject, priority) == 0x28, "");
static_assert(offsetof(ResourceObject, path) == 0x2c, "");
static_assert(sizeof(ResourceObject) == 0xb0, "");

} // namespace fw
