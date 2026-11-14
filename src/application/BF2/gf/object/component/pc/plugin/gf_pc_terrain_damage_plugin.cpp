#include "gf/object/component/pc/plugin/gf_pc_terrain_damage_plugin.h"

#include "framework/object/updatable_object.h"
#include "fw/fw_transform.h"
#include "fw/fw_update_info.h"
#include "gf/field/gf_field_dmg.h"
#include "gf/object/component/env_sensor/gf_com_env_sensor.h"
#include "gf/object/component/pc/gf_com_property_pc.h"
#include "gf/object/component/pc/gf_pc_state_util.h"
#include "gf/object/component/property/gf_com_property.h"
#include "gf/object/gf_obj.h"
#include "mm_math/mm_vec3.h"

namespace gf {
namespace pc {

TerrainDamagePlugin::TerrainDamagePlugin() : unknown0c(0.0f), unknown10(false) {}

bool TerrainDamagePlugin::setup(GfComBehaviorPc &) { return true; }

void TerrainDamagePlugin::cleanup(GfComBehaviorPc &) {}

void TerrainDamagePlugin::onActivate() { reset(); }

void TerrainDamagePlugin::reset() {
  unknown0c = 0.0f;
  unknown10 = false;
}

void TerrainDamagePlugin::onDeactivate() {}

void TerrainDamagePlugin::update(GfComBehaviorPc &behavior, const fw::UpdateInfo &info) {
  bool isDamage = unknown10;
  EnviromentSensor::GroundInfo *ground = StateUtil::getGroundInfo(behavior);
  EnviromentSensor::unknown001 *water = StateUtil::getWaterInfo(behavior);
  if (ground != nullptr && water != nullptr) {
    const GfFieldDmgManager::BdatInfo *damage = GfFieldDmgManager::get()->findBdatInfo(static_cast<u16>(water->unknown30));
    if (damage != nullptr) {
      GfComPropertyPc *property = behavior.unknown08->getComponent<GfComPropertyPc>();
      f32 range = unknown10 ? 3.0f : 0.0f;
      if (property->unknown160.unknown00.y - water->unknown00 <= range) {
        if (!unknown10) {
          onEnterDamage(behavior);
        }
        unknown0c += info.unknown04;
        if (unknown0c >= damage->unknown04) {
          unknown0c -= damage->unknown04;
          StateUtil::applyDamage(behavior, damage->unknown08, true);
        }
        return;
      }
    }
  }
  if (isDamage) {
    onLeaveDamage(behavior);
  }
}

void TerrainDamagePlugin::onEnterDamage(GfComBehaviorPc &behavior) {
  unknown10 = true;
  MsgObjectStopAutoHeal message(true);
  GfObj *obj = static_cast<GfObj *>(behavior.unknown08);
  obj->sendMessage(obj, message);
}

void TerrainDamagePlugin::onLeaveDamage(GfComBehaviorPc &behavior) {
  MsgObjectStopAutoHeal message(false);
  GfObj *obj = static_cast<GfObj *>(behavior.unknown08);
  obj->sendMessage(obj, message);
  reset();
}

} // namespace pc
} // namespace gf
