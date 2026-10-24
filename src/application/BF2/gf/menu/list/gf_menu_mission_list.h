#pragma once
#include <stddef.h>

#include "types.h"
#include "ui/list/ui_list_info.h"

namespace gf {

struct MenuMissionInfo {
  u32 unknown00; // Inferred role: mission; original member name unknown.
};

static_assert(sizeof(MenuMissionInfo) == 0x4, "");

class GfMenuMissionList : public ui::UIListInfo<MenuMissionInfo> {
public:
  struct MissionSetup {
    SetupParam unknown00; // Inferred role: param; original member name unknown.
    u32 unknown14;        // Inferred role: zone; original member name unknown.
  };

  GfMenuMissionList();
  ~GfMenuMissionList() override;
  static GfMenuMissionList *create();
  void setupFromZone(const MissionSetup &setup);
};

static_assert(offsetof(GfMenuMissionList::MissionSetup, unknown14) == 0x14, "");
static_assert(sizeof(GfMenuMissionList) == 0x68, "");

} // namespace gf
