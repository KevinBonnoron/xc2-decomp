#include "gf/game/smn_enemy/gf_smn_enemy.h"

#include <algorithm>

#include "gf/object/gf_obj_acc.h"
#include "gf/object/gf_obj_handle.h"
#include "gf/object/gf_obj_util.h"
#include "gf/scom/gf_scom_obj.h"
#include "mm_mtl/vector.h"

namespace gf {

bool GfRelSmnEnemy::isOwnerValid() const {
  GfObjAcc acc(unknown10);
  return !acc.isDestroy() && !acc.testFlag(OBJ_FLAG_UI_HIDDEN) && acc.getObj() != nullptr;
}

u32 GfRelSmnEnemy::getEnemyNum() const {
  if (unknown10 == INVALID_HANDLE) {
    return 0;
  }
  if (unknown18 > 0) {
    return unknowna0.size();
  }
  return 0;
}

GF_OBJ_HANDLE *GfRelSmnEnemy::getEnemy(u32 index) const {
  if (unknown10 == INVALID_HANDLE || unknown18 < 1) {
    return INVALID_HANDLE;
  }
  return unknowna0[index];
}

void GfRelSmnEnemy::disposeWaitEnemies() {
  if (!unknown78.empty()) {
    for (std::pair<PopInfo *, GF_OBJ_HANDLE *> *enemy = unknown78.begin(), *end = unknown78.end(); enemy != end; ++enemy) {
      if (enemy->second != INVALID_HANDLE) {
        GfObjUtil::destroy(enemy->second);
      }
    }
    unknown78.destroy();
  }
}

void GfRelSmnEnemy::disposeEnemies(bool isFade) {
  disposeWaitEnemies();
  if (!unknowna0.empty()) {
    for (GF_OBJ_HANDLE **enemy = unknowna0.begin(), **end = unknowna0.end(); enemy != end; ++enemy) {
      if (*enemy != INVALID_HANDLE) {
        if (isFade) {
          SCOM_DESTROY_GAME_OBJ::create(*enemy, 0.5f, 0);
        } else {
          GfObjUtil::destroy(*enemy);
        }
      }
    }
    unknowna0.destroy();
  }
}

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

void GfSmnEnemyManager::dispose() {
  if (get() != nullptr) {
    delete get();
  }
}

void GfRelSmnEnemy::listenerGfObj(OBJEVT event, GF_OBJ_HANDLE *handle, u32 objectType) {
  if (event == OBJEVT_DESTROY) {
    removeEnemy(handle);
  }
}

} // namespace gf

template mm::mtl::PtrSingleton<gf::GfSmnEnemyManager>::~PtrSingleton();

template void mm::mtl::Vector<gf::GF_OBJ_HANDLE *>::expand(size_t, size_t);
template gf::GfRelSmnEnemy **mm::mtl::Vector<gf::GfRelSmnEnemy *>::erase(gf::GfRelSmnEnemy **);
template void mm::mtl::Vector<gf::GfRelSmnEnemy *>::expand(size_t, size_t);
template void mm::mtl::Vector<gf::GfRelSmnEnemy::PopInfo>::push_back(const gf::GfRelSmnEnemy::PopInfo &);
template void mm::mtl::Vector<gf::GfRelSmnEnemy::PopInfo>::expand(size_t, size_t);
template void mm::mtl::Vector<std::pair<gf::GfRelSmnEnemy::PopInfo *, gf::GF_OBJ_HANDLE *>>::expand(size_t, size_t);
