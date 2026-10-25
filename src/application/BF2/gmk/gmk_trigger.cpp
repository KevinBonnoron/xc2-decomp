#include "gmk/gmk_trigger.h"

#include "gmk/gmk_set.h"

namespace gmk {

GmkType GmkTrigger::getGmkType() const { return GMK_TYPE; }

bool GmkTrigger::isValid() const { return unknown08.unknown00 != nullptr && unknown20.unknown08 != nullptr; }

void GmkTrigger::debugDraw() const {}

void GmkTrigger::seqUpdate(f32 deltaTime) { applyPopCondMatched(unknownD3); }

const AGmkBase *GmkTrigger::getBindedMapGimmick(u32 index) const {
  IGmkList *list = unknown08.unknown00->getCreateInfo().unknown08->unknown1b8[GMK_TYPE_MAP_GIMMICK];
  if (list == nullptr) {
    return nullptr;
  }
  u32 listIndex = getData()->unknown00 + index;
  if (list->getInstNum() <= listIndex) {
    return nullptr;
  }
  const AGmkBase *gmk = list->getInst(listIndex);
  if (gmk->getGmkType() == GMK_TYPE_MAP_GIMMICK) {
    return gmk;
  }
  return nullptr;
}

const AGmkBase *GmkTrigger::getBindedEnemy(u32 index) const {
  IGmkList *list = unknown08.unknown00->getCreateInfo().unknown08->unknown1b8[GMK_TYPE_ENEMY];
  if (list == nullptr) {
    return nullptr;
  }
  u32 listIndex = getData()->unknown10 + index;
  if (list->getInstNum() <= listIndex) {
    return nullptr;
  }
  const AGmkBase *gmk = list->getInst(listIndex);
  if (gmk->getGmkType() == GMK_TYPE_ENEMY) {
    return gmk;
  }
  return nullptr;
}

const AGmkBase *GmkTrigger::getBindedRoutedEnemy(u32 index) const {
  IGmkList *list = unknown08.unknown00->getCreateInfo().unknown08->unknown1b8[GMK_TYPE_ROUTED_ENEMY];
  if (list == nullptr) {
    return nullptr;
  }
  u32 listIndex = getData()->unknown18 + index;
  if (list->getInstNum() <= listIndex) {
    return nullptr;
  }
  const AGmkBase *gmk = list->getInst(listIndex);
  if (gmk->getGmkType() == GMK_TYPE_ROUTED_ENEMY) {
    return gmk;
  }
  return nullptr;
}

int GmkTrigger::getBindedMapGimmickNum() const { return getData()->unknown04 - getData()->unknown00; }

int GmkTrigger::getBindedEnemyNum() const { return getData()->unknown14 - getData()->unknown10; }

int GmkTrigger::getBindedRoutedEnemyNum() const { return getData()->unknown1c - getData()->unknown18; }

} // namespace gmk
