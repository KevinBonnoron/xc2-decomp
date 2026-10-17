#include "gf/object/component/pc/field/gf_pc_state_field_water.h"

#include "gf/object/component/pc/gf_pc_state_util.h"
#include "gf/object/component/pc/gf_pc_state_util_field.h"

namespace gf {
namespace pc {

void StateFieldWater::leave(GfComBehaviorPc *behavior, ai::State *next) {
  StateUtilField::setWaterMode(*behavior, false);
  StateUtil::setEnableLookIK(*behavior, true);
  StateUtilField::setLookAtFlag(*behavior, true);
}

} // namespace pc
} // namespace gf
