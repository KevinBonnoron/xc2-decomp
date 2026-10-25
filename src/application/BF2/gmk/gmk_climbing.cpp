#include "gmk/gmk_climbing.h"

#include "gf/data/gf_bdat_wrapper.h"
#include "gf/game/gf_game_cond.h"
#include "gmk/gmk_bdat.h"

namespace gmk {

void GmkClimbing::BdatInfo::create(CBdatWrapper bdat, int id, const AGmkBase &gmk) {
  unknown04 = ScenarioFlagCond(bdat.getValCheck("ScenarioFlagMin", id, BDAT_TYPE_U16), bdat.getValCheck("ScenarioFlagMax", id, BDAT_TYPE_U16));
  unknown08 = QuestFlagCond(bdat.getValCheck("QuestFlag", id, BDAT_TYPE_U16), bdat.getValCheck("QuestFlagMin", id, BDAT_TYPE_U8), bdat.getValCheck("QuestFlagMax", id, BDAT_TYPE_U8));
  unknown00 = bdat.getValCheck("Condition", id, BDAT_TYPE_U16);
  unknown0c = BootedGmkCond(bdat, id, "OP_");
  unknown02 = bdat.getValCheck("climiconRadius", id, BDAT_TYPE_U16);
}

bool GmkClimbing::BdatInfo::isPopCondMatched() const {
  if (unknown04.isEnable() && !unknown04.isMatch()) {
    return false;
  }
  if (unknown08.isEnable() && !unknown08.isMatch()) {
    return false;
  }
  if (unknown00 != 0 && !gf::GfGameCond::isGameCond(unknown00)) {
    return false;
  }
  if (unknown0c.isEnable() && !unknown0c.isMatch()) {
    return false;
  }
  return true;
}

GmkType GmkClimbing::getGmkType() const { return GMK_TYPE; }

} // namespace gmk
