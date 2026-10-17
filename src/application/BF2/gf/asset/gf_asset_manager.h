#pragma once
#include "gf/asset/gf_asset_def.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace fw {
struct UpdateInfo;
}

namespace mm {
namespace mtl {
class IAllocator;
} // namespace mtl
} // namespace mm

namespace gf {

struct GF_ASSET_HANDLE;
struct GfSetupParam;
struct GF_SLOT_HANDLE;
class GfAssetPack;
class GfAssetResource;
struct GfAssetFilesInfo;

class GfAssetManager : public mm::mtl::PtrSingleton<GfAssetManager> {
public:
  static void build(const GfSetupParam &param);
  static void destroy();
  static void destroy(GF_ASSET_HANDLE *handle);
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
  static GfAssetPack *getAssetPack(GF_ASSET_HANDLE *handle, GfFileIdx index);
  static GfAssetResource *getResource(GF_ASSET_HANDLE *handle, GfFileIdx index, GfAssetType type);
  static void destroySlotCache(GfAssetType type);
  static bool isExistSameAsset(GfAssetPack *pack);
  static void clear();
  void releaseRefResource(void *data);
  static void lockEnterRersource(GF_ASSET_HANDLE *handle);
  void update(const fw::UpdateInfo &info);
};

} // namespace gf
