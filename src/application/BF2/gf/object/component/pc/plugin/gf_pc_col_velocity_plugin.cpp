#include "gf/object/component/pc/plugin/gf_pc_col_velocity_plugin.h"

namespace gf {
namespace pc {

ColVelCalculatorPlugin::ColVelCalculatorPlugin() : isFirstFrame(true) {}

void ColVelCalculatorPlugin::onActivate() { isFirstFrame = true; }

} // namespace pc
} // namespace gf
