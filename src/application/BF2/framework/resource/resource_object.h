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
    this->unknown2c = path;
    unknown20 = ResourceManager::getHash(path);
  }

  u32 unknown0c;                  // Inferred role: type; original member name unknown.
  mtl::ALLOC_HANDLE unknown10;    // Inferred role: handle; original member name unknown.
  mm::mtl::IAllocator *unknown18; // Inferred role: allocator; original member name unknown.
  u32 unknown20;                  // Inferred role: hash; original member name unknown.
  int unknown24;                  // Inferred role: option; original member name unknown.
  LOAD_PRIO unknown28;            // Inferred role: priority; original member name unknown.
  mm::mtl::FixStr<128> unknown2c; // Inferred role: path; original member name unknown.
};

static_assert(offsetof(ResourceObject, unknown0c) == 0x0c, "");
static_assert(offsetof(ResourceObject, unknown18) == 0x18, "");
static_assert(offsetof(ResourceObject, unknown28) == 0x28, "");
static_assert(offsetof(ResourceObject, unknown2c) == 0x2c, "");
static_assert(sizeof(ResourceObject) == 0xb0, "");

} // namespace fw
