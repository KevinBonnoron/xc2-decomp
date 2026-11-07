#pragma once
#include "gf/game/quest/gf_quest_id.h"
#include "ui/list/ui_list_info.h"

namespace gf {

class GfMenuQuestList : public ui::UIListInfo<QuestID> {
public:
  GfMenuQuestList();
  ~GfMenuQuestList() override;
  static GfMenuQuestList *create();
};

static_assert(sizeof(GfMenuQuestList) == 0x68, "");

} // namespace gf
