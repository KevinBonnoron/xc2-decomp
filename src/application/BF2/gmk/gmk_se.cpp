#include "gmk/gmk_se.h"

#include "bdat.h"
#include "gf/data/gf_bdat_wrapper.h"
#include "gf/field/gf_field_sound.h"
#include "gf/game/gf_game_cond.h"
#include "gmk/gmk_bdat.h"

namespace gmk {

void GmkSe::BdatInfo::create(CBdatWrapper bdat, int id, const AGmkBase &gmk) {
  unknown00 = Bdat::getFlagVal(bdat.unknown00, "flag", id, "se_type") != 0;
  unknown01 = Bdat::getFlagVal(bdat.unknown00, "flag", id, "play_once") != 0;
  unknown02 = bdat.getValCheck("seName", id, BDAT_TYPE_U16);
  unknown04 = bdat.getValCheck("volumeMAX", id, BDAT_TYPE_U8);
  unknown05 = bdat.getValCheck("volumeMIN", id, BDAT_TYPE_U8);
  unknown0a = ScenarioFlagCond(bdat.getValCheck("ScenarioFlagMin", id, BDAT_TYPE_U16), bdat.getValCheck("ScenarioFlagMax", id, BDAT_TYPE_U16));
  unknown0e = QuestFlagCond(bdat.getValCheck("QuestFlag", id, BDAT_TYPE_U16), bdat.getValCheck("QuestFlagMin", id, BDAT_TYPE_U8), bdat.getValCheck("QuestFlagMax", id, BDAT_TYPE_U8));
  unknown06 = bdat.getValCheck("Condition", id, BDAT_TYPE_U16);
  u16 popTime = bdat.getValCheck("SEpopTime", id, BDAT_TYPE_U16);
  unknown18.unknown08 = popTime;
  unknown28.unknown08 = bdat.getValCheck("wtrSEType", id, BDAT_TYPE_U8);
  unknown38 = BootedGmkCond(bdat, id, nullptr);
  unknown3c = BootedGmkCond(bdat, id, "OP_");
  unknown08 = bdat.getValCheck("InRoom_volume", id, BDAT_TYPE_U8);
}

bool GmkSe::BdatInfo::isPopCondMatched() const {
  if (unknown0a.isEnable() && !unknown0a.isMatch()) {
    return false;
  }
  if (unknown0e.isEnable() && !unknown0e.isMatch()) {
    return false;
  }
  if (unknown06 != 0 && !gf::GfGameCond::isGameCond(unknown06)) {
    return false;
  }
  if (unknown18.isEnable() && !unknown18.isMatch()) {
    return false;
  }
  if (unknown28.isEnable() && !unknown28.isMatch()) {
    return false;
  }
  if (unknown38.isEnable() && !unknown38.isMatch()) {
    return false;
  }
  if (unknown3c.isEnable() && unknown3c.isMatch()) {
    return false;
  }
  return true;
}

fw::SoundPack *GmkSe::BdatInfo::getSoundPack() const {
  if (unknown00) {
    return gf::GfFieldSound::get()->getMapPack();
  }
  return gf::GfFieldSound::get()->getCommonPack();
}

} // namespace gmk
