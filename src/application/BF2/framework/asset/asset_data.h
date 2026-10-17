#pragma once
#include <stddef.h>

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
  static AssetData *AssignFromMemory(mtl::ALLOC_HANDLE handle, const void *data, u32 size, const char *name, u64 timeStamp);
  static AssetData *AssignFromMemory(mm::mtl::IAllocator *allocator, const void *data, u32 size, const char *name, u64 timeStamp);
  static AssetData *CreateFromCache(mtl::ALLOC_HANDLE handle, const char *name);
  static AssetData *CreateFromCache(mm::mtl::IAllocator *allocator, const char *name);
  AssetData();
  ~AssetData() override;

  mtl::ALLOC_HANDLE handle;
  mm::mtl::IAllocator *allocator;
  u8 _18[0x1c - 0x18];
  u32 size;
  void *data;
  u64 timeStamp;
  mm::mtl::FixStr<128> name;
};

static_assert(offsetof(AssetData, allocator) == 0x10, "");
static_assert(offsetof(AssetData, size) == 0x1c, "");
static_assert(offsetof(AssetData, timeStamp) == 0x28, "");
static_assert(offsetof(AssetData, name) == 0x30, "");

} // namespace fw
