#include "gmk/gmk_mob/gmk_routed_mob.h"
#include "gmk/gmk_set.h"

namespace gmk {

GmkType GmkRoutedMob::getGmkType() const { return GMK_TYPE; }

const IGmkList *GmkRoutedMob::getBindedRoutePointList() const { return unknown08.unknown00->getCreateInfo().unknown08->unknown1b8[GMK_TYPE_MOB_ROUTE_POINT]; }

} // namespace gmk
