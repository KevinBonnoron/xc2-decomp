#include "gf/object/component/pc/field/gf_pc_state_field_slide_move.h"

#include "gf/object/component/pc/gf_pc_state_util.h"
#include "mm_math/mm_vec3.h"

namespace gf {
namespace pc {

void StateFieldSlideMove::leave(GfComBehaviorPc *behavior, ai::State *next) { StateUtil::changeGroundAnglesForMotion(*behavior, mm::Vec3::zero); }

} // namespace pc
} // namespace gf
