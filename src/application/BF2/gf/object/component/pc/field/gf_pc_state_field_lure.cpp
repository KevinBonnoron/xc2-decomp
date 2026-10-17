#include "gf/object/component/pc/field/gf_pc_state_field_lure.h"

#include "gf/object/component/pc/gf_pc_state_util_field.h"

namespace gf {
namespace pc {

void StateFieldLure::leave(GfComBehaviorPc *behavior, ai::State *next) { StateUtilField::setEnableLure(*behavior, false); }

} // namespace pc
} // namespace gf
