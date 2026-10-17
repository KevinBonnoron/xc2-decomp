#include "gf/menu/list/gf_menu_team_list.h"

#include "gf/data/gf_data_mercenaries.h"
#include "gf/gf_allocator.h"
#include "mm_mtl/fixed_vector.h"

namespace gf {

GfMenuTeamList::GfMenuTeamList() {}

GfMenuTeamList::~GfMenuTeamList() { ; }

GfMenuTeamList *GfMenuTeamList::create() {
  // __LINE__ must be 38 as in the original source: it is the line argument of operator new.
#line 38
  GfMenuTeamList *list = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) GfMenuTeamList();
  list->addRef();
  return list;
}

void GfMenuTeamList::setupFromMercenaries(const TeamSetup &setup) {
  mm::mtl::FixedVector<u16, 3> teams;
  u32 teamNum = GfDataMercenaries::getTeamNum();
  for (u32 team = 1; team <= teamNum; team++) {
    teams.push_back(team);
  }
  SetupParam param = setup.param;
  UIListInfo<MenuTeamInfo>::setup(getAllocator(ALLOCATOR_DEFAULT), param);
  if (isValid()) {
    MenuTeamInfo info = {};
    for (u32 i = 0; i < teams.size(); i++) {
      info.team = *teams.at(i);
      addContents(info);
    }
  }
}

} // namespace gf
