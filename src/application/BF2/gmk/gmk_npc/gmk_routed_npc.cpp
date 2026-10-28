#include "gmk/gmk_npc/gmk_routed_npc.h"

#include "gf/game/gf_game_manager.h"
#include "gf/object/component/behavior/gf_com_behavior_npc.h"
#include "gf/object/component/gf_com_transform.h"
#include "gf/object/gf_obj.h"
#include "gf/object/gf_obj_acc.h"
#include "gf/object/gf_obj_handle.h"
#include "gf/object/gf_obj_util.h"
#include "gmk/gmk_base.h"
#include "gmk/gmk_cond.h"
#include "gmk/gmk_gob_event_listener_impl.h" // IWYU pragma: keep
#include "gmk/gmk_npc/gmk_npc_manager.h"
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

void GmkRoutedNpc::onGobEvent(gf::IGfObjListener::OBJEVT event, gf::GF_OBJ_HANDLE *handle) {
  AGmkBase::onGobEvent(event, handle);
  if (event == gf::IGfObjListener::OBJEVT_DESTROY) {
    unbindToGameObj(handle);
    unknown78 = true;
    if (AGmkNpc::unknown18->unknown30 == handle) {
      AGmkNpc::unknown18->disposeGobInst(false);
    }
  }
}

void GmkRoutedNpc::bindToGameObj(gf::GF_OBJ_HANDLE *handle) const {
  AGmkBase::bindToGameObj(handle);
  gf::GfObjAcc acc(handle);
  gf::GfObj *obj = acc.getObj();
  if (obj == nullptr) {
    return;
  }
  gf::GfComBehaviorNpc *behavior = obj->getComponent<gf::GfComBehaviorNpc>();
  if (behavior != nullptr) {
    behavior->validateBindedGmkInstInfo(true);
  }
}

void GmkRoutedNpc::unbindToGameObj(gf::GF_OBJ_HANDLE *handle) const {
  getGobPosRot(unknown80, unknown90, handle);
  AGmkBase::unbindToGameObj(handle);
}

gf::GF_OBJ_HANDLE *GmkRoutedNpc::getGobInst() const {
  if (AGmkNpc::unknown18 == nullptr) {
    return gf::INVALID_HANDLE;
  }
  gf::GF_OBJ_HANDLE *handle = AGmkNpc::unknown18->unknown30;
  if (this != getBindedGmkInst(handle)) {
    return gf::INVALID_HANDLE;
  }
  return handle;
}

bool GmkRoutedNpc::isPopCondMatchedExceptDist() const {
  if (AGmkNpc::unknown18 != nullptr && AGmkNpc::unknown18->unknown18 == this) {
    return isPopCondMatched();
  }
  return false;
}

void GmkRoutedNpc::validateDisp() const {
  gf::GF_OBJ_HANDLE *handle = getGobInst();
  if (handle != gf::INVALID_HANDLE) {
    bool isDisp = unknown79 && debugIsDispGmkType(getGmkType());
    setEventDisp(handle, isDisp);
  }
}

void GmkRoutedNpc::debugDraw() const {
  if (!isValid()) {
    return;
  }
  bool isPopCondMatched = getBdatInfo()->isPopCommonCondMatched(*this);
  GmkRoute::debugDraw(isPopCondMatched);
}

int GmkRoutedNpc::getBindedBdatId() const { return GmkRoute::unknown20.unknown18; }

u8 *GmkRoutedNpc::getBindedBdatFp() const { return GmkRoute::unknown08.unknown00->getBindedBdatFp(); }

const IGmkList *GmkRoutedNpc::getBindedRoutePointList() const { return GmkRoute::unknown08.unknown00->getCreateInfo().unknown08->unknown1b8[GMK_TYPE_NPC_ROUTE_POINT]; }

} // namespace gmk
