#include "gf/object/component/pc/plugin/gf_pc_terrain_damage_plugin.h"

#include "gf/object/component/property/gf_com_property.h"
#include "gf/object/gf_obj.h"

namespace gf {
namespace pc {

TerrainDamagePlugin::TerrainDamagePlugin() : damageTimer(0.0f), isInDamage(false) {}

bool TerrainDamagePlugin::setup(GfComBehaviorPc &) { return true; }

void TerrainDamagePlugin::cleanup(GfComBehaviorPc &) {}

void TerrainDamagePlugin::onActivate() { reset(); }

void TerrainDamagePlugin::reset() {
  damageTimer = 0.0f;
  isInDamage = false;
}

void TerrainDamagePlugin::onDeactivate() {}

void TerrainDamagePlugin::onEnterDamage(GfComBehaviorPc &behavior) {
  isInDamage = true;
  MsgObjectStopAutoHeal message(true);
  GfObj *obj = static_cast<GfObj *>(behavior.owner);
  obj->sendMessage(obj, message);
}

void TerrainDamagePlugin::onLeaveDamage(GfComBehaviorPc &behavior) {
  MsgObjectStopAutoHeal message(false);
  GfObj *obj = static_cast<GfObj *>(behavior.owner);
  obj->sendMessage(obj, message);
  reset();
}

} // namespace pc
} // namespace gf
