#include "gmk/gmk_map_obj.h"
#include "gmk/gmk_list_impl.h" // IWYU pragma: keep

#include "bdat.h"
#include "gf/data/gf_bdat_wrapper.h"
#include "gf/game/gf_game_cond.h"
#include "gf/game/gf_game_manager.h"
#include "gf/object/component/gf_com_transform.h"
#include "gf/object/gf_obj.h"
#include "gf/object/gf_obj_factory.h"
#include "gf/object/gf_obj_handle.h"
#include "gf/object/gf_obj_setup.h"
#include "gf/object/gf_obj_util.h"
#include "gmk/gmk_bdat.h"
#include "gmk/gmk_set.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/rtti.h"

namespace gmk {

template bool TGmkList<GmkMapObj, GmkMapObj::BdatInfo, 1330659661u, 3u, GmkMapObjGob>::initGmkBdatInfo(GmkMapObj::BdatInfo &, int &, const AGmkBase &);
template bool TGmkList<GmkRoutedMapObj, GmkMapObj::BdatInfo, 1330662738u, 7u, GmkRouteGob>::initGmkBdatInfo(GmkMapObj::BdatInfo &, int &, const AGmkBase &);

void GmkMapObj::BdatInfo::create(CBdatWrapper bdat, int id, const AGmkBase &gmk) {
  unknown00 = bdat.getValCheck("Condition", id, BDAT_TYPE_U16);
  u16 visibleXZ = bdat.getValCheck("Visible_XZ", id, BDAT_TYPE_U16);
  u16 visibleY = bdat.getValCheck("Visible_Y", id, BDAT_TYPE_U16);
  unknown04.set(visibleXZ, visibleY);
  u16 invisibleXZ = DistHvCond::clampDepopDist(bdat.getValCheck("Invisible_XZ", id, BDAT_TYPE_U16), visibleXZ);
  u16 invisibleY = DistHvCond::clampDepopDist(bdat.getValCheck("Invisible_Y", id, BDAT_TYPE_U16), visibleY);
  unknown0c.set(invisibleXZ, invisibleY);
  if (Bdat::getMember(bdat.unknown00, "Priority") != nullptr) {
    unknown02 = bdat.getValCheck("Priority", id, BDAT_TYPE_U8);
  }
}

bool GmkMapObj::BdatInfo::isPopCondMatched(const mm::Vec3 &position) const {
  if (!unknown04.isMatch(position)) {
    return false;
  }
  if (unknown00 != 0 && !gf::GfGameCond::isGameCond(unknown00)) {
    return false;
  }
  return true;
}

bool GmkMapObj::BdatInfo::isDepopCondMatched(const mm::Vec3 &position) const {
  if (!unknown0c.isMatch(position)) {
    return true;
  }
  if (unknown00 != 0 && !gf::GfGameCond::isGameCond(unknown00)) {
    return true;
  }
  return false;
}

void GmkMapObj::reqDisposeGob(f32 fadeTime, u32 attribute) const {
  unknown54 = fadeTime;
  unknown58 = attribute;
}

void GmkMapObj::dispose() {
  disposeGobInst(false);
  AGmkBase::dispose();
}

void GmkMapObj::disposeGobInst(bool isFadeOut) {
  if (unknown48 == gf::INVALID_HANDLE) {
    return;
  }
  if (isFadeOut && unknown54 > 0.0f) {
    disposeGobInstWithAttr(unknown48, unknown58, unknown54);
    unknown54 = 0.0f;
  } else {
    unbindToGameObj(unknown48);
    gmk::disposeGobInst(unknown48, 0.0f);
    unknown48 = gf::INVALID_HANDLE;
  }
}

void GmkMapObj::update(f32 deltaTime) {
  AGmkBase::update(deltaTime);
  if (!isValid()) {
    return;
  }
  if (!isInterestPosExist()) {
    return;
  }
  if (canPopGobInst()) {
    createGobInst();
  } else if (canDepopGobInst()) {
    disposeGobInst(true);
  }
}

bool GmkMapObj::canPopGobInst() const {
  if (unknown48 != gf::INVALID_HANDLE || !getBdatInfo()->isPopCondMatched(unknown08.unknown08->unknown00)) {
    return false;
  }
  if (unknown51 && !unknown52) {
    return false;
  }
  return true;
}

void GmkMapObj::createGobInst() {
  if (!canCreateGameEntity()) {
    return;
  }
  disposeGobInst(false);
  CBdatWrapper bdat = {getBindedBdatFp()};
  unknown48 = gf::GfObjFactory::createGmkMapObj(bdat, unknown20.unknown18);
  bindToGameObj(unknown48);
  validateDisp();
  gf::GfObjSetupGimmick *setup = gf::GfObjUtil::getObjSetup<gf::GfObjSetupGimmick>(unknown48);
  const Xform *xform = unknown08.unknown08;
  setup->unknown20 = xform->unknown00;
  setup->unknown30 = xform->unknown10;
  setup->setInitialScale(unknown08.unknown08->unknown20.x);
}

bool GmkMapObj::canDepopGobInst() const {
  if (unknown48 != gf::INVALID_HANDLE && (getBdatInfo()->isDepopCondMatched(unknown08.unknown08->unknown00) || (unknown51 && !unknown52))) {
    return true;
  }
  return false;
}

void GmkMapObj::validateDisp() const {
  if (unknown48 == gf::INVALID_HANDLE) {
    return;
  }
  setEventDisp(unknown48, unknown50 && debugIsDispGmkType(getGmkType()));
}

void GmkMapObj::onGobEvent(gf::IGfObjListener::OBJEVT event, gf::GF_OBJ_HANDLE *handle) {
  AGmkBase::onGobEvent(event, handle);
  if (event == gf::IGfObjListener::OBJEVT_DESTROY) {
    disposeGobInst(false);
  }
}

GmkRoutedMapObj::GmkRoutedMapObj() : unknown50(gf::INVALID_HANDLE), unknown58(true) {}

void GmkRoutedMapObj::create(const CreateInfo &info) { GmkRoute::create(info); }

void GmkRoutedMapObj::dispose() {
  disposeGobInst();
  GmkRoute::dispose();
}

void GmkRoutedMapObj::disposeGobInst() {
  if (unknown50 == gf::INVALID_HANDLE) {
    return;
  }
  unbindToGameObj(unknown50);
  gf::GfObjUtil::destroy(unknown50);
  unknown50 = gf::INVALID_HANDLE;
}

void GmkRoutedMapObj::update(f32 deltaTime) {
  AGmkBase::update(deltaTime);
  if (!isValid()) {
    return;
  }
  if (!isInterestPosExist()) {
    return;
  }
  if (canPopGobInst()) {
    createGobInst();
  } else if (canDepopGobInst()) {
    disposeGobInst();
  }
}

bool GmkRoutedMapObj::canDepopGobInst() const {
  if (unknown50 == gf::INVALID_HANDLE || gf::GfGameManager::getControlMover() == gf::INVALID_HANDLE) {
    return false;
  }
  const GmkMapObj::BdatInfo *info = getBdatInfo();
  const mm::Vec3 &position = gf::GfObjUtil::getObj(gf::GfGameManager::getControlMover())->getComponent<gf::GfComTransform>()->getPosition();
  mm::Vec3 nearest;
  if (!GmkRoute::getNearestPos(nearest, position)) {
    return false;
  }
  if (info->unknown0c.isMatch(nearest)) {
    if (info->unknown00 == 0) {
      return false;
    }
    if (gf::GfGameCond::isGameCond(info->unknown00)) {
      return false;
    }
  }
  return true;
}

void GmkRoutedMapObj::createGobInst() {
  if (!canCreateGameEntity()) {
    return;
  }
  disposeGobInst();
  CBdatWrapper bdat = {getBindedBdatFp()};
  unknown50 = gf::GfObjFactory::createGmkMapObj(bdat, unknown20.unknown18);
  bindToGameObj(unknown50);
  validateDisp();
  gf::GfObjSetupGimmick *setup = mm::mtl::dynamicCast<gf::GfObjSetupGimmick>(gf::GfObjManager::getObjInfo(unknown50)->unknown30);
  const Xform *xform = unknown08.unknown08;
  setup->unknown20 = xform->unknown00;
  setup->unknown30 = xform->unknown10;
}

void GmkRoutedMapObj::validateDisp() const {
  if (unknown50 == gf::INVALID_HANDLE) {
    return;
  }
  setEventDisp(unknown50, unknown58 && debugIsDispGmkType(getGmkType()));
}

const IGmkList *GmkRoutedMapObj::getBindedRoutePointList() const { return unknown08.unknown00->getCreateInfo().unknown08->unknown1b8[GMK_TYPE_MAP_OBJ_ROUTE_POINT]; }

void GmkRoutedMapObj::onGobEvent(gf::IGfObjListener::OBJEVT event, gf::GF_OBJ_HANDLE *handle) {
  AGmkBase::onGobEvent(event, handle);
  if (event == gf::IGfObjListener::OBJEVT_DESTROY) {
    this->unknown50 = gf::INVALID_HANDLE;
  }
}

} // namespace gmk
