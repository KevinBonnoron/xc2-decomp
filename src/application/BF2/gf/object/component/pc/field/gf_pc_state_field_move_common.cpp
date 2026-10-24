#include "gf/object/component/pc/field/gf_pc_state_field_move_common.h"

#include "framework/object/updatable_object.h"
#include "gf/object/component/animation/gf_com_asm.h"
#include "gf/object/component/pc/gf_com_behavior_pc.h"
#include "gf/object/component/pc/gf_com_property_pc.h"
#include "gf/object/component/pc/gf_pc_state_id.h"
#include "gf/object/component/pc/gf_pc_state_util_field.h"

namespace gf {
namespace pc {

void StateFieldMoveCommon::enter(GfComBehaviorPc *behavior, ai::State *previous) { unknown18 = 0; }

void StateFieldMoveCommon::leave(GfComBehaviorPc *behavior, ai::State *next) { behavior->owner->getComponent<GfComPropertyPc>(); }

void StateFieldMoveCommon::update(GfComBehaviorPc *behavior, const fw::UpdateInfo &info) {
  GfComPropertyPc *property = behavior->owner->getComponent<GfComPropertyPc>();
  unknown18 = property->existInputXY() ? 0 : unknown18 + 1;
  behavior->owner->getComponent<GfComAsm>();
  if (StateUtilField::isStop(*property, unknown18)) {
    reqState(STATE_ID_FIELD_STOP_BRAKE);
  }
}

} // namespace pc
} // namespace gf
