#include "gf/object/component/pc/plugin/gf_pc_dead_col_check_plugin.h"

#include "framework/coli/coli_object.h"
#include "framework/object/updatable_object.h"
#include "fw/fw_transform.h"
#include "gf/object/component/env_sensor/gf_com_env_sensor.h"
#include "gf/object/component/gf_com_collider.h"
#include "gf/object/component/pc/gf_com_property_pc.h"
#include "gf/object/component/pc/gf_pc_state_util.h"
#include "gf/object/component/property/gf_com_property.h"
#include "gf/object/gf_obj.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/intrusive_ptr.h"
#include "types.h"

namespace gf {
namespace pc {

DeadColCheckPlugin::DeadColCheckPlugin() {}

bool DeadColCheckPlugin::setup(GfComBehaviorPc &) { return true; }

void DeadColCheckPlugin::cleanup(GfComBehaviorPc &) {}

void DeadColCheckPlugin::onActivate() {}

void DeadColCheckPlugin::onDeactivate() {}

void DeadColCheckPlugin::update(GfComBehaviorPc &behavior, const fw::UpdateInfo &) {
  if (testDead(behavior)) {
    GfComPropertyPc *property = behavior.getProperty();
    GfObj *obj = static_cast<GfObj *>(property->unknown08);
    u32 hp = property->unknown10.get()->unknown10;
    if (!property->unknown111_2) {
      hp--;
      if (hp != 0) {
        MsgObjectDamage damage(hp, 4);
        obj->sendMessage(obj, damage);
      }

      MsgObjectStopAutoHeal stopAutoHeal(true);
      obj->sendMessage(obj, stopAutoHeal);
    } else if (hp != 0) {
      MsgObjectDamage damage(hp, 4);
      obj->sendMessage(obj, damage);
    }
  }
}

// 1.0.0: 0x7100577a64, 68 instructions; the game keeps the null test of both components (cbz x20 at 0x7100577a7c, cbz x19 at 0x7100577af4, joining at the vector read at 0x7100577b1c), see
// GfComCollider::unknown001 and UpdatableObject::getComponent.
// The `&` is the game's: both float compares are issued before the first branch (fcmp at 0x7100577ab8 and 0x7100577ac4, then `and w0, w8, w9`); `&&` gives 67 instructions.
bool DeadColCheckPlugin::testDead(GfComBehaviorPc &behavior) const {
  GfComPropertyPc *property = behavior.unknown08->getComponent<GfComPropertyPc>();
  const EnviromentSensor::unknown002 *plane = StateUtil::getDeadPlaneInfo(behavior);
  if (plane != nullptr) {
    return (property->unknown180.unknown00.y > plane->unknown00.y) & (property->unknown160.unknown00.y <= plane->unknown00.y);
  }
  if (property->unknown111_2) {
    return behavior.unknown08->getComponent<GfComCollider>()->unknown001()->testAttribute(fw::COLI_ATRR_UNKNOWN_1);
  }
  return false;
}

} // namespace pc
} // namespace gf
