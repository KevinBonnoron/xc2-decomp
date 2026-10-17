#include "gf/object/component/pc/field/gf_pc_state_field_extra_control.h"

#include "gf/object/component/pc/gf_pc_state_util.h"

namespace gf {
namespace pc {

void StateFieldExtraControl::leave(GfComBehaviorPc *behavior, ai::State *next) { StateUtil::setEnableDownIK(*behavior, false); }

} // namespace pc
} // namespace gf
