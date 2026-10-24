#include "gmk/gmk_map_obj.h"

#include "bdat.h"
#include "gf/data/gf_bdat_wrapper.h"
#include "gf/game/gf_game_cond.h"
#include "gf/object/gf_obj_factory.h"
#include "gf/object/gf_obj_handle.h"
#include "gf/object/gf_obj_setup.h"
#include "gf/object/gf_obj_util.h"
#include "gmk/gmk_bdat.h"
#include "gmk/gmk_set.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/rtti.h"

namespace gmk {

void GmkMapObj::BdatInfo::create(CBdatWrapper bdat, int id, const AGmkBase &gmk) {
  condition = bdat.getValCheck("Condition", id, BDAT_TYPE_U16);
  u16 visibleXZ = bdat.getValCheck("Visible_XZ", id, BDAT_TYPE_U16);
  u16 visibleY = bdat.getValCheck("Visible_Y", id, BDAT_TYPE_U16);
  popDist.set(visibleXZ, visibleY);
  u16 invisibleXZ = DistHvCond::clampDepopDist(bdat.getValCheck("Invisible_XZ", id, BDAT_TYPE_U16), visibleXZ);
  u16 invisibleY = DistHvCond::clampDepopDist(bdat.getValCheck("Invisible_Y", id, BDAT_TYPE_U16), visibleY);
  depopDist.set(invisibleXZ, invisibleY);
  if (Bdat::getMember(bdat.unknown00, "Priority") != nullptr) {
    priority = bdat.getValCheck("Priority", id, BDAT_TYPE_U8);
  }
}

bool GmkMapObj::BdatInfo::isPopCondMatched(const mm::Vec3 &position) const {
  if (!popDist.isMatch(position)) {
    return false;
  }
  if (condition != 0 && !gf::GfGameCond::isGameCond(condition)) {
    return false;
  }
  return true;
}

bool GmkMapObj::BdatInfo::isDepopCondMatched(const mm::Vec3 &position) const {
  if (!depopDist.isMatch(position)) {
    return true;
  }
  if (condition != 0 && !gf::GfGameCond::isGameCond(condition)) {
    return true;
  }
  return false;
}

void GmkMapObj::reqDisposeGob(f32 fadeTime, u32 attribute) const {
  disposeFadeTime = fadeTime;
  disposeAttribute = attribute;
}

void GmkMapObj::dispose() {
  disposeGobInst(false);
  AGmkBase::dispose();
}

void GmkMapObj::disposeGobInst(bool isFadeOut) {
  if (handle == gf::INVALID_HANDLE) {
    return;
  }
  if (isFadeOut && disposeFadeTime > 0.0f) {
    disposeGobInstWithAttr(handle, disposeAttribute, disposeFadeTime);
    disposeFadeTime = 0.0f;
  } else {
    unbindToGameObj(handle);
    gmk::disposeGobInst(handle, 0.0f);
    handle = gf::INVALID_HANDLE;
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
  if (handle != gf::INVALID_HANDLE || !getBdatInfo()->isPopCondMatched(baseInfo.xform->position)) {
    return false;
  }
  if (isRemoved && !isRevived) {
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
  handle = gf::GfObjFactory::createGmkMapObj(bdat, createInfo.bdatIndex);
  bindToGameObj(handle);
  validateDisp();
  gf::GfObjSetupGimmick *setup = gf::GfObjUtil::getObjSetup<gf::GfObjSetupGimmick>(handle);
  const Xform *xform = baseInfo.xform;
  setup->position = xform->position;
  setup->rotation = xform->rotation;
  setup->setInitialScale(baseInfo.xform->scale.x);
}

bool GmkMapObj::canDepopGobInst() const {
  if (handle != gf::INVALID_HANDLE && (getBdatInfo()->isDepopCondMatched(baseInfo.xform->position) || (isRemoved && !isRevived))) {
    return true;
  }
  return false;
}

void GmkMapObj::validateDisp() const {
  if (handle == gf::INVALID_HANDLE) {
    return;
  }
  setEventDisp(handle, isDisp && debugIsDispGmkType(getGmkType()));
}

void GmkMapObj::onGobEvent(gf::IGfObjListener::OBJEVT event, gf::GF_OBJ_HANDLE *handle) {
  AGmkBase::onGobEvent(event, handle);
  if (event == gf::IGfObjListener::OBJEVT_DESTROY) {
    disposeGobInst(false);
  }
}

GmkRoutedMapObj::GmkRoutedMapObj() : handle(gf::INVALID_HANDLE), isDisp(true) {}

void GmkRoutedMapObj::create(const CreateInfo &info) { GmkRoute::create(info); }

void GmkRoutedMapObj::dispose() {
  disposeGobInst();
  GmkRoute::dispose();
}

void GmkRoutedMapObj::disposeGobInst() {
  if (handle == gf::INVALID_HANDLE) {
    return;
  }
  unbindToGameObj(handle);
  gf::GfObjUtil::destroy(handle);
  handle = gf::INVALID_HANDLE;
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

void GmkRoutedMapObj::createGobInst() {
  if (!canCreateGameEntity()) {
    return;
  }
  disposeGobInst();
  CBdatWrapper bdat = {getBindedBdatFp()};
  handle = gf::GfObjFactory::createGmkMapObj(bdat, createInfo.bdatIndex);
  bindToGameObj(handle);
  validateDisp();
  gf::GfObjSetupGimmick *setup = mm::mtl::dynamicCast<gf::GfObjSetupGimmick>(gf::GfObjManager::getObjInfo(handle)->setup);
  const Xform *xform = baseInfo.xform;
  setup->position = xform->position;
  setup->rotation = xform->rotation;
}

void GmkRoutedMapObj::validateDisp() const {
  if (handle == gf::INVALID_HANDLE) {
    return;
  }
  setEventDisp(handle, isDisp && debugIsDispGmkType(getGmkType()));
}

const IGmkList *GmkRoutedMapObj::getBindedRoutePointList() const { return baseInfo.list->getCreateInfo().set->lists[GMK_TYPE_MAP_OBJ_ROUTE_POINT]; }

void GmkRoutedMapObj::onGobEvent(gf::IGfObjListener::OBJEVT event, gf::GF_OBJ_HANDLE *handle) {
  AGmkBase::onGobEvent(event, handle);
  if (event == gf::IGfObjListener::OBJEVT_DESTROY) {
    this->handle = gf::INVALID_HANDLE;
  }
}

} // namespace gmk
