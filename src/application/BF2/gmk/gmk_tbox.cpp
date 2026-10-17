#include "gmk/gmk_tbox.h"

#include "bdat.h"
#include "gf/data/gf_bdat_id.h"
#include "gf/data/gf_data_bdat.h"
#include "gf/game/gf_game_cond.h"
#include "gmk/gmk_bdat.h"

namespace mm {
struct Vec3;
} // namespace mm

namespace gmk {

void GmkTbox::BdatInfo::create(u8 *bdat, int id, const AGmkBase &gmk) {
  condition = Bdat::getValCheck(bdat, "Condition", id, BDAT_TYPE_U16);
  isDig = Bdat::getFlagVal(bdat, "flag", id, "Digflg") != 0;
  msgVisible = Bdat::getValCheck(bdat, "msgVisible", id, BDAT_TYPE_U8);
  msgDigVisible = Bdat::getValCheck(bdat, "msgdigVisible", id, BDAT_TYPE_U8);
  u16 resourceId = Bdat::getValCheck(bdat, "RSC_ID", id, BDAT_TYPE_U16);
  u8 *tboxList = gf::GfDataBdat::getFP(gf::BDAT_RSC_TBOX_LIST);
  u16 visibleRadius = Bdat::getValCheck(tboxList, "visible_Radius", resourceId, BDAT_TYPE_U16);
  popDist.distSq = static_cast<f32>(visibleRadius) * static_cast<f32>(visibleRadius);
  u16 invisibleRadius = Bdat::getValCheck(tboxList, "invisible_Radius", resourceId, BDAT_TYPE_U16);
  depopDist.distSq = static_cast<f32>(invisibleRadius) * static_cast<f32>(invisibleRadius);
  u16 categoryResourceId = Bdat::getValCheck(bdat, "RSC_ID", id, BDAT_TYPE_U16);
  isTboxCategory = Bdat::getFlagVal(gf::GfDataBdat::getFP(gf::BDAT_RSC_TBOX_LIST), "flag", categoryResourceId, "TBOX_category") != 0;
}

void GmkTbox::BdatInfo::dispose() {}

bool GmkTbox::BdatInfo::isPopCondMatchedExceptDist() const {
  if (condition != 0 && !gf::GfGameCond::isGameCond(condition)) {
    return false;
  }
  return true;
}

bool GmkTbox::BdatInfo::isPopCondMatched(const mm::Vec3 &position) const {
  if (!isPopCondMatchedExceptDist()) {
    return false;
  }
  return DistCond::isMatch(popDist.distSq, position);
}

bool GmkTbox::BdatInfo::isDepopCondMatched(const mm::Vec3 &position) const {
  if (!isPopCondMatchedExceptDist()) {
    return true;
  }
  return !DistCond::isMatch(depopDist.distSq, position);
}

void GmkTbox::BdatInfo::debugDraw(const AGmkBase &gmk) const {}

} // namespace gmk
