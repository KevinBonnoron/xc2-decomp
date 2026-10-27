#include "gmk/gmk_enemy/gmk_routed_enemy.h"

#include "gf/object/gf_obj_handle.h"
#include "gmk/gmk_base.h"
#include "gmk/gmk_gob_event_listener_impl.h" // IWYU pragma: keep
#include "gmk/gmk_list_impl.h"               // IWYU pragma: keep
#include "gmk/gmk_route_navi.h"
#include "gmk/gmk_set.h"

namespace gf {
struct GF_OBJ_HANDLE;
} // namespace gf

namespace gmk {

template bool TGmkList<GmkRoutedEnemyPoint, GmkRoutedEnemyPoint::BdatInfo, 1347571269u, 4u, GmkRoutedEnemyPointGobCustom>::initGmkBdatInfo(GmkRoutedEnemyPoint::BdatInfo &, int &, const AGmkBase &);

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
  return unknown50 != nullptr && unknown58 != nullptr && unknown60 > 0;
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
  if (handle == gf::INVALID_HANDLE) {
    return;
  }
  for (std::pair<gf::GF_OBJ_HANDLE *, GmkRouteNavi> *it = unknown1D8.begin(); it != unknown1D8.end(); ++it) {
    if (it->first == handle) {
      it->first = gf::INVALID_HANDLE;
      if (isDispose) {
        it->second.dispose();
      }
      break;
    }
  }
}

void GmkRoutedEnemy::bindRouteNavi(gf::GF_OBJ_HANDLE *handle, GmkRouteNavi &navi) {
  unbindRouteNavi(handle, true);
  for (std::pair<gf::GF_OBJ_HANDLE *, GmkRouteNavi> *it = unknown1D8.begin(); it != unknown1D8.end(); ++it) {
    if (&it->second == &navi) {
      it->first = handle;
      return;
    }
  }
}

GmkRouteNavi *GmkRoutedEnemy::findFreeRouteNavi() const {
  for (std::pair<gf::GF_OBJ_HANDLE *, GmkRouteNavi> *it = unknown1D8.begin(); it != unknown1D8.end(); ++it) {
    if (it->first == gf::INVALID_HANDLE) {
      return &it->second;
    }
  }
  return nullptr;
}

GmkRouteNavi *GmkRoutedEnemy::findRouteNavi(gf::GF_OBJ_HANDLE *handle) const {
  for (std::pair<gf::GF_OBJ_HANDLE *, GmkRouteNavi> *it = unknown1D8.begin(); it != unknown1D8.end(); ++it) {
    if (it->first == handle) {
      return &it->second;
    }
  }
  return nullptr;
}

} // namespace gmk
