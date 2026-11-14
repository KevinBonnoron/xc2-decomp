#include "gf/object/component/pc/field/gf_pc_state_field_turn.h"

#include <math.h>

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

void StateFieldTurn::enter(GfComBehaviorPc *behavior, ai::State *previous) {
  GfComPropertyPc *property = behavior->unknown08->getComponent<GfComPropertyPc>();
  StateUtilField::setAsmSpeedMove(*property);
  property->unknown80 = mm::Vec3::zero;
  property->unknown94 = 0.0f;
  unknown18 = previous->unknown08 != STATE_ID_UNKNOWN_7;
  unknown20 = property->unknown2b0 * property->unknown60.unknown04 + property->unknown2d0 * property->unknown60.unknown00;
  if (!(fabsf(unknown20.x) <= 0.000001f) || !(fabsf(unknown20.y) <= 0.000001f) || !(fabsf(unknown20.z) <= 0.000001f)) {
    unknown20.unknown001();
  } else {
    unknown20 = property->unknown1f0;
  }
  StateUtilField::notifyTurn(*behavior);
}

void StateFieldTurn::leave(GfComBehaviorPc *behavior, ai::State *next) {
  GfComPropertyPc *property = behavior->unknown08->getComponent<GfComPropertyPc>();
  if (next != nullptr && next->unknown08 != STATE_ID_UNKNOWN_12) {
    property->unknown80 = mm::Vec3::zero;
  }
  property->unknown94 = 0.0f;
}

void StateFieldTurn::update(GfComBehaviorPc *behavior, const fw::UpdateInfo &info) {
  GfComPropertyPc *property = behavior->unknown08->getComponent<GfComPropertyPc>();
  if (StateUtilField::isTurnEndRangeCacheInput(*property, unknown20)) {
    reqState(STATE_ID_UNKNOWN_7);
    return;
  }
  if (unknown18) {
    MoveUtilField::updateMoveWalkTurn(info, *property, unknown20);
  } else {
    MoveUtilField::updateMoveTurn(info, *property, unknown20);
  }
}

} // namespace pc
} // namespace gf
