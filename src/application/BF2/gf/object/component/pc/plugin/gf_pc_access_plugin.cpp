#include "gf/object/component/pc/plugin/gf_pc_access_plugin.h"

#include "gf/object/gf_obj_handle.h"
#include "gf/request/gf_req_scom.h"

namespace gf {
namespace pc {

AccessPlugin::AccessPlugin() : unknown10(INVALID_HANDLE), unknown20(nullptr), unknown28(-1) {}

bool AccessPlugin::setup(GfComBehaviorPc &behavior) {
  unknown18 = fw::ParamManager::get()->unknown430;
  this->unknown20 = &behavior;
  return true;
}

void AccessPlugin::cleanup(GfComBehaviorPc &) {
  if (unknown10 != INVALID_HANDLE) {
    unknown10 = INVALID_HANDLE;
    SCOM_ACCESS_TARGET::create(INVALID_HANDLE);
  }
}

void AccessPlugin::onActivate() {}

void AccessPlugin::onDeactivate() {
  if (unknown10 != INVALID_HANDLE) {
    unknown10 = INVALID_HANDLE;
    SCOM_ACCESS_TARGET::create(INVALID_HANDLE);
  }
}

const AccessParam *AccessPlugin::getParam(u32 index) const {
  const fw::ParamList *list = unknown18.operator->();
  const fw::ParamList::unknown005 *entry = index < list->unknown0c ? &list->unknown10[index] : nullptr;
  return entry != nullptr ? static_cast<const AccessParam *>(entry->param) : nullptr;
}

} // namespace pc
} // namespace gf
