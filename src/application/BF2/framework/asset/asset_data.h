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
    this->name = name;
    hash = AssetManager::getHash(name);
  }

  void copyName(const mm::mtl::FixStr<128> &name) { this->name = name; }

  mtl::ALLOC_HANDLE handle;
  mm::mtl::IAllocator *allocator;
  u32 hash;
  u32 size;
  void *data;
  u64 timeStamp;
  mm::mtl::FixStr<128> name;
};

static_assert(offsetof(AssetData, allocator) == 0x10, "");
static_assert(offsetof(AssetData, hash) == 0x18, "");
static_assert(offsetof(AssetData, size) == 0x1c, "");
static_assert(offsetof(AssetData, timeStamp) == 0x28, "");
static_assert(offsetof(AssetData, name) == 0x30, "");
static_assert(sizeof(AssetData) == 0xb8, "");

} // namespace fw
