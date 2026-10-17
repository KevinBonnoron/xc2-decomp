#include "gmk/gmk_warp.h"

#include "bdat.h"
#include "gf/data/gf_bdat_id.h"
#include "gf/data/gf_bdat_wrapper.h"
#include "gf/data/gf_data_bdat.h"
#include "gf/game/gf_game_cond.h"
#include "gf/game/gf_game_manager.h"
#include "gmk/gmk_bdat.h"

namespace mm {
struct Vec3;
} // namespace mm

namespace gmk {

void GmkWarp::BdatInfo::create(CBdatWrapper bdat, int id, const AGmkBase &gmk) {
  condition = bdat.getValCheck("Condition", id, BDAT_TYPE_U16);
  bootedGmk = BootedGmkCond(bdat, id, nullptr);
  nameRadius = bdat.getValCheck("nameRadius", id, BDAT_TYPE_U16);
  u8 *mapList = gf::GfDataBdat::getFP(gf::BDAT_FLD_MAPLIST);
  if (mapList != nullptr) {
    int map = gf::GfGameManager::getMapID();
    if (map >= Bdat::getIdTop(mapList) && Bdat::getIdTop(mapList) + Bdat::getIdCount(mapList) > map) {
      u8 displayRadius = Bdat::getValCheck(mapList, "ene_disp_r", map, BDAT_TYPE_U8);
      u8 displayHeight = Bdat::getValCheck(mapList, "ene_disp_h", map, BDAT_TYPE_U8);
      popDist.set(displayRadius, displayHeight);
      u8 releaseRadius = Bdat::getValCheck(mapList, "ene_release_r", map, BDAT_TYPE_U8);
      u8 releaseHeight = Bdat::getValCheck(mapList, "ene_release_h", map, BDAT_TYPE_U8);
      depopDist.set(displayRadius + releaseRadius, displayHeight + releaseHeight);
    }
  }
}

bool GmkWarp::BdatInfo::isPopCondMatched(const mm::Vec3 &position) const {
  if (!isPopCondCommonMatched()) {
    return false;
  }
  return popDist.isMatch(position);
}

bool GmkWarp::BdatInfo::isPopCondCommonMatched() const {
  if (condition != 0 && !gf::GfGameCond::isGameCond(condition)) {
    return false;
  }
  if (bootedGmk.isEnable() && !bootedGmk.isMatch()) {
    return false;
  }
  return true;
}

bool GmkWarp::BdatInfo::isDepopCondMatched(const mm::Vec3 &position) const {
  if (!isPopCondCommonMatched()) {
    return true;
  }
  return !depopDist.isMatch(position);
}

void GmkWarp::BdatInfo::debugDraw(const AGmkBase &gmk) const {}

} // namespace gmk
