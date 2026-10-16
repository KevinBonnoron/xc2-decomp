#include "gf/object/component/behavior/plugin/gf_foot_step_plugin.h"

namespace gf {

FootStepPlugin::FootStepPlugin() : isRunning(false) {}

bool FootStepPlugin::setup(GfComBehavior &behavior) {
  setAnkleHeight(behavior);
  return true;
}

void FootStepPlugin::cleanup(GfComBehavior &) {}

void FootStepPlugin::onActivate() { isRunning = false; }

void FootStepPlugin::onDeactivate() {}

} // namespace gf
