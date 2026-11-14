#include "gf/object/component/pc/plugin/gf_pc_access_plugin.h"

#include <math.h>

#include "fw/fw_transform.h"
#include "gf/game/gf_game_manager.h"
#include "gf/object/component/behavior/gf_com_behavior.h"
#include "gf/object/component/pc/gf_com_property_pc.h"
#include "gf/object/component/pc/gf_pc_property_field.h"
#include "gf/object/gf_obj.h"
#include "gf/object/gf_obj_acc.h"
#include "gf/object/gf_obj_handle.h"
#include "gf/object/gf_obj_util.h"
#include "gf/param/access/gf_param_access.h"
#include "gf/request/gf_req_scom.h"
#include "mm_math/mm_quat.h"
#include "mm_math/mm_vec3.h"

namespace gf {
namespace pc {

bool isActiveRange(GfComPropertyPc &property, const AccessParam &param, GF_OBJ_HANDLE *target) {
  bool isActive = false;
  GfObj *obj = GfObjUtil::getObj(target);
  if (obj != nullptr && (obj->unknown110 & 1) && GfGameManager::isEnableFieldAccess()) {
    MsgPcFieldGetAccessType message;
    static_cast<GfObj *>(property.unknown08)->sendMessage(obj, message);
    if (message.unknown0c) {
      GfObjAcc acc(obj);
      const mm::Vec3 &position = acc.getWorldTransform().unknown00;
      mm::Vec3 center = property.unknown160.unknown00 + property.unknown160.unknown10.rotate(mm::Vec3::unitZ * param.offsetFront);
      mm::Vec3 difference = position - center;
      bool isInHeight = AccessParam::unknown001(difference.y, param.accessUpper, -param.accessDown);
      f32 distance = sqrtf(difference.x * difference.x + 0.0f + difference.z * difference.z);
      isActive = distance < param.accessRadius && isInHeight;
    }
  }
  return isActive;
}

AccessPlugin::AccessPlugin() : unknown10(unknown020), unknown20(nullptr), unknown28(-1) {}

bool AccessPlugin::setup(GfComBehaviorPc &behavior) {
  unknown18 = fw::ParamManager::get()->unknown408[5];
  this->unknown20 = &behavior;
  return true;
}

void AccessPlugin::cleanup(GfComBehaviorPc &) {
  if (unknown10 != unknown020) {
    unknown10 = unknown020;
    SCOM_ACCESS_TARGET::create(unknown020);
  }
}

void AccessPlugin::onActivate() {}

void AccessPlugin::onDeactivate() {
  if (unknown10 != unknown020) {
    unknown10 = unknown020;
    SCOM_ACCESS_TARGET::create(unknown020);
  }
}

const AccessParam *AccessPlugin::getParam(u32 index) const {
  const fw::ParamList *list = unknown18.operator->();
  const fw::ParamList::unknown005 *entry = index < list->unknown0c ? &list->unknown10[index] : nullptr;
  return entry != nullptr ? static_cast<const AccessParam *>(entry->param) : nullptr;
}

u32 AccessPlugin::getParamIndex(GfComPropertyPc &property) const {
  if (property.unknown113_7) {
    return property.unknown310.unknown10_4 | 2;
  }
  return property.unknown310.unknown10_4;
}

} // namespace pc
} // namespace gf
