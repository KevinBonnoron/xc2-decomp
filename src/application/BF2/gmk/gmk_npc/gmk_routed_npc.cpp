#include "gmk/gmk_npc/gmk_routed_npc.h"

#include "gf/game/gf_game_manager.h"
#include "gf/object/component/gf_com_transform.h"
#include "gf/object/gf_obj.h"
#include "gf/object/gf_obj_handle.h"
#include "gf/object/gf_obj_util.h"
#include "gmk/gmk_cond.h"
#include "gmk/gmk_gob_event_listener_impl.h" // IWYU pragma: keep
#include "gmk/gmk_set.h"
#include "mm_math/mm_vec3.h"

namespace gmk {

void GmkRoutedNpcList::create(const CreateInfo &info) { TGmkList::create(info); }

GmkType GmkRoutedNpc::getGmkType() const { return GMK_TYPE; }

bool GmkRoutedNpc::isPopCondMatched() const {
  if (!isValid()) {
    return false;
  }
  return getBdatInfo()->isPopCommonCondMatched(*this);
}

bool GmkRoutedNpc::isDepopCondMatched() const {
  if (!isValid()) {
    return false;
  }
  return !getBdatInfo()->isPopCommonCondMatched(*this);
}

bool GmkRoutedNpc::isPopDistCondMatched() const {
  if (!isValid() || gf::GfGameManager::getControlMover() == gf::INVALID_HANDLE) {
    return false;
  }
  const mm::Vec3 &position = gf::GfObjUtil::getObj(gf::GfGameManager::getControlMover())->getComponent<gf::GfComTransform>()->getPosition();
  mm::Vec3 nearest;
  if (!GmkRoute::getNearestPos(nearest, position)) {
    return false;
  }
  return getBdatInfo()->unknown20.isMatch(nearest);
}

bool GmkRoutedNpc::isDepopDistCondMatched() const {
  if (!isValid() || gf::GfGameManager::getControlMover() == gf::INVALID_HANDLE) {
    return false;
  }
  const mm::Vec3 &position = gf::GfObjUtil::getObj(gf::GfGameManager::getControlMover())->getComponent<gf::GfComTransform>()->getPosition();
  mm::Vec3 nearest;
  if (!GmkRoute::getNearestPos(nearest, position)) {
    return false;
  }
  return !getBdatInfo()->unknown28.isMatch(nearest);
}

int GmkRoutedNpc::getBindedBdatId() const { return unknown20.unknown18; }

u8 *GmkRoutedNpc::getBindedBdatFp() const { return unknown08.unknown00->getBindedBdatFp(); }

const IGmkList *GmkRoutedNpc::getBindedRoutePointList() const { return unknown08.unknown00->getCreateInfo().unknown08->unknown1b8[GMK_TYPE_NPC_ROUTE_POINT]; }

} // namespace gmk
