#include "gmk/gmk_jump.h"

#include "bdat.h"
#include "framework/effect/effect_manager.h"
#include "gf/data/gf_bdat_id.h"
#include "gf/data/gf_bdat_wrapper.h"
#include "gf/data/gf_data_bdat.h"
#include "gf/game/gf_game_cond.h"
#include "gf/game/gf_game_manager.h"
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
  condition = bdat.getValCheck("Condition", id, BDAT_TYPE_U16);
  jumpType = bdat.getValCheck("jumpType", id, BDAT_TYPE_U8);
  nameRadius = bdat.getValCheck("nameRadius", id, BDAT_TYPE_U16);
}

bool GmkJump::BdatInfo::isPopCondMatched() const {
  if (condition != 0 && !gf::GfGameCond::isGameCond(condition)) {
    return false;
  }
  return true;
}

void GmkJump::BdatInfo::debugDraw(const AGmkBase &gmk) const {}

GmkJump::GmkJump() : _48(), isCondMatched(false), handle(gf::INVALID_HANDLE), popDist(), depopDist(), iconDist(), isIconDead(false), isDisp(true) {}

void GmkJump::create(const CreateInfo &info) {
  AGmkBase::create(info);
  u8 *mapList = gf::GfDataBdat::getFP(gf::BDAT_FLD_MAPLIST);
  if (mapList != nullptr) {
    int map = gf::GfGameManager::getMapID();
    if (map >= Bdat::getIdTop(mapList) && Bdat::getIdTop(mapList) + Bdat::getIdCount(mapList) > map) {
      u8 displayRadius = Bdat::getValCheck(mapList, "ene_disp_r", map, BDAT_TYPE_U8);
      u8 displayHeight = Bdat::getValCheck(mapList, "ene_disp_h", map, BDAT_TYPE_U8);
      popDist.set(displayRadius, displayHeight);
      u8 releaseRadius = Bdat::getValCheck(mapList, "ene_release_r", map, BDAT_TYPE_U8);
      u8 releaseHeight = Bdat::getValCheck(mapList, "ene_release_h", map, BDAT_TYPE_U8);
      depopDist.set(displayRadius + releaseRadius, displayHeight + releaseHeight);
      f32 iconDistance = Bdat::getValCheck(gf::GfDataBdat::getFP(gf::BDAT_FLD_WILDCARD_DATA), 0, WILDCARD_JUMP_ICON_DIST_ROW, BDAT_TYPE_F32).valueF32;
      iconDist.distSq = iconDistance * iconDistance;
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
  if (iconHandle == 0) {
    return;
  }
  if (isFadeOut) {
    fw::EffectManager::get()->fadeOutDead(iconHandle, ICON_FADE_OUT_FRAME);
  } else {
    fw::EffectManager::get()->remove(iconHandle);
  }
  iconHandle = 0;
}

void GmkJump::disposeGobInst(bool isFadeOut) {
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

void GmkJump::update(f32 deltaTime) {
  AGmkBase::update(deltaTime);
  if (!isValid()) {
    return;
  }
  isCondMatched = getBdatInfo()->isPopCondMatched();
  if (!isInterestPosExist()) {
    return;
  }
  if (canPopGobInst()) {
    createGobInst();
  } else if (canDepopGobInst()) {
    disposeGobInst(true);
  }
  if (isIconDead) {
    return;
  }
  if (isCondMatched && DistCond::isMatch(iconDist.distSq, getData()->position)) {
    if (iconHandle == 0) {
      createIcon();
    }
  } else {
    disposeIcon(true);
  }
}

bool GmkJump::canPopGobInst() const {
  if (handle != gf::INVALID_HANDLE || !isCondMatched) {
    return false;
  }
  const mm::Vec3 &position = getData()->position;
  return popDist.isMatch(position);
}

bool GmkJump::canDepopGobInst() const {
  if (handle == gf::INVALID_HANDLE) {
    return false;
  }
  if (!isCondMatched) {
    return true;
  }
  const mm::Vec3 &position = getData()->position;
  return !depopDist.isMatch(position);
}

void GmkJump::createIcon() {
  if (!canCreateGameEntity()) {
    return;
  }
  disposeIcon(false);
  const char *name;
  switch (getBdatInfo()->jumpType) {
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
  iconHandle = fw::EffectManager::get()->create(data, true);
  if (iconHandle == 0) {
    return;
  }
  fw::EffectManager::get()->setCategory(iconHandle, ICON_EFFECT_CATEGORY);
  validateIconPos();
}

void GmkJump::debugUpdateMmf() {}

void GmkJump::reqDeadIcon() {
  if (isIconDead) {
    return;
  }
  isIconDead = true;
  if (iconHandle != 0) {
    fw::EffectManager::get()->dead(iconHandle);
    iconHandle = 0;
  }
}

void GmkJump::reqRecreateIcon() {
  if (!isIconDead) {
    return;
  }
  isIconDead = false;
  if (iconHandle == 0) {
    createIcon();
  }
}

void GmkJump::onGobEvent(gf::IGfObjListener::OBJEVT event, gf::GF_OBJ_HANDLE *handle) {
  AGmkBase::onGobEvent(event, handle);
  if (event == gf::IGfObjListener::OBJEVT_DESTROY) {
    disposeGobInst(false);
  }
}

} // namespace gmk
