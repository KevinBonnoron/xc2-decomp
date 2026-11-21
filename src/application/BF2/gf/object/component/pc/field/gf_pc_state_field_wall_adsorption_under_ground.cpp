#include "gf/object/component/pc/field/gf_pc_state_field_wall_adsorption_under_ground.h"

#include "anm/anm_qs_transform.h"
#include "framework/object/updatable_object.h"
#include "gf/object/component/animation/gf_com_asm.h"
#include "gf/object/component/pc/gf_com_behavior_pc.h"
#include "gf/object/component/pc/gf_com_property_pc.h"
#include "gf/object/component/pc/gf_pc_asm_cmd_id_field.h"
#include "gf/object/component/pc/gf_pc_property_field.h"
#include "gf/object/component/pc/gf_pc_state_id.h"
#include "gf/object/component/pc/gf_pc_state_util.h"
#include "gf/object/component/pc/gf_pc_state_util_field.h"
#include "mm_math/mm_vec4.h"

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

void StateFieldWallAdsorptionUnderGround::update(GfComBehaviorPc *behavior, const fw::UpdateInfo &info) {
  GfComPropertyPc *property = behavior->unknown08->getComponent<GfComPropertyPc>();
  GfComAsm *comAsm = behavior->unknown08->getComponent<GfComAsm>();
  const anm::QsTransform &locomotion = comAsm->getLocomotion();
  unknown009(*property, locomotion);
  unknown20 = unknown20 + unknown30.rotate(mm::Vec3(locomotion.unknown00.x, locomotion.unknown00.y, locomotion.unknown00.z));
  unknown30 = mm::Quat::mul(unknown30, locomotion.unknown10);
  property->unknown310.unknown18 = unknown18 + unknown20.z < property->unknown310.unknown4c ? unknown18 + unknown20.z : property->unknown310.unknown4c;
  if (comAsm->isEnd(ANIM_LAYER_UNKNOWN_0) && StateUtilField::execAsmCmd(*comAsm, ASM_CMD_ID_FIELD_CLIMBIDLE)) {
    reqState(STATE_ID_UNKNOWN_46);
  }
}

} // namespace pc
} // namespace gf
