#pragma once
#include <stddef.h>

#include "framework/asset/asset_manager.h"
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

class AssetData : public mm::mtl::ReferenceObject {
public:
  static AssetData *CreateFromFile(mtl::ALLOC_HANDLE handle, const char *name);
  static AssetData *CreateFromMemory(mtl::ALLOC_HANDLE handle, const void *data, u32 size, const char *name);
  static AssetData *CreateFromMemory(mm::mtl::IAllocator *allocator, const void *data, u32 size, const char *name);
  static AssetData *AssignFromMemory(mtl::ALLOC_HANDLE handle, const void *data, u32 size, const char *name, u64 timeStamp);
  static AssetData *AssignFromMemory(mm::mtl::IAllocator *allocator, const void *data, u32 size, const char *name, u64 timeStamp);
  static AssetData *CreateFromCache(mtl::ALLOC_HANDLE handle, const char *name);
  AssetData *Clone(mtl::ALLOC_HANDLE handle) const;
  static AssetData *CreateFromCache(mm::mtl::IAllocator *allocator, const char *name);
  AssetData *Clone(mm::mtl::IAllocator *allocator) const;
  static void *LoadFromPacdata(mtl::ALLOC_HANDLE handle, const char *name, int &size);
  AssetData();
  ~AssetData() override;

  void setName(const char *name) {
    this->unknown30 = name;
    unknown18 = AssetManager::getHash(name);
  }

  void copyName(const mm::mtl::FixStr<128> &name) { this->unknown30 = name; }

  mtl::ALLOC_HANDLE unknown0c;    // Inferred role: handle; original member name unknown.
  mm::mtl::IAllocator *unknown10; // Inferred role: allocator; original member name unknown.
  u32 unknown18;                  // Inferred role: hash; original member name unknown.
  u32 unknown1c;                  // Inferred role: size; original member name unknown.
  void *unknown20;                // Inferred role: data; original member name unknown.
  u64 unknown28;                  // Inferred role: time stamp; original member name unknown.
  mm::mtl::FixStr<128> unknown30; // Inferred role: name; original member name unknown.
};

static_assert(offsetof(AssetData, unknown10) == 0x10, "");
static_assert(offsetof(AssetData, unknown18) == 0x18, "");
static_assert(offsetof(AssetData, unknown1c) == 0x1c, "");
static_assert(offsetof(AssetData, unknown28) == 0x28, "");
static_assert(offsetof(AssetData, unknown30) == 0x30, "");
static_assert(sizeof(AssetData) == 0xb8, "");

} // namespace fw
