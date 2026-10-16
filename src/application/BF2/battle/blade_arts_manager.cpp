#include "battle/blade_arts_manager.h"

namespace btl {

BladeArtsManager::~BladeArtsManager() {}

void BladeArtsManager::Destroy() {
  if (get() != nullptr) {
    delete get();
  }
}

void BladeArtsManager::Finalize() {}

void BladeArtsManager::PreUpdate(const fw::UpdateInfo &updateInfo) { get()->PreUpdateProc(updateInfo); }

void BladeArtsManager::PreUpdateProc(const fw::UpdateInfo &) {}

} // namespace btl
