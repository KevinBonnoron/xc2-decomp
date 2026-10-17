#pragma once
#include <stddef.h>

#include "types.h"
#include "ui/list/ui_list_info.h"

namespace gf {

struct MenuMissionInfo {
  u32 mission;
};

static_assert(sizeof(MenuMissionInfo) == 0x4, "");

class GfMenuMissionList : public ui::UIListInfo<MenuMissionInfo> {
public:
  struct MissionSetup {
    SetupParam param;
    u32 zone;
  };

  GfMenuMissionList();
  ~GfMenuMissionList() override;
  static GfMenuMissionList *create();
  void setupFromZone(const MissionSetup &setup);
};

static_assert(offsetof(GfMenuMissionList::MissionSetup, zone) == 0x14, "");
static_assert(sizeof(GfMenuMissionList) == 0x68, "");

} // namespace gf
