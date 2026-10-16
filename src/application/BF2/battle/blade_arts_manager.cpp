#include "battle/blade_arts_manager.h"

#include "gf/gf_allocator.h"

namespace gf {
struct GF_OBJ_HANDLE;
} // namespace gf

namespace btl {

BladeArtsManager::BladeArtsManager() : procNum(0) {}

BladeArtsManager::~BladeArtsManager() {}

void BladeArtsManager::Create() {
  BladeArtsManager *manager = new (gf::getAllocator(gf::ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) BladeArtsManager();
  manager->Initialize();
}

void BladeArtsManager::Initialize() {
  for (int i = 0; i < 10; i++) {
    procs[i] = PROC_DATA();
  }
  procNum = 0;
}

void BladeArtsManager::Destroy() {
  if (get() != nullptr) {
    delete get();
  }
}

void BladeArtsManager::Finalize() {}

void BladeArtsManager::NotifyMapChange() {
  for (int i = 0; i < 10; i++) {
    procs[i] = PROC_DATA();
  }
  procNum = 0;
}

void BladeArtsManager::PreUpdate(const fw::UpdateInfo &updateInfo) { get()->PreUpdateProc(updateInfo); }

void BladeArtsManager::PreUpdateProc(const fw::UpdateInfo &) {}

void BladeArtsManager::FinishBladeArts(gf::GF_OBJ_HANDLE *handle) {
  int num = procNum;
  for (int i = 0; i < num; i++) {
    if (procs[i].driver == handle || procs[i].blade == handle) {
      procs[i].state = STATE_FINISH;
    }
  }
}

gf::GF_OBJ_HANDLE *BladeArtsManager::GetTargetHandle(gf::GF_OBJ_HANDLE *handle) const {
  for (int i = 0; i < procNum; i++) {
    if (procs[i].driver == handle || procs[i].blade == handle) {
      return procs[i].target;
    }
  }
  return gf::INVALID_HANDLE;
}

bool BladeArtsManager::IsRegister(gf::GF_OBJ_HANDLE *handle) const {
  for (int i = 0; i < procNum; i++) {
    if (procs[i].driver == handle || procs[i].blade == handle) {
      return true;
    }
  }
  return false;
}

bool BladeArtsManager::IsBladeStart(gf::GF_OBJ_HANDLE *handle) const {
  bool isFound = false;
  bool isStart;
  for (int i = 0; i < procNum; i++) {
    if (procs[i].driver == handle || procs[i].blade == handle) {
      isFound = true;
      isStart = procs[i].state >= STATE_ATTACK;
      break;
    }
  }
  return isFound && isStart;
}

bool BladeArtsManager::IsBladeAttack(gf::GF_OBJ_HANDLE *handle) const {
  bool isFound = false;
  bool isAttack;
  for (int i = 0; i < procNum; i++) {
    if (procs[i].driver == handle || procs[i].blade == handle) {
      isFound = true;
      isAttack = procs[i].state == STATE_ATTACK;
      break;
    }
  }
  return isFound && isAttack;
}

} // namespace btl
