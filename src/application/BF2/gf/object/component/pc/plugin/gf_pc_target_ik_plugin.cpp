#include "gf/object/component/pc/plugin/gf_pc_target_ik_plugin.h"

#include <math.h>

#include "gf/object/component/pc/gf_com_property_pc.h"
#include "gf/object/component/property/gf_com_property.h"
#include "gf/object/gf_obj_handle.h"
#include "mm_math/mm_math.h"
#include "mm_math/mm_quat.h"

namespace gf {
namespace pc {

constexpr f32 EPSILON = 0.000001f;

TargetIKPlugin::TargetIKPlugin() : unknown10(INVALID_HANDLE), unknown20(nullptr), unknown30(mm::Vec3::unitZ), unknown40(1.0f), unknown44(1.0f) {}

TargetIKPlugin::~TargetIKPlugin() {}

void TargetIKPlugin::cleanup(GfComBehaviorPc &) { unknown18 = nullptr; }

bool TargetIKPlugin::isActiveRange(GfComPropertyPc &property, const mm::Vec3 &target) {
  const unknown001 *param = getParam();
  mm::Vec3 direction(target.x - property.unknown160.x, 0.0f, target.z - property.unknown160.z);
  if (!(mm::fabs(direction.x) <= EPSILON && mm::fabs(direction.z) <= EPSILON)) {
    f32 length = sqrtf(direction.x * direction.x + direction.y * direction.y + direction.z * direction.z);
    if (length <= EPSILON) {
      direction = mm::Vec3::zero;
    } else {
      f32 inverse = 1.0f / length;
      direction *= inverse;
    }
  }

  mm::Vec3 axis = property.unknown170.rotate(unknown30);
  f32 cosine = mm::clamp(direction.x * axis.x + direction.y * axis.y + direction.z * axis.z, -1.0f, 1.0f);
  return mm::acos(cosine) * mm::RAD_TO_DEG <= param->unknown00;
}

void TargetIKPlugin::procMsgGameChangeTarget(fw::MessageObject *object, MsgGameChangeTarget &message) {
  if (message.unknown08 != INVALID_HANDLE) {
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
