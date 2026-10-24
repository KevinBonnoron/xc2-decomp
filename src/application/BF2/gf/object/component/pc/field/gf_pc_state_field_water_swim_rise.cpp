#include "gf/object/component/pc/field/gf_pc_state_field_water_swim_rise.h"

#include "framework/object/updatable_object.h"
#include "fw/fw_update_info.h"
#include "gf/object/component/pc/gf_com_behavior_pc.h"
#include "gf/object/component/pc/gf_com_property_pc.h"
#include "gf/object/component/pc/gf_pc_move_util_field.h"
#include "gf/object/component/pc/gf_pc_state_id.h"
#include "gf/object/component/pc/gf_pc_state_util_field.h"
#include "types.h"

namespace gf {
namespace pc {

void StateFieldWaterSwimRise::enter(GfComBehaviorPc *behavior, ai::State *previous) { behavior->getProperty()->unknown90 = 0.0f; }

void StateFieldWaterSwimRise::leave(GfComBehaviorPc *behavior, ai::State *next) {}

void StateFieldWaterSwimRise::update(GfComBehaviorPc *behavior, const fw::UpdateInfo &info) {
  GfComPropertyPc *property = behavior->owner->getComponent<GfComPropertyPc>();
  MoveUtilField::updateMoveSwim(info, *property);
  MoveUtilField::updateMoveWaterRise(info, *property);
  f32 distance = info.deltaTime * property->unknown90;
  if (StateUtilField::getChildFrameHeight(*behavior) + distance >= 0.0f) {
    reqState(STATE_ID_FIELD_WATER_SWIM);
  }
}

} // namespace pc
} // namespace gf
