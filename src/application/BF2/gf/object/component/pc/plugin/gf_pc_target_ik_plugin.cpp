#include "gf/object/component/pc/plugin/gf_pc_target_ik_plugin.h"

#include <math.h>

#include "framework/ik/ik_solver.h"
#include "framework/object/updatable_object.h"
#include "fw/fw_transform.h"
#include "fw/fw_update_info.h"
#include "gf/object/component/animation/gf_com_asm.h"
#include "gf/object/component/behavior/gf_com_behavior.h"
#include "gf/object/component/pc/gf_com_property_pc.h"
#include "gf/object/component/property/gf_com_property.h"
#include "gf/object/gf_obj.h"
#include "gf/object/gf_obj_acc.h"
#include "gf/object/gf_obj_handle.h"
#include "gf/object/gf_obj_util.h"
#include "mm_math/mm_math.h"
#include "mm_math/mm_quat.h"

namespace gf {
namespace pc {

constexpr f32 unknown018 = 0.000001f; // Inferred role: epsilon; original name unknown.

TargetIKPlugin::TargetIKPlugin() : unknown10(unknown020), unknown20(nullptr), unknown30(mm::Vec3::unitZ), unknown40(1.0f), unknown44(1.0f) {}

TargetIKPlugin::~TargetIKPlugin() {}

void TargetIKPlugin::cleanup(GfComBehaviorPc &) { unknown18 = nullptr; }

void TargetIKPlugin::update(GfComBehaviorPc &behavior, const fw::UpdateInfo &info) {
  if (unknown10 == unknown020) {
    return;
  }

  const unknown001 *param = getParam();
  GfComAsm *comAsm = behavior.unknown08->getComponent<GfComAsm>();
  if (comAsm != nullptr) {
    u64 attribute = comAsm->getAttribute(static_cast<AsmCategory>(0), ANIM_LAYER_UNKNOWN_0);
    f32 delta = info.unknown04 / param->unknown14;
    unknown40 = mm::clamp(unknown40 + ((attribute & 0x10) == 0 ? delta : -delta), 0.0f, 1.0f);
    unknown18->setTargetUpRatio(unknown40);
    unknown44 = mm::clamp(unknown44 + ((attribute & 0x20) == 0 ? delta : -delta), 0.0f, 1.0f);
    unknown18->setTargetDownRatio(unknown44);
  }

  GfObj *obj = GfObjUtil::getObj(unknown10);
  if (obj != nullptr) {
    MsgPcGetLookPoint message;
    if (static_cast<GfObj *>(behavior.unknown08)->sendMessage(obj, message) && message.unknown20) {
      unknown18->setTarget(message.unknown10);
      GfComPropertyPc *property = behavior.unknown08->getComponent<GfComPropertyPc>();
      GfObjAcc acc(obj);
      u32 attribute = acc.getAttribute();
      if (isActiveRange(*property, message.unknown10) && (attribute & 2) != 0) {
        if (unknown18->isEnable() && unknown18->unknown001() != fw::IkFadeSolver::unknown002_2) {
          return;
        }
        unknown18->fadeIn(param->unknown04);
      } else {
        if (!unknown18->isEnable() && unknown18->unknown001() != fw::IkFadeSolver::unknown002_1) {
          return;
        }
        unknown18->fadeOut(param->unknown04);
      }
    }
  }
}

bool TargetIKPlugin::isActiveRange(GfComPropertyPc &property, const mm::Vec3 &target) {
  const unknown001 *param = getParam();
  mm::Vec3 direction(target.x - property.unknown160.unknown00.x, 0.0f, target.z - property.unknown160.unknown00.z);
  if (!(mm::fabs(direction.x) <= unknown018 && mm::fabs(direction.z) <= unknown018)) {
    f32 length = sqrtf(direction.x * direction.x + direction.y * direction.y + direction.z * direction.z);
    if (length <= unknown018) {
      direction = mm::Vec3::zero;
    } else {
      f32 inverse = 1.0f / length;
      direction *= inverse;
    }
  }

  mm::Vec3 axis = property.unknown160.unknown10.rotate(unknown30);
  f32 cosine = mm::clamp(direction.x * axis.x + direction.y * axis.y + direction.z * axis.z, -1.0f, 1.0f);
  return mm::acos(cosine) * mm::RAD_TO_DEG <= param->unknown00;
}

void TargetIKPlugin::procMsgGameChangeTarget(fw::MessageObject *object, MsgGameChangeTarget &message) {
  if (message.unknown08 != unknown020) {
    const unknown001 *param = getParam();
    if (unknown18.get() != nullptr) {
      unknown18->startTargetFade(param->unknown04);
    }
  }
  unknown10 = message.unknown08;
}

void TargetIKPlugin::onActivate() {
  const unknown001 *param = getParam();
  unknown18->fadeIn(param->unknown04);
}

const unknown001 *TargetIKPlugin::getParam() const { return unknown20 != nullptr ? static_cast<const unknown001 *>(unknown20->param) : nullptr; }

void TargetIKPlugin::onDeactivate() {
  const unknown001 *param = getParam();
  unknown18->fadeOut(param->unknown04);
  unknown40 = 1.0f;
  unknown44 = 1.0f;
  unknown18->setTargetUpRatio(unknown40);
  unknown18->setTargetDownRatio(unknown44);
}

} // namespace pc
} // namespace gf
