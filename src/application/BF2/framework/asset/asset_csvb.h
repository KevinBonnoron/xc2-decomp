#pragma once
#include <stddef.h>

#include "framework/asset/asset_manager.h"
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
  static AssetCsvb *CreateFromFile(mtl::ALLOC_HANDLE handle, const char *name);
  static AssetCsvb *CreateFromMemory(mtl::ALLOC_HANDLE handle, const void *data, u32 size, const char *name);
  static AssetCsvb *CreateFromMemory(mm::mtl::IAllocator *allocator, const void *data, u32 size, const char *name);
  static AssetCsvb *CreateFromCache(mtl::ALLOC_HANDLE handle, const char *name);
  AssetCsvb *Clone(mtl::ALLOC_HANDLE handle) const;
  static AssetCsvb *CreateFromCache(mm::mtl::IAllocator *allocator, const char *name);
  AssetCsvb *Clone(mm::mtl::IAllocator *allocator) const;
  static void *LoadFromPacdata(mtl::ALLOC_HANDLE handle, const char *name, int &size);
  AssetCsvb();
  ~AssetCsvb() override;

  // Inferred helper: names a created asset and takes the first reference; original name unknown.
  void unknown001(const char *name) {
    unknown28 = name;
    unknown18 = AssetManager::getHash(name);
    addRef();
  }

  mtl::ALLOC_HANDLE unknown0c;    // Inferred role: handle; original member name unknown.
  mm::mtl::IAllocator *unknown10; // Inferred role: allocator; original member name unknown.
  u32 unknown18;                  // Inferred role: hash; original member name unknown.
  csvb::CCsvbData *unknown20;     // Inferred role: data; original member name unknown.
  mm::mtl::FixStr<128> unknown28; // Inferred role: name; original member name unknown.
};

static_assert(offsetof(AssetCsvb, unknown18) == 0x18, "");
static_assert(offsetof(AssetCsvb, unknown20) == 0x20, "");
static_assert(offsetof(AssetCsvb, unknown28) == 0x28, "");
static_assert(sizeof(AssetCsvb) == 0xb0, "");

} // namespace fw
