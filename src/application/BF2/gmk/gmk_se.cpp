#include "gmk/gmk_se.h"

#include "bdat.h"
#include "gf/data/gf_bdat_wrapper.h"
#include "gf/field/gf_field_sound.h"
#include "gf/game/gf_game_cond.h"
#include "gmk/gmk_bdat.h"

namespace gmk {

void GmkSe::BdatInfo::create(CBdatWrapper bdat, int id, const AGmkBase &gmk) {
  isMapPack = Bdat::getFlagVal(bdat.data, "flag", id, "se_type") != 0;
  isPlayOnce = Bdat::getFlagVal(bdat.data, "flag", id, "play_once") != 0;
  seName = bdat.getValCheck("seName", id, BDAT_TYPE_U16);
  volumeMax = bdat.getValCheck("volumeMAX", id, BDAT_TYPE_U8);
  volumeMin = bdat.getValCheck("volumeMIN", id, BDAT_TYPE_U8);
  scenarioFlag = ScenarioFlagCond(bdat.getValCheck("ScenarioFlagMin", id, BDAT_TYPE_U16), bdat.getValCheck("ScenarioFlagMax", id, BDAT_TYPE_U16));
  questFlag = QuestFlagCond(bdat.getValCheck("QuestFlag", id, BDAT_TYPE_U16),
                            bdat.getValCheck("QuestFlagMin", id, BDAT_TYPE_U8),
                            bdat.getValCheck("QuestFlagMax", id, BDAT_TYPE_U8));
  condition = bdat.getValCheck("Condition", id, BDAT_TYPE_U16);
  u16 popTime = bdat.getValCheck("SEpopTime", id, BDAT_TYPE_U16);
  timeCond.timeRangeBits = popTime;
  weatherCond.weatherBits = bdat.getValCheck("wtrSEType", id, BDAT_TYPE_U8);
  bootedGmk = BootedGmkCond(bdat, id, nullptr);
  opBootedGmk = BootedGmkCond(bdat, id, "OP_");
  inRoomVolume = bdat.getValCheck("InRoom_volume", id, BDAT_TYPE_U8);
}

bool GmkSe::BdatInfo::isPopCondMatched() const {
  if (scenarioFlag.isEnable() && !scenarioFlag.isMatch()) {
    return false;
  }
  if (questFlag.isEnable() && !questFlag.isMatch()) {
    return false;
  }
  if (condition != 0 && !gf::GfGameCond::isGameCond(condition)) {
    return false;
  }
  if (timeCond.isEnable() && !timeCond.isMatch()) {
    return false;
  }
  if (weatherCond.isEnable() && !weatherCond.isMatch()) {
    return false;
  }
  if (bootedGmk.isEnable() && !bootedGmk.isMatch()) {
    return false;
  }
  if (opBootedGmk.isEnable() && opBootedGmk.isMatch()) {
    return false;
  }
  return true;
}

fw::SoundPack *GmkSe::BdatInfo::getSoundPack() const {
  if (isMapPack) {
    return gf::GfFieldSound::get()->getMapPack();
  }
  return gf::GfFieldSound::get()->getCommonPack();
}

} // namespace gmk
