#include "gf/object/component/pc/field/gf_pc_state_field_move.h"

#include "gf/object/component/pc/gf_pc_state_util.h"

namespace gf {
namespace pc {

void StateFieldMove::leave(GfComBehaviorPc *behavior, ai::State *next) { StateUtil::resetPlacementDownDist(*behavior); }

} // namespace pc
} // namespace gf
