#include "battle/effect/effect_manager_battle.h"

namespace btl {

void EffectManager::Initialize() {}

void EffectManager::Destroy() {
  EffectManager *manager = get();
  manager->Finalize();
  if (manager != nullptr) {
    delete manager;
  }
}

void EffectManager::Finalize() { DeleteAllEffect(); }

void EffectManager::NotifyMapChange() { DeleteAllEffect(); }

void EffectManager::DeleteAllEffect() {
  for (auto it = unknownf3d0.begin(); it != unknownf3d0.end();) {
    EFFECT_DATA &data = unknown10[(*it).unknown04];
    data.unknown261 = false;
    data.unknown00.Initialize(0);
    it = unknownf3d0.erase(it);
  }
}

EffectObject *EffectManager::GetEffect(u32 id) {
  for (auto it = unknownf3d0.begin(); it != unknownf3d0.end(); ++it) {
    if ((*it).unknown00 == id) {
      EFFECT_DATA &data = unknown10[(*it).unknown04];
      if (data.unknown00.unknown240 == id) {
        return &data.unknown00;
      }
    }
  }
  return nullptr;
}

bool EffectManager::IsExistChrHitEffect(gf::GF_OBJ_HANDLE *handle) const {
  for (auto it = unknownf3d0.begin(); it != unknownf3d0.end(); ++it) {
    const EFFECT_DATA &data = unknown10[(*it).unknown04];
    if (data.unknown261 && data.unknown00.unknown48 == handle && data.unknown00.unknown258 != 0) {
      return true;
    }
  }
  for (auto it = unknown10f80.begin(); it != unknown10f80.end(); ++it) {
    const REGISTER_DATA &data = unknownf940[(*it).unknown00];
    if (data.unknown72 && data.unknown08 == handle) {
      return true;
    }
  }
  return false;
}

void EffectManager::PreUpdate(const fw::UpdateInfo &updateInfo) { get()->PreUpdateProc(updateInfo); }

void EffectManager::PreUpdateProc(const fw::UpdateInfo &) {}

void EffectManager::Update(const fw::UpdateInfo &updateInfo) { get()->UpdateProc(updateInfo); }

} // namespace btl
