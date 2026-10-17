#include "gmk/gmk_kizuna_talk.h"

#include "gf/data/gf_bdat_wrapper.h"
#include "gf/game/gf_game_cond.h"
#include "gmk/gmk_bdat.h"

namespace gmk {

void GmkKizunaTalk::BdatInfo::create(CBdatWrapper bdat, int id, const AGmkBase &gmk) {
  condition = bdat.getValCheck("ConditionID", id, BDAT_TYPE_U16);
  title = bdat.getValCheck("Title", id, BDAT_TYPE_U16);
  eventCondition = bdat.getValCheck("EVCondition", id, BDAT_TYPE_U16);
}

bool GmkKizunaTalk::BdatInfo::isCondMatched() const {
  if (condition != 0 && !gf::GfGameCond::isGameCond(condition)) {
    return false;
  }
  return true;
}

} // namespace gmk
