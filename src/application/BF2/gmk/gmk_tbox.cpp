#include "gmk/gmk_tbox.h"
#include "gmk/gmk_list_impl.h" // IWYU pragma: keep

#include "bdat.h"
#include "gf/data/gf_bdat_id.h"
#include "gf/data/gf_bdat_wrapper.h"
#include "gf/data/gf_data_bdat.h"
#include "gf/data/gf_game_flag.h"
#include "gf/game/gf_game_cond.h"
#include "gf/object/gf_obj_factory.h"
#include "gf/object/gf_obj_handle.h"
#include "gf/object/gf_obj_setup.h"
#include "gf/object/gf_obj_util.h"
#include "gmk/gmk_bdat.h"
#include "mm_mtl/fixstr.h"

namespace gf {
struct GF_OBJ_HANDLE;
} // namespace gf

namespace gmk {

template bool TGmkList<GmkTbox, GmkTbox::BdatInfo, 1481589332u, 6u, GmkTboxGob>::initGmkBdatInfo(GmkTbox::BdatInfo &, int &, const AGmkBase &);

void GmkTbox::BdatInfo::create(u8 *bdat, int id, const AGmkBase &gmk) {
  unknown00 = Bdat::getValCheck(bdat, "Condition", id, BDAT_TYPE_U16);
  unknown02 = Bdat::getFlagVal(bdat, "flag", id, "Digflg") != 0;
  unknown03 = Bdat::getValCheck(bdat, "msgVisible", id, BDAT_TYPE_U8);
  unknown04 = Bdat::getValCheck(bdat, "msgdigVisible", id, BDAT_TYPE_U8);
  u16 resourceId = Bdat::getValCheck(bdat, "RSC_ID", id, BDAT_TYPE_U16);
  u8 *tboxList = gf::GfDataBdat::getFP(gf::BDAT_RSC_TBOX_LIST);
  u16 visibleRadius = Bdat::getValCheck(tboxList, "visible_Radius", resourceId, BDAT_TYPE_U16);
  unknown08.unknown00 = static_cast<f32>(visibleRadius) * static_cast<f32>(visibleRadius);
  u16 invisibleRadius = Bdat::getValCheck(tboxList, "invisible_Radius", resourceId, BDAT_TYPE_U16);
  unknown0c.unknown00 = static_cast<f32>(invisibleRadius) * static_cast<f32>(invisibleRadius);
  u16 categoryResourceId = Bdat::getValCheck(bdat, "RSC_ID", id, BDAT_TYPE_U16);
  unknown05 = Bdat::getFlagVal(gf::GfDataBdat::getFP(gf::BDAT_RSC_TBOX_LIST), "flag", categoryResourceId, "TBOX_category") != 0;
}

void GmkTbox::BdatInfo::dispose() {}

bool GmkTbox::BdatInfo::isPopCondMatchedExceptDist() const {
  if (unknown00 != 0 && !gf::GfGameCond::isGameCond(unknown00)) {
    return false;
  }
  return true;
}

bool GmkTbox::BdatInfo::isPopCondMatched(const mm::Vec3 &position) const {
  if (!isPopCondMatchedExceptDist()) {
    return false;
  }
  return DistCond::isMatch(unknown08.unknown00, position);
}

bool GmkTbox::BdatInfo::isDepopCondMatched(const mm::Vec3 &position) const {
  if (!isPopCondMatchedExceptDist()) {
    return true;
  }
  return !DistCond::isMatch(unknown0c.unknown00, position);
}

void GmkTbox::BdatInfo::debugDraw(const AGmkBase &gmk) const {}

namespace {

void setGobTargetable(gf::GF_OBJ_HANDLE *handle, bool isTargetable) {
  if (handle == gf::INVALID_HANDLE) {
    return;
  }
  unknown002(handle, isTargetable);
}

} // namespace

GmkTbox::GmkTbox() : unknown48(gf::INVALID_HANDLE), unknown50(true), unknown54(0.0f), unknown58(0.0f) {}

int GmkTbox::getGameFlagId() const { return unknown20.unknown18 + GAME_FLAG_PROGRESS; }

void GmkTbox::successToAccess() {
  u32 progress;
  if (getBdatInfo()->unknown02 && getProgress() == PROGRESS_CLOSED) {
    progress = PROGRESS_DUG;
  } else {
    setGobTargetable(unknown48, false);
    progress = PROGRESS_OPENED;
  }
  gf::GfGameFlag::setLocal(2, unknown20.unknown18 + GAME_FLAG_PROGRESS, progress);
}

void GmkTbox::setTargetable(bool isTargetable) const { setGobTargetable(unknown48, isTargetable); }

void GmkTbox::create(const CreateInfo &info) { AGmkBase::create(info); }

void GmkTbox::dispose() {
  disposeGobInst(false);
  AGmkBase::dispose();
}

void GmkTbox::disposeGobInst(bool isFadeOut) {
  if (unknown48 == gf::INVALID_HANDLE) {
    return;
  }
  if (isFadeOut) {
    gmk::disposeGobInst(unknown48, 1.0f);
  } else {
    unbindToGameObj(unknown48);
    gf::GfObjUtil::destroy(unknown48);
    unknown48 = gf::INVALID_HANDLE;
  }
}

void GmkTbox::update(f32 deltaTime) {
  AGmkBase::update(deltaTime);
  if (!isValid()) {
    return;
  }
  if (!(getBdatInfo()->unknown08.unknown00 > 0.0f) || !(getBdatInfo()->unknown0c.unknown00 > 0.0f)) {
    return;
  }
  if (isInterestPosExist()) {
    if (canPopGobInst()) {
      createGobInst();
    } else if (canDepopGobInst()) {
      disposeGobInst(true);
    }
  }
  if (getBdatInfo()->unknown05 && getProgress() == PROGRESS_OPENED && unknown48 != gf::INVALID_HANDLE && unknown58 < unknown54) {
    unknown58 += deltaTime;
    if (unknown54 <= unknown58) {
      gmk::disposeGobInst(unknown48, 1.0f);
    }
  }
}

bool GmkTbox::canPopGobInst() const {
  if (unknown48 != gf::INVALID_HANDLE) {
    return false;
  }
  if (getBdatInfo()->unknown05 && getProgress() == PROGRESS_OPENED) {
    return false;
  }
  return getBdatInfo()->isPopCondMatched(unknown08.unknown08->unknown00);
}

void GmkTbox::createGobInst() {
  if (!canCreateGameEntity()) {
    return;
  }
  disposeGobInst(false);
  CBdatWrapper bdat = {getBindedBdatFp()};
  unknown48 = gf::GfObjFactory::createGmkTbox(bdat, unknown20.unknown18);
  bindToGameObj(unknown48);
  validateDisp();
  bool isOpened = getProgress() == PROGRESS_OPENED;
  gf::GfObjSetupGimmick *setup = gf::GfObjUtil::getObjSetup<gf::GfObjSetupGimmick>(unknown48);
  setup->unknown70 = isOpened ? "S_open_02" : "S_open_00";
  unknown003(setup, unknown08.unknown08);
  setup->setInitialScale(getData()->unknown04 * 0.1f);
  if (getBdatInfo()->unknown02 && getProgress() == PROGRESS_CLOSED) {
    setup->unknown50 = 0.0f;
  }
  setup->unknowna1 = !isOpened;
  setGobTargetable(unknown48, !isOpened);
}

bool GmkTbox::canDepopGobInst() const {
  if (unknown48 != gf::INVALID_HANDLE && getBdatInfo()->isDepopCondMatched(unknown08.unknown08->unknown00)) {
    return true;
  }
  return false;
}

void GmkTbox::debugDraw() const {
  AGmkBase::debugDraw();
  isValid();
}

void GmkTbox::validateDisp() const {
  if (unknown48 == gf::INVALID_HANDLE) {
    return;
  }
  setEventDisp(unknown48, unknown50 && debugIsDispGmkType(getGmkType()));
}

void GmkTbox::onGobEvent(gf::IGfObjListener::OBJEVT event, gf::GF_OBJ_HANDLE *handle) {
  AGmkBase::onGobEvent(event, handle);
  if (event == gf::IGfObjListener::OBJEVT_DESTROY) {
    disposeGobInst(false);
  }
}

void GmkTbox::onPlayerAccessed(gf::GF_OBJ_HANDLE *handle) {}

} // namespace gmk
