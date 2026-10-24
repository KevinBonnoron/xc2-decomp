#pragma once
#include "types.h"
#include "ui/list/ui_list_info.h"

namespace gf {

struct MenuArtsInfo {
  u32 unknown00; // Inferred role: arts; original member name unknown.
  u32 unknown04; // Inferred role: level; original member name unknown.
};

static_assert(sizeof(MenuArtsInfo) == 0x8, "");

class GfMenuArtsList : public ui::UIListInfo<MenuArtsInfo> {
public:
  GfMenuArtsList();
  ~GfMenuArtsList() override;
  static GfMenuArtsList *create();
};

static_assert(sizeof(GfMenuArtsList) == 0x70, "");

} // namespace gf
