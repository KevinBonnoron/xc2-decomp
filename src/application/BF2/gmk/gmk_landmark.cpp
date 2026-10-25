#include "gmk/gmk_landmark.h"

#include "bdat.h"
#include "gf/data/gf_bdat_id.h"
#include "gf/data/gf_bdat_wrapper.h"
#include "gf/data/gf_data_bdat.h"
#include "gf/data/gf_game_flag.h"
#include "gf/game/gf_game_cond.h"
#include "gmk/gmk_bdat.h"

namespace gmk {

void GmkLandmark::BdatInfo::create(CBdatWrapper bdat, int id, const AGmkBase &gmk) {
  unknown00 = bdat.getValCheck("MSGID", id, BDAT_TYPE_U16);
  unknown02 = bdat.getValCheck("category", id, BDAT_TYPE_U8);
  unknown04 = bdat.getValCheck("cndID", id, BDAT_TYPE_U16);
  unknown06 = Bdat::getFlagVal(bdat.unknown00, "flag", id, "noTelop") != 0;
  if (unknown00 != 0) {
    unknown08 = Bdat::getMSText(gf::GfDataBdat::getFP(gf::BDAT_FLD_LANDMARK), unknown00);
  }
}

bool GmkLandmark::BdatInfo::isCondMatched() const {
  if (unknown04 != 0 && !gf::GfGameCond::isGameCond(unknown04)) {
    return false;
  }
  return true;
}

GmkType GmkLandmark::getGmkType() const { return GMK_TYPE; }

int GmkLandmark::getGameFlagId() const { return unknown20.unknown18 + 0xc7d9; }

bool GmkLandmark::isFound() const { return gf::GfGameFlag::getLocal(1, getGameFlagId()) != 0; }

void GmkLandmark::onEnterPhantom(const IGmkPhantomEventListener::OnEnterInfo &info) {}

} // namespace gmk
