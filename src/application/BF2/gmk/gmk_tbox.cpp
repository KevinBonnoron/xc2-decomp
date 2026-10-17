#include "gmk/gmk_tbox.h"

#include "bdat.h"
#include "gf/data/gf_bdat_id.h"
#include "gf/data/gf_bdat_wrapper.h"
#include "gf/data/gf_data_bdat.h"
#include "gf/data/gf_game_flag.h"
#include "gf/game/gf_game_cond.h"
#include "gf/object/gf_obj.h"
#include "gf/object/gf_obj_acc.h"
#include "gf/object/gf_obj_factory.h"
#include "gf/object/gf_obj_handle.h"
#include "gf/object/gf_obj_setup.h"
#include "gf/object/gf_obj_util.h"
#include "gmk/gmk_bdat.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/rtti.h"

namespace gf {
struct GF_OBJ_HANDLE;
} // namespace gf

namespace gmk {

void GmkTbox::BdatInfo::create(u8 *bdat, int id, const AGmkBase &gmk) {
  condition = Bdat::getValCheck(bdat, "Condition", id, BDAT_TYPE_U16);
  isDig = Bdat::getFlagVal(bdat, "flag", id, "Digflg") != 0;
  msgVisible = Bdat::getValCheck(bdat, "msgVisible", id, BDAT_TYPE_U8);
  msgDigVisible = Bdat::getValCheck(bdat, "msgdigVisible", id, BDAT_TYPE_U8);
  u16 resourceId = Bdat::getValCheck(bdat, "RSC_ID", id, BDAT_TYPE_U16);
  u8 *tboxList = gf::GfDataBdat::getFP(gf::BDAT_RSC_TBOX_LIST);
  u16 visibleRadius = Bdat::getValCheck(tboxList, "visible_Radius", resourceId, BDAT_TYPE_U16);
  popDist.distSq = static_cast<f32>(visibleRadius) * static_cast<f32>(visibleRadius);
  u16 invisibleRadius = Bdat::getValCheck(tboxList, "invisible_Radius", resourceId, BDAT_TYPE_U16);
  depopDist.distSq = static_cast<f32>(invisibleRadius) * static_cast<f32>(invisibleRadius);
  u16 categoryResourceId = Bdat::getValCheck(bdat, "RSC_ID", id, BDAT_TYPE_U16);
  isTboxCategory = Bdat::getFlagVal(gf::GfDataBdat::getFP(gf::BDAT_RSC_TBOX_LIST), "flag", categoryResourceId, "TBOX_category") != 0;
}

void GmkTbox::BdatInfo::dispose() {}

bool GmkTbox::BdatInfo::isPopCondMatchedExceptDist() const {
  if (condition != 0 && !gf::GfGameCond::isGameCond(condition)) {
    return false;
  }
  return true;
}

bool GmkTbox::BdatInfo::isPopCondMatched(const mm::Vec3 &position) const {
  if (!isPopCondMatchedExceptDist()) {
    return false;
  }
  return DistCond::isMatch(popDist.distSq, position);
}

bool GmkTbox::BdatInfo::isDepopCondMatched(const mm::Vec3 &position) const {
  if (!isPopCondMatchedExceptDist()) {
    return true;
  }
  return !DistCond::isMatch(depopDist.distSq, position);
}

void GmkTbox::BdatInfo::debugDraw(const AGmkBase &gmk) const {}

namespace {

void setGobTargetable(gf::GF_OBJ_HANDLE *handle, bool isTargetable) {
  if (handle == gf::INVALID_HANDLE) {
    return;
  }
  gf::GfObjAcc acc(handle);
  if (acc.isValid()) {
    gf::GfObjSetupGimmick *setup = mm::mtl::dynamicCast<gf::GfObjSetupGimmick>(gf::GfObjManager::getObjInfo(handle)->setup);
    if (isTargetable) {
      setup->attribute |= gf::OBJ_ATTRIBUTE_TARGET_MASK;
    } else {
      setup->attribute &= ~gf::OBJ_ATTRIBUTE_TARGET_MASK;
    }
  }
  gf::GfObj *obj = acc.getObj();
  if (obj != nullptr) {
    if (isTargetable) {
      obj->attribute |= gf::OBJ_ATTRIBUTE_TARGET_MASK;
    } else {
      obj->attribute &= ~gf::OBJ_ATTRIBUTE_TARGET_MASK;
    }
  }
}

} // namespace

GmkTbox::GmkTbox() : handle(gf::INVALID_HANDLE), isDisp(true), openedDisposeTime(0.0f), openedTimer(0.0f) {}

int GmkTbox::getGameFlagId() const { return createInfo.bdatIndex + GAME_FLAG_PROGRESS; }

void GmkTbox::successToAccess() {
  u32 progress;
  if (getBdatInfo()->isDig && getProgress() == PROGRESS_CLOSED) {
    progress = PROGRESS_DUG;
  } else {
    setGobTargetable(handle, false);
    progress = PROGRESS_OPENED;
  }
  gf::GfGameFlag::setLocal(2, createInfo.bdatIndex + GAME_FLAG_PROGRESS, progress);
}

void GmkTbox::setTargetable(bool isTargetable) const { setGobTargetable(handle, isTargetable); }

void GmkTbox::create(const CreateInfo &info) { AGmkBase::create(info); }

void GmkTbox::dispose() {
  disposeGobInst(false);
  AGmkBase::dispose();
}

void GmkTbox::disposeGobInst(bool isFadeOut) {
  if (handle == gf::INVALID_HANDLE) {
    return;
  }
  if (isFadeOut) {
    gmk::disposeGobInst(handle, 1.0f);
  } else {
    unbindToGameObj(handle);
    gf::GfObjUtil::destroy(handle);
    handle = gf::INVALID_HANDLE;
  }
}

void GmkTbox::update(f32 deltaTime) {
  AGmkBase::update(deltaTime);
  if (!isValid()) {
    return;
  }
  if (!(getBdatInfo()->popDist.distSq > 0.0f) || !(getBdatInfo()->depopDist.distSq > 0.0f)) {
    return;
  }
  if (isInterestPosExist()) {
    if (canPopGobInst()) {
      createGobInst();
    } else if (canDepopGobInst()) {
      disposeGobInst(true);
    }
  }
  if (getBdatInfo()->isTboxCategory && getProgress() == PROGRESS_OPENED && handle != gf::INVALID_HANDLE && openedTimer < openedDisposeTime) {
    openedTimer += deltaTime;
    if (openedDisposeTime <= openedTimer) {
      gmk::disposeGobInst(handle, 1.0f);
    }
  }
}

bool GmkTbox::canPopGobInst() const {
  if (handle != gf::INVALID_HANDLE) {
    return false;
  }
  if (getBdatInfo()->isTboxCategory && getProgress() == PROGRESS_OPENED) {
    return false;
  }
  return getBdatInfo()->isPopCondMatched(baseInfo.xform->position);
}

void GmkTbox::createGobInst() {
  if (!canCreateGameEntity()) {
    return;
  }
  disposeGobInst(false);
  CBdatWrapper bdat = {getBindedBdatFp()};
  handle = gf::GfObjFactory::createGmkTbox(bdat, createInfo.bdatIndex);
  bindToGameObj(handle);
  validateDisp();
  bool isOpened = getProgress() == PROGRESS_OPENED;
  gf::GfObjSetupGimmick *setup = gf::GfObjUtil::getObjSetup<gf::GfObjSetupGimmick>(handle);
  setup->motion = isOpened ? "S_open_02" : "S_open_00";
  const Xform *xform = baseInfo.xform;
  setup->position = xform->position;
  setup->rotation = xform->rotation;
  setup->setInitialScale(getData()->scale * 0.1f);
  if (getBdatInfo()->isDig && getProgress() == PROGRESS_CLOSED) {
    setup->opacity = 0.0f;
  }
  setup->isAccessible = !isOpened;
  setGobTargetable(handle, !isOpened);
}

bool GmkTbox::canDepopGobInst() const {
  if (handle != gf::INVALID_HANDLE && getBdatInfo()->isDepopCondMatched(baseInfo.xform->position)) {
    return true;
  }
  return false;
}

void GmkTbox::debugDraw() const {
  AGmkBase::debugDraw();
  isValid();
}

void GmkTbox::validateDisp() const {
  if (handle == gf::INVALID_HANDLE) {
    return;
  }
  setEventDisp(handle, isDisp && debugIsDispGmkType(getGmkType()));
}

void GmkTbox::onGobEvent(gf::IGfObjListener::OBJEVT event, gf::GF_OBJ_HANDLE *handle) {
  AGmkBase::onGobEvent(event, handle);
  if (event == gf::IGfObjListener::OBJEVT_DESTROY) {
    disposeGobInst(false);
  }
}

void GmkTbox::onPlayerAccessed(gf::GF_OBJ_HANDLE *handle) {}

} // namespace gmk
