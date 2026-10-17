#include "gf/object/component/pc/field/gf_pc_state_field_move.h"

#include "framework/object/updatable_object.h"
#include "gf/object/component/pc/gf_com_behavior_pc.h"
#include "gf/object/component/pc/gf_com_property_pc.h"
#include "gf/object/component/pc/gf_pc_move_util_field.h"
#include "gf/object/component/pc/gf_pc_state_util.h"
#include "gf/object/component/pc/gf_pc_state_util_field.h"

namespace gf {
namespace pc {

void StateFieldMove::enter(GfComBehaviorPc *behavior, ai::State *previous) {
  GfComPropertyPc *property = behavior->owner->getComponent<GfComPropertyPc>();
  MoveUtilField::enterMoveRun(*property, false);
  StateUtilField::setAsmSpeedMove(*property);
  StateUtil::changePlacementDownDist(*behavior, 0.05f);
  StateUtil::setEnableDownIK(*behavior, false);
}

void StateFieldMove::leave(GfComBehaviorPc *behavior, ai::State *next) { StateUtil::resetPlacementDownDist(*behavior); }

} // namespace pc
} // namespace gf
