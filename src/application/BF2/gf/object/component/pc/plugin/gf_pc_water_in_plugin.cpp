#include "gf/object/component/pc/plugin/gf_pc_water_in_plugin.h"

#include "framework/object/updatable_object.h"
#include "gf/object/component/env_sensor/gf_com_env_sensor.h"
#include "gf/object/component/pc/gf_com_property_pc.h"
#include "mm_math/mm_vec3.h"

namespace gf {
namespace pc {

WaterInPlugin::WaterInPlugin() : unknown10(nullptr), unknown18(false) {}

WaterInPlugin::~WaterInPlugin() {}

bool WaterInPlugin::setup(GfComBehaviorPc &behavior) {
  this->unknown10 = &behavior;
  return true;
}

void WaterInPlugin::cleanup(GfComBehaviorPc &) { unknown10 = nullptr; }

void WaterInPlugin::onActivate() { unknown18 = false; }

void WaterInPlugin::onDeactivate() {
  if (!unknown18) {
    GfComEnvSensor *envSensor = unknown10->unknown08->getComponent<GfComEnvSensor>();
    GfComPropertyPc *property = unknown10->unknown08->getComponent<GfComPropertyPc>();
    if (envSensor != nullptr && property != nullptr && envSensor->unknown10.unknown24_1 && envSensor->unknown10.unknown30.unknown70.unknown00 >= property->unknown160.y) {
      onEvent(*unknown10);
    }
  }
}

void WaterInPlugin::update(GfComBehaviorPc &behavior, const fw::UpdateInfo &) {
  if (!unknown18) {
    GfComEnvSensor *envSensor = behavior.unknown08->getComponent<GfComEnvSensor>();
    GfComPropertyPc *property = behavior.unknown08->getComponent<GfComPropertyPc>();
    if (envSensor != nullptr && property != nullptr && envSensor->unknown10.unknown24_1) {
      if (property->unknown160.y < property->unknown180.y && property->unknown180.y > envSensor->unknown10.unknown30.unknown70.unknown00 &&
          envSensor->unknown10.unknown30.unknown70.unknown00 >= property->unknown160.y) {
        onEvent(behavior);
      }
    }
  }
}

} // namespace pc
} // namespace gf
