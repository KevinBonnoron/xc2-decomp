#include "gmk/gmk_collection.h"

#include "bdat.h"
#include "gf/data/gf_bdat_id.h"
#include "gf/data/gf_bdat_wrapper.h"
#include "gf/data/gf_data_bdat.h"
#include "gf/game/gf_game_cond.h"
#include "gmk/gmk_bdat.h"

namespace gmk {

constexpr int WILDCARD_COLLECTION_POP_DIST_ROW = 1;

void GmkCollection::BdatInfo::create(CBdatWrapper bdat, int id, const AGmkBase &gmk) {
  timeCond.timeRangeBits = bdat.getValCheck("POP_TIME", id, BDAT_TYPE_U32);
  weatherCond.weatherBits = bdat.getValCheck("popWeather", id, BDAT_TYPE_U8);
  nameRadius = bdat.getValCheck("nameRadius", id, BDAT_TYPE_U16);
  condition = bdat.getValCheck("Condition", id, BDAT_TYPE_U16);
  f32 popDist = Bdat::getValCheck(gf::GfDataBdat::getFP(gf::BDAT_FLD_WILDCARD_DATA), 0, WILDCARD_COLLECTION_POP_DIST_ROW, BDAT_TYPE_F32).valueF32;
  distCond.distSq = popDist * popDist;
}

bool GmkCollection::BdatInfo::isPopCondMatchedExceptDist() const {
  if (condition != 0 && !gf::GfGameCond::isGameCond(condition)) {
    return false;
  }
  if (timeCond.isEnable() && !timeCond.isMatch()) {
    return false;
  }
  if (weatherCond.isEnable() && !weatherCond.isMatch()) {
    return false;
  }
  return true;
}

void GmkCollection::BdatInfo::debugDraw(const AGmkBase &gmk) const {}

} // namespace gmk
