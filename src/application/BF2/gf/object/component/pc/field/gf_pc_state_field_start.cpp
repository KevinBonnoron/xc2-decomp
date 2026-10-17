#include "gf/object/component/pc/field/gf_pc_state_field_start.h"

#include "gf/object/component/pc/gf_pc_state_util_field.h"

namespace gf {
namespace pc {

void StateFieldStart::leave(GfComBehaviorPc *behavior, ai::State *next) { StateUtilField::setSpecialActStatus(*behavior, false); }

} // namespace pc
} // namespace gf
