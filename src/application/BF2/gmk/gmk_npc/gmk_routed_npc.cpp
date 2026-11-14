#include "gmk/gmk_npc/gmk_routed_npc.h"

#include <math.h>

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
#include "gmk/gmk_npc/gmk_routed_npc_impl.h" // IWYU pragma: keep
#include "gmk/gmk_route_navi.h"
#include "gmk/gmk_set.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/vector.h"

namespace gmk {

void GmkRoutedNpcList::create(const CreateInfo &info) { TGmkList::create(info); }

void GmkRoutedNpcList::createGmk(void *data) {
  TGmkList::createGmk(data);
  GmkNpcManager *manager = &getCreateInfo().unknown08->unknown178;
  u32 num = getInstNum();
  for (u32 i = 0; i < num; i++) {
    manager->addGmkNpc(&gmkInsts[i]);
  }
}

void GmkRoutedNpcList::disposeGmk() {
  GmkSet *set = getCreateInfo().unknown08;
  if (set != nullptr) {
    GmkNpcManager *manager = &set->unknown178;
    u32 num = getInstNum();
    for (u32 i = 0; i < num; i++) {
      manager->removeGmkNpc(&gmkInsts[i]);
    }
  }
  TGmkList::disposeGmk();
}

GmkType GmkRoutedNpc::getGmkType() const { return GMK_TYPE; }

void GmkRoutedNpc::dispose() {
  if (unknown70 != nullptr) {
    delete unknown70;
    unknown70 = nullptr;
  }
  AGmkBase::dispose();
}

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
  if (!isValid() || gf::GfGameManager::getControlMover() == gf::unknown020) {
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
  if (!isValid() || gf::GfGameManager::getControlMover() == gf::unknown020) {
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
  if (event == gf::IGfObjListener::OBJEVT_UNKNOWN_3) {
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
    return gf::unknown020;
  }
  gf::GF_OBJ_HANDLE *handle = AGmkNpc::unknown18->unknown30;
  if (this != getBindedGmkInst(handle)) {
    return gf::unknown020;
  }
  return handle;
}

bool GmkRoutedNpc::isPopCondMatchedExceptDist() const {
  if (AGmkNpc::unknown18 != nullptr && AGmkNpc::unknown18->unknown18 == this) {
    return isPopCondMatched();
  }
  return false;
}

bool GmkRoutedNpc::findPopPosRot(mm::Vec3 &position, mm::Vec3 &rotation) const {
  f32 angle;
  if (!unknown78) {
    position = unknown80;
    mm::Vec3 forward = unknown90.rotate(mm::Vec3(0.0f, 0.0f, 1.0f));
    angle = atan2f(forward.x, forward.z);
  } else {
    unknown78 = false;
    GmkRouteNavi::InitResult result;
    if (!unknown70->initAtRandom(result)) {
      return false;
    }
    position = result.position;
    if (!result.direction.unknown003()) {
      result.direction.unknown001();
    }
    angle = atan2f(result.direction.x, result.direction.z);
  }
  rotation.y = angle;
  rotation.z = 0.0f;
  rotation.x = 0.0f;
  return true;
}

void GmkRoutedNpc::validateDisp() const {
  gf::GF_OBJ_HANDLE *handle = getGobInst();
  if (handle != gf::unknown020) {
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

const IGmkList *GmkRoutedNpc::getBindedRoutePointList() const { return GmkRoute::unknown08.unknown00->getCreateInfo().unknown08->unknown1b8[GMK_TYPE_UNKNOWN_5]; }

} // namespace gmk

template void mm::mtl::Vector<gmk::GmkRoutedNpc>::expand(size_t, size_t);
template void mm::mtl::Vector<gmk::GmkRoutedNpc>::extend(size_t, size_t);
template void mm::mtl::Vector<gmk::GmkRoutedNpc>::resize(size_t);
