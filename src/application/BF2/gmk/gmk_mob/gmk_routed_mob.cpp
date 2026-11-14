#include "gmk/gmk_mob/gmk_routed_mob.h"

#include "gf/game/gf_game_manager.h"
#include "gf/gf_allocator.h"
#include "gf/object/component/gf_com_transform.h"
#include "gf/object/gf_obj.h"
#include "gf/object/gf_obj_handle.h"
#include "gf/object/gf_obj_util.h"
#include "gmk/gmk_base.h"
#include "gmk/gmk_list_impl.h"        // IWYU pragma: keep
#include "gmk/gmk_mob/gmk_mob_impl.h" // IWYU pragma: keep
#include "gmk/gmk_route_navi.h"
#include "gmk/gmk_set.h"
#include "mm_math/mm_col4.h"
#include "mm_math/mm_vec3.h"

namespace gf {
struct GF_OBJ_HANDLE;
} // namespace gf

namespace gmk {

template bool TGmkList<GmkRoutedMob, GmkMob::BdatInfo, 1112493394u, 6u, GmkRouteGob>::initGmkBdatInfo(GmkMob::BdatInfo &, int &, const AGmkBase &);

GmkRoutedMob::GmkRoutedMob() {}

GmkType GmkRoutedMob::getGmkType() const { return GMK_TYPE; }

const IGmkList *GmkRoutedMob::getBindedRoutePointList() const { return unknown08.unknown00->getCreateInfo().unknown08->unknown1b8[GMK_TYPE_UNKNOWN_20]; }

void GmkRoutedMob::unbindRouteNavi(gf::GF_OBJ_HANDLE *handle) {
  if (handle == gf::unknown020) {
    return;
  }
  for (std::pair<gf::GF_OBJ_HANDLE *, GmkRouteNavi> *it = unknown120.begin(); it != unknown120.end(); ++it) {
    if (it->first == handle) {
      it->first = gf::unknown020;
      it->second.dispose();
      break;
    }
  }
}

void GmkRoutedMob::bindRouteNavi(gf::GF_OBJ_HANDLE *handle, GmkRouteNavi &navi) {
  unbindRouteNavi(handle);
  for (std::pair<gf::GF_OBJ_HANDLE *, GmkRouteNavi> *it = unknown120.begin(); it != unknown120.end(); ++it) {
    if (&it->second == &navi) {
      it->first = handle;
      return;
    }
  }
}

void GmkRoutedMob::PopXformFinder::onPopGob(gf::GF_OBJ_HANDLE *handle) const {
  if (unknown10 != nullptr) {
    unknown08->bindRouteNavi(handle, *unknown10);
  }
}

void GmkRoutedMob::PopXformFinder::onCreateGobInsts(u32 num) const { unknown08->createRouteNavis(num); }

void GmkRoutedMob::debugDraw() const {
  if (isValid()) {
    bool isPopCondMatched = unknown50.unknownb8 & GmkMobInsts::MATCHED_UNKNOWN_0;
    if (isValid()) {
      mm::Col4 color;
      if (isPopCondMatched) {
        color = mm::Col4::yellow;
      } else {
        color = mm::Col4::gray;
      }
      debugDrawRoute(color);
    }
  }
}

void GmkRoutedMob::onGobEvent(gf::IGfObjListener::OBJEVT event, gf::GF_OBJ_HANDLE *handle) {
  if (event == gf::IGfObjListener::OBJEVT_UNKNOWN_3 && handle != gf::unknown020) {
    unbindToGameObj(handle);
    unbindRouteNavi(handle);
    unknown50.removeGobInst(handle);
  }
}

bool GmkRoutedMob::isValid() const {
  if (!AGmkBase::isValid()) {
    return false;
  }
  const IGmkList *list = getBindedRoutePointList();
  if (list == nullptr) {
    return false;
  }
  if (list->getInstNum() == 0) {
    return false;
  }
  return unknown50.isValid();
}

void GmkRoutedMob::create(const CreateInfo &info) {
  if (info.unknown10 != nullptr) {
    AGmkBase::create(info);
    GmkMobInsts::CreateInfo createInfo;
    createInfo.unknown00 = this;
    createInfo.unknown08 = unknown08.unknown00->getBindedBdatFp();
    createInfo.unknown10 = info.unknown18;
    unknown50.create(createInfo);
  }
}

void GmkRoutedMob::dispose() {
  disposeRouteNavis();
  unknown50.dispose();
  AGmkBase::dispose();
}

void GmkRoutedMob::disposeRouteNavis() {
  if (!unknown120.empty()) {
    unknown120.destroy();
  }
}

void GmkRoutedMob::createRouteNavis(u32 num) {
  disposeRouteNavis();
  unknown120.setAllocator(gf::getAllocator(gf::ALLOCATOR_UNKNOWN_0));
  unknown120.reserve(num, 16);
  unknown120.resize(num);
  if (!unknown120.empty()) {
    for (std::pair<gf::GF_OBJ_HANDLE *, GmkRouteNavi> *it = unknown120.begin(); it != unknown120.end(); ++it) {
      it->first = gf::unknown020;
    }
  }
}

void GmkRoutedMob::update(f32 deltaTime) {
  debugUpdateMmf();
  if (!isValid() || gf::GfGameManager::getControlMover() == gf::unknown020) {
    return;
  }
  const mm::Vec3 &playerPosition = gf::GfObjUtil::getObj(gf::GfGameManager::getControlMover())->getComponent<gf::GfComTransform>()->getPosition();
  mm::Vec3 nearestPosition;
  if (getNearestPos(nearestPosition, playerPosition)) {
    GmkMobInsts::UpdateInfo info;
    PopXformFinder finder;
    finder.unknown10 = nullptr;
    finder.unknown08 = this;
    info.unknown00 = deltaTime;
    info.unknown08 = &nearestPosition;
    info.unknown10 = &finder;
    unknown50.update(info);
  }
}

GmkRouteNavi *GmkRoutedMob::findFreeRouteNavi() const {
  for (std::pair<gf::GF_OBJ_HANDLE *, GmkRouteNavi> *it = unknown120.begin(); it != unknown120.end(); ++it) {
    if (it->first == gf::unknown020) {
      return &it->second;
    }
  }
  return nullptr;
}

GmkRouteNavi *GmkRoutedMob::findRouteNavi(gf::GF_OBJ_HANDLE *handle) const {
  for (std::pair<gf::GF_OBJ_HANDLE *, GmkRouteNavi> *it = unknown120.begin(); it != unknown120.end(); ++it) {
    if (it->first == handle) {
      return &it->second;
    }
  }
  return nullptr;
}

} // namespace gmk

template void mm::mtl::Vector<gmk::GmkRoutedMob>::expand(size_t, size_t);
template void mm::mtl::Vector<gmk::GmkRoutedMob>::extend(size_t, size_t);
template void mm::mtl::Vector<gmk::GmkRoutedMob>::resize(size_t);
