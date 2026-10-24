#pragma once
#include "types.h"
#include "ui/list/ui_list_info.h"

namespace gf {

struct MenuID {
  u32 unknown00; // Inferred role: id; original member name unknown.
  u8 _04[0x8 - 0x4];
};

static_assert(sizeof(MenuID) == 0x8, "");

class GfMenuIDList : public ui::UIListInfo<MenuID> {
public:
  GfMenuIDList();
  ~GfMenuIDList() override;
  static GfMenuIDList *create();
  void setupMercenaryZoneList(const SetupParam &param, bool isCondition);
  void setupMissionListFromZone(const SetupParam &param, u32 zone);
  static bool sortMissionComplete(const MenuID &mission, const MenuID &other);
  void setupTeamList(const SetupParam &param);
  void setupExcTaskListFromShop(const SetupParam &param, u32 shop);
};

static_assert(sizeof(GfMenuIDList) == 0x70, "");

} // namespace gf
