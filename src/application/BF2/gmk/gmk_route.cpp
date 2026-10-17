#include "gmk/gmk_route.h"

#include "framework/debug/debug_draw.h"
#include "gf/data/gf_bdat_wrapper.h"
#include "gmk/gmk_acc.h"
#include "gmk/gmk_enemy/gmk_routed_enemy.h"
#include "gmk/gmk_list.h"
#include "gmk/gmk_map_obj.h"
#include "gmk/gmk_mob/gmk_routed_mob.h"
#include "gmk/gmk_npc/gmk_routed_npc.h"
#include "gmk/gmk_route_navi.h"
#include "gmk/gmk_set.h"
#include "ml/rand.h"
#include "mm_math/mm_col4.h"
#include "mm_math/mm_mat44.h"

namespace gmk {

namespace {

mm::Vec3 getSidePos(const GmkRoutePoint::Data &data, f32 width) {
  mm::Vec3 offset(width * data.sideX, width * data.sideY, width * data.sideZ);
  return offset + data.position;
}

} // namespace

GmkRouteNavi::CreateInfo::CreateInfo(const GmkRoute *route)
    : gmkSetId(-1), type(GMK_TYPE_NUM), index(0), widthRatio(0.0f), arriveDist(1.0f), arriveHeight(2.0f), curveDivisionNum(16), initResult(nullptr) {
  if (route != nullptr) {
    validate(*route);
  }
}

void GmkRouteNavi::CreateInfo::validate(const GmkRoute &route) {
  IGmkList *list = route.baseInfo.list;
  gmkSetId = list->getCreateInfo().set->createInfo.gmkSetId;
  type = route.getGmkType();
  u32 num = list->getInstNum();
  for (u32 i = 0; i < num; i++) {
    if (list->getInst(i) == &route) {
      index = i;
    }
  }
}

bool GmkRouteNavi::CreateInfo::isValid() const {
  if (gmkSetId <= 0) {
    return false;
  }
  switch (type) {
  case GMK_TYPE_ROUTED_ENEMY:
  case GMK_TYPE_ROUTED_NPC:
  case GMK_TYPE_ROUTED_MAP_OBJ:
  case GMK_TYPE_ROUTED_MOB:
  case GMK_TYPE_ROUTE:
    break;
  default:
    return false;
  }
  return curveDivisionNum != 0;
}

void GmkRouteNavi::create(const CreateInfo &info) {
  dispose();
  createInfo = info;
  arriveDist = info.arriveDist;
  arriveHeight = info.arriveHeight;
  pointIndex = 1;
  curveStep = 0;
  {
    GmkAcc::CreateInfo accInfo;
    accInfo.gmkSetId = info.gmkSetId;
    accInfo.type = info.type;
    accInfo.index = info.index;
    acc.create(accInfo);
  }
  if (isValid()) {
    initIsReverse();
  }
  if (info.initResult != nullptr) {
    initAtRandom(*info.initResult);
    return;
  }
  seq = &GmkRouteNavi::seqInit;
}

void GmkRouteNavi::dispose() {
  curveAngle = 0.0f;
  isReverse = false;
  pointIndex = 0;
  hasTargetPos = false;
  createInfo = CreateInfo(nullptr);
}

void GmkRouteNavi::initIsReverse() {
  u32 flags = getRoute()->getData()->flags;
  if ((flags & (GmkRoute::FLAG_FORWARD | GmkRoute::FLAG_REVERSE)) == (GmkRoute::FLAG_FORWARD | GmkRoute::FLAG_REVERSE)) {
    isReverse = ml::mtRandf1() > 0.5f;
  } else if (flags & GmkRoute::FLAG_FORWARD) {
    isReverse = false;
  } else if (flags & GmkRoute::FLAG_REVERSE) {
    isReverse = true;
  }
}

int GmkRouteNavi::validatePointIndex(bool &isReverse, int index) const {
  isReverse = this->isReverse;
  const GmkRoute *route = getRoute();
  bool isClosed = route->isClosed();
  int num = route->getRoutePointNum();
  if (index < 0) {
    index %= num;
    if (isClosed) {
      index += num;
    } else {
      index = -index;
      isReverse = (index / num) & 1;
    }
  }
  if (num <= index) {
    if (isClosed) {
      return index % num;
    }
    index = num - 2;
    isReverse = !((index / num) & 1);
  }
  return index;
}

bool GmkRouteNavi::getPosDirOnLine(mm::Vec3 &position, mm::Vec3 &direction, u32 index, f32 ratio) const {
  const GmkRoute *route = getRoute();
  if (route == nullptr) {
    return false;
  }
  bool isReverse;
  int prevIndex = validatePointIndex(isReverse, index - getPointStep());
  const GmkRoutePoint *prev = route->getRoutePoint(prevIndex);
  const GmkRoutePoint *current = route->getRoutePoint(index);
  if (prev == nullptr || current == nullptr) {
    return false;
  }
  const GmkRoutePoint::Data &prevData = *prev->getData();
  const GmkRoutePoint::Data &currentData = *current->getData();
  f32 width = getWidthRatio();
  mm::Vec3 start = getSidePos(prevData, width);
  direction = getSidePos(currentData, width) - start;
  position = start + direction * ratio;
  return true;
}

u32 GmkRoute::getRoutePointNum() const { return getData()->endPointIndex - getData()->firstPointIndex; }

bool GmkRoute::isClosed() const { return (getData()->flags & FLAG_CLOSED) != 0; }

void GmkRouteNavi::update(const UpdateInfo &info) {
  if (isValid() && seq) {
    (this->*seq)(info);
  }
}

void GmkRouteNavi::updateNextPos() {
  UpdateInfo info;
  info.position = targetPos;
  update(info);
}

bool GmkRouteNavi::isArrived(const mm::Vec3 &targetPosition, const mm::Vec3 &position) const {
  f32 height = targetPosition.y - position.y;
  if (arriveHeight < height) {
    return false;
  }
  f32 x = targetPosition.x - position.x;
  f32 z = targetPosition.z - position.z;
  f32 distSq = x * x + z * z;
  if (arriveDist * arriveDist < distSq) {
    return false;
  }
  return true;
}

void GmkRouteNavi::debugDraw() {
  mm::Vec3 position = targetPos;
  mm::Mat44 matrix;
  matrix.rows[0][0] = 1.0f;
  matrix.rows[0][1] = 0.0f;
  matrix.rows[0][2] = 0.0f;
  matrix.rows[0][3] = 0.0f;
  matrix.rows[1][0] = 0.0f;
  matrix.rows[1][1] = 1.0f;
  matrix.rows[1][2] = 0.0f;
  matrix.rows[1][3] = 0.0f;
  matrix.rows[2][0] = 0.0f;
  matrix.rows[2][1] = 0.0f;
  matrix.rows[2][2] = 1.0f;
  matrix.rows[2][3] = 0.0f;
  matrix.rows[3][0] = position.x;
  matrix.rows[3][1] = position.y;
  matrix.rows[3][2] = position.z;
  matrix.rows[3][3] = 1.0f;
  fw::debug::drawAxis(matrix, 1.0f);
}

void GmkRouteNavi::updateNextPointIndx() {
  if (isReverse) {
    pointIndex = validatePointIndex(isReverse, pointIndex - 1);
  } else {
    pointIndex = validatePointIndex(isReverse, pointIndex + 1);
  }
}

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

f32 GmkRouteNavi::getWidthRatio() const {
  const GmkRoute *route = getRoute();
  if (route == nullptr) {
    return 0.0f;
  }
  f32 width;
  switch (route->getData()->widthSide) {
  case 0:
    return createInfo.widthRatio;
  case 1:
    width = createInfo.widthRatio > 0.0f ? createInfo.widthRatio : -createInfo.widthRatio;
    break;
  case 2:
    width = createInfo.widthRatio > 0.0f ? -createInfo.widthRatio : createInfo.widthRatio;
    break;
  default:
    return 0.0f;
  }
  if (isReverse) {
    width = -width;
  }
  return width;
}

const GmkRoute *GmkRouteNavi::findGmkRouteByBdatId(GmkType type, int bdatId) {
  const AGmkBase *gmk = GmkManager::get()->findFirstGmkInstByBdatId(type, bdatId);
  if (gmk != nullptr) {
    switch (type) {
    case GMK_TYPE_ROUTED_ENEMY:
      return static_cast<const GmkRoutedEnemy *>(gmk);
    case GMK_TYPE_ROUTED_NPC:
      return static_cast<const GmkRoutedNpc *>(gmk);
    case GMK_TYPE_ROUTED_MAP_OBJ:
      return static_cast<const GmkRoutedMapObj *>(gmk);
    case GMK_TYPE_ROUTED_MOB:
      return static_cast<const GmkRoutedMob *>(gmk);
    case GMK_TYPE_ROUTE:
      return static_cast<const GmkRoute *>(gmk);
    default:
      break;
    }
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
