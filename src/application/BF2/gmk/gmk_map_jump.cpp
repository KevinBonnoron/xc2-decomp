#include "gmk/gmk_map_jump.h"

#include "gf/data/gf_bdat_wrapper.h"
#include "gf/game/gf_game_cond.h"
#include "gmk/gmk_bdat.h"

namespace gmk {

void GmkMapJump::debugDraw() const { isValid(); }

void GmkMapJump::BdatInfo::create(CBdatWrapper bdat, int id, const AGmkBase &gmk) {
  unknown00 = bdat.getValCheck("MapJumpId", id, BDAT_TYPE_U16);
  unknown04 = ScenarioFlagCond(bdat.getValCheck("ScenarioFlagMin", id, BDAT_TYPE_U16), bdat.getValCheck("ScenarioFlagMax", id, BDAT_TYPE_U16));
  unknown08 = QuestFlagCond(bdat.getValCheck("QuestFlag", id, BDAT_TYPE_U16), bdat.getValCheck("QuestFlagMin", id, BDAT_TYPE_U8), bdat.getValCheck("QuestFlagMax", id, BDAT_TYPE_U8));
  unknown02 = bdat.getValCheck("Condition", id, BDAT_TYPE_U16);
}

bool GmkMapJump::BdatInfo::isCondMatched() const {
  if (unknown04.isEnable() && !unknown04.isMatch()) {
    return false;
  }
  if (unknown08.isEnable() && !unknown08.isMatch()) {
    return false;
  }
  if (unknown02 != 0 && !gf::GfGameCond::isGameCond(unknown02)) {
    return false;
  }
  return true;
}

GmkType GmkMapJump::getGmkType() const { return GMK_TYPE; }

void GmkMapJump::endEvent() {
  if (unknownE1) {
    unknownE1 = false;
  }
}

} // namespace gmk
