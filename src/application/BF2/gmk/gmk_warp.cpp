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
#include "gmk/gmk_list_impl.h" // IWYU pragma: keep

namespace fw {
enum EF_CATEGORY : int;
} // namespace fw

namespace gmk {

template bool TGmkList<GmkWarp, GmkWarp::BdatInfo, 1347567959u, 1u, GmkWarpGobCustom>::initGmkBdatInfo(GmkWarp::BdatInfo &, int &, const AGmkBase &);

constexpr int WILDCARD_UNKNOWN_1_3 = 1;                                          // Inferred role: wildcard warp icon dist row; original name unknown.
constexpr u32 WARP_ICON_FADE_OUT_UNKNOWN_5 = 5;                                  // Inferred role: warp icon fade out frame; original name unknown.
const fw::EF_CATEGORY EF_CATEGORY_UNKNOWN_1_2 = static_cast<fw::EF_CATEGORY>(1); // Inferred role: warp icon effect category; original name unknown.

void GmkWarp::BdatInfo::create(CBdatWrapper bdat, int id, const AGmkBase &gmk) {
  unknown00 = bdat.getValCheck("Condition", id, BDAT_TYPE_UNKNOWN_2);
  unknown04 = BootedGmkCond(bdat, id, nullptr);
  unknown02 = bdat.getValCheck("nameRadius", id, BDAT_TYPE_UNKNOWN_2);
  u8 *mapList = gf::GfDataBdat::getFP(gf::BDAT_FLD_MAPLIST);
  if (mapList != nullptr) {
    int map = gf::GfGameManager::getMapID();
    if (map >= Bdat::getIdTop(mapList) && Bdat::getIdTop(mapList) + Bdat::getIdCount(mapList) > map) {
      u8 displayRadius = Bdat::getValCheck(mapList, "ene_disp_r", map, BDAT_TYPE_UNKNOWN_1);
      u8 displayHeight = Bdat::getValCheck(mapList, "ene_disp_h", map, BDAT_TYPE_UNKNOWN_1);
      unknown08.set(displayRadius, displayHeight);
      u8 releaseRadius = Bdat::getValCheck(mapList, "ene_release_r", map, BDAT_TYPE_UNKNOWN_1);
      u8 releaseHeight = Bdat::getValCheck(mapList, "ene_release_h", map, BDAT_TYPE_UNKNOWN_1);
      unknown10.set(displayRadius + releaseRadius, displayHeight + releaseHeight);
    }
  }
}

bool GmkWarp::BdatInfo::isPopCondMatched(const mm::Vec3 &position) const {
  if (!isPopCondCommonMatched()) {
    return false;
  }
  return unknown08.isMatch(position);
}

bool GmkWarp::BdatInfo::isPopCondCommonMatched() const {
  if (unknown00 != 0 && !gf::GfGameCond::isGameCond(unknown00)) {
    return false;
  }
  if (unknown04.isEnable() && !unknown04.isMatch()) {
    return false;
  }
  return true;
}

bool GmkWarp::BdatInfo::isDepopCondMatched(const mm::Vec3 &position) const {
  if (!isPopCondCommonMatched()) {
    return true;
  }
  return !unknown10.isMatch(position);
}

void GmkWarp::BdatInfo::debugDraw(const AGmkBase &gmk) const {}

GmkWarp::GmkWarp() : _48(), unknown68(), unknown6c(false), unknown6d(true) {
  for (u32 i = 0; i < POINT_UNKNOWN_2; i++) {
    unknown50[i] = gf::unknown020;
  }
  for (u32 i = 0; i < POINT_UNKNOWN_2; i++) {
    unknown60[i] = 0;
  }
}

void GmkWarp::create(const CreateInfo &info) {
  AGmkBase::create(info);
  f32 iconDistance = Bdat::getValCheck(gf::GfDataBdat::getFP(gf::BDAT_FLD_WILDCARD_DATA), 0, WILDCARD_UNKNOWN_1_3, BDAT_TYPE_UNKNOWN_8).valueF32;
  unknown68.unknown00 = iconDistance * iconDistance;
}

void GmkWarp::dispose() {
  clearIcons();
  clearGobInsts();
  AGmkBase::dispose();
}

void GmkWarp::clearIcons() {
  for (u32 i = 0; i < POINT_UNKNOWN_2; i++) {
    disposeIcon(i, false);
  }
}

void GmkWarp::clearGobInsts() {
  for (u32 i = 0; i < POINT_UNKNOWN_2; i++) {
    if (unknown50[i] != gf::unknown020) {
      unbindToGameObj(unknown50[i]);
      gf::GfObjUtil::destroy(unknown50[i]);
      unknown50[i] = gf::unknown020;
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
  unknown60[index] = fw::EffectManager::get()->create(data, true);
  if (unknown60[index] == 0) {
    return;
  }
  fw::EffectManager::get()->setCategory(unknown60[index], EF_CATEGORY_UNKNOWN_1_2);
  validateIconPos();
}

void GmkWarp::disposeIcon(u32 index, bool isFadeOut) {
  if (unknown60[index] == 0) {
    return;
  }
  if (isFadeOut) {
    fw::EffectManager::get()->fadeOutDead(unknown60[index], WARP_ICON_FADE_OUT_UNKNOWN_5);
  } else {
    fw::EffectManager::get()->remove(unknown60[index]);
  }
  unknown60[index] = 0;
}

void GmkWarp::validateDisp() const {
  bool isDisp = unknown6d && debugIsDispGmkType(getGmkType());
  for (u32 i = 0; i < POINT_UNKNOWN_2; i++) {
    if (unknown50[i] != gf::unknown020) {
      setEventDisp(unknown50[i], isDisp);
    }
  }
  for (u32 i = 0; i < POINT_UNKNOWN_2; i++) {
    if (unknown60[i] != 0) {
      fw::EffectManager::get()->setDisp(unknown60[i], isDisp);
    }
  }
}

void GmkWarp::debugUpdateMmf() {}

void GmkWarp::reqDeadIcon() {
  if (unknown6c) {
    return;
  }
  unknown6c = true;
  for (u32 i = 0; i < POINT_UNKNOWN_2; i++) {
    if (unknown60[i] != 0) {
      fw::EffectManager::get()->dead(unknown60[i]);
      unknown60[i] = 0;
    }
  }
}

void GmkWarp::reqRecreateIcon() {
  if (!unknown6c) {
    return;
  }
  unknown6c = false;
  for (u32 i = 0; i < POINT_UNKNOWN_2; i++) {
    if (unknown60[i] == 0) {
      createIcon(i);
    }
  }
}

void GmkWarp::onGobEvent(gf::IGfObjListener::OBJEVT event, gf::GF_OBJ_HANDLE *handle) {
  AGmkBase::onGobEvent(event, handle);
  if (event != gf::IGfObjListener::OBJEVT_UNKNOWN_3) {
    return;
  }
  for (u32 i = 0; i < POINT_UNKNOWN_2; i++) {
    if (unknown50[i] == handle) {
      unknown50[i] = gf::unknown020;
      break;
    }
  }
}

} // namespace gmk

template void mm::mtl::Vector<gmk::GmkWarp::BdatInfo>::expand(size_t, size_t);
template void mm::mtl::Vector<gmk::GmkWarp>::expand(size_t, size_t);

template void mm::mtl::Vector<gmk::GmkWarp::BdatInfo>::extend(size_t, size_t);
template void mm::mtl::Vector<gmk::GmkWarp::BdatInfo>::resize(size_t);
template void mm::mtl::Vector<gmk::GmkWarp>::extend(size_t, size_t);
template void mm::mtl::Vector<gmk::GmkWarp>::resize(size_t);
