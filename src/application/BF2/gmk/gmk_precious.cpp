#include "gmk/gmk_precious.h"

#include "gf/data/gf_bdat_wrapper.h"
#include "gf/game/gf_game_cond.h"
#include "gf/util/gf_item_util.h"
#include "gmk/gmk_bdat.h"

namespace gmk {

void GmkPrecious::BdatInfo::create(CBdatWrapper bdat, int id, const AGmkBase &gmk) {
  dispose();
  itemId = bdat.getValCheck("itmID", id, BDAT_TYPE_U16);
  gf::GfItemUtil::isPrecious(itemId);
  condition = bdat.getValCheck("Condition", id, BDAT_TYPE_U16);
  questId = bdat.getValCheck("QuestID", id, BDAT_TYPE_U16);
  scenarioFlag = ScenarioFlagCond(bdat.getValCheck("ScenarioFlagMin", id, BDAT_TYPE_U16), bdat.getValCheck("ScenarioFlagMax", id, BDAT_TYPE_U16));
  questFlag = QuestFlagCond(bdat.getValCheck("QuestFlag", id, BDAT_TYPE_U16), bdat.getValCheck("QuestFlagMin", id, BDAT_TYPE_U8), bdat.getValCheck("QuestFlagMax", id, BDAT_TYPE_U8));
  timeCond.timeRangeBits = bdat.getValCheck("POP_TIME", id, BDAT_TYPE_U32);
  weatherCond.weatherBits = bdat.getValCheck("popWeather", id, BDAT_TYPE_U8);
}

void GmkPrecious::BdatInfo::dispose() { itemId = 0; }

bool GmkPrecious::BdatInfo::isPopCondMatched() const {
  if (scenarioFlag.isEnable() && !scenarioFlag.isMatch()) {
    return false;
  }
  if (questFlag.isEnable() && !questFlag.isMatch()) {
    return false;
  }
  if (timeCond.isEnable() && !timeCond.isMatch()) {
    return false;
  }
  if (weatherCond.isEnable() && !weatherCond.isMatch()) {
    return false;
  }
  if (condition != 0 && !gf::GfGameCond::isGameCond(condition)) {
    return false;
  }
  return true;
}

} // namespace gmk
