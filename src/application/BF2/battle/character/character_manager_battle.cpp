#include "battle/character/character_manager_battle.h"

#include "battle/battle_global.h"
#include "battle/character/character_parameter_battle.h"
#include "battle/talk_manager_battle.h"
#include "gf/gf_allocator.h"
#include "gf/object/gf_obj_handle.h"

namespace btl {

CharacterManager::CharacterManager() : unknown65488(CHARACTER_COUNT) {
  for (int i = 0; i < CHARACTER_PLAYER_COUNT; i++) {
    unknown65489[i] = 0xff;
  }

  for (int i = 0; i < CHARACTER_COUNT - CHARACTER_PLAYER_COUNT; i++) {
    unknown6549d[i] = 0xff;
  }
}

CharacterManager::~CharacterManager() {}

void CharacterManager::Create() {
  // __LINE__ must be 71 as in the original file: its value changes the instruction order.
#line 71
  CharacterManager *manager = new (gf::getAllocator(gf::ALLOCATOR_SYSTEM), __FILE__, __LINE__, 8) CharacterManager();
  manager->Initialize();
}

void CharacterManager::Initialize() {}

void CharacterManager::Destroy() {
  if (get() != nullptr) {
    delete get();
  }
}

void CharacterManager::Finalize() {}

int CharacterManager::SearchCharacter(gf::GF_OBJ_HANDLE *handle) const {
  if (handle == gf::INVALID_HANDLE) {
    return -1;
  }

  int low = 0;
  int high = static_cast<int>(unknown65420.size()) - 1;
  while (low <= high) {
    int middle = (low + high) >> 1;
    u8 id = unknown65420[middle];
    gf::GF_OBJ_HANDLE *middleHandle = unknown20[id].unknown00.unknown118;
    if (middleHandle == handle) {
      return id;
    }

    if (middleHandle > handle) {
      high = middle - 1;
    } else {
      low = middle + 1;
    }
  }

  return -1;
}

void CharacterManager::Release(gf::GF_OBJ_HANDLE *handle) {
  int id = SearchCharacter(handle);
  if (id >= 0) {
    Release(id, handle);
  }
}

void CharacterManager::SetAiChrTable(int id, int aiId, bool isPlayer) {
  u8 value = id < 0 ? -1 : id;
  if (isPlayer) {
    unknown65489[aiId] = value;
  } else {
    unknown6549d[aiId] = value;
  }
}

BattleCharacter *CharacterManager::GetCharacterConst(gf::GF_OBJ_HANDLE *handle) const {
  int id = SearchCharacter(handle);
  if (id < 0) {
    return nullptr;
  }

  return const_cast<BattleCharacter *>(&unknown20[id].unknown00);
}

BattleCharacter *CharacterManager::GetCharacterConst(int id) const {
  if (id >= 0 && id < CHARACTER_COUNT) {
    return unknown20[id].unknown11f0 ? const_cast<BattleCharacter *>(&unknown20[id].unknown00) : nullptr;
  }

  return nullptr;
}

gf::GF_OBJ_HANDLE *CharacterManager::GetCharacterHandle(int id) const {
  const BattleCharacter *character = GetCharacterConst(id);
  if (character == nullptr) {
    return gf::INVALID_HANDLE;
  }

  return character->unknown118;
}

BattleCharacter *CharacterManager::GetControlCharacter() {
  if (unknown65488 >= CHARACTER_COUNT) {
    return nullptr;
  }

  return unknown20[unknown65488].unknown11f0 ? &unknown20[unknown65488].unknown00 : nullptr;
}

bool CharacterManager::IsControlCharacter(gf::GF_OBJ_HANDLE *handle) {
  if (unknown65488 >= CHARACTER_COUNT) {
    return false;
  }

  const BattleCharacter *character = unknown20[unknown65488].unknown11f0 ? &unknown20[unknown65488].unknown00 : nullptr;
  return character != nullptr && character->unknown118 == handle;
}

BattleCharacter *CharacterManager::GetBattleEnemyCharacter(bool isAlive, bool isExcludeBlade) {
  for (int id = CHARACTER_PLAYER_COUNT; id < CHARACTER_COUNT; id++) {
    if (!unknown20[id].unknown11f0) {
      continue;
    }

    BattleCharacter &character = unknown20[id].unknown00;
    if (!character.IsBattle()) {
      continue;
    }
    if (isExcludeBlade && character.IsBlade()) {
      continue;
    }
    if (isAlive && character.IsDead(0)) {
      continue;
    }
    return &character;
  }

  return nullptr;
}

int CharacterManager::GetAliveBossNum() const {
  int num = 0;
  for (int id = CHARACTER_PLAYER_COUNT; id < CHARACTER_COUNT; id++) {
    if (!unknown20[id].unknown11f0) {
      continue;
    }

    const BattleCharacter &character = unknown20[id].unknown00;
    const CharacterParameter *parameter = character.GetCharacterParameterConst(true);
    if (parameter == nullptr || !parameter->unknown5df_1 || parameter->m_invalidTarget || character.IsDead(0)) {
      continue;
    }

    num += parameter->IsBoss();
  }

  return num;
}

int CharacterManager::GetBattleEnemyMaxLevel(bool includeNamed) const {
  int maxLevel = 0;
  for (int id = CHARACTER_PLAYER_COUNT; id < CHARACTER_COUNT; id++) {
    const BattleCharacter *character = GetCharacterConst(id);
    if (character == nullptr) {
      continue;
    }

    const CharacterParameter *parameter = character->GetCharacterParameterConst(false);
    if (parameter == nullptr || !parameter->unknown5df_1 || character->IsDead(0)) {
      continue;
    }

    int level = parameter->GetLevel();
    if (includeNamed && parameter->IsNamed()) {
      level += 15;
    }
    if (maxLevel <= level) {
      maxLevel = level;
    }
  }

  return maxLevel;
}

bool CharacterManager::IsCharacterDead(int id) const {
  if (id < 0 || id >= CHARACTER_COUNT || !unknown20[id].unknown11f0) {
    return true;
  }

  return unknown20[id].unknown00.IsDead(0);
}

bool CharacterManager::IsCharacterDead(gf::GF_OBJ_HANDLE *handle) const { return IsCharacterDead(SearchCharacter(handle)); }

void CharacterManager::PostUpdate(const fw::UpdateInfo &updateInfo) { get()->PostUpdateProc(updateInfo); }

void CharacterManager::PostUpdateProc(const fw::UpdateInfo &updateInfo) {
  bool isScout = false;
  for (u8 id : unknown65420) {
    BattleCharacter &character = unknown20[id].unknown00;
    character.PostManagerUpdate(updateInfo);
    if (character.IsPlayer()) {
      character.UpdateHateRingData();
    } else if (!isScout) {
      isScout = character.IsScout();
    }
  }
  BattleGlobal::get()->unknown65e0_4 = isScout;
  for (u8 id : unknown65420) {
    if (unknown20[id].unknown00.IsEnemy()) {
      unknown20[id].unknown00.UpdateHateRingData();
    }
  }
}

bool CharacterManager::IsExistAlivePlayer() const {
  for (int id = 0; id < CHARACTER_PLAYER_COUNT; id++) {
    if (unknown20[id].unknown11f0 && !unknown20[id].unknown00.IsBlade() && !unknown20[id].unknown00.IsDead(0)) {
      return true;
    }
  }

  return false;
}

bool CharacterManager::IsExistEnArrange(u32 enemy) const {
  for (int id = CHARACTER_PLAYER_COUNT; id < CHARACTER_COUNT; id++) {
    if (unknown20[id].unknown11f0 && static_cast<u32>(unknown20[id].unknown00.unknowncc8) == enemy && unknown20[id].unknown00.IsBattle()) {
      return true;
    }
  }

  return false;
}

bool CharacterManager::IsExistHikariSp() const {
  for (int id = CHARACTER_PLAYER_COUNT; id < CHARACTER_COUNT; id++) {
    if (!unknown20[id].unknown11f0) {
      continue;
    }

    const CharacterParameter *parameter = unknown20[id].unknown00.GetCharacterParameterConst(false);
    if (parameter != nullptr && parameter->IsInvalidHikariSp() && parameter->unknown5df_1 && !unknown20[id].unknown00.IsDead(0)) {
      return true;
    }
  }

  return false;
}

bool CharacterManager::IsExistAlwaysKakusei() const {
  for (int id = CHARACTER_PLAYER_COUNT; id < CHARACTER_COUNT; id++) {
    if (!unknown20[id].unknown11f0) {
      continue;
    }

    const CharacterParameter *parameter = unknown20[id].unknown00.GetCharacterParameterConst(false);
    if (parameter != nullptr && parameter->IsAlwaysKakusei() && parameter->unknown5df_1 && !unknown20[id].unknown00.IsDead(0)) {
      return true;
    }
  }

  return false;
}

void CharacterManager::PlayEnemyWinVoice() {
  for (int id = CHARACTER_PLAYER_COUNT; id < CHARACTER_COUNT; id++) {
    if (!unknown20[id].unknown11f0) {
      continue;
    }

    BattleCharacter &character = unknown20[id].unknown00;
    if (!character.IsBattle() || character.IsBlade() || character.IsDead(0)) {
      continue;
    }

    if (TalkManager::get()->NotifyTrigger(id, TalkManager::TRIGGER_ENEMY_WIN, 0, 0)) {
      break;
    }
  }
}

void CharacterManager::SetupBGM() {
  bool isReset = false;
  for (int id = CHARACTER_PLAYER_COUNT; id < CHARACTER_COUNT; id++) {
    if (!unknown20[id].unknown11f0) {
      continue;
    }

    BattleCharacter &character = unknown20[id].unknown00;
    if (!character.IsBattle() || character.IsDead(0)) {
      continue;
    }

    CharacterParameter *parameter = character.GetCharacterParameter(true);
    if (parameter == nullptr) {
      continue;
    }

    if (!isReset) {
      BattleGlobal::get()->ResetBGM();
    }

    parameter->SetupBGM();
    isReset = true;
  }
}

} // namespace btl
