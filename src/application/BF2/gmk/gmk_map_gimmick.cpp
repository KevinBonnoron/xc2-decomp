#include "gmk/gmk_map_gimmick.h"

#include "bdat.h"
#include "gf/data/gf_bdat_wrapper.h"
#include "gf/game/gf_game_cond.h"
#include "gmk/gmk_bdat.h"

namespace gmk {

void GmkMapGimmick::BdatInfo::create(CBdatWrapper bdat, int id, const AGmkBase &gmk) {
  u16 popTime = bdat.getValCheck("popTime", id, BDAT_TYPE_U32);
  timeCond.timeRangeBits = popTime;
  weatherCond.weatherBits = bdat.getValCheck("popWeather", id, BDAT_TYPE_U8);
  bootedGmk = BootedGmkCond(bdat, id, nullptr);
  condition = bdat.getValCheck("Condition", id, BDAT_TYPE_U16);
  nameRadius = bdat.getValCheck("nameRadius", id, BDAT_TYPE_U16);
  mapObjId = bdat.getValCheck("mapobjID", id, BDAT_TYPE_U16);
  isMsgRay = Bdat::getFlagVal(bdat.data, "flag", id, "MSG_ray") != 0;
}

bool GmkMapGimmick::BdatInfo::isPopCondMatched() const {
  if (timeCond.isEnable() && !timeCond.isMatch()) {
    return false;
  }
  if (weatherCond.isEnable() && !weatherCond.isMatch()) {
    return false;
  }
  if (bootedGmk.isEnable() && !bootedGmk.isMatch()) {
    return false;
  }
  if (condition != 0 && !gf::GfGameCond::isGameCond(condition)) {
    return false;
  }
  return true;
}

void GmkMapGimmick::BdatInfo::debugDraw(const AGmkBase &gmk) const {}

} // namespace gmk
