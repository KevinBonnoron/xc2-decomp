#include "gf/object/component/enemy/gf_enemy_state_field_idle.h"

#include "framework/object/updatable_object.h"
#include "gf/object/component/animation/gf_com_asm.h"
#include "gf/object/component/enemy/gf_com_behavior_enemy.h"
#include "gf/object/component/enemy/gf_enemy_state_id.h"

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

} // namespace enemy
} // namespace gf
