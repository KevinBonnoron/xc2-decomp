#pragma once
#include <stddef.h>

#include "gf/asset/gf_asset_def.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/fixstr.h"
#include "types.h"

namespace gf {

struct GF_ASSET_HANDLE;
struct GF_SLOT_HANDLE;
class GfAssetPack;
class GfExtendResource;

struct AssetPackInfo {
  virtual ~AssetPackInfo();
  void setLoadComplete();
  void setupLoadStart();
  void replaceAssetPack(GfAssetType from, GfAssetType to, GfAssetPack *pack);
  void setExtendResource(u32 index, GfExtendResource *resource);
  void releaseExtResource();
  void setNoCache(bool noCache);
  bool isUseSameAsset(const AssetPackInfo *other) const;
  bool isFullResource() const;
  bool isExistAssetPack(const GfAssetPack *pack) const;
  void setDestroy();
  GfAssetPack *getAssetPack(GF_SLOT_HANDLE *handle) const;
  void setAssetPack(GfAssetType type, GfAssetPack *pack);
  void setModelName(const char *name);
  void setMotionName(const char *name);
  bool getSlotHandle(mm::mtl::FixedVector<GF_SLOT_HANDLE *, 88> &slots) const;

  GF_ASSET_HANDLE *unknown08;                        // Inferred role: handle; original member name unknown.
  mm::mtl::FixedVector<GfAssetPack *, 88> unknown10; // Inferred role: asset packs; original member name unknown.
  s64 unknown2d8;                                    // Inferred role: invalid marker; original member name unknown.
  GfExtendResource *unknown2e0[4];                   // Inferred role: extend resources; original member name unknown.
  u32 unknown300;                                    // Inferred role: priority; original member name unknown.
  bool unknown304;                                   // Inferred role: destroy requested; original member name unknown.
  bool unknown305;                                   // Inferred role: using game; original member name unknown.
  bool unknown306;                                   // Inferred role: unknown flag, written with its neighbours at construction; original member name unknown.
  bool unknown307;                                   // Inferred role: reload; original member name unknown.
  GfAssetType unknown308;                            // Inferred role: first asset type; original member name unknown.
  mm::mtl::FixStr<16> unknown30c;                    // Inferred role: model name; original member name unknown.
  mm::mtl::FixStr<16> unknown320;                    // Inferred role: motion name; original member name unknown.
  u32 unknown334;                                    // Inferred role: load check count; original member name unknown.
};

static_assert(offsetof(AssetPackInfo, unknown08) == 0x08, "");
static_assert(offsetof(AssetPackInfo, unknown10) == 0x10, "");
static_assert(offsetof(AssetPackInfo, unknown2d8) == 0x2d8, "");
static_assert(offsetof(AssetPackInfo, unknown2e0) == 0x2e0, "");
static_assert(offsetof(AssetPackInfo, unknown300) == 0x300, "");
static_assert(offsetof(AssetPackInfo, unknown304) == 0x304, "");
static_assert(offsetof(AssetPackInfo, unknown305) == 0x305, "");
static_assert(offsetof(AssetPackInfo, unknown306) == 0x306, "");
static_assert(offsetof(AssetPackInfo, unknown307) == 0x307, "");
static_assert(offsetof(AssetPackInfo, unknown308) == 0x308, "");
static_assert(offsetof(AssetPackInfo, unknown30c) == 0x30c, "");
static_assert(offsetof(AssetPackInfo, unknown320) == 0x320, "");
static_assert(offsetof(AssetPackInfo, unknown334) == 0x334, "");
static_assert(sizeof(AssetPackInfo) == 0x338, "");

} // namespace gf
