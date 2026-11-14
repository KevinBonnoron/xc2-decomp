#include "gf/object/component/pc/plugin/gf_pc_lure_plugin.h"

#include <math.h>

#include "framework/object/updatable_object.h"
#include "fw/fw_transform.h"
#include "gf/data/gf_object_type.h"
#include "gf/game/gf_game_manager.h"
#include "gf/object/component/pc/gf_com_property_pc.h"
#include "gf/object/component/pc/gf_pc_state_util.h"
#include "gf/object/gf_obj_acc.h"
#include "gf/object/gf_obj_handle.h"
#include "gf/object/gf_obj_util.h"
#include "gf/param/access/gf_param_access.h"
#include "mm_math/mm_quat.h"
#include "mm_math/mm_vec3.h"
#include "types.h"

namespace gf {
class GfObj;

namespace pc {

bool isActiveRangeLure(GfComPropertyPc &property, const AccessParam &param, GF_OBJ_HANDLE *target) {
  bool isActive = false;
  GfObj *obj = GfObjUtil::getObj(target);
  if (obj != nullptr && GfObjUtil::getObjType(target) == OBJECT_TYPE_ENEMY) {
    GfObjAcc acc(obj);
    const mm::Vec3 &position = acc.getWorldTransform().unknown00;
    mm::Vec3 center = property.unknown160.unknown00 + property.unknown160.unknown10.rotate(mm::Vec3::unitZ * param.offsetFront);
    mm::Vec3 difference = position - center;
    bool isInHeight = AccessParam::unknown001(difference.y, param.accessUpper, -param.accessDown);
    s16 ownerBonus = GfGameManager::getOwnerBonus()->unknown00[OWNER_BONUS_UNKNOWN_11];
    f32 radius = param.accessRadius + (ownerBonus >= 0 ? static_cast<f32>(ownerBonus < 10 ? ownerBonus : 10) : 0.0f);
    bool isInRadius = sqrtf(difference.x * difference.x + 0.0f + difference.z * difference.z) < radius;
    isActive = isInHeight && isInRadius;
  }
  return isActive;
}

LurePlugin::LurePlugin() : unknown10(unknown020), unknown20(nullptr) {}

bool LurePlugin::setup(GfComBehaviorPc &behavior) {
  unknown18 = fw::ParamManager::get()->unknown408[7];
  this->unknown20 = &behavior;
  return true;
}

void LurePlugin::cleanup(GfComBehaviorPc &) {}

void LurePlugin::onActivate() {}

void LurePlugin::onDeactivate() {
  if (unknown10 != unknown020) {
    unknown10 = unknown020;
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
  if (target != unknown020) {
    const AccessParam *param = getParam();
    GfComPropertyPc *property = behavior.unknown08->getComponent<GfComPropertyPc>();
    if (!isActiveRangeLure(*property, *param, target)) {
      target = unknown020;
    }
  }
  if (unknown10 != target) {
    unknown10 = target;
  }
}

} // namespace pc
} // namespace gf
