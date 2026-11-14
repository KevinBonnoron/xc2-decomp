#include "gf/object/component/pc/field/gf_pc_state_field_wall_adsorption_under_ground.h"

#include "framework/object/updatable_object.h"
#include "gf/object/component/pc/gf_com_behavior_pc.h"
#include "gf/object/component/pc/gf_com_property_pc.h"
#include "gf/object/component/pc/gf_pc_property_field.h"
#include "gf/object/component/pc/gf_pc_state_util.h"
#include "gf/object/component/pc/gf_pc_state_util_field.h"

namespace gf {
namespace pc {

void StateFieldWallAdsorptionUnderGround::enter(GfComBehaviorPc *behavior, ai::State *previous) {
  GfComPropertyPc *property = behavior->unknown08->getComponent<GfComPropertyPc>();
  unknown18 = property->unknown310.unknown18;
  unknown20 = mm::Vec3::zero;
  unknown30 = mm::Quat::identity;
  if (property->unknown38 == 0) {
    property->unknown310.unknown10_7 = true;
  }
  property->unknown310.unknown12_0 = true;
  StateUtil::setEnvSensor(*behavior, 0x40, false);
  StateUtilField::resetCameraForWall(*behavior, StateUtilField::TIMING_UNKNOWN_0);
}

void StateFieldWallAdsorptionUnderGround::leave(GfComBehaviorPc *behavior, ai::State *next) {
  StateUtil::setEnvSensor(*behavior, 0x40, true);
  behavior->getProperty()->unknown310.unknown12_0 = false;
}

} // namespace pc
} // namespace gf
