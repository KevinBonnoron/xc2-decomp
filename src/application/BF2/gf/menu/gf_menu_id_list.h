#pragma once
#include "types.h"
#include "ui/list/ui_list_info.h"

namespace gf {

struct MenuID {
  u32 id;
  u8 _04[0x8 - 0x4];
};

static_assert(sizeof(MenuID) == 0x8, "");

class GfMenuIDList : public ui::UIListInfo<MenuID> {
public:
  GfMenuIDList();
  ~GfMenuIDList() override;
};

static_assert(sizeof(GfMenuIDList) == 0x70, "");

} // namespace gf
