#include "gmk/gmk_collection.h"

#include "bdat.h"
#include "gf/data/gf_bdat_id.h"
#include "gf/data/gf_bdat_wrapper.h"
#include "gf/data/gf_data_bdat.h"
#include "gf/game/gf_game_cond.h"
#include "gf/game/gf_game_manager.h"
#include "gmk/gmk_bdat.h"

namespace gmk {

constexpr int WILDCARD_COLLECTION_POP_DIST_ROW = 1;

void GmkCollection::BdatInfo::create(CBdatWrapper bdat, int id, const AGmkBase &gmk) {
  unknown08.unknown08 = bdat.getValCheck("POP_TIME", id, BDAT_TYPE_U32);
  unknown18.unknown08 = bdat.getValCheck("popWeather", id, BDAT_TYPE_U8);
  unknown00 = bdat.getValCheck("nameRadius", id, BDAT_TYPE_U16);
  unknown02 = bdat.getValCheck("Condition", id, BDAT_TYPE_U16);
  f32 popDist = Bdat::getValCheck(gf::GfDataBdat::getFP(gf::BDAT_FLD_WILDCARD_DATA), 0, WILDCARD_COLLECTION_POP_DIST_ROW, BDAT_TYPE_F32).valueF32;
  unknown28.unknown00 = popDist * popDist;
}

bool GmkCollection::BdatInfo::isPopCondMatchedExceptDist() const {
  if (unknown02 != 0 && !gf::GfGameCond::isGameCond(unknown02)) {
    return false;
  }
  if (unknown08.isEnable() && !unknown08.isMatch()) {
    return false;
  }
  if (unknown18.isEnable() && !unknown18.isMatch()) {
    return false;
  }
  return true;
}

void GmkCollection::BdatInfo::debugDraw(const AGmkBase &gmk) const {}

bool GmkCollectionList::BdatInfo::create() {
  u8 *mapList = gf::GfDataBdat::getFP(gf::BDAT_FLD_MAPLIST);
  if (mapList == nullptr) {
    unknown00 = -1;
    return false;
  }
  unknown00 = gf::GfGameManager::getMapID();
  if (unknown00 < Bdat::getIdTop(mapList) || Bdat::getIdTop(mapList) + Bdat::getIdCount(mapList) <= unknown00) {
    unknown00 = -1;
    return false;
  }
  unknown04 = Bdat::getValCheck(mapList, "m_repoptime", unknown00, BDAT_TYPE_U8);
  return true;
}

} // namespace gmk
