#include "gf/object/component/pc/field/gf_pc_state_field_wall_prepare_jump.h"

#include "gf/object/component/pc/gf_pc_state_util_field.h"

namespace gf {
namespace pc {

void StateFieldWallPrepareJump::leave(GfComBehaviorPc *behavior, ai::State *next) {
  StateUtilField::setSpecialActStatus(*behavior, false);
  StateUtilField::setAccessFlag(*behavior, false);
}

} // namespace pc
} // namespace gf
