#include "gmk/gmk_grave.h"

#include "bdat.h"
#include "gf/data/gf_bdat_id.h"
#include "gf/data/gf_data_bdat.h"
#include "gf/game/gf_game_manager.h"
#include "gf/object/gf_obj_handle.h"
#include "gf/object/gf_obj_util.h"
#include "gmk/gmk_bdat.h"
#include "gmk/gmk_set.h"

namespace mm {
struct Vec3;
} // namespace mm

namespace gmk {
class GmkEnemy;
class GmkRoutedEnemy;

void GmkGrave::BdatInfo::create(u8 *bdat, int id, const AGmkBase &gmk) {
  dispose();
  enemyPopId = Bdat::getValCheck(bdat, "en_popID", id, BDAT_TYPE_U16);
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
      const GmkSet *set = gmk.baseInfo.list->getCreateInfo().set;
      u8 *enemyBdat;
      if (set->lists[GMK_TYPE_ENEMY] == nullptr || (enemyBdat = set->lists[GMK_TYPE_ENEMY]->getBindedBdatFp()) == nullptr) {
        if (set->lists[GMK_TYPE_ROUTED_ENEMY] == nullptr) {
          return;
        }
        enemyBdat = set->lists[GMK_TYPE_ROUTED_ENEMY]->getBindedBdatFp();
        if (enemyBdat == nullptr) {
          return;
        }
      }
      enemyId = Bdat::getValCheck(enemyBdat, "ene1ID", enemyPopId, BDAT_TYPE_U16);
      return;
    }
  }
  dispose();
}

bool GmkGrave::BdatInfo::isPopCondMatched(const mm::Vec3 &position) const { return popDist.isMatch(position); }

bool GmkGrave::BdatInfo::isDepopCondMatched(const mm::Vec3 &position) const { return !depopDist.isMatch(position); }

void GmkGrave::BdatInfo::debugDraw(const AGmkBase &gmk) const {}

void GmkGrave::disposeGobInst(bool isFadeOut) {
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

void GmkGrave::update(f32 deltaTime) {
  AGmkBase::update(deltaTime);
  if (!isValid()) {
    return;
  }
  if (!getBdatInfo()->isValid()) {
    return;
  }
  isEnemyDefeated = getDefeatedNum(getBdatInfo()->enemyId) != 0;
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
  if (handle != gf::INVALID_HANDLE || !isEnemyDefeated) {
    return false;
  }
  return getBdatInfo()->isPopCondMatched(baseInfo.xform->position);
}

bool GmkGrave::canDepopGobInst() const {
  if (handle == gf::INVALID_HANDLE) {
    return false;
  }
  if (!isEnemyDefeated) {
    return true;
  }
  return getBdatInfo()->isDepopCondMatched(baseInfo.xform->position);
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

} // namespace gmk
