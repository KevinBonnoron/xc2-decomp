#include "gf/object/component/pc/field/gf_pc_state_field_wall_land.h"

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

void StateFieldWallLand::enter(GfComBehaviorPc *behavior, ai::State *previous) {}

void StateFieldWallLand::leave(GfComBehaviorPc *behavior, ai::State *next) {}

void StateFieldWallLand::update(GfComBehaviorPc *behavior, const fw::UpdateInfo &info) {
  GfComPropertyPc *property = behavior->unknown08->getComponent<GfComPropertyPc>();
  GfComAsm *comAsm = behavior->unknown08->getComponent<GfComAsm>();
  const anm::QsTransform &locomotion = comAsm->getLocomotion();
  unknown009(*property, locomotion);
  // Statement without effect the game holds (0x710055ab80, ruling 5): it loads the param list pointer at 0x318 and asserts
  // `_ptr != 0` before the height update; nothing uses the pointer and the original statement that did is gone.
  property->m_propertyField.unknown08.operator->();
  property->m_propertyField.unknown18 -= locomotion.unknown00.z;
  if (comAsm->isEnd(ANIM_LAYER_UNKNOWN_0) && StateUtilField::execAsmCmd(*comAsm, ASM_CMD_ID_FIELD_IDLE)) {
    reqState(STATE_ID_UNKNOWN_3);
  }
}

} // namespace pc
} // namespace gf
