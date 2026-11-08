#include "gf/field/gf_gmk_locator_atlas.h"

#include <string.h>

#include "bdat.h"
#include "gf/data/gf_bdat_id.h"
#include "gf/data/gf_data_bdat.h"
#include "gf/data/gf_data_map.h"
#include "gf/gf_allocator.h"
#include "gf/menu/gf_menu_map_info.h"
#include "gmk/gmk_bdat.h"
#include "gmk/gmk_manager.h"

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

bool GfGmkLocatorAtlas::isBelongToCurMap(const mm::Vec3 &position) const {
  if (unknown00 <= 0 || unknown04 <= 0) {
    return false;
  }
  const BdatInfo *info = getBdatInfo(unknown04);
  if (info == nullptr || GfMenuMapInfo::get() == nullptr) {
    return false;
  }
  const char *mapName = GfDataMap::getMapResourceNameByMapID(unknown00);
  if (mapName == nullptr) {
    return false;
  }
  int mapIndex = GfMenuMapInfo::getMapInfoIndex(mapName);
  const char *levelName = info->unknown00;
  if (levelName == nullptr) {
    return false;
  }
  const GfMenuMapInfo::MapAreaInfo *area = GfMenuMapInfo::getMapAreaFromName(mapIndex, levelName);
  if (area == nullptr) {
    return false;
  }
  u16 priority;
  if (position.x < area->unknown20 || area->unknown2c <= position.x || position.y < area->unknown24 || area->unknown30 <= position.y || position.z < area->unknown28 || area->unknown34 <= position.z) {
    priority = 0;
  } else {
    priority = info->unknown08;
  }
  u32 areaCount = GfMenuMapInfo::getMapAreaCount(mapIndex);
  for (u32 i = 0; i < areaCount; i++) {
    const GfMenuMapInfo::MapAreaInfo *other = GfMenuMapInfo::getMapArea(mapIndex, i);
    if (other == nullptr || strncmp(other->unknown00, levelName, 0x1f) == 0) {
      continue;
    }
    if (position.x < other->unknown20 || other->unknown2c <= position.x || position.y < other->unknown24 || other->unknown30 <= position.y || position.z < other->unknown28 ||
        other->unknown34 <= position.z) {
      continue;
    }
    u16 otherPriority = 0xffff;
    u32 bdatInfoNum = unknown30.size();
    for (u32 j = 0; j < bdatInfoNum; j++) {
      const BdatInfo &bdatInfo = unknown30[j];
      if (strcmp(bdatInfo.unknown00, other->unknown00) == 0) {
        otherPriority = bdatInfo.unknown08;
        break;
      }
    }
    if (priority > otherPriority) {
      return false;
    }
  }
  return true;
}

void GfGmkLocatorAtlas::seqWaitToCreateCurMapGmkSet(f32) {
  gmk::GmkManager *manager = gmk::GmkManager::get();
  if (!manager->unknownf358.empty()) {
    unknown60 = manager->unknownf358[0];
    unknown438 = &GfGmkLocatorAtlas::seqWaitToCreateGmkSet;
  }
}

} // namespace gf

template void mm::mtl::Vector<gf::GfGmkLocatorAtlas::BdatInfo>::expand(size_t, size_t);
template void mm::mtl::Vector<gf::GfGmkLocatorAtlas::BdatInfo>::extend(size_t, size_t);
template void mm::mtl::Vector<gf::GfGmkLocatorAtlas::BdatInfo>::resize(size_t);
