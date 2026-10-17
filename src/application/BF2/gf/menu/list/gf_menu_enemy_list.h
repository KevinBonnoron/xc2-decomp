#pragma once
#include "types.h"
#include "ui/list/ui_list_info.h"

namespace gf {

struct MenuEnemyInfo {
  u32 enemy;
  u8 _04[0x8 - 0x4];
};

static_assert(sizeof(MenuEnemyInfo) == 0x8, "");

class GfMenuEnemyList : public ui::UIListInfo<MenuEnemyInfo> {
public:
  GfMenuEnemyList();
  ~GfMenuEnemyList() override;
  static GfMenuEnemyList *create();
};

static_assert(sizeof(GfMenuEnemyList) == 0x70, "");

} // namespace gf
