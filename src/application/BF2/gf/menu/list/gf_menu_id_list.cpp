#include "gf/menu/list/gf_menu_id_list.h"

#include <functional>

#include "gf/data/gf_data_mercenaries.h"
#include "gf/game/mercenaries/gf_game_mercenaries.h"
#include "gf/gf_allocator.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "mm_mtl/fixed_vector.h"

namespace gf {

constexpr u32 MERCENARY_ZONE_FIRST = 1;
constexpr u32 MERCENARY_ZONE_LAST = 7;

struct MercenaryZone {
  u32 unknown00; // Inferred role: zone; original member name unknown.
  u32 unknown04; // Inferred role: condition; original member name unknown.
};

static const MercenaryZone MERCENARY_ZONES[] = {
    {1, 25},
    {2, 26},
    {3, 27},
    {4, 28},
    {5, 29},
    {6, 30},
    {7, 31},
};

GfMenuIDList::GfMenuIDList() {}

GfMenuIDList::~GfMenuIDList() { ; }

GfMenuIDList *GfMenuIDList::create() {
  // __LINE__ must be 52 as in the original source: it is the line argument of operator new.
#line 52
  GfMenuIDList *list = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) GfMenuIDList();
  list->addRef();
  return list;
}

void GfMenuIDList::setupMercenaryZoneList(const SetupParam &param, bool isCondition) {
  SetupParam setupParam = param;
  UIListInfo<MenuID>::setup(getAllocator(ALLOCATOR_DEFAULT), setupParam);
  if (isCondition) {
    for (u32 i = 0; i < sizeof(MERCENARY_ZONES) / sizeof(MERCENARY_ZONES[0]); i++) {
      if (GfMenuObjUtil::getMenuCondition(MERCENARY_ZONES[i].unknown04)) {
        mm::mtl::FixedVector<u16, 500> missions;
        u32 zone = MERCENARY_ZONES[i].unknown00;
        GfGameMercenaries::getZoneMission(missions, zone);
        if (!missions.empty()) {
          MenuID id = {zone};
          addContents(id);
        }
      }
    }
  } else {
    for (u32 zone = MERCENARY_ZONE_FIRST; zone <= MERCENARY_ZONE_LAST; zone++) {
      mm::mtl::FixedVector<u16, 500> missions;
      GfGameMercenaries::getZoneMission(missions, zone);
      if (!missions.empty()) {
        MenuID id = {zone};
        addContents(id);
      }
    }
  }
}

void GfMenuIDList::setupMissionListFromZone(const SetupParam &param, u32 zone) {
  mm::mtl::FixedVector<u16, 500> missions;
  GfGameMercenaries::getZoneMission(missions, zone);
  SetupParam setupParam = param;
  UIListInfo<MenuID>::setup(getAllocator(ALLOCATOR_DEFAULT), setupParam);
  if (isValid()) {
    MenuID id = {};
    for (u32 i = 0; i < missions.size(); i++) {
      id.unknown00 = *missions.at(i);
      addContents(id);
    }
    sort(sortMissionComplete);
  }
}

bool GfMenuIDList::sortMissionComplete(const MenuID &mission, const MenuID &other) {
  bool isComplete = GfDataMercenaries::isOrderOnlyOne(mission.unknown00) && GfDataMercenaries::isMissionCompleteFlag(mission.unknown00);
  bool isOtherComplete = GfDataMercenaries::isOrderOnlyOne(other.unknown00) && GfDataMercenaries::isMissionCompleteFlag(other.unknown00);
  if (isComplete != isOtherComplete) {
    return !isComplete;
  }
  return mission.unknown00 < other.unknown00;
}

void GfMenuIDList::setupTeamList(const SetupParam &param) {
  mm::mtl::FixedVector<u16, 3> teams;
  u32 teamNum = GfDataMercenaries::getTeamNum();
  for (u32 team = 1; team <= teamNum; team++) {
    teams.push_back(team);
  }
  UIListInfo<MenuID>::setup(getAllocator(ALLOCATOR_DEFAULT), param);
  if (isValid()) {
    MenuID id = {};
    for (u32 i = 0; i < teams.size(); i++) {
      id.unknown00 = *teams.at(i);
      addContents(id);
    }
  }
}

} // namespace gf
