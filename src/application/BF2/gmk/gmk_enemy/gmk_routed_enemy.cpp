#include "gmk/gmk_enemy/gmk_routed_enemy.h"

#include "gf/game/gf_game_manager.h"
#include "gf/gf_allocator.h"
#include "gf/object/component/enemy/gf_behavior_enemy_field.h"
#include "gf/object/component/enemy/gf_com_behavior_enemy.h"
#include "gf/object/component/gf_com_transform.h"
#include "gf/object/gf_obj.h"
#include "gf/object/gf_obj_acc.h"
#include "gf/object/gf_obj_handle.h"
#include "gf/object/gf_obj_util.h"
#include "gmk/gmk_base.h"
#include "gmk/gmk_gob_event_listener_impl.h" // IWYU pragma: keep
#include "gmk/gmk_list_impl.h"               // IWYU pragma: keep
#include "gmk/gmk_route_navi.h"
#include "gmk/gmk_set.h"
#include "gmk/gmk_squad.h"
#include "mm_math/mm_vec3.h"

namespace gf {
struct GF_OBJ_HANDLE;
} // namespace gf

namespace gmk {

template bool TGmkList<GmkRoutedEnemyPoint, GmkRoutedEnemyPoint::BdatInfo, 1347571269u, 4u, GmkRoutedEnemyPointGobCustom>::initGmkBdatInfo(GmkRoutedEnemyPoint::BdatInfo &, int &, const AGmkBase &);

GmkRoutedEnemy::GmkRoutedEnemy() {}

GmkType GmkRoutedEnemy::getGmkType() const { return GMK_TYPE; }

bool GmkRoutedEnemy::isValid() const {
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
  return unknown50.unknown00.unknown00 != nullptr && unknown50.unknown00.unknown08.unknown00 != nullptr && unknown50.unknown00.unknown10 > 0;
}

bool GmkRoutedEnemy::PopXformFinder::isYSnap() const { return false; }

void GmkRoutedEnemy::PopXformFinder::onCreateGobInsts(u32 num) const { unknown08->createRouteNavis(num); }

bool GmkRoutedEnemy::PopXformFinder::getSquadMemberIndex(int &index, gf::GF_OBJ_HANDLE *handle) const {
  gf::GfObjAcc acc(handle);
  gf::GfObj *obj = acc.getObj();
  if (obj != nullptr) {
    gf::GfComBehaviorEnemy *behavior = obj->getComponent<gf::GfComBehaviorEnemy>();
    if (behavior != nullptr && behavior->unknown140.unknown50.unknown001()) {
      index = behavior->unknown140.unknown50.unknown28;
      return index != 0;
    }
  }
  return false;
}

bool GmkRoutedEnemy::PopXformFinder::onPopGob(gf::GF_OBJ_HANDLE *handle) const {
  int index;
  if (getSquadMemberIndex(index, handle)) {
    return true;
  }
  GmkRouteNavi *navi = unknown08->findFreeRouteNavi();
  if (navi == nullptr) {
    return false;
  }
  unknown08->bindRouteNavi(handle, *navi);
  return true;
}

void GmkRoutedEnemy::createRouteNavis(u32 num) {
  disposeRouteNavis();
  unknown1d8.setAllocator(gf::getAllocator(gf::ALLOCATOR_UNKNOWN_0));
  unknown1d8.reserve(num, 16);
  unknown1d8.resize(num);
  if (!unknown1d8.empty()) {
    for (std::pair<gf::GF_OBJ_HANDLE *, GmkRouteNavi> *it = unknown1d8.begin(); it != unknown1d8.end(); ++it) {
      it->first = gf::unknown020;
    }
  }
}

void GmkRoutedEnemy::dispose() {
  disposeRouteNavis();
  unknown50.dispose();
  AGmkBase::dispose();
}

void GmkRoutedEnemy::disposeRouteNavis() {
  if (!unknown1d8.empty()) {
    unknown1d8.destroy();
  }
}

void GmkRoutedEnemy::update(f32 deltaTime) {
  debugUpdateMmf();
  if (!isValid() || gf::GfGameManager::getControlMover() == gf::unknown020) {
    return;
  }
  const mm::Vec3 &playerPosition = gf::GfObjUtil::getObj(gf::GfGameManager::getControlMover())->getComponent<gf::GfComTransform>()->getPosition();
  mm::Vec3 nearestPosition;
  if (getNearestPos(nearestPosition, playerPosition)) {
    GmkEnemyInsts::UpdateInfo info;
    PopXformFinder finder;
    finder.unknown08 = this;
    info.unknown00 = deltaTime;
    info.unknown08 = &nearestPosition;
    info.unknown10 = &finder;
    unknown50.update(info);
  }
}

GmkType GmkRoutedEnemyPoint::getGmkType() const { return GMK_TYPE; }

GmkRoutedEnemyList::GmkRoutedEnemyList(u32 updateGmkNumPerFrame) : TGmkList(updateGmkNumPerFrame), unknown240(0xffffffff) {}

void GmkRoutedEnemyList::create(const CreateInfo &info) {
  if (!unknown228.create()) {
    dispose();
    return;
  }
  TGmkList::create(info);
}

void GmkRoutedEnemyList::createGmk(void *data) {
  TGmkList::createGmk(data);
  unknown001(unknown240, getCreateInfo());
}

void GmkRoutedEnemyList::dispose() {
  unknown240.dispose();
  TGmkList::dispose();
}

void GmkRoutedEnemyList::update(f32 deltaTime) {
  unknown240.update(deltaTime);
  TGmkList::update(deltaTime);
}

bool GmkRoutedEnemyList::updateImmediate() {
  if (!TGmkList::updateImmediate()) {
    return false;
  }
  return unknown240.updateImmediate();
}

void GmkRoutedEnemyList::setUpdateGmkNumPerFrame(u32 num) {
  TGmkList::setUpdateGmkNumPerFrame(num);
  unknown240.setUpdateGmkNumPerFrame(num);
}

IGmkList *GmkRoutedEnemy::getOwnerGmkEnemyList() const { return unknown08.unknown00; }

bool GmkRoutedEnemy::isPopPointRouteEnd(const GmkRouteNavi &navi) const {
  if (navi.isValid()) {
    bool isReverse = navi.unknowna4;
    const Data *data = getData();
    if (data->unknown00 == data->unknown14) {
      if (isReverse && (data->unknown0c & FLAG_UNKNOWN_3)) {
        return true;
      }
    } else if (!isReverse && data->unknown04 - 1 == data->unknown14 && (data->unknown0c & FLAG_UNKNOWN_3)) {
      return true;
    }
  }
  return false;
}

const IGmkList *GmkRoutedEnemy::getBindedRoutePointList() const { return unknown08.unknown00->getCreateInfo().unknown08->unknown1b8[GMK_TYPE_ROUTED_ENEMY_POINT]; }

void GmkRoutedEnemyList::debugDraw() const {
  TGmkList::debugDraw();
  unknown240.debugDraw();
}

void GmkRoutedEnemyList::debugUpdateMmf() {
  TGmkList::debugUpdateMmf();
  unknown240.debugUpdateMmf();
}

void GmkRoutedEnemy::unbindRouteNavi(gf::GF_OBJ_HANDLE *handle, bool isDispose) {
  if (handle == gf::unknown020) {
    return;
  }
  for (std::pair<gf::GF_OBJ_HANDLE *, GmkRouteNavi> *it = unknown1d8.begin(); it != unknown1d8.end(); ++it) {
    if (it->first == handle) {
      it->first = gf::unknown020;
      if (isDispose) {
        it->second.dispose();
      }
      break;
    }
  }
}

void GmkRoutedEnemy::bindRouteNavi(gf::GF_OBJ_HANDLE *handle, GmkRouteNavi &navi) {
  unbindRouteNavi(handle, true);
  for (std::pair<gf::GF_OBJ_HANDLE *, GmkRouteNavi> *it = unknown1d8.begin(); it != unknown1d8.end(); ++it) {
    if (&it->second == &navi) {
      it->first = handle;
      return;
    }
  }
}

GmkRouteNavi *GmkRoutedEnemy::findFreeRouteNavi() const {
  for (std::pair<gf::GF_OBJ_HANDLE *, GmkRouteNavi> *it = unknown1d8.begin(); it != unknown1d8.end(); ++it) {
    if (it->first == gf::unknown020) {
      return &it->second;
    }
  }
  return nullptr;
}

GmkRouteNavi *GmkRoutedEnemy::findRouteNavi(gf::GF_OBJ_HANDLE *handle) const {
  for (std::pair<gf::GF_OBJ_HANDLE *, GmkRouteNavi> *it = unknown1d8.begin(); it != unknown1d8.end(); ++it) {
    if (it->first == handle) {
      return &it->second;
    }
  }
  return nullptr;
}

void GmkRoutedEnemy::onEnemyDead(gf::GF_OBJ_HANDLE *handle) {
  unbindRouteNavi(handle, true);
  unknown50.onEnemyDead(handle);
}

void GmkRoutedEnemy::onGobEvent(gf::IGfObjListener::OBJEVT event, gf::GF_OBJ_HANDLE *handle) {
  AGmkBase::onGobEvent(event, handle);
  if (event == gf::IGfObjListener::OBJEVT_UNKNOWN_3) {
    unbindRouteNavi(handle, false);
    unknown50.removeGobInst(handle);
  }
}

} // namespace gmk

template void mm::mtl::Vector<gmk::GmkRoutedEnemyPoint::BdatInfo>::expand(size_t, size_t);
template void mm::mtl::Vector<gmk::GmkRoutedEnemyPoint::BdatInfo>::extend(size_t, size_t);
template void mm::mtl::Vector<gmk::GmkRoutedEnemyPoint::BdatInfo>::resize(size_t);
template void mm::mtl::Vector<gmk::GmkRoutedEnemyPoint>::expand(size_t, size_t);
template void mm::mtl::Vector<gmk::GmkRoutedEnemyPoint>::extend(size_t, size_t);
template void mm::mtl::Vector<gmk::GmkRoutedEnemyPoint>::resize(size_t);
template void mm::mtl::Vector<gmk::GmkRoutedEnemy>::expand(size_t, size_t);
template void mm::mtl::Vector<gmk::GmkRoutedEnemy>::resize(size_t);
