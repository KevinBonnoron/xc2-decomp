#pragma once
#include "gf/asset/gf_asset_def.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace gf {

struct GF_ASSET_HANDLE;
struct GF_SLOT_HANDLE;
class GfAssetPack;
class GfAssetResource;
struct GfAssetFilesInfo;

class GfAssetManager : public mm::mtl::PtrSingleton<GfAssetManager> {
public:
  static void destroy(GF_ASSET_HANDLE *handle);
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
  void releaseRefResource(void *data);
  static void lockEnterRersource(GF_ASSET_HANDLE *handle);
};

} // namespace gf
