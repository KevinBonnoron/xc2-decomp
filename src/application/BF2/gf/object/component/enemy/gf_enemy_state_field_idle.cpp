#include "gf/object/component/enemy/gf_enemy_state_field_idle.h"

#include "framework/object/updatable_object.h"
#include "fw/fw_transform.h"
#include "gf/object/component/animation/gf_com_asm.h"
#include "gf/object/component/enemy/gf_behavior_enemy_field.h"
#include "gf/object/component/enemy/gf_com_behavior_enemy.h"
#include "gf/object/component/enemy/gf_enemy_state_id.h"
#include "mm_math/mm_vec3.h"

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

void StateFieldIdle::seqOthersIdle(GfComBehaviorEnemy &behavior, const fw::UpdateInfo &info) {
  if (unknown20.unknown35) {
    behavior.unknown140.unknownc0 = behavior.getTransform().unknown00;
  }
}

} // namespace enemy
} // namespace gf
