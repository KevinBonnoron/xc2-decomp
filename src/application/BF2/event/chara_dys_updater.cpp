#include "event/chara_dys_updater.h"

#include "framework/dynamics/dynamics_updater.h"
#include "gf/object/component/gf_com_dynamics.h"
#include "gf/object/gf_obj.h"
#include "gf/object/gf_obj_handle.h"
#include "gf/object/gf_obj_util.h"
#include "mm_math/mm_math.h"

namespace event {

CharaDysUpdater::CharaDysUpdater() : flags(), handle(gf::INVALID_HANDLE), mBlendWeight(0.0f) {}

void CharaDysUpdater::create(gf::GF_OBJ_HANDLE *handle) {
  this->handle = handle;
  mBlendWeight = 0.0f;
  flags.clear();
}

void CharaDysUpdater::destroy() {
  handle = gf::INVALID_HANDLE;
  mBlendWeight = 0.0f;
}

void CharaDysUpdater::update(f32 delta) {
  if (flags.test(FLAG_RESET_DYNAMICS)) {
    resetDynamics(handle);
    if (mResetDynamicsFrame-- <= 0) {
      flags.set(FLAG_RESET_DYNAMICS, false);
    }
  }
  if (flags.test(FLAG_RESET_MOVEMENT)) {
    resetMovement(handle);
    if (mResetMovementFrame-- <= 0) {
      flags.set(FLAG_RESET_MOVEMENT, false);
    }
  }
  setDynamicsBlendWeight(handle, mBlendWeight);
}

void CharaDysUpdater::resetDynamics(gf::GF_OBJ_HANDLE *handle) {
  gf::GfObj *obj = gf::GfObjUtil::getObj(handle);
  if (obj == nullptr) {
    return;
  }

  gf::GfComDynamics *dynamics = obj->getComponent<gf::GfComDynamics>();
  if (dynamics != nullptr) {
    dynamics->unknown10.isResetRequested = true;
    dynamics->resetMovement();
  }
}

void CharaDysUpdater::resetMovement(gf::GF_OBJ_HANDLE *handle) {
  gf::GfObj *obj = gf::GfObjUtil::getObj(handle);
  if (obj == nullptr) {
    return;
  }

  gf::GfComDynamics *dynamics = obj->getComponent<gf::GfComDynamics>();
  if (dynamics != nullptr) {
    dynamics->resetMovement();
  }
}

void CharaDysUpdater::setDynamicsBlendWeight(gf::GF_OBJ_HANDLE *handle, f32 weight) {
  gf::GfObj *obj = gf::GfObjUtil::getObj(handle);
  if (obj == nullptr) {
    return;
  }

  gf::GfComDynamics *dynamics = obj->getComponent<gf::GfComDynamics>();
  if (dynamics != nullptr) {
    for (u32 i = 0; i < dynamics->getSolverCount(); i++) {
      dynamics->setSolverBlendWeight(i, weight);
    }
  }
}

void CharaDysUpdater::resetDynamics(int frame) {
  resetDynamics(handle);
  flags.set(FLAG_RESET_DYNAMICS, true);
  mResetDynamicsFrame = frame;
}

void CharaDysUpdater::resetMovement(int frame) {
  resetMovement(handle);
  flags.set(FLAG_RESET_MOVEMENT, true);
  mResetMovementFrame = frame;
}

void CharaDysUpdater::setDynamicsBlendWeight(f32 weight) {
  mm::clampRef(weight, 0.0f, 1.0f);
  mBlendWeight = weight;
}

} // namespace event
