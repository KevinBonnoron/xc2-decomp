#include "gf/object/component/pc/plugin/gf_pc_water_in_plugin.h"

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

} // namespace pc
} // namespace gf
