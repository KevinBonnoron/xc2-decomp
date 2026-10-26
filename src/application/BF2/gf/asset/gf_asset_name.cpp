#include "gf/asset/gf_asset_name.h"

namespace gf {

static const char *const unknown001[10] = {"ma", "", "pc", "bl", "en", "np", "mb", "oj", "", "wp"}; // Inferred role: object type prefixes; original name unknown.

void GfAssetName::clear() {
  unknown00[0] = '\0';
  unknown10 = 0;
  unknown14.clear();
}

const char *GfAssetName::getPrefix(u32 type) {
  if (type - 1 < 10) {
    return unknown001[static_cast<int>(type - 1)];
  }
  return "";
}

void GfAssetName::setObjType(u32 type) { unknown14 = getPrefix(type); }

void GfAssetName::setIdUpper(u32 id) {
  unknown00[2] = '0' + id / 10;
  unknown00[3] = '0' + id % 10;
}

void GfAssetName::setIdMiddle(u32 id) {
  unknown00[4] = '0' + id / 10;
  unknown00[5] = '0' + id % 10;
}

void GfAssetName::setIdLower(u32 id) {
  unknown00[6] = '0' + id / 10;
  unknown00[7] = '0' + id % 10;
}

bool GfAssetName::hasCategory() const { return unknown10 > 9; }

const char *GfAssetName::getCategory() const {
  if (unknown10 > 9) {
    return &unknown00[8];
  }
  return nullptr;
}

void GfAssetName::cutCategory() {
  if (unknown10 > 9) {
    unknown00[8] = '\0';
    unknown10 = 8;
  }
}

const char *GfAssetName::getName() {
  unknown38.format("%s%s", unknown14.c_str(), unknown00);
  return unknown38.c_str();
}

} // namespace gf
