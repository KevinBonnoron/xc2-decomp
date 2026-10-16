#include "battle/character/character_manager_battle.h"

#include "battle/battle_global.h"
#include "battle/character/character_parameter_battle.h"
#include "battle/talk_manager_battle.h"
#include "gf/gf_allocator.h"
#include "gf/object/gf_obj_handle.h"

namespace btl {

CharacterManager::CharacterManager() : controlCharacterId(CHARACTER_COUNT) {
  for (int i = 0; i < CHARACTER_PLAYER_COUNT; i++) {
    playerAiChrTable[i] = 0xff;
  }

  for (int i = 0; i < CHARACTER_COUNT - CHARACTER_PLAYER_COUNT; i++) {
    enemyAiChrTable[i] = 0xff;
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
  int high = static_cast<int>(registeredIds.size()) - 1;
  while (low <= high) {
    int middle = (low + high) >> 1;
    u8 id = registeredIds[middle];
    gf::GF_OBJ_HANDLE *middleHandle = characters[id].character.handle;
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
    playerAiChrTable[aiId] = value;
  } else {
    enemyAiChrTable[aiId] = value;
  }
}

BattleCharacter *CharacterManager::GetCharacterConst(gf::GF_OBJ_HANDLE *handle) const {
  int id = SearchCharacter(handle);
  if (id < 0) {
    return nullptr;
  }

  return const_cast<BattleCharacter *>(&characters[id].character);
}

BattleCharacter *CharacterManager::GetCharacterConst(int id) const {
  if (id >= 0 && id < CHARACTER_COUNT) {
    return characters[id].isUse ? const_cast<BattleCharacter *>(&characters[id].character) : nullptr;
  }

  return nullptr;
}

gf::GF_OBJ_HANDLE *CharacterManager::GetCharacterHandle(int id) const {
  const BattleCharacter *character = GetCharacterConst(id);
  if (character == nullptr) {
    return gf::INVALID_HANDLE;
  }

  return character->handle;
}

BattleCharacter *CharacterManager::GetControlCharacter() {
  if (controlCharacterId >= CHARACTER_COUNT) {
    return nullptr;
  }

  return characters[controlCharacterId].isUse ? &characters[controlCharacterId].character : nullptr;
}

bool CharacterManager::IsControlCharacter(gf::GF_OBJ_HANDLE *handle) {
  if (controlCharacterId >= CHARACTER_COUNT) {
    return false;
  }

  const BattleCharacter *character = characters[controlCharacterId].isUse ? &characters[controlCharacterId].character : nullptr;
  return character != nullptr && character->handle == handle;
}

int CharacterManager::GetAliveBossNum() const {
  int num = 0;
  for (int id = CHARACTER_PLAYER_COUNT; id < CHARACTER_COUNT; id++) {
    if (!characters[id].isUse) {
      continue;
    }

    const BattleCharacter &character = characters[id].character;
    const CharacterParameter *parameter = character.GetCharacterParameterConst(true);
    if (parameter == nullptr || !parameter->isBattle || parameter->isBlade || character.IsDead(0)) {
      continue;
    }

    num += parameter->IsBoss();
  }

  return num;
}

bool CharacterManager::IsCharacterDead(int id) const {
  if (id < 0 || id >= CHARACTER_COUNT || !characters[id].isUse) {
    return true;
  }

  return characters[id].character.IsDead(0);
}

void CharacterManager::PostUpdate(const fw::UpdateInfo &updateInfo) { get()->PostUpdateProc(updateInfo); }

bool CharacterManager::IsExistAlivePlayer() const {
  for (int id = 0; id < CHARACTER_PLAYER_COUNT; id++) {
    if (characters[id].isUse && !characters[id].character.IsBlade() && !characters[id].character.IsDead(0)) {
      return true;
    }
  }

  return false;
}

bool CharacterManager::IsExistEnArrange(u32 enemy) const {
  for (int id = CHARACTER_PLAYER_COUNT; id < CHARACTER_COUNT; id++) {
    if (characters[id].isUse && static_cast<u32>(characters[id].character.bdatId) == enemy && characters[id].character.IsBattle()) {
      return true;
    }
  }

  return false;
}

bool CharacterManager::IsExistHikariSp() const {
  for (int id = CHARACTER_PLAYER_COUNT; id < CHARACTER_COUNT; id++) {
    if (!characters[id].isUse) {
      continue;
    }

    const CharacterParameter *parameter = characters[id].character.GetCharacterParameterConst(false);
    if (parameter != nullptr && parameter->IsInvalidHikariSp() && parameter->isBattle && !characters[id].character.IsDead(0)) {
      return true;
    }
  }

  return false;
}

bool CharacterManager::IsExistAlwaysKakusei() const {
  for (int id = CHARACTER_PLAYER_COUNT; id < CHARACTER_COUNT; id++) {
    if (!characters[id].isUse) {
      continue;
    }

    const CharacterParameter *parameter = characters[id].character.GetCharacterParameterConst(false);
    if (parameter != nullptr && parameter->IsAlwaysKakusei() && parameter->isBattle && !characters[id].character.IsDead(0)) {
      return true;
    }
  }

  return false;
}

void CharacterManager::PlayEnemyWinVoice() {
  for (int id = CHARACTER_PLAYER_COUNT; id < CHARACTER_COUNT; id++) {
    if (!characters[id].isUse) {
      continue;
    }

    BattleCharacter &character = characters[id].character;
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
    if (!characters[id].isUse) {
      continue;
    }

    BattleCharacter &character = characters[id].character;
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
