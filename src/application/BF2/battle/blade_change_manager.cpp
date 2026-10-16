#include "battle/blade_change_manager.h"

#include "gf/gf_allocator.h"

namespace gf {
struct GF_OBJ_HANDLE;
} // namespace gf

namespace btl {

BladeChangeManager::BladeChangeManager() : procNum(0), isEnable(false) {}

BladeChangeManager::~BladeChangeManager() {}

void BladeChangeManager::Create() {
  BladeChangeManager *manager = new (gf::getAllocator(gf::ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) BladeChangeManager();
  manager->Initialize();
}

void BladeChangeManager::Initialize() {
  isEnable = true;
  for (int i = 0; i < 10; i++) {
    procs[i] = PROC_DATA();
  }
  procNum = 0;
}

void BladeChangeManager::Destroy() {
  if (get() != nullptr) {
    delete get();
  }
}

void BladeChangeManager::Finalize() {}

void BladeChangeManager::NotifyMapChange() {
  isEnable = true;
  for (int i = 0; i < 10; i++) {
    procs[i] = PROC_DATA();
  }
  procNum = 0;
}

void BladeChangeManager::PreUpdate(const fw::UpdateInfo &updateInfo) { get()->PreUpdateProc(updateInfo); }

void BladeChangeManager::PreUpdateProc(const fw::UpdateInfo &) {}

void BladeChangeManager::Update(const fw::UpdateInfo &updateInfo) { get()->UpdateProc(updateInfo); }

void BladeChangeManager::FinishBladeChange(gf::GF_OBJ_HANDLE *handle) {
  int num = procNum;
  for (int i = 0; i < num; i++) {
    if (procs[i].driver == handle || procs[i].blade == handle) {
      procs[i].isFinish = true;
    }
  }
}

void BladeChangeManager::NotiryProgress(gf::GF_OBJ_HANDLE *, PROGRESS_ID) {}

int BladeChangeManager::GetChangeBladeIndex(gf::GF_OBJ_HANDLE *handle) const {
  for (int i = 0; i < procNum; i++) {
    if (procs[i].driver == handle || procs[i].blade == handle) {
      return procs[i].changeBladeIndex;
    }
  }
  return -1;
}

int BladeChangeManager::GetBaseBladeBdatID(gf::GF_OBJ_HANDLE *handle) const {
  for (int i = 0; i < procNum; i++) {
    if (procs[i].driver == handle || procs[i].blade == handle) {
      return procs[i].baseBladeBdatId;
    }
  }
  return 0;
}

int BladeChangeManager::GetBladeChangeType(gf::GF_OBJ_HANDLE *handle) const {
  for (int i = 0; i < procNum; i++) {
    if (procs[i].driver == handle || procs[i].blade == handle) {
      return procs[i].changeType;
    }
  }
  return -1;
}

bool BladeChangeManager::IsRegister(gf::GF_OBJ_HANDLE *handle) const {
  for (int i = 0; i < procNum; i++) {
    const PROC_DATA &proc = procs[i];
    if (proc.driver == handle && !proc.isDriverEnd) {
      return true;
    }
    if (proc.blade == handle) {
      return true;
    }
    if (proc.changeBlade == handle && !proc.isChangeBladeEnd) {
      return true;
    }
  }
  return false;
}

bool BladeChangeManager::IsReceiveLater(gf::GF_OBJ_HANDLE *handle) const {
  bool isFound = false;
  bool isLater;
  for (int i = 0; i < procNum; i++) {
    if (procs[i].driver == handle || procs[i].blade == handle) {
      int receive;
      switch (procs[i].receiveType) {
      case RECEIVE_TYPE_BLADE_CHANGE:
        receive = 6;
        break;
      case RECEIVE_TYPE_HOMURA_CHANGE:
        receive = 7;
        break;
      case RECEIVE_TYPE_NONE:
        receive = -1;
        break;
      default:
        receive = -1;
        break;
      }
      isFound = true;
      isLater = procs[i].progress > receive;
      break;
    }
  }
  return isFound && isLater;
}

bool BladeChangeManager::IsProcDisableCancel() const {
  for (int i = 0; i < procNum; i++) {
    if (procs[i].cancelState != CANCEL_STATE_ENABLE) {
      return true;
    }
  }
  return false;
}

bool BladeChangeManager::IsProcHomuriEnd() const {
  for (int i = 0; i < procNum; i++) {
    if (procs[i].changeType >= CHANGE_TYPE_HOMURI_FIRST && procs[i].changeType <= CHANGE_TYPE_HOMURI_LAST &&
        procs[i].cancelState == CANCEL_STATE_DISABLE) {
      return true;
    }
  }
  return false;
}

} // namespace btl
