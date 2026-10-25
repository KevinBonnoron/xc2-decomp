#pragma once
#include <stddef.h>

#include "gf/asset/gf_asset_def.h"
#include "mm_mtl/fixed_queue.h"
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
  bool addResource(GfFileIdx index, const char *name);
  const mm::mtl::FixStr<128> &getFileName(GfFileIdx index) const;

  GfAssetType unknown00; // Inferred role: asset type; original member name unknown.
};

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

  void setLoadSlotNum(u32 num) { unknown24c = num; }

  u8 _0c[0x120 - 0x0c];
  GfAssetFiles m_assetType;
  u8 _124[0x230 - 0x124];
  GF_SLOT_HANDLE *unknown230; // Inferred role: slot handle; original member name unknown.
  u8 _238[0x23a - 0x238];
  bool unknown23a; // Inferred role: waiting slot; original member name unknown.
  u8 _23b[0x248 - 0x23b];
  u32 unknown248; // Inferred role: slot num; original member name unknown.
  u32 unknown24c; // Inferred role: load slot num; original member name unknown.
  u32 unknown250; // Inferred role: priority; original member name unknown.
  u32 unknown254; // Inferred role: user count; original member name unknown.
  u8 _258[0x2b0 - 0x258];
  GfFileIdx unknown2b0; // Inferred role: se pack file index; original member name unknown.
};

static_assert(offsetof(GfAssetPack, m_assetType) == 0x120, "");
static_assert(offsetof(GfAssetPack, unknown230) == 0x230, "");
static_assert(offsetof(GfAssetPack, unknown23a) == 0x23a, "");
static_assert(offsetof(GfAssetPack, unknown248) == 0x248, "");
static_assert(offsetof(GfAssetPack, unknown254) == 0x254, "");
static_assert(offsetof(GfAssetPack, unknown2b0) == 0x2b0, "");

} // namespace gf
