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
  GfAssetFilesInfo() : handle(INVALID_ASSET_HANDLE), assetType(ASSET_TYPE_BASE), name(nullptr), _38(), slotNum(1), priority(0) {}

  GF_ASSET_HANDLE *handle;
  GfAssetType assetType;
  mm::mtl::FixedQueue<GfAssetType, 4> backupAssetTypes;
  const char *name;
  u8 _38[0x3c - 0x38];
  u32 slotNum;
  u32 priority;
};

static_assert(offsetof(GfAssetFilesInfo, assetType) == 0x08, "");
static_assert(offsetof(GfAssetFilesInfo, backupAssetTypes) == 0x10, "");
static_assert(offsetof(GfAssetFilesInfo, name) == 0x30, "");
static_assert(offsetof(GfAssetFilesInfo, slotNum) == 0x3c, "");
static_assert(offsetof(GfAssetFilesInfo, priority) == 0x40, "");
static_assert(sizeof(GfAssetFilesInfo) == 0x48, "");

class GfAssetFiles {
public:
  bool addResource(GfFileIdx index, const char *name);
  const mm::mtl::FixStr<128> &getFileName(GfFileIdx index) const;

  GfAssetType assetType;
};

class GfAssetPack : public mm::mtl::ReferenceObject {
public:
  GfAssetResource *getResource(GfFileIdx index) const;
  GfAssetType getAssetType() const;
  void dispAssetLogForDebug();
  const char *getAssetName() const;
  bool isPreSizeSizeValid() const;
  void setResource(GfFileIdx index, GfAssetResource *resource);
  size_t getNeedLoadFileSize(size_t blockSize, bool);
  void setTimeout();
  bool changeBackupAssetType();

  void setLoadSlotNum(u32 num) { loadSlotNum = num; }

  u8 _0c[0x120 - 0x0c];
  GfAssetFiles files;
  u8 _124[0x230 - 0x124];
  GF_SLOT_HANDLE *slotHandle;
  u8 _238[0x23a - 0x238];
  bool isWaitingSlot;
  u8 _23b[0x248 - 0x23b];
  u32 slotNum;
  u32 loadSlotNum;
  u32 priority;
  u32 userCount;
  u8 _258[0x2b0 - 0x258];
  GfFileIdx sePackFileIndex;
};

static_assert(offsetof(GfAssetPack, files) == 0x120, "");
static_assert(offsetof(GfAssetPack, slotHandle) == 0x230, "");
static_assert(offsetof(GfAssetPack, isWaitingSlot) == 0x23a, "");
static_assert(offsetof(GfAssetPack, slotNum) == 0x248, "");
static_assert(offsetof(GfAssetPack, userCount) == 0x254, "");
static_assert(offsetof(GfAssetPack, sePackFileIndex) == 0x2b0, "");

} // namespace gf
