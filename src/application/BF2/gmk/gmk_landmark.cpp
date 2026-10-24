#include "gmk/gmk_landmark.h"

#include "bdat.h"
#include "gf/data/gf_bdat_id.h"
#include "gf/data/gf_bdat_wrapper.h"
#include "gf/data/gf_data_bdat.h"
#include "gf/game/gf_game_cond.h"
#include "gmk/gmk_bdat.h"

namespace gmk {

void GmkLandmark::BdatInfo::create(CBdatWrapper bdat, int id, const AGmkBase &gmk) {
  msgId = bdat.getValCheck("MSGID", id, BDAT_TYPE_U16);
  category = bdat.getValCheck("category", id, BDAT_TYPE_U8);
  condition = bdat.getValCheck("cndID", id, BDAT_TYPE_U16);
  isNoTelop = Bdat::getFlagVal(bdat.unknown00, "flag", id, "noTelop") != 0;
  if (msgId != 0) {
    name = Bdat::getMSText(gf::GfDataBdat::getFP(gf::BDAT_FLD_LANDMARK), msgId);
  }
}

bool GmkLandmark::BdatInfo::isCondMatched() const {
  if (condition != 0 && !gf::GfGameCond::isGameCond(condition)) {
    return false;
  }
  return true;
}

} // namespace gmk
