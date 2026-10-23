#include "battle/blade_arts_manager.h"

#include "gf/gf_allocator.h"

namespace gf {
struct GF_OBJ_HANDLE;
} // namespace gf

namespace btl {

BladeArtsManager::BladeArtsManager() : unknown198(0) {}

BladeArtsManager::~BladeArtsManager() {}

void BladeArtsManager::Create() {
  BladeArtsManager *manager = new (gf::getAllocator(gf::ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) BladeArtsManager();
  manager->Initialize();
}

void BladeArtsManager::Initialize() {
  for (int i = 0; i < 10; i++) {
    unknown08[i] = PROC_DATA();
  }
  unknown198 = 0;
}

void BladeArtsManager::Destroy() {
  if (get() != nullptr) {
    delete get();
  }
}

void BladeArtsManager::Finalize() {}

void BladeArtsManager::NotifyMapChange() {
  for (int i = 0; i < 10; i++) {
    unknown08[i] = PROC_DATA();
  }
  unknown198 = 0;
}

void BladeArtsManager::PreUpdate(const fw::UpdateInfo &updateInfo) { get()->PreUpdateProc(updateInfo); }

void BladeArtsManager::PreUpdateProc(const fw::UpdateInfo &) {}

void BladeArtsManager::FinishBladeArts(gf::GF_OBJ_HANDLE *handle) {
  int num = unknown198;
  for (int i = 0; i < num; i++) {
    if (unknown08[i].unknown00 == handle || unknown08[i].unknown08 == handle) {
      unknown08[i].unknown1c = STATE_FINISH;
    }
  }
}

gf::GF_OBJ_HANDLE *BladeArtsManager::GetTargetHandle(gf::GF_OBJ_HANDLE *handle) const {
  for (int i = 0; i < unknown198; i++) {
    if (unknown08[i].unknown00 == handle || unknown08[i].unknown08 == handle) {
      return unknown08[i].unknown10;
    }
  }
  return gf::INVALID_HANDLE;
}

bool BladeArtsManager::IsRegister(gf::GF_OBJ_HANDLE *handle) const {
  for (int i = 0; i < unknown198; i++) {
    if (unknown08[i].unknown00 == handle || unknown08[i].unknown08 == handle) {
      return true;
    }
  }
  return false;
}

bool BladeArtsManager::IsBladeStart(gf::GF_OBJ_HANDLE *handle) const {
  bool isFound = false;
  bool isStart;
  for (int i = 0; i < unknown198; i++) {
    if (unknown08[i].unknown00 == handle || unknown08[i].unknown08 == handle) {
      isFound = true;
      isStart = unknown08[i].unknown1c >= STATE_ATTACK;
      break;
    }
  }
  return isFound && isStart;
}

bool BladeArtsManager::IsBladeAttack(gf::GF_OBJ_HANDLE *handle) const {
  bool isFound = false;
  bool isAttack;
  for (int i = 0; i < unknown198; i++) {
    if (unknown08[i].unknown00 == handle || unknown08[i].unknown08 == handle) {
      isFound = true;
      isAttack = unknown08[i].unknown1c == STATE_ATTACK;
      break;
    }
  }
  return isFound && isAttack;
}

} // namespace btl
