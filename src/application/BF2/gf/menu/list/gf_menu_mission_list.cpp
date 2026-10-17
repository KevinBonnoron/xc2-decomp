#include "gf/menu/list/gf_menu_mission_list.h"

#include "gf/game/mercenaries/gf_game_mercenaries.h"
#include "gf/gf_allocator.h"
#include "mm_mtl/fixed_vector.h"

namespace gf {

GfMenuMissionList::GfMenuMissionList() {}

GfMenuMissionList::~GfMenuMissionList() {
  // A body that is not empty keeps the vtable pointer store that the game does.
  ;
}

GfMenuMissionList *GfMenuMissionList::create() {
  // __LINE__ must be 38 as in the original source: it is the line argument of operator new.
#line 38
  GfMenuMissionList *list = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) GfMenuMissionList();
  list->addRef();
  return list;
}

void GfMenuMissionList::setupFromZone(const MissionSetup &setup) {
  mm::mtl::FixedVector<u16, 500> missions;
  GfGameMercenaries::getZoneMission(missions, setup.zone);
  SetupParam param = setup.param;
  UIListInfo<MenuMissionInfo>::setup(getAllocator(ALLOCATOR_DEFAULT), param);
  if (isValid()) {
    MenuMissionInfo info = {};
    for (u32 i = 0; i < missions.size(); i++) {
      info.mission = *missions.at(i);
      addContents(info);
    }
  }
}

} // namespace gf
