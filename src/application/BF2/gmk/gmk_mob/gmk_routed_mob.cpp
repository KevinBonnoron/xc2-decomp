#include "gmk/gmk_mob/gmk_routed_mob.h"
#include "gmk/gmk_list_impl.h" // IWYU pragma: keep

#include "gf/object/gf_obj_handle.h"
#include "gmk/gmk_route_navi.h"
#include "gmk/gmk_set.h"
#include "mm_math/mm_col4.h"

namespace gf {
struct GF_OBJ_HANDLE;
} // namespace gf

namespace gmk {

template bool TGmkList<GmkRoutedMob, GmkMob::BdatInfo, 1112493394u, 6u, GmkRouteGob>::initGmkBdatInfo(GmkMob::BdatInfo &, int &, const AGmkBase &);

GmkType GmkRoutedMob::getGmkType() const { return GMK_TYPE; }

const IGmkList *GmkRoutedMob::getBindedRoutePointList() const { return unknown08.unknown00->getCreateInfo().unknown08->unknown1b8[GMK_TYPE_MOB_ROUTE_POINT]; }

void GmkRoutedMob::unbindRouteNavi(gf::GF_OBJ_HANDLE *handle) {
  if (handle == gf::INVALID_HANDLE) {
    return;
  }
  for (std::pair<gf::GF_OBJ_HANDLE *, GmkRouteNavi> *it = unknown120.begin(); it != unknown120.end(); ++it) {
    if (it->first == handle) {
      it->first = gf::INVALID_HANDLE;
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
  if (event == gf::IGfObjListener::OBJEVT_DESTROY && handle != gf::INVALID_HANDLE) {
    unbindToGameObj(handle);
    unbindRouteNavi(handle);
    unknown50.removeGobInst(handle);
  }
}

GmkRouteNavi *GmkRoutedMob::findFreeRouteNavi() const {
  for (std::pair<gf::GF_OBJ_HANDLE *, GmkRouteNavi> *it = unknown120.begin(); it != unknown120.end(); ++it) {
    if (it->first == gf::INVALID_HANDLE) {
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
