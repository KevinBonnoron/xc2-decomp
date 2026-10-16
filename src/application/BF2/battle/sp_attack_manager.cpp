#include "battle/sp_attack_manager.h"

#include "battle/utility_battle.h"
#include "fw/fw_camera.h"
#include "gf/object/gf_obj_handle.h"

namespace btl {

constexpr int SP_ATTACK_SLOT_NONE = 15;

bool SpAttackManager::PROC_DATA::IsRegister(gf::GF_OBJ_HANDLE *handle) const {
  if (driver == handle) {
    return true;
  }

  if (blade == handle) {
    return true;
  }

  if (trinityAttack != nullptr && Utility::IsThirdCharacter(handle)) {
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
  int num = procCount;
  for (int i = 0; i < num; i++) {
    if (procs[i].IsRegister(handle)) {
      return true;
    }
  }

  return false;
}

void SpAttackManager::FinishUpdateAttackData(gf::GF_OBJ_HANDLE *handle) {
  PROC_DATA *proc = const_cast<PROC_DATA *>(GetProcDataConst(handle));
  if (proc != nullptr) {
    proc->isUpdateAttackData = false;
  }
}

int SpAttackManager::GetSpAttackSlot(gf::GF_OBJ_HANDLE *handle) const {
  const PROC_DATA *proc = GetProcDataConst(handle);
  if (proc == nullptr) {
    return SP_ATTACK_SLOT_NONE;
  }

  return proc->slot;
}

gf::GF_OBJ_HANDLE *SpAttackManager::GetTargetHandle(gf::GF_OBJ_HANDLE *handle) const {
  const PROC_DATA *proc = GetProcDataConst(handle);
  if (proc == nullptr) {
    return gf::INVALID_HANDLE;
  }

  return proc->target;
}

bool SpAttackManager::IsLastAttackDriver(gf::GF_OBJ_HANDLE *handle) const {
  bool isFound = false;
  bool isLastAttackDriver;
  const PROC_DATA *proc = GetProcDataConst(handle);
  if (proc != nullptr) {
    isLastAttackDriver = proc->isLastAttackDriver;
    isFound = true;
  }

  return isFound & isLastAttackDriver;
}

bool SpAttackManager::IsTrinityAttack(gf::GF_OBJ_HANDLE *handle) const {
  bool isFound = false;
  bool isTrinityAttack;
  const PROC_DATA *proc = GetProcDataConst(handle);
  if (proc != nullptr) {
    isTrinityAttack = proc->trinityAttack != nullptr;
    isFound = true;
  }

  return isFound & isTrinityAttack;
}

bool SpAttackManager::IsDispThirdChr() const {
  bool isFound = false;
  bool isDispThirdChr;
  int num = procCount;
  for (int i = 0; i < num; i++) {
    if (procs[i].trinityAttack != nullptr) {
      isDispThirdChr = procs[i].isDispThirdChr;
      isFound = true;
      break;
    }
  }

  return isFound & isDispThirdChr;
}

bool SpAttackManager::IsMovie() const {
  for (int i = 0; i < procCount; i++) {
    if (procs[i].movieStep == MOVIE_STEP_LOAD || procs[i].movieStep == MOVIE_STEP_PLAY) {
      return true;
    }
  }

  return false;
}

} // namespace btl
