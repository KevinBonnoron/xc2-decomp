#include "gmk/gmk_mob/gmk_routed_mob.h"
#include "gmk/gmk_list_impl.h" // IWYU pragma: keep

#include "gf/object/gf_obj_handle.h"
#include "gmk/gmk_route_navi.h"
#include "gmk/gmk_set.h"

namespace gf {
struct GF_OBJ_HANDLE;
} // namespace gf

namespace gmk {

template bool TGmkList<GmkRoutedMob, GmkMob::BdatInfo, 1112493394u, 6u, GmkRouteGob>::initGmkBdatInfo(GmkMob::BdatInfo &, int &, const AGmkBase &);

GmkType GmkRoutedMob::getGmkType() const { return GMK_TYPE; }

const IGmkList *GmkRoutedMob::getBindedRoutePointList() const { return unknown08.unknown00->getCreateInfo().unknown08->unknown1b8[GMK_TYPE_MOB_ROUTE_POINT]; }

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
