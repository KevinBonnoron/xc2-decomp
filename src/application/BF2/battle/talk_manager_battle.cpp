#include "battle/talk_manager_battle.h"

#include "battle/character/battle_character.h"
#include "bdat.h"
#include "gf/data/gf_bdat_id.h"
#include "gf/data/gf_data_bdat.h"
#include "gf/game/gf_game_voice.h"
#include "gf/gf_allocator.h"
#include "gf/object/gf_obj_handle.h"

namespace btl {

static const int s_bdatDefs[TalkManager::VOICE_TYPE_COUNT] = {-1, gf::BDAT_VO_BATTLE_DRIVER, gf::BDAT_VO_BATTLE_BLADE, gf::BDAT_VO_BATTLE_ENEMY, gf::BDAT_VO_WIN_SP};

TalkManager::TalkManager() : unknown12d8(), unknown14dc(), unknown1576() {}

TalkManager::~TalkManager() {}

void TalkManager::Create() {
  // __LINE__ must be 92 as in the original file: it is an argument of operator new.
#line 92
  TalkManager *manager = new (gf::getAllocator(gf::ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) TalkManager();
  manager->Initialize();
}

void TalkManager::ResetVoiceGroupID() { __builtin_memset(unknown14dc, 0, sizeof(unknown14dc)); }

void TalkManager::InitializeGroupTopData() {
  ResetVoiceGroupID();
  for (int type = VOICE_TYPE_DRIVER; type <= VOICE_TYPE_ENEMY; type++) {
    u8 *bdat = gf::GfDataBdat::getFP(s_bdatDefs[type]);
    int id = Bdat::getIdTop(bdat);
    int count = Bdat::getIdCount(bdat);
    u32 previous = 0;
    for (int end = id + count; id < end; id++) {
      u8 group = Bdat::getValCheck(bdat, "Group", id, 1);
      if (group == 0) {
        previous = 0;
      } else if (group != previous) {
        unknown14dc[group] = id;
        previous = group;
      }
    }
  }
}

void TalkManager::Initialize() { InitializeGroupTopData(); }

void TalkManager::Destroy() {
  if (get() != nullptr) {
    delete get();
  }
}

void TalkManager::Finalize() {}

void TalkManager::NotifyMapChange() { unknown898.clear(); }

bool TalkManager::IsEnableFieldBladeChange() const { return true; }

void TalkManager::PreUpdate(const fw::UpdateInfo &updateInfo) { get()->PreUpdateProc(updateInfo); }

void TalkManager::PreUpdateProc(const fw::UpdateInfo &) {}

void TalkManager::Update(const fw::UpdateInfo &updateInfo) { get()->UpdateProc(updateInfo); }

bool TalkManager::CheckPriority(gf::GF_OBJ_HANDLE *handle, int priority, bool isExcludeSame) const { return CheckPriority(GetRegisterDataConst(handle), priority, isExcludeSame); }

int TalkManager::GetBdatDef(int type) const {
  if (type >= VOICE_TYPE_NONE && type < VOICE_TYPE_COUNT) {
    return s_bdatDefs[type];
  }

  return -1;
}

bool TalkManager::CheckPriority(int id, int priority, bool isExcludeSame) const { return CheckPriority(GetRegisterDataConst(id), priority, isExcludeSame); }

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

gf::GAME_VOICE_HANDLE *TalkManager::PlayVoice(int id, int voice) {
  BattleCharacter *character = CharacterManager::get()->GetCharacterConst(id);
  if (character != nullptr) {
    int type;
    if (character->IsBlade()) {
      type = VOICE_TYPE_BLADE;
    } else if (character->IsPlayer()) {
      type = VOICE_TYPE_DRIVER;
    } else {
      type = VOICE_TYPE_ENEMY;
    }
    if (RegisterTalk(id, voice, type, -1, 0, 0, false)) {
      const CHR_VOICE_DATA *data = GetRegisterDataConst(id);
      if (data != nullptr) {
        return data->unknown08;
      }
    }
  }
  return nullptr;
}

gf::GAME_VOICE_HANDLE *TalkManager::PlayVoice(int id, const char *name) {
  gf::GAME_VOICE_HANDLE *voice = nullptr;
  BattleCharacter *character = CharacterManager::get()->GetCharacterConst(id);
  if (character != nullptr && character->unknown118 != gf::INVALID_HANDLE) {
    voice = gf::GfGameVoice::playVoice(character->unknown118, name, gf::CV_PRIO_UNKNOWN_2);
    if (voice != nullptr) {
      CHR_VOICE_DATA data;
      data.unknown00 = character->unknown118;
      data.unknown08 = voice;
      data.unknown10_0 = 0;
      data.unknown10_3 = 0;
      data.unknown11_5 = id;
      data.unknown12_4 = 0;
      data.unknown14 = 0x5a5a5a5a;
      CHR_VOICE_DATA *registered = unknown003(id);
      if (registered != nullptr) {
        *registered = data;
        return voice;
      }
      unknown08.push_back(data);
    }
  }
  return voice;
}

} // namespace btl
