#pragma once
#include <stddef.h>

#include "types.h"
#include "ui/list/ui_list_info.h"

namespace gf {

class GfMenuBladeList;

struct MenuFieldSkill {
  MenuFieldSkill() : fieldSkill(0), level(0) {}

  u16 fieldSkill;
  u8 level;
};

static_assert(offsetof(MenuFieldSkill, level) == 0x2, "");
static_assert(sizeof(MenuFieldSkill) == 0x4, "");

class GfMenuFieldSkillList : public ui::UIListInfo<MenuFieldSkill> {
public:
  GfMenuFieldSkillList();
  ~GfMenuFieldSkillList() override;
  static GfMenuFieldSkillList *create();
  void addFieldSkill(const MenuFieldSkill &fieldSkill);
  void addFieldSkillFromBlade(u32 blade);
  void addFieldSkillFromBladeList(const GfMenuBladeList *list);
  void addFieldSkillFromParty();
};

static_assert(sizeof(GfMenuFieldSkillList) == 0x68, "");

} // namespace gf
