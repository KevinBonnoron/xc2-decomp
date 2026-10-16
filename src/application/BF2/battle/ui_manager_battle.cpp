#include "battle/ui_manager_battle.h"

namespace btl {

UIManager::~UIManager() {}

void UIManager::Initialize() {}

void UIManager::Destroy() {
  if (get() != nullptr) {
    delete get();
  }
}

void UIManager::Finalize() {}

void UIManager::PreUpdate(const fw::UpdateInfo &updateInfo) { get()->PreUpdateProc(updateInfo); }

void UIManager::PreUpdateProc(const fw::UpdateInfo &) {}

void UIManager::Update(const fw::UpdateInfo &updateInfo) { get()->UpdateProc(updateInfo); }

void UIManager::SetKakuseiData(bool isEnableKakusei, bool isKakusei, f32 kakuseiRestTimeRatio) {
  this->isEnableKakusei = isEnableKakusei;
  this->kakuseiRestTimeRatio = kakuseiRestTimeRatio;
  this->isKakusei = isKakusei;
}

void UIManager::RegisterRescueUI(gf::GF_OBJ_HANDLE *handle) { rescueTarget = handle; }

} // namespace btl
