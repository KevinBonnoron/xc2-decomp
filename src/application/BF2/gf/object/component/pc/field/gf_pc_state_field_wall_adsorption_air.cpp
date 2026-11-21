#include "gf/object/component/pc/field/gf_pc_state_field_wall_adsorption_air.h"

#include "framework/object/updatable_object.h"
#include "fw/fw_param_manager.h"
#include "fw/fw_update_info.h"
#include "gf/object/component/pc/field/gf_pc_param_field.h"
#include "gf/object/component/pc/gf_com_behavior_pc.h"
#include "gf/object/component/pc/gf_com_property_pc.h"
#include "gf/object/component/pc/gf_pc_property_field.h"
#include "gf/object/component/pc/gf_pc_state_id.h"
#include "gf/object/component/pc/gf_pc_state_util_field.h"

namespace gf {
namespace pc {

void StateFieldWallAdsorptionAir::enter(GfComBehaviorPc *behavior, ai::State *previous) {
  unknown18 = 0.0f;
  unknown1c = behavior->getProperty()->unknown310.unknown18;
  StateUtilField::resetCameraForWall(*behavior, StateUtilField::TIMING_UNKNOWN_2);
}

void StateFieldWallAdsorptionAir::leave(GfComBehaviorPc *behavior, ai::State *next) {}

// Inferred name; kept as an exception to the unknown-name rule (AGENTS.md): single-user helper whose existence only the match proves; rename if a sibling build gives a symbol.
// Gets the wall param of the pc param list (entry 15, "wall_common") from the property component. Single user: StateFieldWallAdsorptionAir::update (1.0.0: 0x710055a800, 66 instructions), which keeps
// the null test of the property component (cbz x21 at 0x710055a820, joining at the param list read). Forms tried without the helper: the param read directly after getComponent<GfComPropertyPc>(),
// and a helper taking the GfPropertyField, both give 65 instructions (test dropped). The cause is written at UpdatableObject::getComponent.
static const WallCommonParam *getWallParam(GfComPropertyPc *property) { return property->unknown310.unknown004(15).get<WallCommonParam>(); }

void StateFieldWallAdsorptionAir::update(GfComBehaviorPc *behavior, const fw::UpdateInfo &info) {
  GfComPropertyPc *property = behavior->unknown08->getComponent<GfComPropertyPc>();
  pc::GfPropertyField &field = property->unknown310;
  const WallCommonParam *param = getWallParam(property);
  unknown18 += info.unknown04;
  if (unknown18 >= param->adsorptionTime) {
    reqState(STATE_ID_UNKNOWN_46);
  } else {
    f32 ratio = unknown18 / param->adsorptionTime;
    field.unknown18 = unknown1c * (1.0f - ratio) + field.unknown4c * ratio;
  }
}

} // namespace pc
} // namespace gf
