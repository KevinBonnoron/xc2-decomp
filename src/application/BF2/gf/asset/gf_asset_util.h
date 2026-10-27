#pragma once

namespace gf {

struct GF_ASSET_HANDLE;
struct GF_SLOT_HANDLE;

class GfAssetUtil {
public:
  static bool isEnableDeleteObject(GF_SLOT_HANDLE *handle);
  static bool isObjectDestroy(GF_ASSET_HANDLE *handle);
  static void addDestroyObject(GF_ASSET_HANDLE *handle, bool flag);
};

} // namespace gf
