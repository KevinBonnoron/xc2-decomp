#include "gmk/gmk_trigger.h"
#include "gmk/gmk_list_impl.h" // IWYU pragma: keep

#include "gmk/gmk_enemy/gmk_enemy.h"
#include "gmk/gmk_enemy/gmk_routed_enemy.h"
#include "gmk/gmk_map_gimmick.h"
#include "gmk/gmk_set.h"
#include "mm_mtl/fixstr.h"
#include "mtl/alloc_handle.h"

namespace gmk {

GmkTrigger::GmkTrigger() : unknown50(nullptr), unknownE0(nullptr) {}

template bool TGmkList<GmkTrigger, GmkTrigger::BdatInfo, 1380405844u, 2u, GmkTriggerGob>::initGmkBdatInfo(GmkTrigger::BdatInfo &, int &, const AGmkBase &);

namespace {

bool isGmkListReady(const IGmkList *list) {
  if (list == nullptr) {
    return true;
  }
  const IGmkList::CreateInfo &info = list->getCreateInfo();
  if (!info.unknown00.isValid() || info.unknown10.empty()) {
    return true;
  }
  return list->isValid();
}

} // namespace

GmkType GmkTrigger::getGmkType() const { return GMK_TYPE; }

bool GmkTrigger::isValid() const { return unknown08.unknown00 != nullptr && unknown20.unknown08 != nullptr; }

void GmkTrigger::debugDraw() const {}

void GmkTrigger::dispose() {
  unknownE0 = nullptr;
  unknown50.dispose();
  AGmkBase::dispose();
}

void GmkTrigger::createGmkPhantom() {
  const GmkSet *set = unknown08.unknown00->getCreateInfo().unknown08;
  if (set != nullptr && set->unknown10.unknown24) {
    return;
  }
  unknown50.create(*this, nullptr, false);
}

void GmkTrigger::applyPopCondMatched(bool matched) {
  u32 mapGimmickNum = getBindedMapGimmickNum();
  for (u32 i = 0; i < mapGimmickNum; i++) {
    GmkMapGimmick *gmk = static_cast<GmkMapGimmick *>(getBindedMapGimmick(i));
    if (gmk != nullptr) {
      gmk->unknownA8 = true;
      gmk->unknownA9 = matched;
    }
  }
  u32 enemyNum = getBindedEnemyNum();
  for (u32 i = 0; i < enemyNum; i++) {
    GmkEnemy *gmk = static_cast<GmkEnemy *>(getBindedEnemy(i));
    if (gmk != nullptr) {
      gmk->unknown48.unknown158 = true;
      gmk->unknown48.unknown159 = matched;
    }
  }
  u32 routedEnemyNum = getBindedRoutedEnemyNum();
  for (u32 i = 0; i < routedEnemyNum; i++) {
    GmkRoutedEnemy *gmk = static_cast<GmkRoutedEnemy *>(getBindedRoutedEnemy(i));
    if (gmk != nullptr) {
      gmk->unknown50.unknown158 = true;
      gmk->unknown50.unknown159 = matched;
    }
  }
}

void GmkTrigger::seqUpdate(f32 deltaTime) { applyPopCondMatched(unknown50.unknown83); }

void GmkTrigger::seqWaitToValidLinkGmkList(f32 deltaTime) {
  const GmkSet *set = unknown08.unknown00->getCreateInfo().unknown08;
  if (isGmkListReady(set->unknown1b8[GMK_TYPE_MAP_GIMMICK]) && isGmkListReady(set->unknown1b8[GMK_TYPE_ENEMY]) && isGmkListReady(set->unknown1b8[GMK_TYPE_ROUTED_ENEMY])) {
    applyPopCondMatched(false);
    unknownE0 = &GmkTrigger::seqUpdate;
  }
}

void GmkTrigger::create(const CreateInfo &info) {
  AGmkBase::create(info);
  createGmkPhantom();
  applyPopCondMatched(false);
  unknownE0 = &GmkTrigger::seqWaitToValidLinkGmkList;
}

void GmkTrigger::update(f32 deltaTime) {
  debugUpdateMmf();
  if (unknownE0) {
    (this->*unknownE0)(deltaTime);
  }
}

AGmkBase *GmkTrigger::getBindedMapGimmick(u32 index) const {
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
    return const_cast<AGmkBase *>(gmk);
  }
  return nullptr;
}

AGmkBase *GmkTrigger::getBindedEnemy(u32 index) const {
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
    return const_cast<AGmkBase *>(gmk);
  }
  return nullptr;
}

AGmkBase *GmkTrigger::getBindedRoutedEnemy(u32 index) const {
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
    return const_cast<AGmkBase *>(gmk);
  }
  return nullptr;
}

int GmkTrigger::getBindedMapGimmickNum() const { return getData()->unknown04 - getData()->unknown00; }

int GmkTrigger::getBindedEnemyNum() const { return getData()->unknown14 - getData()->unknown10; }

int GmkTrigger::getBindedRoutedEnemyNum() const { return getData()->unknown1c - getData()->unknown18; }

} // namespace gmk
