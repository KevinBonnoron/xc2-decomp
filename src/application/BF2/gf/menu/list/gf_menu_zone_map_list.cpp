#include "gf/menu/list/gf_menu_zone_map_list.h"

namespace gf {

GfMenuZoneMapList::~GfMenuZoneMapList() {
  // A body that is not empty keeps the vtable pointer store that the game does.
  ;
}

bool GfMenuZoneMapList::sortPriority(const MenuZoneMapInfo &info, const MenuZoneMapInfo &other) {
  if (info.priority == other.priority) {
    return info.mapId < other.mapId;
  }
  return info.priority < other.priority;
}

} // namespace gf
