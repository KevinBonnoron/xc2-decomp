#include "gmk/gmk_salvage.h"

#include "gf/data/gf_bdat_wrapper.h"
#include "gf/game/gf_game_cond.h"
#include "gmk/gmk_bdat.h"

namespace gmk {

void GmkSalvage::BdatInfo::create(CBdatWrapper bdat, int id, const AGmkBase &gmk) { unknown00 = bdat.getValCheck("Condition", id, BDAT_TYPE_U16); }

bool GmkSalvage::BdatInfo::isCondMatched() const {
  if (unknown00 != 0 && !gf::GfGameCond::isGameCond(unknown00)) {
    return false;
  }
  return true;
}

} // namespace gmk
