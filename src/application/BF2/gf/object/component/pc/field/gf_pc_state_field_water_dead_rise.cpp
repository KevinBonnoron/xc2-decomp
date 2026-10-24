#include "gf/object/component/pc/field/gf_pc_state_field_water_dead_rise.h"

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

void StateFieldWaterDeadRise::enter(GfComBehaviorPc *behavior, ai::State *previous) { behavior->getProperty()->unknown90 = 0.0f; }

void StateFieldWaterDeadRise::leave(GfComBehaviorPc *behavior, ai::State *next) {}

void StateFieldWaterDeadRise::update(GfComBehaviorPc *behavior, const fw::UpdateInfo &info) {
  GfComPropertyPc *property = behavior->unknown08->getComponent<GfComPropertyPc>();
  MoveUtilField::updateMoveWaterRise(info, *property);
  f32 distance = info.unknown04 * property->unknown90;
  if (StateUtilField::getChildFrameHeight(*behavior) + distance >= 0.0f) {
    reqState(STATE_ID_FIELD_WATER_DEAD_IDLE);
  }
}

} // namespace pc
} // namespace gf
