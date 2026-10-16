#include "gf/object/component/pc/plugin/gf_pc_water_in_plugin.h"

namespace gf {
namespace pc {

WaterInPlugin::WaterInPlugin() : behavior(nullptr), isEventDone(false) {}

WaterInPlugin::~WaterInPlugin() {}

bool WaterInPlugin::setup(GfComBehaviorPc &behavior) {
  this->behavior = &behavior;
  return true;
}

void WaterInPlugin::cleanup(GfComBehaviorPc &) { behavior = nullptr; }

void WaterInPlugin::onActivate() { isEventDone = false; }

} // namespace pc
} // namespace gf
