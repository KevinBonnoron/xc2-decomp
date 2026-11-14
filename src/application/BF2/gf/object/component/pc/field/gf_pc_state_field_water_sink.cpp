#include "gf/object/component/pc/field/gf_pc_state_field_water_sink.h"

#include "framework/object/updatable_object.h"
#include "fw/fw_update_info.h"
#include "gf/object/component/pc/field/gf_pc_param_field.h"
#include "gf/object/component/pc/gf_com_behavior_pc.h"
#include "gf/object/component/pc/gf_com_property_pc.h"
#include "gf/object/component/pc/gf_pc_move_util_field.h"
#include "gf/object/component/pc/gf_pc_property_field.h"
#include "gf/object/component/pc/gf_pc_state_id.h"
#include "gf/object/component/pc/gf_pc_state_util_field.h"
#include "mm_math/mm_vec3.h"

namespace gf {
namespace pc {

void StateFieldWaterSink::enter(GfComBehaviorPc *behavior, ai::State *previous) {
  GfComPropertyPc *property = behavior->unknown08->getComponent<GfComPropertyPc>();
  property->unknown80 = mm::Vec3::zero;
  unknown18 = 0.0f;
}

void StateFieldWaterSink::leave(GfComBehaviorPc *behavior, ai::State *next) {}

void StateFieldWaterSink::update(GfComBehaviorPc *behavior, const fw::UpdateInfo &info) {
  GfComPropertyPc *property = behavior->unknown08->getComponent<GfComPropertyPc>();
  const WaterCommonParam *param = property->unknown310.unknown005();
  unknown18 += info.unknown04;
  if (property->unknown110_4 || unknown18 >= param->sinkTime) {
    reqState(STATE_ID_UNKNOWN_26);
  } else if (StateUtilField::getChildFrameHeight(*behavior) <= -param->sinkDepth) {
    property->unknown90 = 0.0f;
  } else {
    MoveUtilField::updateMoveWaterSink(info, *property);
  }
}

} // namespace pc
} // namespace gf
