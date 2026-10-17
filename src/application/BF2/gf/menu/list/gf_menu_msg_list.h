#pragma once
#include <stddef.h>

#include "types.h"
#include "ui/list/ui_list_info.h"

namespace ui {
class UIStr;
} // namespace ui

namespace gf {

struct MsgID {
  u32 id;
};

static_assert(sizeof(MsgID) == 0x4, "");

class GfMenuMsgList : public ui::UIListInfo<MsgID> {
public:
  GfMenuMsgList();
  ~GfMenuMsgList() override;
  static GfMenuMsgList *create();
  void setBdat(u32 nameBdatId, u32 msgBdatId);
  bool getMsg(int index, ui::UIStr &msg, bool isPage);

  u8 *nameBdat;
  u8 *msgBdat;
};

static_assert(offsetof(GfMenuMsgList, nameBdat) == 0x68, "");
static_assert(offsetof(GfMenuMsgList, msgBdat) == 0x70, "");
static_assert(sizeof(GfMenuMsgList) == 0x78, "");

} // namespace gf
