#include "gf/object/component/enemy/gf_enemy_asm_callback.h"
#include "gf/object/component/effect/gf_com_effect_caster.h"

namespace gf {
namespace enemy {

void registerAsmCallback(GF_OBJ_HANDLE *handle, anm::ResASM *resAsm, fw::EffectResData *effectData) {
  if (resAsm != nullptr) {
    registerAsmCallbackField(handle, resAsm);
    registerAsmCallbackBattle(handle, resAsm);
    GfComEffectCaster::registerAsmCallbackEffect(handle, resAsm, effectData);
  }
}

} // namespace enemy
} // namespace gf
