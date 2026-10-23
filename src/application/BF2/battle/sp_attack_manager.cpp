#include "battle/sp_attack_manager.h"

#include "battle/utility_battle.h"
#include "fw/fw_camera.h"
#include "gf/object/gf_obj_handle.h"

namespace btl {

constexpr int SP_ATTACK_SLOT_NONE = 15;

bool SpAttackManager::PROC_DATA::IsRegister(gf::GF_OBJ_HANDLE *handle) const {
  if (unknown10 == handle) {
    return true;
  }

  if (unknown18 == handle) {
    return true;
  }

  if (unknown08 != nullptr && Utility::IsThirdCharacter(handle)) {
    return true;
  }

  return false;
}

SpAttackManager::~SpAttackManager() {}

void SpAttackManager::Destroy() {
  if (get() != nullptr) {
    delete get();
  }
}

void SpAttackManager::Finalize() {}

void SpAttackManager::PreUpdate(const fw::UpdateInfo &updateInfo) { get()->PreUpdateProc(updateInfo); }

void SpAttackManager::PreUpdateProc(const fw::UpdateInfo &) {}

void SpAttackManager::Update(const fw::UpdateInfo &updateInfo) { get()->UpdateProc(updateInfo); }

bool SpAttackManager::IsRegister(gf::GF_OBJ_HANDLE *handle) const {
  int num = unknown208;
  for (int i = 0; i < num; i++) {
    if (unknown28[i].IsRegister(handle)) {
      return true;
    }
  }

  return false;
}

void SpAttackManager::FinishUpdateAttackData(gf::GF_OBJ_HANDLE *handle) {
  PROC_DATA *proc = const_cast<PROC_DATA *>(GetProcDataConst(handle));
  if (proc != nullptr) {
    proc->unknown5c_2 = false;
  }
}

int SpAttackManager::GetSpAttackSlot(gf::GF_OBJ_HANDLE *handle) const {
  const PROC_DATA *proc = GetProcDataConst(handle);
  if (proc == nullptr) {
    return SP_ATTACK_SLOT_NONE;
  }

  return proc->unknown5a;
}

gf::GF_OBJ_HANDLE *SpAttackManager::GetTargetHandle(gf::GF_OBJ_HANDLE *handle) const {
  const PROC_DATA *proc = GetProcDataConst(handle);
  if (proc == nullptr) {
    return gf::INVALID_HANDLE;
  }

  return proc->unknown20;
}

bool SpAttackManager::IsLastAttackDriver(gf::GF_OBJ_HANDLE *handle) const {
  bool isFound = false;
  bool isLastAttackDriver;
  const PROC_DATA *proc = GetProcDataConst(handle);
  if (proc != nullptr) {
    isLastAttackDriver = proc->unknown5c_3;
    isFound = true;
  }

  return isFound & isLastAttackDriver;
}

bool SpAttackManager::IsTrinityAttack(gf::GF_OBJ_HANDLE *handle) const {
  bool isFound = false;
  bool isTrinityAttack;
  const PROC_DATA *proc = GetProcDataConst(handle);
  if (proc != nullptr) {
    isTrinityAttack = proc->unknown08 != nullptr;
    isFound = true;
  }

  return isFound & isTrinityAttack;
}

bool SpAttackManager::IsDispThirdChr() const {
  bool isFound = false;
  bool isDispThirdChr;
  int num = unknown208;
  for (int i = 0; i < num; i++) {
    if (unknown28[i].unknown08 != nullptr) {
      isDispThirdChr = unknown28[i].unknown5c_6;
      isFound = true;
      break;
    }
  }

  return isFound & isDispThirdChr;
}

bool SpAttackManager::IsMovie() const {
  for (int i = 0; i < unknown208; i++) {
    if (unknown28[i].unknown53 == MOVIE_STEP_LOAD || unknown28[i].unknown53 == MOVIE_STEP_PLAY) {
      return true;
    }
  }

  return false;
}

} // namespace btl
