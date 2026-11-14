#pragma once
#include <stddef.h>

#include "types.h"
#include "ui/list/ui_list_info.h"

namespace gf {

struct MenuZoneMapInfo {
  MenuZoneMapInfo() : unknown00(0), unknown04(0), unknown08(0), _0c(), unknown10(0), unknown14(0) {}

  u32 unknown00; // Inferred role: map id; original member name unknown.
  u32 unknown04; // Inferred role: param; original member name unknown.
  u32 unknown08; // Inferred role: jump condition; original member name unknown.
  u8 _0c[0x10 - 0xc];
  s32 unknown10; // Inferred role: map icon selection index, set by GfMenuObjWorldMap::seqGimik; original member name unknown.
  u16 unknown14; // Inferred role: priority; original member name unknown.
};

static_assert(offsetof(MenuZoneMapInfo, unknown08) == 0x8, "");
static_assert(offsetof(MenuZoneMapInfo, unknown10) == 0x10, "");
static_assert(offsetof(MenuZoneMapInfo, unknown14) == 0x14, "");
static_assert(sizeof(MenuZoneMapInfo) == 0x18, "");

class GfMenuZoneMapList : public ui::UIListInfo<MenuZoneMapInfo> {
public:
  GfMenuZoneMapList();
  ~GfMenuZoneMapList() override;
  static GfMenuZoneMapList *create();
  void sortFromPriority();
  static bool sortPriority(const MenuZoneMapInfo &info, const MenuZoneMapInfo &other);

  bool unknown79; // Inferred role: group mode; original member name unknown.
};

static_assert(offsetof(GfMenuZoneMapList, unknown79) == 0x79, "");
static_assert(sizeof(GfMenuZoneMapList) == 0x80, "");

} // namespace gf
