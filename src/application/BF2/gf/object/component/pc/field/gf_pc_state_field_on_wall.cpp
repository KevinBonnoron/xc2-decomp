#include "gf/object/component/pc/field/gf_pc_state_field_on_wall.h"

#include "ai/ai_state.h"
#include "framework/message/message_object.h"
#include "framework/object/updatable_object.h"
#include "fw/fw_transform.h"
#include "gf/object/component/animation/gf_com_asm.h"
#include "gf/object/component/behavior/gf_com_behavior.h"
#include "gf/object/component/pc/gf_com_behavior_pc.h"
#include "gf/object/component/pc/gf_com_property_pc.h"
#include "gf/object/component/pc/gf_pc_asm_cmd_id_field.h"
#include "gf/object/component/pc/gf_pc_property_field.h"
#include "gf/object/component/pc/gf_pc_state_id.h"
#include "gf/object/component/pc/gf_pc_state_util.h"
#include "gf/object/component/pc/gf_pc_state_util_field.h"
#include "gf/object/component/pc/plugin/gf_pc_access_plugin.h"
#include "gf/object/gf_obj.h"
#include "mm_math/mm_plane.h"
#include "mm_math/mm_quat.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/bitflag.h"

namespace gf {
namespace pc {

void StateFieldOnWall::enter(GfComBehaviorPc *behavior, ai::State *previous) {
  GfComPropertyPc *property = behavior->unknown08->getComponent<GfComPropertyPc>();
  property->m_propertyField.unknown10_5 = true;
  StateUtilField::setAccessFlag(*behavior, true);
  StateUtil::setEnvSensor(*behavior, 0x100, true);
  property->m_propertyField.unknown18 = property->m_propertyField.unknown4c;
  unknown20 = *property->m_propertyField.unknown003();
  MsgPcFieldNotifyWall message;
  message.unknown10 = unknown20.unknown00;
  message.m_transform.unknown00 = property->unknown160.unknown00;
  message.m_transform.unknown10 = property->unknown160.unknown10;
  message.unknown50 = 0;
  StateUtilField::sendMessageWallChilds(*property, message);
  AccessPlugin *plugin = behavior->unknown001<AccessPlugin>(4);
  if (plugin != nullptr) {
    plugin->unknown28 = 8;
  }
}

void StateFieldOnWall::leave(GfComBehaviorPc *behavior, ai::State *next) {
  GfComPropertyPc *property = behavior->unknown08->getComponent<GfComPropertyPc>();
  property->m_propertyField.unknown10_5 = false;
  StateUtil::setEnvSensor(*behavior, 0x100, false);
  if (next != nullptr && next->m_state != STATE_ID_UNKNOWN_48) {
    StateUtilField::setAccessFlag(*behavior, false);
    u32 type = next->m_state == STATE_ID_UNKNOWN_15 ? 2 : 1;
    MsgPcFieldNotifyWall message;
    message.unknown10 = unknown20.unknown00;
    message.m_transform.unknown00 = property->unknown160.unknown00;
    message.m_transform.unknown10 = property->unknown160.unknown10;
    message.unknown50 = type;
    if (next->m_state == STATE_ID_UNKNOWN_43) {
      EnviromentSensor::GroundInfo *ground = StateUtil::getClimbEndGroundInfo(*behavior);
      if (ground != nullptr) {
        message.m_transform.unknown00.y = ground->unknown00.y;
      }
    }
    StateUtilField::sendMessageWallChilds(*property, message);
  }
  AccessPlugin *plugin = behavior->unknown001<AccessPlugin>(4);
  if (plugin != nullptr) {
    plugin->unknown28 = 0;
  }
}

void StateFieldOnWall::update(GfComBehaviorPc *behavior, const fw::UpdateInfo &info) {
  GfComPropertyPc *property = behavior->unknown08->getComponent<GfComPropertyPc>();
  if (StateUtilField::isWallDetach(*property) && StateUtilField::execAsmCmd(*behavior->unknown08->getComponent<GfComAsm>(), ASM_CMD_ID_FIELD_DOWNLANDING_01)) {
    reqState(STATE_ID_UNKNOWN_44);
    return;
  }

  GfObj *target = StateUtilField::getAccessTarget(*behavior);
  if (target != nullptr && property->unknown60.unknown08.test(INPUT_ID_UNKNOWN_0)) {
    MsgPcFieldGetAccessType message;
    static_cast<GfObj *>(behavior->unknown08)->sendMessage(target, message);
    if (message.unknown08 == 3) {
      reqState(STATE_ID_UNKNOWN_48);
      return;
    }
  }

  if (StateUtilField::isWallFall(*property) && StateUtilField::execAsmCmd(*behavior->unknown08->getComponent<GfComAsm>(), ASM_CMD_ID_FIELD_FALL)) {
    reqState(STATE_ID_UNKNOWN_15);
    return;
  }

  EnviromentSensor::unknown003 *wallInfo = StateUtil::getClimbWallInfo(*behavior);
  if (wallInfo != nullptr) {
    property->m_propertyField.unknown130 = *wallInfo;
    property->m_propertyField.unknown10_6 = true;
    unknown20 = *wallInfo;
  }
}

bool StateFieldOnWall::recieveMessage(void *owner, fw::MessageObject *sender, fw::Message &message) {
  if (message.unknown00 == MSG_PC_FIELD_UNKNOWN_16777235) {
    procMsgPcFieldWallJump(static_cast<GfComBehaviorPc *>(owner), sender, static_cast<MsgPcFieldWallJump &>(message));
    return true;
  }

  return false;
}

void StateFieldOnWall::procMsgPcFieldWallJump(GfComBehaviorPc *behavior, fw::MessageObject *sender, MsgPcFieldWallJump &message) {
  if (StateUtilField::execAsmCmd(*behavior->unknown08->getComponent<GfComAsm>(), ASM_CMD_ID_FIELD_CLIMBJUMP_00)) {
    message.unknown08 = true;
    reqState(STATE_ID_UNKNOWN_50);
  }
}

} // namespace pc
} // namespace gf

// The wall idle, move, prepare jump and jump states (0x710055b314 to 0x710055c040) sit between the on wall state functions (0x710055ac10 to 0x710055b274) and
// the on wall and prepare jump virtual wrappers (0x710055c128 to 0x710055c188), which a unit emits after everything it defines.
// clang-format off
#include "gf_pc_state_field_wall_idle.cpp"
#include "gf_pc_state_field_wall_move.cpp"
#include "gf_pc_state_field_wall_prepare_jump.cpp"
#include "gf_pc_state_field_wall_jump.cpp"
#include "gf_pc_state_field_wall_jump_start.cpp"
#include "gf_pc_state_field_wall_jump_move.cpp"
#include "gf_pc_state_field_wall_jump_end.cpp"
// clang-format on
