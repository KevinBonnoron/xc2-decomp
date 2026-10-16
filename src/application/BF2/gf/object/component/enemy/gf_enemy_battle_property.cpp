#include "gf/object/component/enemy/gf_enemy_battle_property.h"

#include "gf/object/component/enemy/gf_enemy_asm_callback.h"

namespace anm {
class ResASM;
} // namespace anm

namespace gf {
struct GF_OBJ_HANDLE;

namespace enemy {

bool registerAsmCallbackBattle(GF_OBJ_HANDLE *handle, anm::ResASM *resAsm) { return false; }

GfEnemyBattleProperty::GfEnemyBattleProperty() {
  _10 = 0xffffffff;
  _1e = 0;
}

} // namespace enemy
} // namespace gf
