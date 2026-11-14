#pragma once
#include "gf/gf_allocator.h"
#include "gmk/gmk_npc/gmk_routed_npc.h"
#include "gmk/gmk_route.h"
#include "gmk/gmk_route_navi.h"
#include "ml/rand.h"

namespace gmk {

void GmkRoutedNpc::create(const CreateInfo &info) {
  GmkRoute::create(info);
  if (canCreateGameEntity()) {
    GmkRouteNavi::CreateInfo naviInfo(this);
    naviInfo.unknown0c = ml::mtRandf1(-1.0f, 1.0f);
#line 84
    unknown70 = new (gf::getAllocator(gf::ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) GmkRouteNavi(&naviInfo);
  }
  unknown78 = true;
}

} // namespace gmk
