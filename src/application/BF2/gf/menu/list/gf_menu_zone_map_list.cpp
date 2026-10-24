#include "gf/menu/list/gf_menu_zone_map_list.h"

#include <functional>

#include "gf/gf_allocator.h"

namespace gf {

GfMenuZoneMapList::GfMenuZoneMapList() : unknown79(false) {}

GfMenuZoneMapList::~GfMenuZoneMapList() { ; }

GfMenuZoneMapList *GfMenuZoneMapList::create() {
  // __LINE__ must be 36 as in the original source: it is the line argument of operator new.
#line 36
  GfMenuZoneMapList *list = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) GfMenuZoneMapList();
  list->addRef();
  return list;
}

void GfMenuZoneMapList::sortFromPriority() { sort(sortPriority); }

bool GfMenuZoneMapList::sortPriority(const MenuZoneMapInfo &info, const MenuZoneMapInfo &other) {
  if (info.unknown14 == other.unknown14) {
    return info.unknown00 < other.unknown00;
  }
  return info.unknown14 < other.unknown14;
}

} // namespace gf
