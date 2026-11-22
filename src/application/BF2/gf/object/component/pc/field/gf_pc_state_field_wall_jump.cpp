#include "gf/object/component/pc/field/gf_pc_state_field_wall_jump.h"

#include "framework/object/updatable_object.h"
#include "gf/object/component/pc/gf_com_behavior_pc.h"
#include "gf/object/component/pc/gf_com_property_pc.h"
#include "gf/object/component/pc/gf_pc_property_field.h"
#include "gf/object/component/pc/gf_pc_state_util.h"
#include "gf/object/component/pc/gf_pc_state_util_field.h"
#include "gf/scom/gf_scom_obj.h"

namespace gf {
namespace pc {

void StateFieldWallJump::enter(GfComBehaviorPc *behavior, ai::State *previous) {
  StateUtil::setEnableGravity(*behavior, false);
  StateUtilField::setSpecialActStatus(*behavior, true);
  StateUtilField::notifySkillAct(*behavior, true);
  behavior->getProperty()->unknown120 = 0;
}

void StateFieldWallJump::leave(GfComBehaviorPc *behavior, ai::State *next) {
  StateUtilField::setSpecialActStatus(*behavior, false);
  StateUtilField::notifySkillAct(*behavior, false);
  GfComPropertyPc *property = behavior->unknown08->getComponent<GfComPropertyPc>();
  const MsgPcFieldNotifyWallJump *info = property->m_propertyField.getWallJumpInfo();
  if (info != nullptr) {
    if (property->unknown111_2) {
      SCOM_QUEST_GIMMICK::createJump(info->unknown2c, 0.0f);
    }
    property->m_propertyField.setWallJump(nullptr);
  }
  property->unknown120 = 2;
}

void StateFieldWallJump::update(GfComBehaviorPc *behavior, const fw::UpdateInfo &info) {}

} // namespace pc
} // namespace gf
