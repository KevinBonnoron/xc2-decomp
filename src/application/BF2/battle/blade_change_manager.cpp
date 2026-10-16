#include "battle/blade_change_manager.h"

namespace btl {

BladeChangeManager::~BladeChangeManager() {}

void BladeChangeManager::Destroy() {
  if (get() != nullptr) {
    delete get();
  }
}

void BladeChangeManager::Finalize() {}

void BladeChangeManager::PreUpdate(const fw::UpdateInfo &updateInfo) { get()->PreUpdateProc(updateInfo); }

void BladeChangeManager::PreUpdateProc(const fw::UpdateInfo &) {}

void BladeChangeManager::Update(const fw::UpdateInfo &updateInfo) { get()->UpdateProc(updateInfo); }

void BladeChangeManager::NotiryProgress(gf::GF_OBJ_HANDLE *, PROGRESS_ID) {}

} // namespace btl
