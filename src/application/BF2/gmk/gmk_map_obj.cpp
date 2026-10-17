#include "gmk/gmk_map_obj.h"

#include "bdat.h"
#include "gf/data/gf_bdat_wrapper.h"
#include "gf/game/gf_game_cond.h"
#include "gmk/gmk_bdat.h"

namespace gmk {

void GmkMapObj::BdatInfo::create(CBdatWrapper bdat, int id, const AGmkBase &gmk) {
  condition = bdat.getValCheck("Condition", id, BDAT_TYPE_U16);
  u16 visibleXZ = bdat.getValCheck("Visible_XZ", id, BDAT_TYPE_U16);
  u16 visibleY = bdat.getValCheck("Visible_Y", id, BDAT_TYPE_U16);
  popDist.set(visibleXZ, visibleY);
  u16 invisibleXZ = DistHvCond::clampDepopDist(bdat.getValCheck("Invisible_XZ", id, BDAT_TYPE_U16), visibleXZ);
  u16 invisibleY = DistHvCond::clampDepopDist(bdat.getValCheck("Invisible_Y", id, BDAT_TYPE_U16), visibleY);
  depopDist.set(invisibleXZ, invisibleY);
  if (Bdat::getMember(bdat.data, "Priority") != nullptr) {
    priority = bdat.getValCheck("Priority", id, BDAT_TYPE_U8);
  }
}

bool GmkMapObj::BdatInfo::isPopCondMatched(const mm::Vec3 &position) const {
  if (!popDist.isMatch(position)) {
    return false;
  }
  if (condition != 0 && !gf::GfGameCond::isGameCond(condition)) {
    return false;
  }
  return true;
}

bool GmkMapObj::BdatInfo::isDepopCondMatched(const mm::Vec3 &position) const {
  if (!depopDist.isMatch(position)) {
    return true;
  }
  if (condition != 0 && !gf::GfGameCond::isGameCond(condition)) {
    return true;
  }
  return false;
}

} // namespace gmk
