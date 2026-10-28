#include "gmk/gmk_grave.h"
#include "gmk/gmk_list_impl.h" // IWYU pragma: keep

#include "bdat.h"
#include "gf/data/gf_bdat_id.h"
#include "gf/data/gf_bdat_wrapper.h"
#include "gf/data/gf_data_bdat.h"
#include "gf/game/gf_game_manager.h"
#include "gf/object/gf_obj_factory.h"
#include "gf/object/gf_obj_handle.h"
#include "gf/object/gf_obj_setup.h"
#include "gf/object/gf_obj_util.h"
#include "gmk/gmk_bdat.h"
#include "gmk/gmk_set.h"

namespace mm {} // namespace mm

namespace gmk {

template bool TGmkList<GmkGrave, GmkGrave::BdatInfo, 1447121479u, 4u, GmkGraveGob>::initGmkBdatInfo(GmkGrave::BdatInfo &, int &, const AGmkBase &);
class GmkEnemy;
class GmkRoutedEnemy;

GmkGrave::GmkGrave() : unknown48(false), unknown50(gf::INVALID_HANDLE), unknown58(), unknown98(false) {}

void GmkGrave::BdatInfo::create(u8 *bdat, int id, const AGmkBase &gmk) {
  dispose();
  unknown00 = Bdat::getValCheck(bdat, "en_popID", id, BDAT_TYPE_U16);
  u8 *mapList = gf::GfDataBdat::getFP(gf::BDAT_FLD_MAPLIST);
  if (mapList != nullptr) {
    int map = gf::GfGameManager::getMapID();
    if (map >= Bdat::getIdTop(mapList) && Bdat::getIdTop(mapList) + Bdat::getIdCount(mapList) > map) {
      u8 displayRadius = Bdat::getValCheck(mapList, "ene_disp_r", map, BDAT_TYPE_U8);
      u8 displayHeight = Bdat::getValCheck(mapList, "ene_disp_h", map, BDAT_TYPE_U8);
      unknown04.set(displayRadius, displayHeight);
      u8 releaseRadius = Bdat::getValCheck(mapList, "ene_release_r", map, BDAT_TYPE_U8);
      u8 releaseHeight = Bdat::getValCheck(mapList, "ene_release_h", map, BDAT_TYPE_U8);
      unknown0c.set(displayRadius + releaseRadius, displayHeight + releaseHeight);
      const GmkSet *set = gmk.unknown08.unknown00->getCreateInfo().unknown08;
      u8 *enemyBdat;
      if (set->unknown1b8[GMK_TYPE_ENEMY] == nullptr || (enemyBdat = set->unknown1b8[GMK_TYPE_ENEMY]->getBindedBdatFp()) == nullptr) {
        if (set->unknown1b8[GMK_TYPE_ROUTED_ENEMY] == nullptr) {
          return;
        }
        enemyBdat = set->unknown1b8[GMK_TYPE_ROUTED_ENEMY]->getBindedBdatFp();
        if (enemyBdat == nullptr) {
          return;
        }
      }
      unknown02 = Bdat::getValCheck(enemyBdat, "ene1ID", unknown00, BDAT_TYPE_U16);
      return;
    }
  }
  dispose();
}

bool GmkGrave::BdatInfo::isPopCondMatched(const mm::Vec3 &position) const { return unknown04.isMatch(position); }

bool GmkGrave::BdatInfo::isDepopCondMatched(const mm::Vec3 &position) const { return !unknown0c.isMatch(position); }

void GmkGrave::BdatInfo::debugDraw(const AGmkBase &gmk) const {}

void GmkGrave::disposeGobInst(bool isFadeOut) {
  if (unknown50 == gf::INVALID_HANDLE) {
    return;
  }
  if (isFadeOut) {
    gmk::disposeGobInst(unknown50, 1.0f);
  } else {
    unbindToGameObj(unknown50);
    gf::GfObjUtil::destroy(unknown50);
    unknown50 = gf::INVALID_HANDLE;
  }
}

void GmkGrave::createGobInst() {
  if (!canCreateGameEntity()) {
    return;
  }
  disposeGobInst(false);
  CBdatWrapper bdat = {getBindedBdatFp()};
  unknown50 = gf::GfObjFactory::createGmkMapObj(bdat, unknown20.unknown18);
  bindToGameObj(unknown50);
  unknown002(unknown50, true);
  setEventDisp(unknown50, debugIsDispGmkType(getGmkType()));
  gf::GfObjSetupGimmick *setup = gf::GfObjUtil::getObjSetup<gf::GfObjSetupGimmick>(unknown50);
  unknown003(setup, unknown08.unknown08);
  setup->setInitialScale(getData()->unknown00 * 0.1f);
}

void GmkGrave::update(f32 deltaTime) {
  AGmkBase::update(deltaTime);
  if (!isValid()) {
    return;
  }
  if (!getBdatInfo()->isValid()) {
    return;
  }
  unknown48 = getDefeatedNum(getBdatInfo()->unknown02) != 0;
  validateTargetable();
  if (!isInterestPosExist()) {
    return;
  }
  if (canPopGobInst()) {
    createGobInst();
  } else if (canDepopGobInst()) {
    disposeGobInst(true);
  }
}

bool GmkGrave::canPopGobInst() const {
  if (unknown50 != gf::INVALID_HANDLE || !unknown48) {
    return false;
  }
  return getBdatInfo()->isPopCondMatched(unknown08.unknown08->unknown00);
}

bool GmkGrave::canDepopGobInst() const {
  if (unknown50 == gf::INVALID_HANDLE) {
    return false;
  }
  if (!unknown48) {
    return true;
  }
  return getBdatInfo()->isDepopCondMatched(unknown08.unknown08->unknown00);
}

void GmkGrave::debugDraw() const {
  AGmkBase::debugDraw();
  isValid();
}

bool GmkGrave::reqPopEnemy() const { return reqPopEnemy<GmkEnemy>() || reqPopEnemy<GmkRoutedEnemy>(); }

void GmkGrave::onGobEvent(gf::IGfObjListener::OBJEVT event, gf::GF_OBJ_HANDLE *handle) {
  AGmkBase::onGobEvent(event, handle);
  if (event == gf::IGfObjListener::OBJEVT_DESTROY) {
    disposeGobInst(false);
  }
}

void GmkGrave::onPlayerAccessed(gf::GF_OBJ_HANDLE *handle) {}

} // namespace gmk

template void mm::mtl::Vector<gmk::GmkGrave::BdatInfo>::expand(size_t, size_t);
template void mm::mtl::Vector<gmk::GmkGrave::BdatInfo>::extend(size_t, size_t);
template void mm::mtl::Vector<gmk::GmkGrave::BdatInfo>::resize(size_t);
template void mm::mtl::Vector<gmk::GmkGrave>::expand(size_t, size_t);
template void mm::mtl::Vector<gmk::GmkGrave>::extend(size_t, size_t);
template void mm::mtl::Vector<gmk::GmkGrave>::resize(size_t);
