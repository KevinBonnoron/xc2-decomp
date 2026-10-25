#include "gmk/gmk_area_bgm.h"

#include "gf/data/gf_bdat_wrapper.h"
#include "gmk/gmk_bdat.h"

namespace gmk {

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

} // namespace gmk
