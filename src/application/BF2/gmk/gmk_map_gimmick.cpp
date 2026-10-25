#include "gmk/gmk_map_gimmick.h"

#include "bdat.h"
#include "gf/data/gf_bdat_wrapper.h"
#include "gf/data/gf_game_flag.h"
#include "gf/game/gf_game_cond.h"
#include "gmk/gmk_bdat.h"

namespace gmk {

void GmkMapGimmick::BdatInfo::create(CBdatWrapper bdat, int id, const AGmkBase &gmk) {
  u16 popTime = bdat.getValCheck("popTime", id, BDAT_TYPE_U32);
  unknown08.unknown08 = popTime;
  unknown18.unknown08 = bdat.getValCheck("popWeather", id, BDAT_TYPE_U8);
  unknown28 = BootedGmkCond(bdat, id, nullptr);
  unknown00 = bdat.getValCheck("Condition", id, BDAT_TYPE_U16);
  unknown02 = bdat.getValCheck("nameRadius", id, BDAT_TYPE_U16);
  unknown04 = bdat.getValCheck("mapobjID", id, BDAT_TYPE_U16);
  unknown06 = Bdat::getFlagVal(bdat.unknown00, "flag", id, "MSG_ray") != 0;
}

bool GmkMapGimmick::BdatInfo::isPopCondMatched() const {
  if (unknown08.isEnable() && !unknown08.isMatch()) {
    return false;
  }
  if (unknown18.isEnable() && !unknown18.isMatch()) {
    return false;
  }
  if (unknown28.isEnable() && !unknown28.isMatch()) {
    return false;
  }
  if (unknown00 != 0 && !gf::GfGameCond::isGameCond(unknown00)) {
    return false;
  }
  return true;
}

void GmkMapGimmick::BdatInfo::debugDraw(const AGmkBase &gmk) const {}

void GmkMapGimmick::onPlayerAccessed(gf::GF_OBJ_HANDLE *handle) {}

GmkType GmkMapGimmick::getGmkType() const { return GMK_TYPE; }

int GmkMapGimmick::getGameFlagId() const { return unknown20.unknown18 + 0xab66; }

void GmkMapGimmick::setSolved() const { gf::GfGameFlag::setLocal(1, getGameFlagId(), 1); }

void GmkMapGimmickList::setUpdateGmkNumPerFrame(u32 num) {
  TGmkList::setUpdateGmkNumPerFrame(num);
  unknown230.setUpdateGmkNumPerFrame(num);
}

void GmkMapGimmickList::debugDraw() const {
  TGmkList::debugDraw();
  unknown230.debugDraw();
}

void GmkMapGimmickList::debugUpdateMmf() {
  TGmkList::debugUpdateMmf();
  unknown230.debugUpdateMmf();
}

} // namespace gmk
