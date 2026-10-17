#include "gmk/gmk_warp.h"

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

namespace mm {
struct Vec3;
} // namespace mm

namespace gmk {

constexpr int WILDCARD_WARP_ICON_DIST_ROW = 1;
constexpr u32 WARP_ICON_FADE_OUT_FRAME = 5;
const fw::EF_CATEGORY WARP_ICON_EFFECT_CATEGORY = static_cast<fw::EF_CATEGORY>(1);

void GmkWarp::BdatInfo::create(CBdatWrapper bdat, int id, const AGmkBase &gmk) {
  condition = bdat.getValCheck("Condition", id, BDAT_TYPE_U16);
  bootedGmk = BootedGmkCond(bdat, id, nullptr);
  nameRadius = bdat.getValCheck("nameRadius", id, BDAT_TYPE_U16);
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
    }
  }
}

bool GmkWarp::BdatInfo::isPopCondMatched(const mm::Vec3 &position) const {
  if (!isPopCondCommonMatched()) {
    return false;
  }
  return popDist.isMatch(position);
}

bool GmkWarp::BdatInfo::isPopCondCommonMatched() const {
  if (condition != 0 && !gf::GfGameCond::isGameCond(condition)) {
    return false;
  }
  if (bootedGmk.isEnable() && !bootedGmk.isMatch()) {
    return false;
  }
  return true;
}

bool GmkWarp::BdatInfo::isDepopCondMatched(const mm::Vec3 &position) const {
  if (!isPopCondCommonMatched()) {
    return true;
  }
  return !depopDist.isMatch(position);
}

void GmkWarp::BdatInfo::debugDraw(const AGmkBase &gmk) const {}

void GmkWarp::create(const CreateInfo &info) {
  AGmkBase::create(info);
  f32 iconDistance = Bdat::getValCheck(gf::GfDataBdat::getFP(gf::BDAT_FLD_WILDCARD_DATA), 0, WILDCARD_WARP_ICON_DIST_ROW, BDAT_TYPE_F32).valueF32;
  iconDist.distSq = iconDistance * iconDistance;
}

void GmkWarp::dispose() {
  clearIcons();
  clearGobInsts();
  AGmkBase::dispose();
}

void GmkWarp::clearIcons() {
  for (u32 i = 0; i < POINT_NUM; i++) {
    disposeIcon(i, false);
  }
}

void GmkWarp::clearGobInsts() {
  for (u32 i = 0; i < POINT_NUM; i++) {
    if (handles[i] != gf::INVALID_HANDLE) {
      unbindToGameObj(handles[i]);
      gf::GfObjUtil::destroy(handles[i]);
      handles[i] = gf::INVALID_HANDLE;
    }
  }
}

void GmkWarp::createIcon(u32 index) {
  if (!canCreateGameEntity()) {
    return;
  }
  disposeIcon(index, false);
  void *data = fw::EffectManager::get()->search("cmn_100_100", nullptr);
  if (data == nullptr) {
    return;
  }
  iconHandles[index] = fw::EffectManager::get()->create(data, true);
  if (iconHandles[index] == 0) {
    return;
  }
  fw::EffectManager::get()->setCategory(iconHandles[index], WARP_ICON_EFFECT_CATEGORY);
  validateIconPos();
}

void GmkWarp::disposeIcon(u32 index, bool isFadeOut) {
  if (iconHandles[index] == 0) {
    return;
  }
  if (isFadeOut) {
    fw::EffectManager::get()->fadeOutDead(iconHandles[index], WARP_ICON_FADE_OUT_FRAME);
  } else {
    fw::EffectManager::get()->remove(iconHandles[index]);
  }
  iconHandles[index] = 0;
}

void GmkWarp::debugUpdateMmf() {}

void GmkWarp::reqDeadIcon() {
  if (isIconDead) {
    return;
  }
  isIconDead = true;
  for (u32 i = 0; i < POINT_NUM; i++) {
    if (iconHandles[i] != 0) {
      fw::EffectManager::get()->dead(iconHandles[i]);
      iconHandles[i] = 0;
    }
  }
}

void GmkWarp::reqRecreateIcon() {
  if (!isIconDead) {
    return;
  }
  isIconDead = false;
  for (u32 i = 0; i < POINT_NUM; i++) {
    if (iconHandles[i] == 0) {
      createIcon(i);
    }
  }
}

void GmkWarp::onGobEvent(gf::IGfObjListener::OBJEVT event, gf::GF_OBJ_HANDLE *handle) {
  AGmkBase::onGobEvent(event, handle);
  if (event != gf::IGfObjListener::OBJEVT_DESTROY) {
    return;
  }
  for (u32 i = 0; i < POINT_NUM; i++) {
    if (handles[i] == handle) {
      handles[i] = gf::INVALID_HANDLE;
      break;
    }
  }
}

} // namespace gmk
