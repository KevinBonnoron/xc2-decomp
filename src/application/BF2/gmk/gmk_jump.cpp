#include "gmk/gmk_jump.h"

#include "gf/data/gf_bdat_wrapper.h"
#include "gf/game/gf_game_cond.h"
#include "gmk/gmk_bdat.h"

namespace gmk {

void GmkJump::BdatInfo::create(CBdatWrapper bdat, int id, const AGmkBase &gmk) {
  condition = bdat.getValCheck("Condition", id, BDAT_TYPE_U16);
  jumpType = bdat.getValCheck("jumpType", id, BDAT_TYPE_U8);
  nameRadius = bdat.getValCheck("nameRadius", id, BDAT_TYPE_U16);
}

bool GmkJump::BdatInfo::isPopCondMatched() const {
  if (condition != 0 && !gf::GfGameCond::isGameCond(condition)) {
    return false;
  }
  return true;
}

void GmkJump::BdatInfo::debugDraw(const AGmkBase &gmk) const {}

} // namespace gmk
