#pragma once
#include "gf/asset/gf_asset_def.h"
#include "mm_mtl/fixed_list.h"
#include "mm_mtl/fixed_vector.h"
#include "types.h"

namespace gf {

struct GF_ASSET_HANDLE;
struct GF_OBJ_HANDLE;
struct GF_SLOT_HANDLE;

class GfAssetUtil {
public:
  static bool isEnableDeleteObject(GF_SLOT_HANDLE *handle);
  static void destroyAsset(const mm::mtl::FixedVector<GF_SLOT_HANDLE *, 88> &slots);
  static bool isObjectDestroy(GF_ASSET_HANDLE *handle);
  static void addDestroyObject(GF_ASSET_HANDLE *handle, bool flag);
  static GF_OBJ_HANDLE *getObjHandle(GF_ASSET_HANDLE *handle);
  static u32 getAssetPrio(GF_ASSET_HANDLE *handle);
  static bool isRetargetLoad(GF_ASSET_HANDLE *handle);
  static void setRetargetLoad(GF_ASSET_HANDLE *handle, bool isRetarget);
  static const char *getAssetTypeName(GfAssetType type);
  static void getAssetHandleBySlotHandle(mm::mtl::FixedList<GF_ASSET_HANDLE *, 1024> &assets, const mm::mtl::FixedList<GF_ASSET_HANDLE *, 1024> &handles, GF_SLOT_HANDLE *slot);
};

} // namespace gf
