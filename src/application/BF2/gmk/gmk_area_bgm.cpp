#include "gmk/gmk_area_bgm.h"

#include "gf/data/gf_bdat_wrapper.h"
#include "gf/game/gf_game_cond.h"
#include "gmk/gmk_bdat.h"

namespace gmk {

bool GmkBgmCondInfo::isCondMatched() const { return gf::GfGameCond::isGameCond(unknown18); }

GmkType GmkAreaBgm::getGmkType() const { return GMK_TYPE; }

void GmkAreaBgm::create(const CreateInfo &info) {
  AGmkBase::create(info);
  createBgmCondInfos();
}

void GmkAreaBgm::debugDraw() const {}

void GmkAreaBgm::BdatInfo::create(CBdatWrapper bdat, int id, const AGmkBase &gmk) {
  dispose();
  unknown00 = bdat.getValCheck("bgmCondition", id, BDAT_TYPE_U16);
}

void GmkAreaBgm::onEnterPhantom(const IGmkPhantomEventListener::OnEnterInfo &info) {}

GmkBgmCondInfo *GmkAreaBgm::findCondMatched() {
  if (gf::GfGameCond::isGameCond(unknownE0.unknown18)) {
    return &unknownE0;
  }
  if (gf::GfGameCond::isGameCond(unknown100.unknown18)) {
    return &unknown100;
  }
  if (gf::GfGameCond::isGameCond(unknown120.unknown18)) {
    return &unknown120;
  }
  if (gf::GfGameCond::isGameCond(unknown140.unknown18)) {
    return &unknown140;
  }
  return nullptr;
}

} // namespace gmk
