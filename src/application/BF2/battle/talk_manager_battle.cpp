#include "battle/talk_manager_battle.h"

#include "gf/data/gf_bdat_id.h"

namespace btl {

static const int s_bdatDefs[TalkManager::VOICE_TYPE_COUNT] = {
    -1, gf::BDAT_VO_BATTLE_DRIVER, gf::BDAT_VO_BATTLE_BLADE, gf::BDAT_VO_BATTLE_ENEMY, gf::BDAT_VO_WIN_SP};

void TalkManager::ResetVoiceGroupID() { __builtin_memset(unknown14dc, 0, sizeof(unknown14dc)); }

void TalkManager::Initialize() { InitializeGroupTopData(); }

void TalkManager::Destroy() {
  if (get() != nullptr) {
    delete get();
  }
}

void TalkManager::Finalize() {}

bool TalkManager::IsEnableFieldBladeChange() const { return true; }

void TalkManager::PreUpdate(const fw::UpdateInfo &updateInfo) { get()->PreUpdateProc(updateInfo); }

void TalkManager::PreUpdateProc(const fw::UpdateInfo &) {}

void TalkManager::Update(const fw::UpdateInfo &updateInfo) { get()->UpdateProc(updateInfo); }

bool TalkManager::CheckPriority(gf::GF_OBJ_HANDLE *handle, int priority, bool isExcludeSame) const {
  return CheckPriority(GetRegisterDataConst(handle), priority, isExcludeSame);
}

int TalkManager::GetBdatDef(int type) const {
  if (type >= VOICE_TYPE_NONE && type < VOICE_TYPE_COUNT) {
    return s_bdatDefs[type];
  }

  return -1;
}

bool TalkManager::CheckPriority(int id, int priority, bool isExcludeSame) const {
  return CheckPriority(GetRegisterDataConst(id), priority, isExcludeSame);
}

const TalkManager::CHR_VOICE_DATA *TalkManager::GetRegisterDataConst(int id) const {
  for (const CHR_VOICE_DATA &data : unknown08) {
    if (data.unknown11_5 == id) {
      return &data;
    }
  }

  return nullptr;
}

const TalkManager::CHR_VOICE_DATA *TalkManager::GetRegisterDataConst(gf::GF_OBJ_HANDLE *handle) const {
  for (const CHR_VOICE_DATA &data : unknown08) {
    if (data.unknown00 == handle) {
      return &data;
    }
  }

  return nullptr;
}

int TalkManager::GetPlayVoiceID(int id) const {
  const CHR_VOICE_DATA *data = GetRegisterDataConst(id);
  if (data == nullptr) {
    return 0;
  }

  return data->unknown10_3;
}

bool TalkManager::CheckPriority(const CHR_VOICE_DATA *data, int priority, bool isExcludeSame) const {
  if (data == nullptr) {
    return true;
  }

  if (data->unknown12_4 < priority) {
    return false;
  }

  if (data->unknown12_4 == priority && isExcludeSame) {
    return false;
  }

  return true;
}

int TalkManager::GetGroupTop(int group) const {
  if (group >= 0 && group <= 76) {
    u16 top = unknown14dc[group];
    return top == 0 ? -1 : top;
  }

  return -1;
}

} // namespace btl
