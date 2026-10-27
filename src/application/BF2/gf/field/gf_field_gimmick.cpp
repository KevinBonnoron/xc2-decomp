#include "gf/field/gf_field_gimmick.h"

#include "fw/fw_update_info.h"
#include "gf/game/gf_game_util.h"
#include "gf/gf_manager.h"
#include "gmk/gmk_anti_blade_area.h"
#include "gmk/gmk_base.h"
#include "mm_mtl/singleton.h"

namespace gf {

void GfFieldGimmick::finalize() {
  unknown20.dispose();
  unknownf4a8 = false;
}

bool GfFieldGimmick::isInitialized() {
  GfFieldGimmick *gimmick = mm::mtl::PtrSingleton<GfFieldGimmick>::get();
  if (gimmick != nullptr) {
    return gimmick->unknownf4a8;
  }
  return false;
}

void GfFieldGimmick::update(const fw::UpdateInfo &info) {
  if (GfManager::isDestroyNow()) {
    return;
  }
  GfFieldGimmick *gimmick = mm::mtl::PtrSingleton<GfFieldGimmick>::get();
  gimmick->unknown20.update(info.unknown04);
  gimmick->unknownf3b0.update();
  gimmick->unknownf3e8.update(info.unknown04);
  gimmick->unknownf418.update(info.unknown04);
  gimmick->unknownf480.update(info.unknown04);
  if (gimmick->unknownf4ac) {
    f32 deltaTime = info.unknown04;
    if (!gimmick->unknownf4ad) {
      gimmick->unknownf4ad = mm::mtl::PtrSingleton<gmk::GmkManager>::get()->updateImmediate();
    } else {
      gimmick->unknownf4ae = mm::mtl::PtrSingleton<gmk::GmkManager>::get()->isValidView();
    }
    gimmick->unknownf4b0 += deltaTime;
    if (gimmick->unknownf4b0 > 10.0f) {
      gimmick->unknownf4ae = true;
    }
  }
  gimmick->unknownf910.update();
  if (gmk::isPlayerExist()) {
    gimmick->unknownfe41 = GfGameUtil::isPointSavable(gmk::getPlayerPos());
  }
}

bool GfFieldGimmick::isGmkSetReady() {
  if (GfManager::isDestroyNow()) {
    return true;
  }
  return mm::mtl::PtrSingleton<GfFieldGimmick>::get()->unknown20.isGmkSetsReady();
}

int GfFieldGimmick::getBdatIdFrom_FLD_maplist_To_RSC_GmkSetList(int map) {
  if (mm::mtl::PtrSingleton<GfFieldGimmick>::get()->unknown20.isValid()) {
    return mm::mtl::PtrSingleton<GfFieldGimmick>::get()->unknown20.findFirstBdatId_RSC_GmkSetList(map);
  }
  return -1;
}

void GfFieldGimmick::disposeGmkSet(int gmkSet) {
  if (mm::mtl::PtrSingleton<GfFieldGimmick>::get()->unknown20.isValid()) {
    int rscGmkSet = getBdatIdFrom_FLD_maplist_To_RSC_GmkSetList(gmkSet);
    mm::mtl::PtrSingleton<GfFieldGimmick>::get()->unknown20.disposeGmkSet(rscGmkSet);
  }
}

int GfFieldGimmick::getBdatIdFrom_RSC_GmkSetList_To_FLD_maplist(int gmkSet) {
  if (mm::mtl::PtrSingleton<GfFieldGimmick>::get()->unknown20.isValid()) {
    return mm::mtl::PtrSingleton<GfFieldGimmick>::get()->unknown20.getMapBdatId(gmkSet);
  }
  return -1;
}

int GfFieldGimmick::getBdatIdOfActiveGmkAntiBladeArea() {
  if (mm::mtl::PtrSingleton<GfFieldGimmick>::get() == nullptr) {
    return 0;
  }
  gmk::GmkAntiBladeAreaManager *manager = mm::mtl::PtrSingleton<gmk::GmkAntiBladeAreaManager>::get();
  if (manager != nullptr) {
    gmk::GmkAntiBladeArea *area = manager->unknown20;
    if (area != nullptr) {
      return area->unknown20.unknown10->id;
    }
    return 0;
  }
  return 0;
}

} // namespace gf
