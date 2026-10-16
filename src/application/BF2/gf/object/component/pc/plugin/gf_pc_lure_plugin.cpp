#include "gf/object/component/pc/plugin/gf_pc_lure_plugin.h"

#include "gf/object/gf_obj_handle.h"

namespace gf {
namespace pc {

LurePlugin::LurePlugin() : target(INVALID_HANDLE), behavior(nullptr) {}

bool LurePlugin::setup(GfComBehaviorPc &behavior) {
  paramList = fw::ParamManager::get()->lureParamList;
  this->behavior = &behavior;
  return true;
}

void LurePlugin::cleanup(GfComBehaviorPc &) {}

void LurePlugin::onActivate() {}

void LurePlugin::onDeactivate() {
  if (target != INVALID_HANDLE) {
    target = INVALID_HANDLE;
  }
}

const LureParam *LurePlugin::getParam() const {
  const fw::ParamList *list = paramList.operator->();
  if (list->count == 0 || list->entries == nullptr) {
    return nullptr;
  }

  return static_cast<const LureParam *>(list->entries[0].param);
}

} // namespace pc
} // namespace gf
