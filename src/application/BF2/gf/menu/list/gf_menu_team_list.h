#pragma once
#include "types.h"
#include "ui/list/ui_list_info.h"

namespace gf {

struct MenuTeamInfo {
  u32 team;
};

static_assert(sizeof(MenuTeamInfo) == 0x4, "");

class GfMenuTeamList : public ui::UIListInfo<MenuTeamInfo> {
public:
  struct TeamSetup {
    SetupParam param;
  };

  GfMenuTeamList();
  ~GfMenuTeamList() override;
  static GfMenuTeamList *create();
  void setupFromMercenaries(const TeamSetup &setup);
};

static_assert(sizeof(GfMenuTeamList) == 0x68, "");

} // namespace gf
