#pragma once
#include <stddef.h>

#include "gf/asset/gf_asset_def.h"
#include "gf/asset/gf_asset_pack_info.h"
#include "ml/fixed_size_alloc.h"
#include "ml/work_event.h"
#include "mm_mtl/fixed_list.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/fixstr.h"
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
class GfExtendResource;
class GfSlotMapping;
class GfInitParam;
struct GfAssetFilesInfo;

// Inferred role: listener of the loaded asset packs, registered by GfAssetManager::addEvent; original name known only from the symbols.
class IGfAssetEvent {
public:
  virtual ~IGfAssetEvent() {}
  virtual void unknown001(GfAssetPack *pack) = 0; // Inferred role: called for every loaded asset pack; original name unknown.
};

class GfAssetManager : public mm::mtl::PtrSingleton<GfAssetManager>, public ml::IWorkEvent {
public:
  GfAssetManager(const GfSetupParam &param);
  ~GfAssetManager();
  void initialize(const GfSetupParam &param);
  static void build(const GfSetupParam &param);
  static void destroy();
  void finalize();
  static bool isInitialized();
  static AssetPackInfo *getAssetPackInfo(GF_ASSET_HANDLE *handle);
  static void setNoCacheAsset(GF_ASSET_HANDLE *handle, bool noCache);
  static void destroy(GF_ASSET_HANDLE *handle);
  static void enableGameResource(GF_ASSET_HANDLE *handle);
  static void disableGameResource(GF_ASSET_HANDLE *handle);
  static GF_ASSET_HANDLE *createAssetHandle(const GfInitParam &param);
  static void loadStart(GfAssetPack *pack, mm::mtl::IAllocator *allocator);
  static GfAssetPack *createAssetFiles(const GfAssetFilesInfo &info);
  static void callEventAssetPack(GfAssetPack *pack);
  static void releaseSlotHandle(GF_SLOT_HANDLE *handle);
  static GfAssetPack *getAssetPack(GF_SLOT_HANDLE *handle);
  static GfAssetPack *getAssetPack(GF_ASSET_HANDLE *handle, GfFileIdx index);
  static GfAssetPack *getAssetPack(GfAssetType type, const char *name);
  static bool getAssetPack(mm::mtl::FixedVector<GfAssetPack *, 256> &packs, GfAssetType type);
  static GfAssetPack *getAssetPack(GF_ASSET_HANDLE *handle, GfAssetType type);
  static GfAssetType getBaseAssetType(GF_ASSET_HANDLE *handle);
  static GfSlotMapping *getSlotMapping();
  static GfAssetResource *getResource(GF_ASSET_HANDLE *handle, GfFileIdx index, GfAssetType type);
  static GfAssetResource *getResource(GF_ASSET_HANDLE *handle, const char *name, GfFileIdx index);
  static bool isLoading();
  static bool isLoading(const GfAssetPack *pack);
  static GF_ASSET_HANDLE *getAssetHandle(const char *name);
  static u32 getTimeout(GF_ASSET_HANDLE *handle);
  bool isLoaded(GF_ASSET_HANDLE *handle, mm::mtl::FixStr<128> *name);
  void setupStreamObject(GF_ASSET_HANDLE *handle);
  static bool isStopLoad(GF_ASSET_HANDLE *handle);
  static bool isDestroy(GF_ASSET_HANDLE *handle);
  static bool isReload(GF_ASSET_HANDLE *handle);
  static GF_OBJ_HANDLE *getObj(GF_ASSET_HANDLE *handle);
  static bool isExist(GF_ASSET_HANDLE *handle, GfFileIdx index);
  static void setExtendResource(GF_ASSET_HANDLE *handle, u32 index, GfExtendResource *resource);
  static void destroySlotCache(GfAssetType type);
  static GfExtendResource *getExtentResource(GF_ASSET_HANDLE *handle, u32 index);
  static void destroyExtResource(GF_ASSET_HANDLE *handle);
  static bool isSameAsset(GF_ASSET_HANDLE *handle, GF_ASSET_HANDLE *other);
  static void addEvent(IGfAssetEvent *event);
  static void removeEvent(IGfAssetEvent *event);
  static bool isExistSameAsset(GfAssetPack *pack);
  static bool isExistSameAsset(GF_ASSET_HANDLE *handle, const char *name);
  static void clear();
  static u64 getTimeStamp(const char *name, GfAssetType type);
  static size_t getSlotBlockSize(GfAssetType type);
  static u32 getSlotNumByByteSize(GfAssetType type, size_t size);
  static bool isExistOuterResource();
  static mm::mtl::FixedList<GF_ASSET_HANDLE *, 1024> *getLoadingAsset();
  bool getObjectByUsingAssetPackLocal(mm::mtl::FixedList<GF_OBJ_HANDLE *, 1024> &objects, const mm::mtl::FixedList<GF_ASSET_HANDLE *, 1024> &handles, GF_ASSET_HANDLE *handle) const;
  static bool getSlotHandle(mm::mtl::FixedVector<GF_SLOT_HANDLE *, 88> &slots, GF_ASSET_HANDLE *handle);
  static GF_SLOT_HANDLE *allocateFromAssetTypeSlot(GfAssetType type, size_t size);
  static bool getSlotInfo(mm::mtl::IAllocator *&allocator, void *&buffer, size_t &size, GF_SLOT_HANDLE *handle);
  static void setModelInfo(GF_ASSET_HANDLE *handle, const char *name);
  bool isFullResource(GF_ASSET_HANDLE *handle) const;
  fw::SoundPack *getSePackByFileIdx(GF_ASSET_HANDLE *handle, GfFileIdx index);
  static u32 getUsedAssetPackInfo();
  static u32 getDestroyAssetPackInfo();
  static const char *getModelInfo(GF_ASSET_HANDLE *handle);
  static void setMotionInfo(GF_ASSET_HANDLE *handle, const char *name);
  static const char *getMotionInfo(GF_ASSET_HANDLE *handle);
  void updateCheckLoading();
  void releaseRefResource(void *data);
  static void setupLoadStart(GF_ASSET_HANDLE *handle);
  static void lockEnterRersource(GF_ASSET_HANDLE *handle);
  void updateCheckDestroy();
  void updateCheckCacheReload();
  void update(const fw::UpdateInfo &info);

  ml::fixed_size_alloc_inside<AssetPackInfo, 1024> unknown10; // Inferred role: asset pack info pool; original member name unknown.
  mm::mtl::FixedList<GF_ASSET_HANDLE *, 1024> unknownce0b8;   // Inferred role: loading assets; original member name unknown.
  mm::mtl::FixedList<GF_ASSET_HANDLE *, 1024> unknownd28d8;   // Inferred role: destroying assets; original member name unknown.
  mm::mtl::FixedList<GF_ASSET_HANDLE *, 1024> unknownd70f8;   // Inferred role: reloading assets; original member name unknown.
  u32 unknowndb918;                                           // Inferred role: handle serial; original member name unknown.
  mm::mtl::FixedList<GfAssetPack *, 1024> unknowndb920;       // Inferred role: asset packs; original member name unknown.
  mm::mtl::FixedList<u32, 32> unknowne0140;                   // Inferred role: asset types whose slot cache is destroyed; original member name unknown.
  GfSlotMapping *m_slotMapping;
  mm::mtl::FixedList<IGfAssetEvent *, 32> unknowne0280; // Inferred role: asset events; original member name unknown.
  bool unknowne04c0;                                    // Inferred role: initialized; original member name unknown.
  bool unknowne04c1;                                    // Inferred role: finalizing; original member name unknown.
};

static_assert(offsetof(GfAssetManager, unknown10) == 0x10, "");
static_assert(offsetof(GfAssetManager, unknownce0b8) == 0xce0b8, "");
static_assert(offsetof(GfAssetManager, unknownd28d8) == 0xd28d8, "");
static_assert(offsetof(GfAssetManager, unknownd70f8) == 0xd70f8, "");
static_assert(offsetof(GfAssetManager, unknowndb918) == 0xdb918, "");
static_assert(offsetof(GfAssetManager, unknowndb920) == 0xdb920, "");
static_assert(offsetof(GfAssetManager, unknowne0140) == 0xe0140, "");
static_assert(offsetof(GfAssetManager, unknowne0280) == 0xe0280, "");
static_assert(offsetof(GfAssetManager, m_slotMapping) == 0xe0278, "");
static_assert(offsetof(GfAssetManager, unknowne04c0) == 0xe04c0, "");
static_assert(sizeof(GfAssetManager) == 0xe04c8, "");

} // namespace gf
