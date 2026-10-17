#include "gmk/gmk_route.h"

#include "gf/data/gf_bdat_wrapper.h"
#include "gmk/gmk_set.h"
#include "mm_math/mm_col4.h"

namespace gmk {

u32 GmkRoute::getRoutePointNum() const { return getData()->endPointIndex - getData()->firstPointIndex; }

bool GmkRoute::isClosed() const { return (getData()->flags & FLAG_CLOSED) != 0; }

const GmkRoutePoint *GmkRoute::getRoutePoint(u32 index) const {
  const IGmkList *list = getBindedRoutePointList();
  if (list == nullptr) {
    return nullptr;
  }
  u32 pointIndex = getData()->firstPointIndex + index;
  if (list->getInstNum() > pointIndex) {
    return static_cast<const GmkRoutePoint *>(list->getInst(pointIndex));
  }
  return nullptr;
}

bool GmkRoute::getRoutePointPos(mm::Vec3 &position, u32 index) const {
  const GmkRoutePoint *point = getRoutePoint(index);
  if (point == nullptr || !point->isValid()) {
    return false;
  }
  position = point->getData()->position;
  return true;
}

void GmkRoute::debugDraw(bool isSelected) const {
  if (!isValid()) {
    return;
  }
  mm::Col4 color;
  if (isSelected) {
    color = mm::Col4::yellow;
  } else {
    color = mm::Col4::gray;
  }
  debugDrawRoute(color);
}

void GmkRoute::BdatInfo::create(CBdatWrapper bdat, int id, const AGmkBase &gmk) {}

const IGmkList *GmkRoute::getBindedRoutePointList() const { return baseInfo.list->getCreateInfo().set->lists[GMK_TYPE_ROUTE_POINT]; }

void GmkRoute::debugDraw() const {
  AGmkBase::debugDraw();
  if (!isValid()) {
    return;
  }
  debugDrawRoute(mm::Col4::yellow);
}

void GmkRoute::debugUpdateMmf() {}

void GmkRoutePoint::create(const CreateInfo &info) { AGmkBase::create(info); }

void GmkRoutePoint::dispose() { AGmkBase::dispose(); }

void GmkRoutePoint::debugUpdateMmf() {}

} // namespace gmk
