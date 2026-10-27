#pragma once
#include "gf/asset/gf_asset_def.h"

namespace gf {

struct GF_ASSET_HANDLE;
struct GF_SLOT_HANDLE;

class GfAssetUtil {
public:
  static bool isEnableDeleteObject(GF_SLOT_HANDLE *handle);
  static bool isObjectDestroy(GF_ASSET_HANDLE *handle);
  static void addDestroyObject(GF_ASSET_HANDLE *handle, bool flag);
  static const char *getAssetTypeName(GfAssetType type);
};

} // namespace gf
