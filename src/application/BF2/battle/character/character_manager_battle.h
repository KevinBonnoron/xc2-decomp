#pragma once
#include "battle/character/battle_character.h"
#include "framework/message/message_object.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/singleton.h"
#include "types.h"
#include <stddef.h>

namespace fw {
struct UpdateInfo;
}

namespace gf {
struct GF_OBJ_HANDLE;
}

namespace btl {

constexpr int CHARACTER_PLAYER_COUNT = 20;
constexpr int CHARACTER_COUNT = 90;

class CharacterManager : public mm::mtl::PtrSingleton<CharacterManager>, public fw::MessageObject {
public:
  struct CHARACTER_DATA {
    CHARACTER_DATA() : unknown11f0(false) {}

    BattleCharacter unknown00; // Inferred role: character; original member name unknown.
    bool unknown11f0;          // Inferred role: in use; original member name unknown.
  };

  CharacterManager();
  ~CharacterManager();
  static void Create();
  void Initialize();
  static void Destroy();
  void Finalize();
  int SearchCharacter(gf::GF_OBJ_HANDLE *handle) const;
  void Release(gf::GF_OBJ_HANDLE *handle);
  void Release(int id, gf::GF_OBJ_HANDLE *handle);
  void SetAiChrTable(int id, int aiId, bool isPlayer);
  BattleCharacter *GetCharacterConst(gf::GF_OBJ_HANDLE *handle) const;
  BattleCharacter *GetCharacterConst(int id) const;
  gf::GF_OBJ_HANDLE *GetCharacterHandle(int id) const;
  BattleCharacter *GetControlCharacter();
  bool IsControlCharacter(gf::GF_OBJ_HANDLE *handle);
  BattleCharacter *GetBattleEnemyCharacter(bool isAlive, bool isExcludeBlade);
  int GetAliveBossNum() const;
  bool IsCharacterDead(int id) const;
  bool IsCharacterDead(gf::GF_OBJ_HANDLE *handle) const;
  int GetBattleEnemyMaxLevel(bool includeNamed) const;
  static void Update(const fw::UpdateInfo &updateInfo);
  void UpdateProc(const fw::UpdateInfo &updateInfo);
  void AssignAiChrID();
  static void PostUpdate(const fw::UpdateInfo &updateInfo);
  void PostUpdateProc(const fw::UpdateInfo &updateInfo);
  int GetCharacterIDByAiChrID(int aiId, bool isPlayer) const;
  bool IsExistAlivePlayer() const;
  bool IsExistBattlePlayer() const;
  bool IsExistBattleEnemy(bool *isAngry, gf::GF_OBJ_HANDLE *exclude, bool isIncludeAngry) const;
  void BattleEndInitialize();
  bool IsExistEnArrange(u32 enemy) const;
  bool IsExistHikariSp() const;
  bool IsExistAlwaysKakusei() const;
  bool IsExistHomuri() const;
  void PlayEnemyWinVoice();
  void SetupBGM();

  CHARACTER_DATA unknown20[CHARACTER_COUNT];                 // Inferred role: characters; original member name unknown.
  mm::mtl::FixedVector<u8, CHARACTER_COUNT> unknown65420;    // Inferred role: registered ids; original member name unknown.
  u8 unknown65488;                                           // Inferred role: control character id; original member name unknown.
  u8 unknown65489[CHARACTER_PLAYER_COUNT];                   // Inferred role: player AI character table; original member name unknown.
  u8 unknown6549d[CHARACTER_COUNT - CHARACTER_PLAYER_COUNT]; // Inferred role: enemy AI character table; original member name unknown.
};

static_assert(sizeof(CharacterManager::CHARACTER_DATA) == 0x1200, "");
static_assert(offsetof(CharacterManager, unknown20) == 0x20, "");
static_assert(offsetof(CharacterManager, unknown65420) == 0x65420, "");
static_assert(offsetof(CharacterManager, unknown65488) == 0x65488, "");
static_assert(offsetof(CharacterManager, unknown65489) == 0x65489, "");
static_assert(offsetof(CharacterManager, unknown6549d) == 0x6549d, "");
static_assert(sizeof(CharacterManager) == 0x654f0, "");

} // namespace btl
