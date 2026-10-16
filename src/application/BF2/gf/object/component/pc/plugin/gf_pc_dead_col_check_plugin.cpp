#include "gf/object/component/pc/plugin/gf_pc_dead_col_check_plugin.h"

namespace gf {
namespace pc {

DeadColCheckPlugin::DeadColCheckPlugin() {}

bool DeadColCheckPlugin::setup(GfComBehaviorPc &) { return true; }

void DeadColCheckPlugin::cleanup(GfComBehaviorPc &) {}

void DeadColCheckPlugin::onActivate() {}

void DeadColCheckPlugin::onDeactivate() {}

} // namespace pc
} // namespace gf
