#pragma once
#include <stddef.h>

#include "types.h"
#include "ui/list/ui_list_info.h"

namespace gf {

struct MenuZoneMapInfo {
  u32 mapId;
  u32 param;
  u8 _08[0x14 - 0x8];
  u16 priority;
};

static_assert(offsetof(MenuZoneMapInfo, priority) == 0x14, "");
static_assert(sizeof(MenuZoneMapInfo) == 0x18, "");

class GfMenuZoneMapList : public ui::UIListInfo<MenuZoneMapInfo> {
public:
  GfMenuZoneMapList();
  ~GfMenuZoneMapList() override;

  bool isGroupMode;
};

static_assert(offsetof(GfMenuZoneMapList, isGroupMode) == 0x79, "");
static_assert(sizeof(GfMenuZoneMapList) == 0x80, "");

} // namespace gf
