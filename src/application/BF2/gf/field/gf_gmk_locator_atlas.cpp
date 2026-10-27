#include "gf/field/gf_gmk_locator_atlas.h"

namespace gf {

constexpr f32 AREA_LIMIT = 1.0e12f;

GfGmkLocatorAtlas::GfGmkLocatorAtlas(const CreateInfo *info)
    : unknown00(0), unknown04(0), unknown10(AREA_LIMIT, AREA_LIMIT, AREA_LIMIT), unknown20(-AREA_LIMIT, -AREA_LIMIT, -AREA_LIMIT), unknown58(-1), unknown60(nullptr), unknown70(nullptr),
      unknown438(nullptr) {
  if (info != nullptr) {
    create(*info);
  }
}

const GfGmkLocatorAtlas::BdatInfo *GfGmkLocatorAtlas::getBdatInfo(int id) const {
  if (unknown00 > 0) {
    s32 index = id - unknown58;
    if (index >= 0 && !(unknown30.size() <= static_cast<size_t>(index))) {
      return &unknown30[index];
    }
  }
  return nullptr;
}

void GfGmkLocatorAtlas::disposeBdatInfos() {
  unknown58 = -1;
  unknown30.destroy();
}

void GfGmkLocatorAtlas::update(f32 deltaTime) {
  if (unknown00 > 0) {
    if (unknown70.isValid()) {
      unknown70.update(deltaTime);
    }
    if (unknown438) {
      (this->*unknown438)(deltaTime);
    }
  }
}

} // namespace gf
