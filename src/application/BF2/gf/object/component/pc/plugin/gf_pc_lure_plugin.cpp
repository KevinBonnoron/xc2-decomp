#include "gf/object/component/pc/plugin/gf_pc_lure_plugin.h"

#include "framework/object/updatable_object.h"
#include "gf/object/component/pc/gf_com_property_pc.h"
#include "gf/object/component/pc/gf_pc_state_util.h"
#include "gf/object/gf_obj_handle.h"

namespace gf {
struct AccessParam;

namespace pc {

LurePlugin::LurePlugin() : unknown10(INVALID_HANDLE), unknown20(nullptr) {}

bool LurePlugin::setup(GfComBehaviorPc &behavior) {
  unknown18 = fw::ParamManager::get()->unknown408[7];
  this->unknown20 = &behavior;
  return true;
}

void LurePlugin::cleanup(GfComBehaviorPc &) {}

void LurePlugin::onActivate() {}

void LurePlugin::onDeactivate() {
  if (unknown10 != INVALID_HANDLE) {
    unknown10 = INVALID_HANDLE;
  }
}

const AccessParam *LurePlugin::getParam() const {
  const fw::ParamList *list = unknown18.operator->();
  if (list->unknown0c == 0 || list->unknown10 == nullptr) {
    return nullptr;
  }

  return static_cast<const AccessParam *>(list->unknown10[0].param);
}

void LurePlugin::update(GfComBehaviorPc &behavior, const fw::UpdateInfo &info) {
  GF_OBJ_HANDLE *target = StateUtil::getTarget(behavior);
  if (target != INVALID_HANDLE) {
    const AccessParam *param = getParam();
    GfComPropertyPc *property = behavior.unknown08->getComponent<GfComPropertyPc>();
    if (!isActiveRangeLure(*property, *param, target)) {
      target = INVALID_HANDLE;
    }
  }
  if (unknown10 != target) {
    unknown10 = target;
  }
}

} // namespace pc
} // namespace gf
