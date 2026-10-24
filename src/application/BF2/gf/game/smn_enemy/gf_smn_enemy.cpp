#include "gf/game/smn_enemy/gf_smn_enemy.h"

#include <algorithm>

namespace gf {

void GfRelSmnEnemy::removeEnemy(GF_OBJ_HANDLE *handle) {
  if (!unknown78.empty()) {
    for (std::pair<PopInfo *, GF_OBJ_HANDLE *> *enemy = unknown78.begin(), *end = unknown78.end(); enemy != end; ++enemy) {
      if (enemy->second == handle) {
        unknown78.erase(enemy);
        return;
      }
    }
  }
  if (!unknowna0.empty()) {
    GF_OBJ_HANDLE **enemy = std::find(unknowna0.begin(), unknowna0.end(), handle);
    if (enemy != unknowna0.end()) {
      unknowna0.erase(enemy);
    }
  }
}

void GfRelSmnEnemy::listenerGfObj(OBJEVT event, GF_OBJ_HANDLE *handle, u32 objectType) {
  if (event == OBJEVT_DESTROY) {
    removeEnemy(handle);
  }
}

} // namespace gf
