#include "gf/object/component/pc/field/gf_pc_state_field_turn.h"

#include "ai/ai_state.h"
#include "framework/object/updatable_object.h"
#include "gf/object/component/pc/gf_com_behavior_pc.h"
#include "gf/object/component/pc/gf_com_property_pc.h"
#include "gf/object/component/pc/gf_pc_move_util_field.h"
#include "gf/object/component/pc/gf_pc_state_id.h"
#include "gf/object/component/pc/gf_pc_state_util_field.h"
#include "mm_math/mm_vec3.h"

namespace gf {
namespace pc {

void StateFieldTurn::leave(GfComBehaviorPc *behavior, ai::State *next) {
  GfComPropertyPc *property = behavior->owner->getComponent<GfComPropertyPc>();
  if (next != nullptr && next->stateID != STATE_ID_FIELD_JUMP) {
    property->velocity = mm::Vec3::zero;
  }
  property->horizontalSpeed = 0.0f;
}

void StateFieldTurn::update(GfComBehaviorPc *behavior, const fw::UpdateInfo &info) {
  GfComPropertyPc *property = behavior->owner->getComponent<GfComPropertyPc>();
  if (StateUtilField::isTurnEndRangeCacheInput(*property, inputDirection)) {
    reqState(STATE_ID_FIELD_MOVE);
    return;
  }
  if (isWalkTurn) {
    MoveUtilField::updateMoveWalkTurn(info, *property, inputDirection);
  } else {
    MoveUtilField::updateMoveTurn(info, *property, inputDirection);
  }
}

} // namespace pc
} // namespace gf
