#pragma once
#include <stddef.h>

#include "gf/asset/gf_asset_def.h"
#include "mm_mtl/fixed_queue.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/reference_object.h"
#include "types.h"

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
    GfFileIdx unknown00; // Inferred role: file index; original member name unknown.
    u8 _04[0x10 - 0x04];
    mm::mtl::FixStr<128> unknown10; // Inferred role: file name; original member name unknown.
    int unknown94;                  // Inferred role: file size; original member name unknown.
    bool unknown98;                 // Inferred role: model file; original member name unknown.
  };

  bool addResource(GfFileIdx index, const char *name);
  const mm::mtl::FixStr<128> &getFileName(GfFileIdx index) const;

  GfAssetType unknown00; // Inferred role: asset type; original member name unknown.
  u8 _04[0x08 - 0x04];
  mm::mtl::FixStr<64> unknown08; // Inferred role: asset name; original member name unknown.
};

static_assert(offsetof(GfAssetFiles, unknown08) == 0x08, "");
static_assert(offsetof(GfAssetFiles::AssetFile, unknown10) == 0x10, "");
static_assert(offsetof(GfAssetFiles::AssetFile, unknown94) == 0x94, "");
static_assert(offsetof(GfAssetFiles::AssetFile, unknown98) == 0x98, "");

class GfAssetPack : public mm::mtl::ReferenceObject {
public:
  GfAssetResource *getResource(GfFileIdx index) const;
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

  void setLoadSlotNum(u32 num) { unknown24c = num; }

  u8 _0c[0x120 - 0x0c];
  GfAssetFiles m_assetType;
  u8 _16c[0x170 - 0x16c];
  mm::mtl::FixedVector<GfAssetFiles::AssetFile *, 16> unknown170; // Inferred role: files; original member name unknown.
  u8 _1f8[0x228 - 0x1f8];
  bool unknown228; // Inferred role: resource locked; original member name unknown.
  u8 _229[0x230 - 0x229];
  GF_SLOT_HANDLE *unknown230; // Inferred role: slot handle; original member name unknown.
  bool unknown238;            // Inferred role: force destroy flag; original member name unknown.
  bool unknown239;            // Inferred role: no cache flag; original member name unknown.
  bool unknown23a;            // Inferred role: waiting slot; original member name unknown.
  bool unknown23b;            // Inferred role: timeout flag; original member name unknown.
  u8 _23c[0x248 - 0x23c];
  u32 unknown248; // Inferred role: slot num; original member name unknown.
  u32 unknown24c; // Inferred role: load slot num; original member name unknown.
  u32 unknown250; // Inferred role: priority; original member name unknown.
  u32 unknown254; // Inferred role: user count; original member name unknown.
  u8 _258[0x27c - 0x258];
  u32 unknown27c; // Inferred role: cache count; original member name unknown.
  u32 unknown280; // Inferred role: reload count; original member name unknown.
  u8 _284[0x2b0 - 0x284];
  GfFileIdx unknown2b0; // Inferred role: se pack file index; original member name unknown.
  u8 _2b4[0x2b8 - 0x2b4];
  bool unknown2b8; // Inferred role: resource locked; original member name unknown.
};

static_assert(offsetof(GfAssetPack, m_assetType) == 0x120, "");
static_assert(offsetof(GfAssetPack, unknown170) == 0x170, "");
static_assert(offsetof(GfAssetPack, unknown228) == 0x228, "");
static_assert(offsetof(GfAssetPack, unknown230) == 0x230, "");
static_assert(offsetof(GfAssetPack, unknown238) == 0x238, "");
static_assert(offsetof(GfAssetPack, unknown239) == 0x239, "");
static_assert(offsetof(GfAssetPack, unknown23a) == 0x23a, "");
static_assert(offsetof(GfAssetPack, unknown248) == 0x248, "");
static_assert(offsetof(GfAssetPack, unknown254) == 0x254, "");
static_assert(offsetof(GfAssetPack, unknown280) == 0x280, "");
static_assert(offsetof(GfAssetPack, unknown2b8) == 0x2b8, "");
static_assert(offsetof(GfAssetPack, unknown2b0) == 0x2b0, "");

} // namespace gf
