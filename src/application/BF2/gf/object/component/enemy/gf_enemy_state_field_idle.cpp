#include "gf/object/component/enemy/gf_enemy_state_field_idle.h"

#include "framework/object/updatable_object.h"
#include "fw/fw_transform.h"
#include "fw/fw_update_info.h"
#include "gf/object/component/animation/gf_com_asm.h"
#include "gf/object/component/enemy/gf_behavior_enemy_field.h"
#include "gf/object/component/enemy/gf_com_behavior_enemy.h"
#include "gf/object/component/enemy/gf_enemy_state_id.h"
#include "gf/object/gf_obj.h"
#include "gf/object/gf_obj_handle.h"
#include "gf/object/gf_obj_manager.h"
#include "gf/object/gf_obj_setup.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/rtti.h"

namespace gf {
namespace enemy {

void StateFieldIdle::leave(GfComBehaviorEnemy *behavior, ai::State *next) {
  GfComAsm *comAsm = behavior->unknown08->getComponent<GfComAsm>();
  if (comAsm != nullptr) {
    if (unknown08 == STATE_ID_UNKNOWN_4) {
      comAsm->execCmd("C_specialA_02", ANIM_LAYER_BASE);
    } else if (unknown08 == STATE_ID_UNKNOWN_5) {
      comAsm->execCmd("C_specialB_02", ANIM_LAYER_BASE);
    }
  }
}

void StateFieldIdle::update(GfComBehaviorEnemy *behavior, const fw::UpdateInfo &info) {
  unknown20.update(info.unknown04);
  if (unknown20.unknown00 == INVALID_HANDLE || unknown20.unknown08.empty() || unknown20.unknown34) {
    if (unknown20.unknown35 && unknown5c < 0.0f) {
      GfComAsm *comAsm = behavior->unknown08->getComponent<GfComAsm>();
      if (comAsm != nullptr) {
        const char *stateName = comAsm->getStateName(ANIM_LAYER_BASE);
        if (stateName != nullptr) {
          comAsm->getPlaybackTime(stateName, &unknown5c);
        }
      }
    }

    unknown58 = info.unknown04 + unknown58;
    if ((unknown5c != 0.0f && unknown5c <= unknown58) || (behavior->unknown54e2 && unknown08 != STATE_ID_UNKNOWN_1)) {
      if (behavior->isStateCondMatch(STATE_ID_UNKNOWN_14)) {
        reqState(STATE_ID_UNKNOWN_14);
      } else {
        GfObjSetupEnemy *setup = mm::mtl::dynamicCast<GfObjSetupEnemy>(GfObjManager::getObjInfo(static_cast<GfObj *>(behavior->unknown08)->unknownf8)->unknown30);
        if (!setup->unknownb2) {
          enemy::STATE_ID next = behavior->getNextFieldStateId();
          if (behavior->isStateCondMatch(next)) {
            reqState(next);
          }
        }
      }
    }

    if (unknown60) {
      (this->*unknown60)(*behavior, info);
    }
  }
}

void StateFieldIdle::seqOthersIdle(GfComBehaviorEnemy &behavior, const fw::UpdateInfo &info) {
  if (unknown20.unknown35) {
    behavior.unknown140.unknownc0 = behavior.getTransform().unknown00;
  }
}

} // namespace enemy
} // namespace gf
