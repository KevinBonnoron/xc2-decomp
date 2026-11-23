#include "gf/object/component/pc/field/gf_pc_state_field_wall_adsorption_ground.h"

#include "anm/anm_qs_transform.h"
#include "framework/object/updatable_object.h"
#include "gf/object/component/animation/gf_com_asm.h"
#include "gf/object/component/pc/gf_com_behavior_pc.h"
#include "gf/object/component/pc/gf_com_property_pc.h"
#include "gf/object/component/pc/gf_pc_asm_cmd_id_field.h"
#include "gf/object/component/pc/gf_pc_property_field.h"
#include "gf/object/component/pc/gf_pc_state_id.h"
#include "gf/object/component/pc/gf_pc_state_util_field.h"
#include "mm_math/mm_vec4.h"
#include "mm_mtl/intrusive_ptr.h"

namespace gf {
namespace pc {

void StateFieldWallAdsorptionGround::enter(GfComBehaviorPc *behavior, ai::State *previous) { StateUtilField::resetCameraForWall(*behavior, StateUtilField::TIMING_UNKNOWN_1); }

void StateFieldWallAdsorptionGround::leave(GfComBehaviorPc *behavior, ai::State *next) {}

void StateFieldWallAdsorptionGround::update(GfComBehaviorPc *behavior, const fw::UpdateInfo &info) {
  GfComPropertyPc *property = behavior->unknown08->getComponent<GfComPropertyPc>();
  GfComAsm *comAsm = behavior->unknown08->getComponent<GfComAsm>();
  const anm::QsTransform &locomotion = comAsm->getLocomotion();
  unknown009(*property, locomotion);
  // Statement without effect the game holds (0x710055a1b8, ruling 5): it loads the param list pointer at 0x318 and asserts
  // `_ptr != 0` before the height update; nothing uses the pointer and the original statement that did is gone.
  property->m_propertyField.unknown08.operator->();
  property->m_propertyField.unknown18 -= locomotion.unknown00.z;
  property->m_propertyField.unknown18 = property->m_propertyField.unknown18 > property->m_propertyField.unknown4c ? property->m_propertyField.unknown18 : property->m_propertyField.unknown4c;
  if (comAsm->isEnd(ANIM_LAYER_UNKNOWN_0) && StateUtilField::execAsmCmd(*comAsm, ASM_CMD_ID_FIELD_CLIMBIDLE)) {
    reqState(STATE_ID_UNKNOWN_46);
  }
}

} // namespace pc
} // namespace gf
