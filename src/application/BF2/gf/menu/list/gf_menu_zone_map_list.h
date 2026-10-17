#pragma once
#include <stddef.h>

#include "types.h"
#include "ui/list/ui_list_info.h"

namespace gf {

struct MenuZoneMapInfo {
  MenuZoneMapInfo() : mapId(0), param(0), _08(), priority(0) {}

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
  static GfMenuZoneMapList *create();
  void sortFromPriority();
  static bool sortPriority(const MenuZoneMapInfo &info, const MenuZoneMapInfo &other);

  bool isGroupMode;
};

static_assert(offsetof(GfMenuZoneMapList, isGroupMode) == 0x79, "");
static_assert(sizeof(GfMenuZoneMapList) == 0x80, "");

} // namespace gf
