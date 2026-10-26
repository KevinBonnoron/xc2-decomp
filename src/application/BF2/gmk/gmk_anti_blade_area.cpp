#include "gmk/gmk_anti_blade_area.h"

#include "gf/data/gf_bdat_wrapper.h"
#include "gmk/gmk_bdat.h"

namespace gmk {

void GmkAntiBladeArea::BdatInfo::create(CBdatWrapper bdat, int id, const AGmkBase &gmk) {
  dispose();
  unknown00 = bdat.getValCheck("BTL_MapRevId", id, BDAT_TYPE_U16);
}

GmkType GmkAntiBladeArea::getGmkType() const { return GMK_TYPE; }

void GmkAntiBladeArea::debugDraw() const {}

void GmkAntiBladeArea::create(const CreateInfo &info) {
  AGmkBase::create(info);
  createGmkPhantom();
}

void GmkAntiBladeArea::createGmkPhantom() {
  if (!canCreateGameEntity()) {
    return;
  }
  unknown60.create(*this, this, false);
}

void GmkAntiBladeArea::dispose() {
  GmkAntiBladeAreaManager::removeGmk(this);
  unknown60.dispose();
  AGmkBase::dispose();
}

void GmkAntiBladeArea::onEnterPhantom(const IGmkPhantomEventListener::OnEnterInfo &info) { GmkAntiBladeAreaManager::addGmk(this); }

void GmkAntiBladeArea::onLeavePhantom(const IGmkPhantomEventListener::OnLeaveInfo &info) { GmkAntiBladeAreaManager::removeGmk(this); }

void GmkAntiBladeAreaManager::addGmk(GmkAntiBladeArea *gmk) {
  get()->unknown08.push_front(gmk);
  get()->unknown20 = get()->unknown08.begin().get();
}

void GmkAntiBladeAreaManager::removeGmk(GmkAntiBladeArea *gmk) {
  if (gmk == nullptr || !gmk->intoNode() || get() == nullptr) {
    return;
  }
  get()->unknown08.erase(gmk);
  if (get()->unknown08.empty()) {
    get()->unknown20 = nullptr;
  } else {
    get()->unknown20 = get()->unknown08.begin().get();
  }
}

} // namespace gmk
