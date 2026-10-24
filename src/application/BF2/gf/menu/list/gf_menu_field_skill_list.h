#pragma once
#include <stddef.h>

#include "types.h"
#include "ui/list/ui_list_info.h"

namespace gf {

class GfMenuBladeList;

struct MenuFieldSkill {
  MenuFieldSkill() : unknown00(0), unknown02(0) {}

  u16 unknown00; // Inferred role: field skill; original member name unknown.
  u8 unknown02;  // Inferred role: level; original member name unknown.
  u8 _03[0x4 - 0x3];
};

static_assert(offsetof(MenuFieldSkill, unknown02) == 0x2, "");
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
