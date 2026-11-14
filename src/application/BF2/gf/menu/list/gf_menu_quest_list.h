#pragma once
#include <stddef.h>

#include "gf/game/quest/gf_quest_id.h"
#include "types.h"
#include "ui/list/ui_list_info.h"

namespace gf {

class GfMenuQuestList : public ui::UIListInfo<QuestID> {
public:
  struct SetupParam : ui::UIListInfoBase::SetupParam {
    SetupParam() : unknown14(7), unknown18(3) {}

    u32 unknown14; // Inferred role: category filter flags; original member name unknown.
    u32 unknown18; // Inferred role: state filter flags; original member name unknown.
  };

  GfMenuQuestList();
  ~GfMenuQuestList() override;
  void setup(const SetupParam &param);
  static GfMenuQuestList *create();
};

static_assert(sizeof(GfMenuQuestList) == 0x68, "");
static_assert(offsetof(GfMenuQuestList::SetupParam, unknown14) == 0x14, "");
static_assert(offsetof(GfMenuQuestList::SetupParam, unknown18) == 0x18, "");
static_assert(sizeof(GfMenuQuestList::SetupParam) == 0x1c, "");

} // namespace gf
