#pragma once
#include "types.h"
#include "ui/list/ui_list_info.h"

namespace gf {

struct MenuArtsInfo {
  u32 arts;
  u32 level;
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
