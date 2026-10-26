#include "battle/sp_attack_manager.h"

#include "battle/character/battle_character.h"
#include "battle/character/character_manager_battle.h"
#include "battle/utility_battle.h"
#include "fw/fw_camera.h"
#include "gf/object/gf_obj_handle.h"

namespace btl {

constexpr int SP_ATTACK_SLOT_NONE = 15;

static void unknown001(gf::GF_OBJ_HANDLE *handle) { // Inferred role: clear camera fade disable; original function name unknown.
  BattleCharacter *character = CharacterManager::get()->GetCharacterConst(handle);
  if (character != nullptr) {
    character->unknownf83 &= 0xfb;
  }
}

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

void SpAttackManager::DeleteCamera(bool isFade) {
  if (unknown08.get() != nullptr) {
    f32 time = 0.0f;
    if (isFade) {
      time = static_cast<f32>(unknown210) * (1.0f / 30.0f);
    }
    fw::CameraManager::get()->unknown20[0].pop(unknown08, time);
    unknown08 = nullptr;
    unknown20c = 0;
  }

  gf::GF_OBJ_HANDLE *handle = unknown10;
  unknown001(handle);
  unknown10 = gf::INVALID_HANDLE;

  handle = unknown18;
  unknown001(handle);
  unknown18 = gf::INVALID_HANDLE;

  handle = unknown20;
  unknown001(handle);
  unknown20 = gf::INVALID_HANDLE;
}

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

void SpAttackManager::NotifyProgress(gf::GF_OBJ_HANDLE *handle, PROGRESS_ID progress) {
  PROC_DATA *proc = const_cast<PROC_DATA *>(GetProcDataConst(handle));
  if (proc == nullptr) {
    return;
  }

  int step;
  if (progress == 0) {
    if (proc->unknown08 == nullptr) {
      proc->unknown5c_4 = true;
    } else {
      if (Utility::IsThirdCharacter(handle)) {
        proc->unknown5c_5 = true;
      } else {
        proc->unknown5c_4 = true;
      }
      if (!(proc->unknown5c_4 && proc->unknown5c_5)) {
        return;
      }
    }
    step = 4;
  } else if (progress == 2) {
    step = 5;
  } else if (progress == 3) {
    step = 7;
  } else {
    return;
  }
  proc->unknown40 = step;
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
