#include "gf/object/component/enemy/gf_enemy_state_field_spawn.h"

#include <string.h>

#include "framework/object/updatable_object.h"
#include "gf/object/component/animation/gf_com_asm.h"
#include "gf/object/component/enemy/gf_com_behavior_enemy.h"
#include "gf/object/component/enemy/gf_enemy_state_id.h"

namespace gf {
namespace enemy {

void StateFieldSpawn::enter(GfComBehaviorEnemy *behavior, ai::State *previous) { behavior->disposeMenuObj(); }

void StateFieldSpawn::leave(GfComBehaviorEnemy *behavior, ai::State *next) { behavior->createMenuObj(); }

void StateFieldSpawn::update(GfComBehaviorEnemy *behavior, const fw::UpdateInfo &info) {
  GfComAsm *comAsm = behavior->unknown08->getComponent<GfComAsm>();
  if (comAsm != nullptr) {
    const char *stateName = comAsm->getStateName(ANIM_LAYER_BASE);
    if (stateName != nullptr && strcmp(stateName, "S_idle") != 0) {
      return;
    }
  }

  reqState(STATE_ID_UNKNOWN_1);
}

} // namespace enemy
} // namespace gf
