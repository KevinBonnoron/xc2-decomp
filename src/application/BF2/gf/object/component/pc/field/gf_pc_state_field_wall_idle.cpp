#include "gf/object/component/pc/field/gf_pc_state_field_wall_idle.h"

#include "framework/object/updatable_object.h"
#include "gf/object/component/animation/gf_com_asm.h"
#include "gf/object/component/pc/gf_com_behavior_pc.h"
#include "gf/object/component/pc/gf_com_property_pc.h"
#include "gf/object/component/pc/gf_pc_property_field.h"
#include "gf/object/component/pc/gf_pc_state_id.h"
#include "gf/object/component/pc/gf_pc_state_util_field.h"
#include "mm_math/mm_vec3.h"

namespace gf {
namespace pc {

void StateFieldWallIdle::enter(GfComBehaviorPc *behavior, ai::State *previous) {
  GfComPropertyPc *property = behavior->unknown08->getComponent<GfComPropertyPc>();
  property->unknown80 = mm::Vec3::zero;
}

void StateFieldWallIdle::leave(GfComBehaviorPc *behavior, ai::State *next) {}

void StateFieldWallIdle::update(GfComBehaviorPc *behavior, const fw::UpdateInfo &info) {
  GfComPropertyPc *property = behavior->unknown08->getComponent<GfComPropertyPc>();
  GfPropertyField::WALL_MOVE_MODE mode = StateUtilField::decideWallMoveMode(*property);
  if (StateUtilField::isMovableWall(*property, mode)) {
    GfComAsm *comAsm = behavior->unknown08->getComponent<GfComAsm>();
    if (StateUtilField::execAsmCmd(*comAsm, StateUtilField::getAsmID(mode))) {
      property->unknown310.unknown14 = mode;
      reqState(STATE_ID_UNKNOWN_47);
    }
  } else if (!StateUtilField::isWallUpMove(mode)) {
    property->unknown310.unknown10_7 = false;
  }
}

} // namespace pc
} // namespace gf
