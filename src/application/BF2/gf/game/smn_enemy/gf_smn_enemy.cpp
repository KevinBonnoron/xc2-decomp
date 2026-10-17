#include "gf/game/smn_enemy/gf_smn_enemy.h"

#include <algorithm>

namespace gf {

void GfRelSmnEnemy::removeEnemy(GF_OBJ_HANDLE *handle) {
  if (!popEnemies.empty()) {
    for (std::pair<PopInfo *, GF_OBJ_HANDLE *> *enemy = popEnemies.begin(), *end = popEnemies.end(); enemy != end; ++enemy) {
      if (enemy->second == handle) {
        popEnemies.erase(enemy);
        return;
      }
    }
  }
  if (!waitEnemies.empty()) {
    GF_OBJ_HANDLE **enemy = std::find(waitEnemies.begin(), waitEnemies.end(), handle);
    if (enemy != waitEnemies.end()) {
      waitEnemies.erase(enemy);
    }
  }
}

void GfRelSmnEnemy::listenerGfObj(OBJEVT event, GF_OBJ_HANDLE *handle, u32 objectType) {
  if (event == OBJEVT_DESTROY) {
    removeEnemy(handle);
  }
}

} // namespace gf
