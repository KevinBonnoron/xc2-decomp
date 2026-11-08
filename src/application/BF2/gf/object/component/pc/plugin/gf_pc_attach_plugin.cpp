#include "gf/object/component/pc/plugin/gf_pc_attach_plugin.h"

#include "framework/dynamics/dynamics_updater.h"
#include "framework/object/updatable_object.h"
#include "fw/fw_transform.h"
#include "gf/object/component/gf_com_dynamics.h"
#include "gf/object/gf_obj.h"
#include "gf/object/gf_obj_handle.h"
#include "gf/object/gf_obj_util.h"

namespace gf {
namespace pc {

AttachPlugin::AttachPlugin() : unknown0c(0), unknown10(INVALID_HANDLE), unknown18(nullptr), unknown20(mm::Vec3::zero), unknown30(mm::Quat::identity) {}

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
  if (unknown10 != INVALID_HANDLE) {
    GfObjUtil::dettachGfObject(unknown10, static_cast<GfObj *>(unknown18->unknown08)->unknownf8);
    unknown10 = INVALID_HANDLE;
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

} // namespace pc
} // namespace gf
