#include "gf/field/gf_gmk_locator_atlas.h"

#include "bdat.h"
#include "gf/data/gf_bdat_id.h"
#include "gf/data/gf_data_bdat.h"
#include "gf/gf_allocator.h"
#include "gmk/gmk_bdat.h"

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

void GfGmkLocatorAtlas::createBdatInfos() {
  disposeBdatInfos();
  u8 *bdat = GfDataBdat::getFP(BDAT_MNU_MAP_INFO);
  unknown30.setAllocator(getAllocator(ALLOCATOR_DEFAULT));
  int count = Bdat::getIdCount(bdat);
  unknown30.reserve(count);
  unknown30.resize(count);
  unknown58 = Bdat::getIdTop(bdat);
  for (int i = 0; i < count; i++) {
    BdatInfo &info = unknown30[i];
    int id = unknown58 + i;
    info.unknown00 = reinterpret_cast<const char *>(Bdat::getValCheck(bdat, "level_name", id, gmk::BDAT_TYPE_STRING));
    info.unknown08 = Bdat::getValCheck(bdat, "level_priority", id, gmk::BDAT_TYPE_U16);
  }
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

template void mm::mtl::Vector<gf::GfGmkLocatorAtlas::BdatInfo>::expand(size_t, size_t);
template void mm::mtl::Vector<gf::GfGmkLocatorAtlas::BdatInfo>::extend(size_t, size_t);
template void mm::mtl::Vector<gf::GfGmkLocatorAtlas::BdatInfo>::resize(size_t);
