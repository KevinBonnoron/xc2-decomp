#pragma once
#include <stddef.h>

#include "mm_mtl/fixstr.h"
#include "mm_mtl/reference_object.h"
#include "mtl/alloc_handle.h"
#include "types.h"

namespace csvb {
class CCsvbData;
} // namespace csvb

namespace mm {
namespace mtl {
class IAllocator;
} // namespace mtl
} // namespace mm

namespace fw {

class AssetCsvb : public mm::mtl::ReferenceObject {
public:
  static AssetCsvb *CreateFromMemory(mtl::ALLOC_HANDLE handle, const void *data, u32 size, const char *name);
  static AssetCsvb *CreateFromMemory(mm::mtl::IAllocator *allocator, const void *data, u32 size, const char *name);
  static AssetCsvb *CreateFromCache(mtl::ALLOC_HANDLE handle, const char *name);
  AssetCsvb *Clone(mtl::ALLOC_HANDLE handle) const;
  static AssetCsvb *CreateFromCache(mm::mtl::IAllocator *allocator, const char *name);
  AssetCsvb *Clone(mm::mtl::IAllocator *allocator) const;
  static void *LoadFromPacdata(mtl::ALLOC_HANDLE handle, const char *name, int &size);
  AssetCsvb();
  ~AssetCsvb() override;

  mtl::ALLOC_HANDLE handle;
  mm::mtl::IAllocator *allocator;
  u32 hash;
  csvb::CCsvbData *data;
  mm::mtl::FixStr<128> name;
};

static_assert(offsetof(AssetCsvb, hash) == 0x18, "");
static_assert(offsetof(AssetCsvb, data) == 0x20, "");
static_assert(offsetof(AssetCsvb, name) == 0x28, "");
static_assert(sizeof(AssetCsvb) == 0xb0, "");

} // namespace fw
