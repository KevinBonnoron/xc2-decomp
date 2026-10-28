#include "battle/effect/effect_manager_battle.h"

#include "gf/gf_allocator.h"
#include "mm_mtl/fixed_list.h" // IWYU pragma: keep

namespace btl {

void EffectManager::Create() {
  // __LINE__ must be 57 as in the original file: it is an argument of operator new.
#line 57
  EffectManager *manager = new (gf::getAllocator(gf::ALLOCATOR_SYSTEM), __FILE__, __LINE__, 8) EffectManager();
  manager->Initialize();
}

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

template mm::mtl::FixedList<btl::EffectManager::REGISTER_PROC_DATA, 30>::iterator
    mm::mtl::FixedList<btl::EffectManager::REGISTER_PROC_DATA, 30>::erase(mm::mtl::FixedList<btl::EffectManager::REGISTER_PROC_DATA, 30>::iterator);
template mm::mtl::FixedList<btl::EffectManager::REGISTER_PROC_DATA, 30>::~FixedList();

template mm::mtl::PtrSingleton<btl::EffectManager>::~PtrSingleton();
