#include "gmk/gmk_enemy/gmk_routed_enemy.h"
#include "gmk/gmk_set.h"

#include "gmk/gmk_base.h"

namespace gmk {

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

void GmkRoutedEnemyList::setUpdateGmkNumPerFrame(u32 num) {
  TGmkList::setUpdateGmkNumPerFrame(num);
  unknown240.setUpdateGmkNumPerFrame(num);
}

IGmkList *GmkRoutedEnemy::getOwnerGmkEnemyList() const { return unknown08.unknown00; }

const IGmkList *GmkRoutedEnemy::getBindedRoutePointList() const { return unknown08.unknown00->getCreateInfo().unknown08->unknown1b8[GMK_TYPE_ROUTED_ENEMY_POINT]; }

void GmkRoutedEnemyList::debugDraw() const {
  TGmkList::debugDraw();
  unknown240.debugDraw();
}

void GmkRoutedEnemyList::debugUpdateMmf() {
  TGmkList::debugUpdateMmf();
  unknown240.debugUpdateMmf();
}

} // namespace gmk
