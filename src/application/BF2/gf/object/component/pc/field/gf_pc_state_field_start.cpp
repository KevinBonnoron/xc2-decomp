#include "gf/object/component/pc/field/gf_pc_state_field_start.h"

#include "gf/object/component/pc/gf_com_behavior_pc.h"
#include "gf/object/component/pc/gf_com_property_pc.h"
#include "gf/object/component/pc/gf_pc_state_util.h"
#include "gf/object/component/pc/gf_pc_state_util_field.h"
#include "gf/object/gf_obj_handle.h"

namespace gf {
namespace pc {

void StateFieldStart::enter(GfComBehaviorPc *behavior, ai::State *previous) {
  StateUtilField::setSpecialActStatus(*behavior, true);
  if (!behavior->getProperty()->isPadControl) {
    StateUtil::setTarget(*behavior, INVALID_HANDLE);
  }
}

void StateFieldStart::leave(GfComBehaviorPc *behavior, ai::State *next) { StateUtilField::setSpecialActStatus(*behavior, false); }

} // namespace pc
} // namespace gf
