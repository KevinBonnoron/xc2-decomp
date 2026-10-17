#include "gmk/gmk_event.h"

#include "gf/data/gf_bdat_wrapper.h"
#include "gf/game/gf_game_cond.h"
#include "gmk/gmk_bdat.h"

namespace gmk {

void GmkEvent::BdatInfo::create(CBdatWrapper bdat, int id, const AGmkBase &gmk) {
  scenarioFlag = ScenarioFlagCond(bdat.getValCheck("ScenarioFlagMin", id, BDAT_TYPE_U16), bdat.getValCheck("ScenarioFlagMax", id, BDAT_TYPE_U16));
  questFlag = QuestFlagCond(bdat.getValCheck("QuestFlag", id, BDAT_TYPE_U16),
                            bdat.getValCheck("QuestFlagMin", id, BDAT_TYPE_U8),
                            bdat.getValCheck("QuestFlagMax", id, BDAT_TYPE_U8));
  condition = bdat.getValCheck("Condition", id, BDAT_TYPE_U16);
  eventId = bdat.getValCheck("EventID", id, BDAT_TYPE_U16);
  icon = bdat.getValCheck("Icon", id, BDAT_TYPE_U16);
}

bool GmkEvent::BdatInfo::isCondMatched() const {
  if (scenarioFlag.isEnable() && !scenarioFlag.isMatch()) {
    return false;
  }
  if (questFlag.isEnable() && !questFlag.isMatch()) {
    return false;
  }
  if (condition != 0 && !gf::GfGameCond::isGameCond(condition)) {
    return false;
  }
  return true;
}

} // namespace gmk
