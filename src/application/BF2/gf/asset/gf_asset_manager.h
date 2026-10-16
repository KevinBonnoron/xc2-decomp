#pragma once
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace gf {

struct GF_ASSET_HANDLE;
struct GF_SLOT_HANDLE;

class GfAssetManager : public mm::mtl::PtrSingleton<GfAssetManager> {
public:
  static bool isReload(GF_ASSET_HANDLE *handle);
  static void getSlotHandle(mm::mtl::FixedVector<GF_SLOT_HANDLE *, 88> &slots, GF_ASSET_HANDLE *handle);
  bool isFullResource(GF_ASSET_HANDLE *handle) const;
  static const char *getModelInfo(GF_ASSET_HANDLE *handle);
  static const char *getMotionInfo(GF_ASSET_HANDLE *handle);
  static u32 getUsedAssetPackInfo();
  void releaseRefResource(void *data);
};

} // namespace gf
