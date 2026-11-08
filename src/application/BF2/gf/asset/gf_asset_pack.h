#pragma once
#include <stddef.h>

#include "gf/asset/gf_asset_def.h"
#include "mm_mtl/fixed_queue.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/reference_object.h"
#include "types.h"

namespace mm {
namespace mtl {
class IAllocator;
} // namespace mtl
} // namespace mm

namespace fw {
class SoundPack;
} // namespace fw

namespace gf {

class GfAssetResource;
struct GF_ASSET_HANDLE;
struct GF_SLOT_HANDLE;

struct GfAssetFilesInfo {
  GfAssetFilesInfo() : unknown00(INVALID_ASSET_HANDLE), unknown08(ASSET_TYPE_BASE), unknown30(nullptr), _38(), unknown3c(1), unknown40(0) {}

  GF_ASSET_HANDLE *unknown00;                    // Inferred role: handle; original member name unknown.
  GfAssetType unknown08;                         // Inferred role: asset type; original member name unknown.
  mm::mtl::FixedQueue<GfAssetType, 4> unknown10; // Inferred role: backup asset types; original member name unknown.
  const char *unknown30;                         // Inferred role: name; original member name unknown.
  u8 _38[0x3c - 0x38];
  u32 unknown3c; // Inferred role: slot num; original member name unknown.
  u32 unknown40; // Inferred role: priority; original member name unknown.
};

static_assert(offsetof(GfAssetFilesInfo, unknown08) == 0x08, "");
static_assert(offsetof(GfAssetFilesInfo, unknown10) == 0x10, "");
static_assert(offsetof(GfAssetFilesInfo, unknown30) == 0x30, "");
static_assert(offsetof(GfAssetFilesInfo, unknown3c) == 0x3c, "");
static_assert(offsetof(GfAssetFilesInfo, unknown40) == 0x40, "");
static_assert(sizeof(GfAssetFilesInfo) == 0x48, "");

class GfAssetFiles {
public:
  struct AssetFile {
    AssetFile(GfFileIdx index, const char *name);

    GfFileIdx unknown00; // Inferred role: file index; original member name unknown.
    u8 _04[0x08 - 0x04];
    u64 unknown08;                  // Inferred role: file size request handle; original member name unknown.
    mm::mtl::FixStr<128> unknown10; // Inferred role: file name; original member name unknown.
    int unknown94;                  // Inferred role: file size; original member name unknown.
    bool unknown98;                 // Inferred role: model file; original member name unknown.
    u8 _99[0xa0 - 0x99];
  };

  ~GfAssetFiles();
  bool addResource(GfFileIdx index, const char *name);
  void setInitializeParam(const GfAssetFilesInfo &info);
  void addResourceWithLockAsset(GfFileIdx index, const char *name);
  void replaceAssetType(GfAssetType type);
  void destroyFileSizeCache();
  void applyPreFileSize();
  bool isPreSizeSizeValid() const;
  s64 calcAllFileSize() const;
  s64 calcFileSize(GfFileIdx index) const;
  bool isExistSameAsset(const GfAssetFiles &other) const;
  const mm::mtl::FixStr<128> &getFileName(GfFileIdx index) const;
  GfFileIdx getCommonResource(GfFileIdx index) const;
  bool isExistFile(GfFileIdx index) const;
  bool isNoFile(GfFileIdx index) const;

  GfAssetType unknown00;         // Inferred role: asset type; original member name unknown.
  u32 unknown04;                 // Inferred role: asset name hash; original member name unknown.
  mm::mtl::FixStr<64> unknown08; // Inferred role: asset name; original member name unknown.
  u8 _4c[0x50 - 0x4c];
  mm::mtl::FixedVector<AssetFile *, 16> unknown50; // Inferred role: files; original member name unknown.
  mm::mtl::FixedVector<u32, 8> unknownd8;          // Inferred role: common resources, file index in the low half and replacing file index in the high half; original member name unknown.
  u8 _100[0x108 - 0x100];
  bool unknown108; // Inferred role: resource locked; original member name unknown.
  u8 _109[0x110 - 0x109];
};

static_assert(offsetof(GfAssetFiles, unknown04) == 0x04, "");
static_assert(offsetof(GfAssetFiles, unknown08) == 0x08, "");
static_assert(offsetof(GfAssetFiles, unknown50) == 0x50, "");
static_assert(offsetof(GfAssetFiles, unknownd8) == 0xd8, "");
static_assert(offsetof(GfAssetFiles, unknown108) == 0x108, "");
static_assert(sizeof(GfAssetFiles) == 0x110, "");
static_assert(offsetof(GfAssetFiles::AssetFile, unknown08) == 0x08, "");
static_assert(offsetof(GfAssetFiles::AssetFile, unknown10) == 0x10, "");
static_assert(offsetof(GfAssetFiles::AssetFile, unknown94) == 0x94, "");
static_assert(offsetof(GfAssetFiles::AssetFile, unknown98) == 0x98, "");
static_assert(sizeof(GfAssetFiles::AssetFile) == 0xa0, "");

// Layout evidence: GfAssetPack::calcAssetPackValue (0x71001bbbc8) and the GfAssetPack constructor build it from the asset type
// in the low word and the name hash in the high word; AssetPackInfo::isExistAssetPack compares it as one 64-bit value.
struct AssetPackValue {
  GfAssetType unknown00; // Inferred role: asset type; original member name unknown.
  u32 unknown04;         // Inferred role: asset name hash; original member name unknown.
};

static_assert(offsetof(AssetPackValue, unknown04) == 0x04, "");
static_assert(sizeof(AssetPackValue) == 0x08, "");

class GfAssetPack : public mm::mtl::ReferenceObject {
public:
  // Inferred role: loaded resource of one file, pushed by setResource; original name unknown.
  struct unknown001 {
    GfAssetResource *unknown00; // Inferred role: resource; original member name unknown.
    u16 unknown08;              // Inferred role: file index; original member name unknown.
  };

  GfAssetPack(const GfAssetFilesInfo &info);
  GfAssetResource *getResource(GfFileIdx index) const;
  bool isLoaded(mm::mtl::FixStr<128> *name) const;
  void setupStreamObject();
  bool isStopLoad() const;
  fw::SoundPack *getSePackByFileIdx(GfFileIdx index);
  const char *getLoadingFileForDebug();
  bool isExistReferenceMemory() const;
  u64 getTimeStamp(const char *name);
  bool isNeedLoad() const;
  bool releaseRefResource(void *data);
  ~GfAssetPack() override;
  GfAssetType getAssetType() const;
  void dispAssetLogForDebug();
  void setLoadComplete();
  const char *getAssetName() const;
  bool isPreSizeSizeValid() const;
  void setResource(GfFileIdx index, GfAssetResource *resource);
  size_t getNeedLoadFileSize(size_t blockSize, bool);
  void setTimeout();
  bool changeBackupAssetType();
  void lockEnterRersource();
  bool setForceDestroy();
  void updateCacheCount();
  void updateReloadCount();
  bool isEnableReload() const;
  void releaseSlotHandle();
  bool isExistSameAsset(const GfAssetPack &other) const;
  void loadStart(mm::mtl::IAllocator *allocator);
  void releaseResource();
  void createSoundPack();
  void destroySoundPack();
  void releaseEmptySlot();
  bool isCached() const;
  void applyPreFileSize();
  void calcAllFileSize();
  s64 getAllFileSize();
  void replaceAssetType(const GfAssetFilesInfo &info);
  static GfAssetPack *create(const GfAssetFilesInfo &info);
  static AssetPackValue calcAssetPackValue(const char *name, GfAssetType type);

  void setLoadSlotNum(u32 num) { unknown24c = num; }

  u8 _0c[0x10 - 0x0c];
  u64 unknown10;                                  // Inferred role: asset pack value (AssetPackValue as one 64-bit word); original member name unknown.
  mm::mtl::FixedVector<unknown001, 16> unknown18; // Inferred role: resources; original member name unknown.
  GfAssetFiles m_assetType;
  GF_SLOT_HANDLE *unknown230; // Inferred role: slot handle; original member name unknown.
  bool unknown238;            // Inferred role: force destroy flag; original member name unknown.
  bool unknown239;            // Inferred role: no cache flag; original member name unknown.
  bool unknown23a;            // Inferred role: waiting slot; original member name unknown.
  bool unknown23b;            // Inferred role: timeout flag; original member name unknown.
  u8 _23c[0x240 - 0x23c];
  s64 unknown240; // Inferred role: total file size, -1 until computed; original member name unknown.
  u32 unknown248; // Inferred role: slot num; original member name unknown.
  u32 unknown24c; // Inferred role: load slot num; original member name unknown.
  u32 unknown250; // Inferred role: priority; original member name unknown.
  u32 unknown254; // Inferred role: user count; original member name unknown.
  u8 _258[0x27c - 0x258];
  u32 unknown27c; // Inferred role: cache count; original member name unknown.
  u32 unknown280; // Inferred role: reload count; original member name unknown.
  u8 _284[0x288 - 0x284];
  mm::mtl::FixedQueue<GfAssetType, 4> unknown288; // Inferred role: backup asset types; original member name unknown.
  fw::SoundPack *unknown2a8;                      // Inferred role: se pack; original member name unknown.
  GfFileIdx unknown2b0;                           // Inferred role: se pack file index; original member name unknown.
  int unknown2b4;                                 // Inferred role: se pack reference count; original member name unknown.
  bool unknown2b8;                                // Inferred role: resource locked; original member name unknown.
};

static_assert(sizeof(GfAssetPack::unknown001) == 0x10, "");
static_assert(offsetof(GfAssetPack, unknown18) == 0x18, "");
static_assert(offsetof(GfAssetPack, m_assetType) == 0x120, "");
static_assert(offsetof(GfAssetPack, unknown230) == 0x230, "");
static_assert(offsetof(GfAssetPack, unknown238) == 0x238, "");
static_assert(offsetof(GfAssetPack, unknown240) == 0x240, "");
static_assert(offsetof(GfAssetPack, unknown239) == 0x239, "");
static_assert(offsetof(GfAssetPack, unknown23a) == 0x23a, "");
static_assert(offsetof(GfAssetPack, unknown248) == 0x248, "");
static_assert(offsetof(GfAssetPack, unknown254) == 0x254, "");
static_assert(offsetof(GfAssetPack, unknown280) == 0x280, "");
static_assert(offsetof(GfAssetPack, unknown288) == 0x288, "");
static_assert(offsetof(GfAssetPack, unknown2b8) == 0x2b8, "");
static_assert(offsetof(GfAssetPack, unknown2b0) == 0x2b0, "");

} // namespace gf
