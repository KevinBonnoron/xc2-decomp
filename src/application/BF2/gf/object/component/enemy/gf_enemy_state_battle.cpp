#include "gf/object/component/enemy/gf_enemy_state_battle.h"
#include "anm/anm_res_asm.h"
#include "gf/object/component/enemy/gf_enemy_asm_callback.h"

namespace gf {
namespace enemy {

void StateBattle::onEnter(void *owner, ai::State *previous) {
  mOwner = owner;
  mIsEntered = Enter(static_cast<GfComBehaviorEnemy *>(owner), previous);
  mOwner = nullptr;
}

void registerAsmCallbackField(GF_OBJ_HANDLE *handle, anm::ResASM *resAsm) { resAsm->sortAnnotation(1); }

} // namespace enemy
} // namespace gf
