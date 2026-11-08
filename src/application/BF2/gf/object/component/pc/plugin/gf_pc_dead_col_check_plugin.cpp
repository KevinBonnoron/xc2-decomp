#include "gf/object/component/pc/plugin/gf_pc_dead_col_check_plugin.h"

#include "gf/object/component/pc/gf_com_property_pc.h"
#include "gf/object/component/property/gf_com_property.h"
#include "gf/object/gf_obj.h"
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

} // namespace pc
} // namespace gf
