#include "gf/object/component/pc/field/gf_pc_state_field_access.h"

#include "framework/object/updatable_object.h"
#include "gf/game/gf_game_manager.h"
#include "gf/object/component/animation/gf_com_asm.h"
#include "gf/object/component/behavior/gf_com_behavior.h"
#include "gf/object/component/gimmick/gf_com_behavior_gmk.h"
#include "gf/object/component/pc/gf_com_behavior_pc.h"
#include "gf/object/component/pc/gf_com_property_pc.h"
#include "gf/object/component/pc/gf_pc_state_id.h"
#include "gf/object/component/pc/gf_pc_state_util.h"
#include "gf/object/component/pc/gf_pc_state_util_field.h"
#include "gf/object/gf_obj.h"
#include "gf/object/gf_obj_handle.h"
#include "gf/object/gf_obj_util.h"

namespace fw {
class MessageObject;
} // namespace fw

namespace gf {
namespace pc {

void StateFieldAccess::enter(GfComBehaviorPc *behavior, ai::State *previous) {
  m_GF_OBJ_HANDLE = unknown020;
  GfComPropertyPc *property = behavior->unknown08->getComponent<GfComPropertyPc>();
  GfObj *target = StateUtilField::getAccessTarget(*behavior);
  if (target != nullptr) {
    if (property->unknown111_2) {
      MsgPcGetElvLift lift;
      // Single-use local that places the receiver (target + 0xe0, `mov x22,x21` at 0x7100553c2c): the game loads the vtable of the receiver (0x7100553c30) before the sender (ldr x9,[x19,#8] at
      // 0x7100553c34), whereas the second send (0x7100553c94) loads the sender first. Written directly, or with recieveMessage called on the target, the sender comes first or the function differs.
      fw::MessageObject *receiver = target;
      static_cast<GfObj *>(behavior->unknown08)->sendMessage(receiver, lift);
      if (lift.unknown90) {
        MsgPcFieldElvWarp warp(&lift, target->unknownf8);
        StateUtil::broadcastPlayer(*behavior, warp);
      }
    }
    m_GF_OBJ_HANDLE = target->unknownf8;
    MsgPcFieldNotifyAction message(0);
    static_cast<GfObj *>(behavior->unknown08)->sendMessage(target, message);
  }
  StateUtilField::setAccessFlag(*behavior, false);
  StateUtilField::setSpecialActStatus(*behavior, true);
  property->unknown007();
  StateUtil::setEnableDownIK(*behavior, true);
  GfObjUtil::setInvincible(static_cast<GfObj *>(behavior->unknown08)->unknownf8, true, false);
}

void StateFieldAccess::update(GfComBehaviorPc *behavior, const fw::UpdateInfo &info) {
  GfComAsm *comAsm = behavior->unknown08->getComponent<GfComAsm>();
  if (__builtin_strcmp(comAsm->getStateName(ANIM_LAYER_UNKNOWN_0), "S_idle") == 0 && !GfGameManager::isPlayerPause()) {
    reqState(STATE_ID_UNKNOWN_3);
  }
}

} // namespace pc
} // namespace gf
