#include "gf/object/component/pc/field/gf_pc_state_field_ride_on.h"

#include "framework/message/message_object.h"
#include "framework/object/updatable_object.h"
#include "gf/game/gf_game_player_formation.h"
#include "gf/object/component/animation/gf_com_asm.h"
#include "gf/object/component/pc/gf_com_behavior_pc.h"
#include "gf/object/component/pc/gf_com_property_pc.h"
#include "gf/object/component/pc/gf_pc_asm_cmd_id_field.h"
#include "gf/object/component/pc/gf_pc_state_util.h"
#include "gf/object/component/pc/gf_pc_state_util_field.h"
#include "gf/object/gf_obj.h"
#include "gf/object/gf_obj_util.h"
#include "mm_mtl/fixed_queue.h" // IWYU pragma: keep
#include "mm_mtl/fixstr.h"      // IWYU pragma: keep
#include "types.h"

namespace gf {
namespace pc {

void StateFieldRideOn::enter(GfComBehaviorPc *behavior, ai::State *previous) { behavior->getProperty()->unknown110_0 = true; }

void StateFieldRideOn::leave(GfComBehaviorPc *behavior, ai::State *next) { behavior->getProperty()->unknown110_0 = false; }

void StateFieldRideOn::update(GfComBehaviorPc *behavior, const fw::UpdateInfo &info) {
  syncMotion(behavior);
  while (!unknown18.empty()) {
    GfComAsm *comAsm = behavior->unknown08->getComponent<GfComAsm>();
    mm::mtl::FixStr<32> command = unknown18.front();
    comAsm->execCmd(command.c_str(), ANIM_LAYER_BASE);
    unknown18.pop_front();
  }
}

void StateFieldRideOn::syncMotion(GfComBehaviorPc *behavior) {
  GfComAsm *comAsm = behavior->unknown08->getComponent<GfComAsm>();
  u32 playerId = behavior->unknown08->getComponent<GfComPropertyPc>()->unknown38;
  u32 buddyId = (playerId & 1) != 0 ? playerId - 1 : playerId + 1;
  GfObj *buddy = GfObjUtil::getObj(GfGamePlayerFormation::get()->unknown1a0[buddyId].unknown08);
  GfComAsm *buddyAsm = buddy->getComponent<GfComAsm>();
  unknown001 vehicleType = getVehicleMotType(*buddyAsm);
  unknown001 riderType = getRiderMotType(*comAsm);
  if (vehicleType != riderType) {
    switch (vehicleType) {
    case unknown001_0:
      if (StateUtilField::execAsmCmd(*comAsm, ASM_CMD_ID_FIELD_MOVE_RIDE)) {
        comAsm->setLocalTime(buddyAsm->getLocalTime(ANIM_LAYER_BASE), ANIM_LAYER_BASE);
        unknown18.clear();
      }
      break;
    case unknown001_1:
      if (StateUtilField::execAsmCmd(*comAsm, ASM_CMD_ID_FIELD_RIDEUP_00)) {
        comAsm->setLocalTime(buddyAsm->getLocalTime(ANIM_LAYER_BASE), ANIM_LAYER_BASE);
        unknown18.clear();
      }
      break;
    case unknown001_2:
      if (StateUtilField::execAsmCmd(*comAsm, ASM_CMD_ID_FIELD_RIDEUP_01)) {
        comAsm->setLocalTime(buddyAsm->getLocalTime(ANIM_LAYER_BASE), ANIM_LAYER_BASE);
        unknown18.clear();
      }
      break;
    case unknown001_3:
      if (StateUtilField::execAsmCmd(*comAsm, ASM_CMD_ID_FIELD_RIDEDOWN_00)) {
        comAsm->setLocalTime(buddyAsm->getLocalTime(ANIM_LAYER_BASE), ANIM_LAYER_BASE);
        unknown18.clear();
      }
      break;
    case unknown001_4:
      if (StateUtilField::execAsmCmd(*comAsm, ASM_CMD_ID_FIELD_RIDEDOWN_01)) {
        comAsm->setLocalTime(buddyAsm->getLocalTime(ANIM_LAYER_BASE), ANIM_LAYER_BASE);
        unknown18.clear();
      }
      break;
    case unknown001_5:
      if (StateUtilField::execAsmCmd(*comAsm, ASM_CMD_ID_FIELD_RIDEJUMP_00)) {
        comAsm->setLocalTime(buddyAsm->getLocalTime(ANIM_LAYER_BASE), ANIM_LAYER_BASE);
        unknown18.clear();
      }
      break;
    case unknown001_6:
      if (StateUtilField::execAsmCmd(*comAsm, ASM_CMD_ID_FIELD_RIDEJUMP_02)) {
        comAsm->setLocalTime(buddyAsm->getLocalTime(ANIM_LAYER_BASE), ANIM_LAYER_BASE);
        unknown18.clear();
      }
      break;
    case unknown001_7:
      if (StateUtilField::execAsmCmd(*comAsm, ASM_CMD_ID_FIELD_RIDEJUMPDMG)) {
        comAsm->setLocalTime(buddyAsm->getLocalTime(ANIM_LAYER_BASE), ANIM_LAYER_BASE);
        unknown18.clear();
      }
      break;
    case unknown001_8:
      if (StateUtilField::execAsmCmd(*comAsm, ASM_CMD_ID_FIELD_RIDEHIGHJUMP_00)) {
        comAsm->setLocalTime(buddyAsm->getLocalTime(ANIM_LAYER_BASE), ANIM_LAYER_BASE);
        comAsm->setSpeed(buddyAsm->getSpeed(ANIM_LAYER_BASE), ANIM_LAYER_BASE);
        unknown18.clear();
      }
      break;
    case unknown001_9:
      if (StateUtilField::execAsmCmd(*comAsm, ASM_CMD_ID_FIELD_RIDEHIGHJUMP_01)) {
        comAsm->setLocalTime(buddyAsm->getLocalTime(ANIM_LAYER_BASE), ANIM_LAYER_BASE);
        comAsm->setSpeed(buddyAsm->getSpeed(ANIM_LAYER_BASE), ANIM_LAYER_BASE);
        unknown18.clear();
      }
      break;
    case unknown001_10:
      if (StateUtilField::execAsmCmd(*comAsm, ASM_CMD_ID_FIELD_RIDEFALL)) {
        comAsm->setLocalTime(buddyAsm->getLocalTime(ANIM_LAYER_BASE), ANIM_LAYER_BASE);
        unknown18.clear();
      }
      break;
    case unknown001_11:
      if (StateUtilField::execAsmCmd(*comAsm, ASM_CMD_ID_FIELD_RIDEWATERHOLE_00)) {
        comAsm->setLocalTime(buddyAsm->getLocalTime(ANIM_LAYER_BASE), ANIM_LAYER_BASE);
        unknown18.clear();
      }
      break;
    case unknown001_12:
      if (comAsm->setState("S_ridewaterhole_01", ANIM_LAYER_BASE)) {
        comAsm->setLocalTime(buddyAsm->getLocalTime(ANIM_LAYER_BASE), ANIM_LAYER_BASE);
        unknown18.clear();
      }
      break;
    case unknown001_13:
      switch (riderType) {
      case unknown001_0:
      case unknown001_5:
      case unknown001_6:
      case unknown001_7:
      case unknown001_8:
      case unknown001_9:
      case unknown001_10:
      case unknown001_11:
      case unknown001_12:
        StateUtilField::execAsmCmd(*comAsm, ASM_CMD_ID_FIELD_RIDE);
        break;
      default:
        break;
      }
      break;
    }
  }
  if (vehicleType == unknown001_0) {
    f32 speed;
    if (buddyAsm->getVariable("V_speed", &speed)) {
      comAsm->setVariable("V_speed", speed);
    }
  }
}

StateFieldRideOn::unknown001 StateFieldRideOn::getVehicleMotType(GfComAsm &comAsm) const {
  const char *stateName = comAsm.getStateName(ANIM_LAYER_BASE);
  if (stateName == nullptr) {
    return unknown001_13;
  }
  if (__builtin_strcmp(stateName, "S_move") == 0) {
    return unknown001_0;
  }
  if (__builtin_strcmp(stateName, "S_uplanding_00") == 0) {
    return unknown001_1;
  }
  if (__builtin_strcmp(stateName, "S_uplanding_01") == 0) {
    return unknown001_2;
  }
  if (__builtin_strcmp(stateName, "S_downlanding_00") == 0) {
    return unknown001_3;
  }
  if (__builtin_strcmp(stateName, "S_downlanding_01") == 0) {
    return unknown001_4;
  }
  if (__builtin_strcmp(stateName, "S_jump_00") == 0 || __builtin_strcmp(stateName, "S_jump_01") == 0) {
    return unknown001_5;
  }
  if (__builtin_strcmp(stateName, "S_jump_02") == 0) {
    return unknown001_6;
  }
  if (__builtin_strcmp(stateName, "S_jumpdmg") == 0) {
    return unknown001_7;
  }
  if (__builtin_strcmp(stateName, "S_highjump_00") == 0) {
    return unknown001_8;
  }
  if (__builtin_strcmp(stateName, "S_highjump_01") == 0) {
    return unknown001_9;
  }
  if (__builtin_strcmp(stateName, "S_fall") == 0) {
    return unknown001_10;
  }
  if (__builtin_strcmp(stateName, "S_waterhole_00") == 0) {
    return unknown001_11;
  }
  if (__builtin_strcmp(stateName, "S_waterhole_01") == 0) {
    return unknown001_12;
  }
  return unknown001_13;
}

StateFieldRideOn::unknown001 StateFieldRideOn::getRiderMotType(GfComAsm &comAsm) const {
  const char *stateName = comAsm.getStateName(ANIM_LAYER_BASE);
  if (stateName == nullptr) {
    return unknown001_13;
  }
  if (__builtin_strcmp(stateName, "S_move_ride") == 0) {
    return unknown001_0;
  }
  if (__builtin_strcmp(stateName, "S_rideup_00") == 0) {
    return unknown001_1;
  }
  if (__builtin_strcmp(stateName, "S_rideup_01") == 0) {
    return unknown001_2;
  }
  if (__builtin_strcmp(stateName, "S_ridedown_00") == 0) {
    return unknown001_3;
  }
  if (__builtin_strcmp(stateName, "S_ridedown_01") == 0) {
    return unknown001_4;
  }
  if (__builtin_strcmp(stateName, "S_ridejump_00") == 0 || __builtin_strcmp(stateName, "S_ridejump_01") == 0) {
    return unknown001_5;
  }
  if (__builtin_strcmp(stateName, "S_ridejump_02") == 0) {
    return unknown001_6;
  }
  if (__builtin_strcmp(stateName, "S_ridejumpdmg") == 0) {
    return unknown001_7;
  }
  if (__builtin_strcmp(stateName, "S_ridehigjump_00") == 0) {
    return unknown001_8;
  }
  if (__builtin_strcmp(stateName, "S_ridehigjump_01") == 0) {
    return unknown001_9;
  }
  if (__builtin_strcmp(stateName, "S_ridefall") == 0) {
    return unknown001_10;
  }
  if (__builtin_strcmp(stateName, "S_ridewaterhole_00") == 0) {
    return unknown001_11;
  }
  if (__builtin_strcmp(stateName, "S_ridewaterhole_01") == 0) {
    return unknown001_12;
  }
  return unknown001_13;
}
bool StateFieldRideOn::recieveMessage(void *owner, fw::MessageObject *sender, fw::Message &message) {
  if (message.unknown00 == MSG_PC_FIELD_NOTIFY_RIDER_EVENT) {
    procMsgPcFieldNotifyRiderEvent(static_cast<GfComBehaviorPc *>(owner), sender, static_cast<MsgPcFieldNotifyRiderEvent &>(message));
    return true;
  }

  return false;
}

void StateFieldRideOn::procMsgPcFieldNotifyRiderEvent(GfComBehaviorPc *behavior, fw::MessageObject *sender, MsgPcFieldNotifyRiderEvent &message) {
  if (message.unknown08 == VEHICLE_EVENT_UNKNOWN_2) {
    unknown18.clear();
    behavior->unknown08->getComponent<GfComAsm>()->setState("S_ride", ANIM_LAYER_BASE);
    return;
  }

  static const char *unknown001[] = {getASMCmdNameField(ASM_CMD_ID_FIELD_RIDECLIMBIDLE), getASMCmdNameField(ASM_CMD_ID_FIELD_RIDE), nullptr};
  unknown18.push(unknown001[message.unknown08]);
}
} // namespace pc
} // namespace gf

template mm::mtl::FixStr<32> mm::mtl::FixedQueue<mm::mtl::FixStr<32>, 8>::pop_front();
