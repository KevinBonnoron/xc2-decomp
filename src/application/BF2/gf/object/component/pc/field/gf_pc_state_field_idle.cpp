#include "gf/object/component/pc/field/gf_pc_state_field_idle.h"

#include <float.h>
#include <math.h>

#include "framework/message/message_object.h"
#include "framework/object/updatable_object.h"
#include "fw/fw_coli_check.h"
#include "fw/fw_transform.h"
#include "gf/game/gf_game_ride.h"
#include "gf/object/component/animation/gf_com_asm.h"
#include "gf/object/component/pc/gf_com_behavior_pc.h"
#include "gf/object/component/pc/gf_com_property_pc.h"
#include "gf/object/component/pc/gf_pc_asm_cmd_id_field.h"
#include "gf/object/component/pc/gf_pc_property_field.h"
#include "gf/object/component/pc/gf_pc_state_id.h"
#include "gf/object/component/pc/gf_pc_state_util.h"
#include "gf/object/component/pc/gf_pc_state_util_field.h"
#include "gf/object/gf_obj.h"
#include "mm_math/mm_vec3.h"
#include "types.h"

namespace gf {
namespace pc {

void StateFieldIdle::enter(GfComBehaviorPc *behavior, ai::State *previous) {
  StateUtil::setEnableDownIK(*behavior, true);
  GfComPropertyPc *property = behavior->unknown08->getComponent<GfComPropertyPc>();
  property->unknown007();
  StateUtilField::setIdleStatus(*property, true);
}

void StateFieldIdle::leave(GfComBehaviorPc *behavior, ai::State *next) {
  StateUtilField::setIdleStatus(*behavior->unknown08->getComponent<GfComPropertyPc>(), false);
  StateUtil::setEnableDownIK(*behavior, false);
  StateUtil::setEnableLookIK(*behavior, true);
}

void StateFieldIdle::update(GfComBehaviorPc *behavior, const fw::UpdateInfo &info) {
  GfComPropertyPc *property = behavior->unknown08->getComponent<GfComPropertyPc>();
  GfComAsm *comAsm = behavior->unknown08->getComponent<GfComAsm>();
  const char *stateName = comAsm->getStateName(ANIM_LAYER_UNKNOWN_0);
  StateUtil::setEnableLookIK(*behavior, stateName != nullptr && __builtin_strcmp(stateName, "S_idle") == 0);
  if (property->existInputXY() && StateUtilField::execAsmCmd(*comAsm, ASM_CMD_ID_FIELD_MOVE)) {
    if (StateUtilField::isInputInverseDir(*property)) {
      reqState(STATE_ID_UNKNOWN_4);
    } else {
      reqState(STATE_ID_UNKNOWN_7);
    }
  }
}

// Inferred name; kept as an exception to the unknown-name rule (AGENTS.md): single-user helper whose existence only the match proves; rename if a sibling build gives a symbol.
// Compares the state of the base animation layer with a name and gives the strcmp result through the reference; returns false, leaving the result unset, when the object has no state to compare.
// StateFieldIdle::isEnableUnique (1.0.0: 0x7100558bf0, 39 instructions) ands the comparison with the returned flag (and w0, w9, w8 at 0x7100558c7c) and leaves the comparison register unset on the
// paths without a state: the caller reads the result only when the flag is set.
// Forms tried without the helper, written in isEnableUnique: an early return for the missing component, then stateName != nullptr && strcmp(...) == 0 (36 instructions); a bool cleared first and
// set inside two nested if (36). Other helper shapes: returning the comparison as a bool (36), returning the state name, null when there is none (36), returning the strcmp result, -1 when there is
// no state (36), giving the state name through a reference with strcmp in the caller (36), a bool out-parameter (42, the paths without a state clear it), the strcmp result returned with a bool
// out-parameter for the flag (40). With this helper, the result initialised before the call gives 42 and an early return on false gives 36.
static inline bool compareStateName(const GfComBehaviorPc &behavior, const char *name, int &result) {
  GfComAsm *comAsm = behavior.unknown08->getComponent<GfComAsm>();
  if (comAsm == nullptr) {
    return false;
  }
  const char *stateName = comAsm->getStateName(ANIM_LAYER_UNKNOWN_0);
  if (stateName == nullptr) {
    return false;
  }
  result = __builtin_strcmp(name, stateName);
  return true;
}

bool StateFieldIdle::isEnableUnique(GfComBehaviorPc *behavior) {
  if (GfGameRide::isVehicle(static_cast<GfObj *>(behavior->unknown08)->unknownf8)) {
    return false;
  }
  int result;
  return compareStateName(*behavior, "S_idle", result) && result == 0;
}

bool StateFieldIdle::checkSpace(GfComBehaviorPc *behavior) const {
  GfComPropertyPc *property = behavior->unknown08->getComponent<GfComPropertyPc>();
  f32 space = property->m_propertyField.unknown54;
  if (space > FLT_EPSILON) {
    fw::ColiCheckConfig config;
    config.unknown08 = 0.0f;
    config.unknown0c = 0.0f;
    config.unknown14 = false;
    config.unknown15 = false;
    config.unknown00 = 9;
    config.unknown10 = 0;
    config.unknown04 = 0x80000076;
    f32 length = space - 0.5f;
    mm::Vec3 base = property->unknown160.unknown00 + property->unknown1c0 * 0.6f;
    length = fmaxf(length, 0.01f);
    mm::Vec3 start = base + property->unknown1e0 * 0.5f;
    mm::Vec3 end = base + property->unknown1e0 * length;
    fw::TColiCheckResult<256> result;
    return !fw::ColiCheck::testCapsule(result, start, end, 0.5f, config);
  }

  return true;
}

bool StateFieldIdle::recieveMessage(void *owner, fw::MessageObject *sender, fw::Message &message) {
  switch (message.unknown00) {
  case MSG_PC_FIELD_UNKNOWN_16777238:
    procMsgPcFieldHighJump(static_cast<GfComBehaviorPc *>(owner), sender, static_cast<MsgPcFieldHighJump &>(message));
    break;
  case MSG_PC_FIELD_UNKNOWN_16777251:
    procMsgPcFieldTestEnableUniqueMotion(static_cast<GfComBehaviorPc *>(owner), sender, static_cast<MsgPcFieldTestEnableUniqueMotion &>(message));
    break;
  case MSG_PC_FIELD_UNKNOWN_16777250:
    procMsgPcFieldSetUniqueMotion(static_cast<GfComBehaviorPc *>(owner), sender, static_cast<MsgPcFieldSetUniqueMotion &>(message));
    break;
  default:
    return false;
  }

  return true;
}

void StateFieldIdle::procMsgPcFieldHighJump(GfComBehaviorPc *behavior, fw::MessageObject *sender, MsgPcFieldHighJump &message) {
  message.unknown08 = true;
  reqState(STATE_ID_UNKNOWN_17);
}

void StateFieldIdle::procMsgPcFieldTestEnableUniqueMotion(GfComBehaviorPc *behavior, fw::MessageObject *sender, MsgPcFieldTestEnableUniqueMotion &message) {
  message.unknown08 = isEnableUnique(behavior);
}

void StateFieldIdle::procMsgPcFieldSetUniqueMotion(GfComBehaviorPc *behavior, fw::MessageObject *sender, MsgPcFieldSetUniqueMotion &message) {
  if (isEnableUnique(behavior) && checkSpace(behavior)) {
    GfComAsm *comAsm = behavior->unknown08->getComponent<GfComAsm>();
    if (comAsm != nullptr) {
      message.unknown0c =
          StateUtilField::execAsmCmd(*comAsm, message.unknown08 < MOTION_UNKNOWN_3 ? static_cast<ASM_CMD_ID_FIELD>(ASM_CMD_ID_FIELD_UNIQUE_A + message.unknown08) : ASM_CMD_ID_FIELD_UNIQUE_A);
    }
  }
}

} // namespace pc
} // namespace gf

// The idle turn state (0x7100559114 to 0x7100559350) sits between the idle state functions (0x71005589cc to 0x710055902c) and the idle virtual wrappers
// (0x71005594b8 to 0x71005595bc), which a unit emits after everything it defines.
#include "gf_pc_state_field_idle_turn.cpp"
