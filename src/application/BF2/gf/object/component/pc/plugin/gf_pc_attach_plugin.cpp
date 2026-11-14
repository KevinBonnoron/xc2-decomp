#include "gf/object/component/pc/plugin/gf_pc_attach_plugin.h"

#include "framework/dynamics/dynamics_updater.h"
#include "framework/object/updatable_object.h"
#include "framework/reference_frame.h"
#include "fw/fw_transform.h"
#include "gf/object/component/env_sensor/gf_com_env_sensor.h"
#include "gf/object/component/gf_com_dynamics.h"
#include "gf/object/component/gf_com_transform.h"
#include "gf/object/component/pc/gf_com_property_pc.h"
#include "gf/object/gf_obj.h"
#include "gf/object/gf_obj_handle.h"
#include "gf/object/gf_obj_util.h"
#include "mm_math/mm_quat_impl_nx.h"
#include "mm_mtl/intrusive_ptr.h"

namespace gf {
namespace pc {

AttachPlugin::AttachPlugin() : unknown0c(0), unknown10(unknown020), unknown18(nullptr), unknown20(mm::Vec3::zero), unknown30(mm::Quat::identity) {}

AttachPlugin::~AttachPlugin() {}

bool AttachPlugin::setup(GfComBehaviorPc &behavior) {
  unknown18 = &behavior;
  return true;
}

void AttachPlugin::cleanup(GfComBehaviorPc &) {
  unknown0c &= ~1u;
  unknown18 = nullptr;
}

void AttachPlugin::onActivate() {}

void AttachPlugin::onDeactivate() { dettachObj(); }

void AttachPlugin::dettachObj() {
  if (unknown10 != unknown020) {
    GfObjUtil::dettachGfObject(unknown10, static_cast<GfObj *>(unknown18->unknown08)->unknownf8);
    unknown10 = unknown020;
    GfComDynamics *dynamics = unknown18->unknown08->getComponent<GfComDynamics>();
    if (dynamics != nullptr) {
      fw::Transform transform;
      transform.unknown00 = mm::Vec3::zero;
      transform.unknown10 = mm::Quat::identity;
      dynamics->unknown10.unknown50 = transform;
      notifyExcludeMovementRider(transform);
    }
  }
}

void AttachPlugin::attachObj(GF_OBJ_HANDLE *handle) {
  GfObjUtil::attachGfObj(handle, static_cast<GfObj *>(unknown18->unknown08)->unknownf8);
  unknown10 = handle;
  GfObj *obj = GfObjUtil::getObj(handle);
  if (obj != nullptr) {
    GfComTransform *comTransform = obj->getComponent<GfComTransform>();
    if (comTransform != nullptr) {
      fw::ReferenceFrame *frame = comTransform->unknown001().operator->();
      frame->syncWorldTransform();
      unknown20 = frame->unknown40.unknown00;
      unknown30 = frame->unknown40.unknown10;
    }
    GfComDynamics *dynamics = unknown18->unknown08->getComponent<GfComDynamics>();
    if (dynamics != nullptr) {
      fw::Transform transform;
      transform.unknown00 = mm::Vec3::zero;
      transform.unknown10 = mm::Quat::identity;
      dynamics->unknown10.unknown50 = transform;
      notifyExcludeMovementRider(transform);
    }
  }
}

void AttachPlugin::notifyMovement() {
  GfObj *obj = GfObjUtil::getObj(unknown10);
  if (obj != nullptr) {
    GfComTransform *transform = obj->getComponent<GfComTransform>();
    GfComDynamics *dynamics = unknown18->unknown08->getComponent<GfComDynamics>();
    if (transform != nullptr && dynamics != nullptr) {
      fw::Transform world = transform->unknown001()->getSyncedWorldTransform();
      fw::Transform delta;
      delta.unknown00 = world.unknown00 - unknown20;
      mm::Quat::inverse(unknown30);
      delta.unknown10 = mm::Quat::mul(world.unknown10, unknown30);
      dynamics->unknown10.unknown50 = delta;
      notifyExcludeMovementRider(delta);
      unknown20 = world.unknown00;
      unknown30 = world.unknown10;
    }
  }
}

void AttachPlugin::changeWallMode(bool isWall) {
  if (isWall != ((unknown0c >> 1) & 1)) {
    if (isWall) {
      EnviromentSensor *sensor = unknown18->unknown08->getComponent<GfComPropertyPc>()->getEnvSensor();
      if (sensor->unknown24_1) {
        GF_OBJ_HANDLE *handle = sensor->unknown150.unknown90;
        if (handle != unknown020) {
          dettachObj();
          attachObj(handle);
        }
      }
      unknown0c |= 2;
    } else {
      dettachObj();
      unknown0c &= ~2u;
    }
  }
}

} // namespace pc
} // namespace gf
