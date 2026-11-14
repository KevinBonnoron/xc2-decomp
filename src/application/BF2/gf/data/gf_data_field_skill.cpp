#include "gf/data/gf_data_field_skill.h"
#include "bdat.h"
#include "gf/data/gf_bdat_msg.h"
#include "gf/data/gf_bdat_quest.h"
#include "gf/data/gf_game_flag.h"

namespace gf {

enum {
  FLAG_UNKNOWN_59675 = 0xe91b, // Inferred role: flag field skill setting; original name unknown.
};

enum {
  FIELD_SKILL_SETTING_UNKNOWN_1 = 1, // Inferred role: field skill setting accessed; original name unknown.
  FIELD_SKILL_SETTING_UNKNOWN_2 = 2, // Inferred role: field skill setting complete; original name unknown.
};

const char *GfDataFieldSkill::getName(u32 fieldSkill) {
  u8 *bdat;
  u32 textId;
  const char *name = getName(bdat, textId, fieldSkill) ? Bdat::getMSText(bdat, textId) : nullptr;
  if (name == nullptr) {
    name = "";
  }

  return name;
}

bool GfDataFieldSkill::getName(u8 *&bdat, u32 &textId, u32 fieldSkill) {
  if (fieldSkill == 0) {
    return false;
  }

  textId = QuestListAcc::get()->getFLD_FieldSkillListName(fieldSkill);
  bdat = GfBdatMsg::getFpFieldSkill();
  return textId != 0;
}

bool GfDataFieldSkill::isFieldSkillSettingAccessed(u32 setting) {
  int start = QuestListAcc::get()->getFLD_FieldSkillSettingStart();
  int flag = setting + FLAG_UNKNOWN_59675 - start;
  return (GfGameFlag::getLocal(2, flag) & FIELD_SKILL_SETTING_UNKNOWN_1) != 0;
}

bool GfDataFieldSkill::isFieldSkillSettingComplete(u32 setting) {
  int start = QuestListAcc::get()->getFLD_FieldSkillSettingStart();
  int flag = setting + FLAG_UNKNOWN_59675 - start;
  return (GfGameFlag::getLocal(2, flag) & FIELD_SKILL_SETTING_UNKNOWN_2) != 0;
}

void GfDataFieldSkill::setFieldSkillSettingAccessed(u32 setting) {
  int start = QuestListAcc::get()->getFLD_FieldSkillSettingStart();
  int flag = setting + FLAG_UNKNOWN_59675 - start;
  GfGameFlag::setLocal(2, flag, GfGameFlag::getLocal(2, flag) | FIELD_SKILL_SETTING_UNKNOWN_1);
}

void GfDataFieldSkill::setFieldSkillSettingComplete(u32 setting) {
  int start = QuestListAcc::get()->getFLD_FieldSkillSettingStart();
  int flag = setting + FLAG_UNKNOWN_59675 - start;
  GfGameFlag::setLocal(2, flag, GfGameFlag::getLocal(2, flag) | FIELD_SKILL_SETTING_UNKNOWN_2);
}

bool GfDataFieldSkill::getCaption(u8 *&bdat, u32 &textId, u32 fieldSkill) {
  if (fieldSkill == 0) {
    return false;
  }

  textId = QuestListAcc::get()->getFLD_FieldSkillListCaption(fieldSkill);
  bdat = GfBdatMsg::getFpFieldSkill();
  return textId != 0;
}

} // namespace gf
