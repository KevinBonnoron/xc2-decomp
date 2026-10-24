#include "gf/object/component/pc/field/gf_pc_state_field_water_swim.h"

#include "framework/object/updatable_object.h"
#include "gf/object/component/pc/gf_com_behavior_pc.h"
#include "gf/object/component/pc/gf_com_property_pc.h"
#include "gf/object/component/pc/gf_pc_move_util_field.h"

namespace gf {
namespace pc {

void StateFieldWaterSwim::enter(GfComBehaviorPc *behavior, ai::State *previous) { MoveUtilField::enterMoveSwim(*behavior->owner->getComponent<GfComPropertyPc>()); }

void StateFieldWaterSwim::leave(GfComBehaviorPc *behavior, ai::State *next) {}

} // namespace pc
} // namespace gf
