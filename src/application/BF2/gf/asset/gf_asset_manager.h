#pragma once
#include <stddef.h>

#include "gf/asset/gf_asset_def.h"
#include "mm_mtl/fixed_list.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace fw {
class SoundPack;
struct UpdateInfo;
} // namespace fw

namespace mm {
namespace mtl {
class IAllocator;
} // namespace mtl
} // namespace mm

namespace gf {

struct GF_ASSET_HANDLE;
struct GfSetupParam;
struct GF_OBJ_HANDLE;
struct GF_SLOT_HANDLE;
class GfAssetPack;
class GfAssetResource;
class GfSlotMapping;
struct GfAssetFilesInfo;

class GfAssetManager : public mm::mtl::PtrSingleton<GfAssetManager> {
public:
  static void build(const GfSetupParam &param);
  static void destroy();
  static void destroy(GF_ASSET_HANDLE *handle);
  static void callEventAssetPack(GfAssetPack *pack);
  static void loadStart(GfAssetPack *pack, mm::mtl::IAllocator *allocator);
  static GfAssetPack *createAssetFiles(const GfAssetFilesInfo &info);
  static bool isReload(GF_ASSET_HANDLE *handle);
  static void getSlotHandle(mm::mtl::FixedVector<GF_SLOT_HANDLE *, 88> &slots, GF_ASSET_HANDLE *handle);
  static void setModelInfo(GF_ASSET_HANDLE *handle, const char *name);
  bool isFullResource(GF_ASSET_HANDLE *handle) const;
  static const char *getModelInfo(GF_ASSET_HANDLE *handle);
  static void setMotionInfo(GF_ASSET_HANDLE *handle, const char *name);
  static const char *getMotionInfo(GF_ASSET_HANDLE *handle);
  static u32 getUsedAssetPackInfo();
  static u32 getDestroyAssetPackInfo();
  static mm::mtl::FixedList<GF_ASSET_HANDLE *, 1024> *getLoadingAsset();
  static bool isLoading();
  static bool isInitialized();
  static size_t getSlotBlockSize(GfAssetType type);
  static u32 getSlotNumByByteSize(GfAssetType type, size_t size);
  static GF_SLOT_HANDLE *allocateFromAssetTypeSlot(GfAssetType type, size_t size);
  static bool getSlotInfo(mm::mtl::IAllocator *&allocator, void *&buffer, size_t &size, GF_SLOT_HANDLE *handle);
  static GF_OBJ_HANDLE *getObj(GF_ASSET_HANDLE *handle);
  fw::SoundPack *getSePackByFileIdx(GF_ASSET_HANDLE *handle, GfFileIdx index);
  static GfAssetPack *getAssetPack(GF_ASSET_HANDLE *handle, GfFileIdx index);
  static GfAssetResource *getResource(GF_ASSET_HANDLE *handle, GfFileIdx index, GfAssetType type);
  static void destroySlotCache(GfAssetType type);
  static bool isExistSameAsset(GfAssetPack *pack);
  static void clear();
  void releaseRefResource(void *data);
  static void lockEnterRersource(GF_ASSET_HANDLE *handle);
  void update(const fw::UpdateInfo &info);
  static GfSlotMapping *getSlotMapping();
  static void releaseSlotHandle(GF_SLOT_HANDLE *handle);

  u8 _08[0xce0a0 - 0x08];
  u32 *unknownce0a0;  // Inferred role: asset pack info valid flags; original member name unknown.
  void *unknownce0a8; // Inferred role: asset pack infos; original member name unknown.
  u8 _ce0b0[0xce0b4 - 0xce0b0];
  u32 unknownce0b4;                                         // Inferred role: used asset pack info count; original member name unknown.
  mm::mtl::FixedList<GF_ASSET_HANDLE *, 1024> unknownce0b8; // Inferred role: loading assets; original member name unknown.
  mm::mtl::FixedList<GF_ASSET_HANDLE *, 1024> unknownd28d8; // Inferred role: destroying assets; original member name unknown.
  u8 _d70f8[0xe0278 - 0xd70f8];
  GfSlotMapping *m_slotMapping;
  u8 _e0280[0xe04c0 - 0xe0280];
  bool unknowne04c0; // Inferred role: initialized; original member name unknown.
  u8 _e04c1[0xe04c8 - 0xe04c1];
};

static_assert(offsetof(GfAssetManager, unknownce0a0) == 0xce0a0, "");
static_assert(offsetof(GfAssetManager, unknownce0b4) == 0xce0b4, "");
static_assert(offsetof(GfAssetManager, unknownce0b8) == 0xce0b8, "");
static_assert(offsetof(GfAssetManager, unknownd28d8) == 0xd28d8, "");
static_assert(offsetof(GfAssetManager, m_slotMapping) == 0xe0278, "");
static_assert(offsetof(GfAssetManager, unknowne04c0) == 0xe04c0, "");
static_assert(sizeof(GfAssetManager) == 0xe04c8, "");

} // namespace gf
