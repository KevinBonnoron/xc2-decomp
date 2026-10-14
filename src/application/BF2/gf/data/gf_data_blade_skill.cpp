#include "gf/data/gf_data_blade_skill.h"
#include "bdat.h"
#include "gf/data/gf_bdat_btl.h"
#include "gf/data/gf_bdat_msg.h"

namespace gf {

const char *GfDataBladeSkill::getName(u32 skill) {
  u32 textId = GfBdatBtl::get()->getBTL_Skill_BlName(skill);
  u8 *bdat = GfBdatMsg::getFpBlSkill();
  const char *name = textId == 0 ? nullptr : Bdat::getMSText(bdat, textId);
  if (name == nullptr) {
    name = "";
  }

  return name;
}

bool GfDataBladeSkill::getName(u8 *&bdat, u32 &textId, u32 skill) {
  textId = GfBdatBtl::get()->getBTL_Skill_BlName(skill);
  bdat = GfBdatMsg::getFpBlSkill();
  return textId != 0;
}

u32 GfDataBladeSkill::getEnhance(u32 skill, u32 level) { return GfBdatBtl::get()->getBTL_Skill_BlEnhance(skill, level - 1); }

bool GfDataBladeSkill::getEnhanceCaption(u8 *&bdat, u32 &textId, u32 skill, u32 level) {
  u32 enhance = GfBdatBtl::get()->getBTL_Skill_BlEnhance(skill, level - 1);
  if (enhance == 0) {
    return false;
  }

  textId = GfBdatBtl::get()->getBTL_EnhanceCaption(enhance);
  bdat = GfBdatMsg::getFpBtlEnhanceCap();
  return textId != 0;
}

} // namespace gf
