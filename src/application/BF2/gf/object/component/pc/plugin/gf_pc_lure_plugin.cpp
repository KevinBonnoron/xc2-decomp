#include "gf/object/component/pc/plugin/gf_pc_lure_plugin.h"

#include "gf/object/gf_obj_handle.h"

namespace gf {
namespace pc {

LurePlugin::LurePlugin() : unknown10(INVALID_HANDLE), unknown20(nullptr) {}

bool LurePlugin::setup(GfComBehaviorPc &behavior) {
  unknown18 = fw::ParamManager::get()->unknown440;
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

const LureParam *LurePlugin::getParam() const {
  const fw::ParamList *list = unknown18.operator->();
  if (list->unknown0c == 0 || list->unknown10 == nullptr) {
    return nullptr;
  }

  return static_cast<const LureParam *>(list->unknown10[0].param);
}

} // namespace pc
} // namespace gf
