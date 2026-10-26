#include "battle/blade_change_manager.h"

#include "battle/misc_battle.h"
#include "framework/effect/effect_manager.h"
#include "gf/gf_allocator.h"
#include "mm_math/mm_vec3.h"

namespace gf {
struct GF_OBJ_HANDLE;
} // namespace gf

namespace btl {

BladeChangeManager::BladeChangeManager() : unknown470(0), unknown474(false) {}

BladeChangeManager::~BladeChangeManager() {}

void BladeChangeManager::Create() {
  BladeChangeManager *manager = new (gf::getAllocator(gf::ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) BladeChangeManager();
  manager->Initialize();
}

void BladeChangeManager::Initialize() {
  unknown474 = true;
  for (int i = 0; i < 10; i++) {
    unknown10[i] = PROC_DATA();
  }
  unknown470 = 0;
}

void BladeChangeManager::Destroy() {
  if (get() != nullptr) {
    delete get();
  }
}

void BladeChangeManager::Finalize() {}

void BladeChangeManager::NotifyMapChange() {
  unknown474 = true;
  for (int i = 0; i < 10; i++) {
    unknown10[i] = PROC_DATA();
  }
  unknown470 = 0;
}

void BladeChangeManager::PreUpdate(const fw::UpdateInfo &updateInfo) { get()->PreUpdateProc(updateInfo); }

void BladeChangeManager::PreUpdateProc(const fw::UpdateInfo &) {}

void BladeChangeManager::Update(const fw::UpdateInfo &updateInfo) { get()->UpdateProc(updateInfo); }

void BladeChangeManager::UpdateEffect(PROC_DATA &proc, f32) {
  if (proc.unknown40 != 0) {
    fw::EffectManager *manager = fw::EffectManager::get();
    if (!manager->isExist(proc.unknown40)) {
      proc.unknown40 = 0;
    } else {
      mm::Vec3 position;
      if (Misc::GetObjectTransform(proc.unknown08, position, Misc::TRANS_TYPE_POSITION)) {
        manager->setParam(proc.unknown40, position, mm::Vec3::unit);
      }
    }
  }
}

void BladeChangeManager::FinishBladeChange(gf::GF_OBJ_HANDLE *handle) {
  int num = unknown470;
  for (int i = 0; i < num; i++) {
    if (unknown10[i].unknown00 == handle || unknown10[i].unknown08 == handle) {
      unknown10[i].unknown62 = true;
    }
  }
}

void BladeChangeManager::NotiryProgress(gf::GF_OBJ_HANDLE *, PROGRESS_ID) {}

int BladeChangeManager::GetChangeBladeIndex(gf::GF_OBJ_HANDLE *handle) const {
  for (int i = 0; i < unknown470; i++) {
    if (unknown10[i].unknown00 == handle || unknown10[i].unknown08 == handle) {
      return unknown10[i].unknown48;
    }
  }
  return -1;
}

int BladeChangeManager::GetBaseBladeBdatID(gf::GF_OBJ_HANDLE *handle) const {
  for (int i = 0; i < unknown470; i++) {
    if (unknown10[i].unknown00 == handle || unknown10[i].unknown08 == handle) {
      return unknown10[i].unknown4c;
    }
  }
  return 0;
}

int BladeChangeManager::GetBladeChangeType(gf::GF_OBJ_HANDLE *handle) const {
  for (int i = 0; i < unknown470; i++) {
    if (unknown10[i].unknown00 == handle || unknown10[i].unknown08 == handle) {
      return unknown10[i].unknown5c;
    }
  }
  return -1;
}

bool BladeChangeManager::IsRegister(gf::GF_OBJ_HANDLE *handle) const {
  for (int i = 0; i < unknown470; i++) {
    const PROC_DATA &proc = unknown10[i];
    if (proc.unknown00 == handle && !proc.unknown60) {
      return true;
    }
    if (proc.unknown08 == handle) {
      return true;
    }
    if (proc.unknown10 == handle && !proc.unknown61) {
      return true;
    }
  }
  return false;
}

bool BladeChangeManager::IsReceiveLater(gf::GF_OBJ_HANDLE *handle) const {
  bool isFound = false;
  bool isLater;
  for (int i = 0; i < unknown470; i++) {
    if (unknown10[i].unknown00 == handle || unknown10[i].unknown08 == handle) {
      int receive;
      switch (unknown10[i].unknown5d) {
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
      isLater = unknown10[i].unknown50 > receive;
      break;
    }
  }
  return isFound && isLater;
}

bool BladeChangeManager::IsProcDisableCancel() const {
  for (int i = 0; i < unknown470; i++) {
    if (unknown10[i].unknown63 != CANCEL_STATE_ENABLE) {
      return true;
    }
  }
  return false;
}

bool BladeChangeManager::IsProcHomuriEnd() const {
  for (int i = 0; i < unknown470; i++) {
    if (unknown10[i].unknown5c >= CHANGE_TYPE_HOMURI_FIRST && unknown10[i].unknown5c <= CHANGE_TYPE_HOMURI_LAST && unknown10[i].unknown63 == CANCEL_STATE_DISABLE) {
      return true;
    }
  }
  return false;
}

} // namespace btl
