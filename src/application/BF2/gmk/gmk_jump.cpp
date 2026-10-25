#include "gmk/gmk_jump.h"

#include "bdat.h"
#include "framework/effect/effect_manager.h"
#include "gf/data/gf_bdat_id.h"
#include "gf/data/gf_bdat_wrapper.h"
#include "gf/data/gf_data_bdat.h"
#include "gf/game/gf_game_cond.h"
#include "gf/game/gf_game_manager.h"
#include "gf/object/gf_obj_acc.h"
#include "gf/object/gf_obj_handle.h"
#include "gf/object/gf_obj_util.h"
#include "gmk/gmk_bdat.h"

namespace fw {
enum EF_CATEGORY : int;
} // namespace fw

namespace gmk {

constexpr int WILDCARD_JUMP_ICON_DIST_ROW = 1;
constexpr u32 ICON_FADE_OUT_FRAME = 5;
const fw::EF_CATEGORY ICON_EFFECT_CATEGORY = static_cast<fw::EF_CATEGORY>(1);

void GmkJump::BdatInfo::create(CBdatWrapper bdat, int id, const AGmkBase &gmk) {
  unknown00 = bdat.getValCheck("Condition", id, BDAT_TYPE_U16);
  unknown02 = bdat.getValCheck("jumpType", id, BDAT_TYPE_U8);
  unknown04 = bdat.getValCheck("nameRadius", id, BDAT_TYPE_U16);
}

bool GmkJump::BdatInfo::isPopCondMatched() const {
  if (unknown00 != 0 && !gf::GfGameCond::isGameCond(unknown00)) {
    return false;
  }
  return true;
}

void GmkJump::BdatInfo::debugDraw(const AGmkBase &gmk) const {}

GmkJump::GmkJump() : _48(), unknown50(false), unknown58(gf::INVALID_HANDLE), unknown60(), unknown68(), unknown74(), unknown78(false), unknown79(true) {}

void GmkJump::create(const CreateInfo &info) {
  AGmkBase::create(info);
  u8 *mapList = gf::GfDataBdat::getFP(gf::BDAT_FLD_MAPLIST);
  if (mapList != nullptr) {
    int map = gf::GfGameManager::getMapID();
    if (map >= Bdat::getIdTop(mapList) && Bdat::getIdTop(mapList) + Bdat::getIdCount(mapList) > map) {
      u8 displayRadius = Bdat::getValCheck(mapList, "ene_disp_r", map, BDAT_TYPE_U8);
      u8 displayHeight = Bdat::getValCheck(mapList, "ene_disp_h", map, BDAT_TYPE_U8);
      unknown60.set(displayRadius, displayHeight);
      u8 releaseRadius = Bdat::getValCheck(mapList, "ene_release_r", map, BDAT_TYPE_U8);
      u8 releaseHeight = Bdat::getValCheck(mapList, "ene_release_h", map, BDAT_TYPE_U8);
      unknown68.set(displayRadius + releaseRadius, displayHeight + releaseHeight);
      f32 iconDistance = Bdat::getValCheck(gf::GfDataBdat::getFP(gf::BDAT_FLD_WILDCARD_DATA), 0, WILDCARD_JUMP_ICON_DIST_ROW, BDAT_TYPE_F32).valueF32;
      unknown74.unknown00 = iconDistance * iconDistance;
      return;
    }
  }
  dispose();
}

void GmkJump::dispose() {
  disposeIcon(false);
  disposeGobInst(false);
  AGmkBase::dispose();
}

void GmkJump::disposeIcon(bool isFadeOut) {
  if (unknown70 == 0) {
    return;
  }
  if (isFadeOut) {
    fw::EffectManager::get()->fadeOutDead(unknown70, ICON_FADE_OUT_FRAME);
  } else {
    fw::EffectManager::get()->remove(unknown70);
  }
  unknown70 = 0;
}

void GmkJump::disposeGobInst(bool isFadeOut) {
  if (unknown58 == gf::INVALID_HANDLE) {
    return;
  }
  if (isFadeOut) {
    gmk::disposeGobInst(unknown58, 1.0f);
  } else {
    unbindToGameObj(unknown58);
    gf::GfObjUtil::destroy(unknown58);
    unknown58 = gf::INVALID_HANDLE;
  }
}

void GmkJump::update(f32 deltaTime) {
  AGmkBase::update(deltaTime);
  if (!isValid()) {
    return;
  }
  unknown50 = getBdatInfo()->isPopCondMatched();
  if (!isInterestPosExist()) {
    return;
  }
  if (canPopGobInst()) {
    createGobInst();
  } else if (canDepopGobInst()) {
    disposeGobInst(true);
  }
  if (unknown78) {
    return;
  }
  if (unknown50 && DistCond::isMatch(unknown74.unknown00, getData()->position)) {
    if (unknown70 == 0) {
      createIcon();
    }
  } else {
    disposeIcon(true);
  }
}

bool GmkJump::canPopGobInst() const {
  if (unknown58 != gf::INVALID_HANDLE || !unknown50) {
    return false;
  }
  const mm::Vec3 &position = getData()->position;
  return unknown60.isMatch(position);
}

bool GmkJump::canDepopGobInst() const {
  if (unknown58 == gf::INVALID_HANDLE) {
    return false;
  }
  if (!unknown50) {
    return true;
  }
  const mm::Vec3 &position = getData()->position;
  return !unknown68.isMatch(position);
}

void GmkJump::createIcon() {
  if (!canCreateGameEntity()) {
    return;
  }
  disposeIcon(false);
  const char *name;
  switch (getBdatInfo()->unknown02) {
  case 0:
    name = "cmn_100_103";
    break;
  case 1:
    name = "cmn_100_106";
    break;
  default:
    name = "cmn_100_103";
    break;
  }
  void *data = fw::EffectManager::get()->search(name, nullptr);
  if (data == nullptr) {
    return;
  }
  unknown70 = fw::EffectManager::get()->create(data, true);
  if (unknown70 == 0) {
    return;
  }
  fw::EffectManager::get()->setCategory(unknown70, ICON_EFFECT_CATEGORY);
  validateIconPos();
}

void GmkJump::debugUpdateMmf() {}

void GmkJump::reqDeadIcon() {
  if (unknown78) {
    return;
  }
  unknown78 = true;
  if (unknown70 != 0) {
    fw::EffectManager::get()->dead(unknown70);
    unknown70 = 0;
  }
}

void GmkJump::reqRecreateIcon() {
  if (!unknown78) {
    return;
  }
  unknown78 = false;
  if (unknown70 == 0) {
    createIcon();
  }
}

void GmkJump::onGobEvent(gf::IGfObjListener::OBJEVT event, gf::GF_OBJ_HANDLE *handle) {
  AGmkBase::onGobEvent(event, handle);
  if (event == gf::IGfObjListener::OBJEVT_DESTROY) {
    disposeGobInst(false);
  }
}

void GmkJump::validateDisp() const {
  bool isDisp = unknown79 && debugIsDispGmkType(getGmkType());
  gf::GfObjAcc acc(unknown58);
  if (acc.isValid()) {
    acc.setDisp(gf::OBJDISP_GMK_EVENT, isDisp);
  }
  if (unknown70 != 0) {
    fw::EffectManager::get()->setDisp(unknown70, isDisp);
  }
}

} // namespace gmk
