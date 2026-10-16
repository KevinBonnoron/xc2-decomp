#include "gf/object/component/pc/plugin/gf_pc_access_plugin.h"

#include "gf/object/gf_obj_handle.h"
#include "gf/request/gf_req_scom.h"

namespace gf {
namespace pc {

AccessPlugin::AccessPlugin() : target(INVALID_HANDLE), behavior(nullptr), paramIndex(-1) {}

bool AccessPlugin::setup(GfComBehaviorPc &behavior) {
  paramList = fw::ParamManager::get()->pcParamList;
  this->behavior = &behavior;
  return true;
}

void AccessPlugin::cleanup(GfComBehaviorPc &) {
  if (target != INVALID_HANDLE) {
    target = INVALID_HANDLE;
    SCOM_ACCESS_TARGET::create(INVALID_HANDLE);
  }
}

void AccessPlugin::onActivate() {}

void AccessPlugin::onDeactivate() {
  if (target != INVALID_HANDLE) {
    target = INVALID_HANDLE;
    SCOM_ACCESS_TARGET::create(INVALID_HANDLE);
  }
}

const AccessParam *AccessPlugin::getParam(u32 index) const {
  const fw::ParamList *list = paramList.operator->();
  const fw::ParamList::Entry *entry = index < list->count ? &list->entries[index] : nullptr;
  return entry != nullptr ? static_cast<const AccessParam *>(entry->param) : nullptr;
}

} // namespace pc
} // namespace gf
