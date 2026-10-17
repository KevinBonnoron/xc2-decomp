#include "gf/object/component/pc/field/gf_pc_state_field_air.h"

#include "gf/object/component/pc/gf_pc_state_util.h"
#include "gf/object/component/pc/gf_pc_state_util_field.h"

namespace gf {
namespace pc {

void StateFieldAir::enter(GfComBehaviorPc *behavior, ai::State *previous) {
  StateUtil::setEnableGravity(*behavior, false);
  StateUtilField::setEnableFallIntoColi(*behavior, true);
  StateUtilField::setAirStatus(*behavior, true);
  StateUtilField::setEnableWaterIn(*behavior, true);
  StateUtil::setEnableFallDistChecker(*behavior, true);
}

} // namespace pc
} // namespace gf
