#include "gmk/gmk_field_lock.h"

#include "gf/data/gf_bdat_wrapper.h"
#include "gf/game/gf_game_cond.h"
#include "gmk/gmk_bdat.h"

namespace gmk {

void GmkFieldLock::BdatInfo::create(CBdatWrapper bdat, int id, const AGmkBase &gmk) {
  scenarioFlag = ScenarioFlagCond(bdat.getValCheck("ScenarioFlagMin", id, BDAT_TYPE_U16), bdat.getValCheck("ScenarioFlagMax", id, BDAT_TYPE_U16));
  questFlag = QuestFlagCond(bdat.getValCheck("QuestFlag", id, BDAT_TYPE_U16),
                            bdat.getValCheck("QuestFlagMin", id, BDAT_TYPE_U8),
                            bdat.getValCheck("QuestFlagMax", id, BDAT_TYPE_U8));
  condition = bdat.getValCheck("Condition", id, BDAT_TYPE_U16);
  lockType = bdat.getValCheck("rockTYPE", id, BDAT_TYPE_U8);
  textId = bdat.getValCheck("txtID", id, BDAT_TYPE_U16);
}

bool GmkFieldLock::BdatInfo::isCondMatched() const {
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
