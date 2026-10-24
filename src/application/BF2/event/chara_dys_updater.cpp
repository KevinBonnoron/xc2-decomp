#include "event/chara_dys_updater.h"

#include "framework/dynamics/dynamics_updater.h"
#include "gf/object/component/gf_com_dynamics.h"
#include "gf/object/gf_obj.h"
#include "gf/object/gf_obj_handle.h"
#include "gf/object/gf_obj_util.h"
#include "mm_math/mm_math.h"

namespace event {

CharaDysUpdater::CharaDysUpdater() : unknown08(), unknown10(gf::INVALID_HANDLE), unknown20(0.0f) {}

void CharaDysUpdater::create(gf::GF_OBJ_HANDLE *handle) {
  this->unknown10 = handle;
  unknown20 = 0.0f;
  unknown08.clear();
}

void CharaDysUpdater::destroy() {
  unknown10 = gf::INVALID_HANDLE;
  unknown20 = 0.0f;
}

void CharaDysUpdater::update(f32 delta) {
  if (unknown08.test(FLAG_RESET_DYNAMICS)) {
    resetDynamics(unknown10);
    if (unknown18-- <= 0) {
      unknown08.set(FLAG_RESET_DYNAMICS, false);
    }
  }
  if (unknown08.test(FLAG_RESET_MOVEMENT)) {
    resetMovement(unknown10);
    if (unknown1c-- <= 0) {
      unknown08.set(FLAG_RESET_MOVEMENT, false);
    }
  }
  setDynamicsBlendWeight(unknown10, unknown20);
}

void CharaDysUpdater::resetDynamics(gf::GF_OBJ_HANDLE *handle) {
  gf::GfObj *obj = gf::GfObjUtil::getObj(handle);
  if (obj == nullptr) {
    return;
  }

  gf::GfComDynamics *dynamics = obj->getComponent<gf::GfComDynamics>();
  if (dynamics != nullptr) {
    dynamics->unknown10.unknown72 = true;
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
  resetDynamics(unknown10);
  unknown08.set(FLAG_RESET_DYNAMICS, true);
  unknown18 = frame;
}

void CharaDysUpdater::resetMovement(int frame) {
  resetMovement(unknown10);
  unknown08.set(FLAG_RESET_MOVEMENT, true);
  unknown1c = frame;
}

void CharaDysUpdater::setDynamicsBlendWeight(f32 weight) {
  mm::clampRef(weight, 0.0f, 1.0f);
  unknown20 = weight;
}

} // namespace event
