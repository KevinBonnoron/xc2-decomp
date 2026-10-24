#pragma once
#include <stddef.h>

#include "gf/asset/gf_asset_def.h"
#include "mm_mtl/fixed_vector.h"
#include "mtl/alloc_handle.h"
#include "types.h"

namespace fw {
struct UpdateInfo;
} // namespace fw

namespace mm {
namespace mtl {
class IAllocator;
} // namespace mtl
} // namespace mm

namespace gf {

struct GF_ASSET_HANDLE;
struct GF_SLOT_HANDLE;
struct GfSetupParam;
class GfAllocator;
class GfAssetPack;
class GfSlotAll;
class GfSlotAllocator;

class GfSlotMapping {
public:
  struct REQ {
    GF_ASSET_HANDLE *unknown00; // Inferred role: handle; original member name unknown.
    GfAssetPack *unknown08;     // Inferred role: pack; original member name unknown.
    u16 unknown10;              // Inferred role: retry count; original member name unknown.
    f32 unknown14;              // Inferred role: timer; original member name unknown.
  };

  struct BiggerPrio {
    bool operator()(REQ &request, REQ &other) const;
  };

  class ExtendSlotAllocator {
  public:
    void createAllocator(size_t size, const char *name);
    void destroyAllocator();

    GfSlotAllocator *unknown00;  // Inferred role: allocator; original member name unknown.
    void *unknown08;             // Inferred role: memory; original member name unknown.
    mtl::ALLOC_HANDLE unknown10; // Inferred role: handle; original member name unknown.
  };

  static const u32 REQUEST_MAX = 256;

  static size_t getAllSize();
  void createMapping(const GfSetupParam &param);
  void destroyMapping();
  void registSoundMemeory(GfAssetType type);
  void unregistSoundMemeory(GfAssetType type);
  GfSlotMapping();
  ~GfSlotMapping();
  void setup(const GfSetupParam &param, GfAllocator *allocator, size_t size);
  void destroy();
  void update(const fw::UpdateInfo &info);
  void updateSlotRequest(const fw::UpdateInfo &info);
  bool setupFreeSlot(REQ *request);
  void requestSlotLoad(GF_ASSET_HANDLE *handle, GfAssetPack *pack);
  bool isRequest(const GfAssetPack *pack) const;
  void releaseSlot(GF_SLOT_HANDLE *handle);
  u32 getSlots(GF_SLOT_HANDLE *handle) const;
  const char *getSlotName(GF_SLOT_HANDLE *handle) const;
  const char *getSlotName(GfAssetType type) const;
  f32 getSlotUsingRatio(GfAssetType type) const;
  size_t getSlotSize(GfAssetType type) const;
  size_t getSlotBlockSize(GfAssetType type) const;
  u32 getSlotCount(GfAssetType type) const;
  GF_SLOT_HANDLE *getSlotHandle(GfAssetType type, u32 index) const;
  u32 getSystemSlotCount(GfAssetType type) const;
  bool isSystemSlotParent(GfAssetType type, u32 index);
  bool isSystemSlotChild(GfAssetType type, u32 index);
  GF_SLOT_HANDLE *getSystemSlotHandle(GfAssetType type, u32 index);
  u32 getSlotNumByByteSize(GfAssetType type, size_t size) const;
  GF_SLOT_HANDLE *allocateSlot(GfAssetType type, size_t size);
  bool getSlotInfo(mm::mtl::IAllocator *&allocator, void *&buffer, size_t &size, GF_SLOT_HANDLE *handle);
  bool isExistAsset(GF_SLOT_HANDLE *handle) const;
  void *allocateSize(size_t size, size_t alignment);
  bool deallocateSize(void *pointer);

  GfSlotAllocator *unknown00;                       // Inferred role: allocator; original member name unknown.
  GfSlotAll *unknown08;                             // Inferred role: slot all; original member name unknown.
  mm::mtl::FixedVector<REQ, REQUEST_MAX> unknown10; // Inferred role: requests; original member name unknown.
  u64 unknown1818;                                  // Inferred role: top address; original member name unknown.
  u64 unknown1820;                                  // Inferred role: end address; original member name unknown.
};

static_assert(sizeof(GfSlotMapping::REQ) == 0x18, "");
static_assert(sizeof(GfSlotMapping::ExtendSlotAllocator) == 0x18, "");
static_assert(offsetof(GfSlotMapping, unknown10) == 0x10, "");
static_assert(offsetof(GfSlotMapping, unknown1818) == 0x1818, "");
static_assert(sizeof(GfSlotMapping) == 0x1828, "");

} // namespace gf
