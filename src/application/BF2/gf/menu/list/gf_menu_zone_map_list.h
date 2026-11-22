#pragma once
#include <stddef.h>

#include "types.h"
#include "ui/list/ui_list_info.h"

namespace gf {

struct MenuZoneMapInfo {
  MenuZoneMapInfo() : unknown00(0), unknown04(0), unknown08(0), unknown0c(0), unknown10(0), unknown14(0) {}

  u32 unknown00; // Inferred role: map id; original member name unknown.
  u32 unknown04; // Inferred role: param; original member name unknown.
  u32 unknown08; // Inferred role: jump condition; original member name unknown.
  u32 unknown0c; // Inferred role: zero for a zone that has map icons, tested by GfMenuObjWorldMap::refreshZoneMap; original member name unknown.
  s32 unknown10; // Inferred role: map icon selection index, set by GfMenuObjWorldMap::seqGimik; original member name unknown.
  u16 unknown14; // Inferred role: priority; original member name unknown.
};

static_assert(offsetof(MenuZoneMapInfo, unknown08) == 0x8, "");
static_assert(offsetof(MenuZoneMapInfo, unknown0c) == 0xc, "");
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

  // Inferred name; kept as an exception to the unknown-name rule (AGENTS.md): single-user helper whose existence only the match proves; rename if a sibling build gives a symbol.
  // Forms tried without the helper in GfMenuObjWorldMap::refreshZoneMap (1.0.0: 0x71004eac50): `unknown2f0->m_groupMode` read directly, whichever branch comes first, gives 153 instructions with
  // another register allocation (checked on the compiled output against the game).
  bool isGroupMode() const { return m_groupMode; }

  bool m_groupMode; // Inferred role: group mode; named after the game accessor gf::GfMenuZoneMapAdapter::ListConverter::isGroupMode.
};

static_assert(offsetof(GfMenuZoneMapList, m_groupMode) == 0x79, "");
static_assert(sizeof(GfMenuZoneMapList) == 0x80, "");

} // namespace gf
