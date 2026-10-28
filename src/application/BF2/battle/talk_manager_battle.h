#pragma once
#include "battle/character/character_manager_battle.h"
#include "mm_mtl/fixed_list.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/singleton.h"
#include "types.h"
#include <stddef.h>

namespace fw {
struct UpdateInfo;
}

namespace gf {
struct GF_OBJ_HANDLE;
struct GAME_VOICE_HANDLE;
} // namespace gf

namespace btl {

class TalkManager : public mm::mtl::PtrSingleton<TalkManager> {
public:
  enum TRIGGER {
    TRIGGER_STRIKE_DAMAGE = 20,
    TRIGGER_UNKNOWN_1C = 28, // Inferred role: blade guard, one less for a player; original name unknown.
    TRIGGER_ENEMY_WIN = 26,
    TRIGGER_UNKNOWN_2B = 43, // Inferred role: first of three triggers raised when the character gets the hate, one per custom voice slot; original name unknown.
  };

  enum VOICE_TYPE {
    VOICE_TYPE_NONE,
    VOICE_TYPE_DRIVER,
    VOICE_TYPE_BLADE,
    VOICE_TYPE_ENEMY,
    VOICE_TYPE_WIN_SP,
    VOICE_TYPE_COUNT,
  };

  struct CHR_VOICE_DATA {
    gf::GF_OBJ_HANDLE *unknown00;     // Inferred role: handle; original member name unknown.
    gf::GAME_VOICE_HANDLE *unknown08; // Inferred role: voice handle; original member name unknown.
    u32 unknown10_0 : 3;              // Inferred role: type; original member name unknown.
    u32 unknown10_3 : 10;             // Inferred role: voice id; original member name unknown.
    u32 unknown11_5 : 7;              // Inferred role: id; original member name unknown.
    u32 unknown12_4 : 8;              // Inferred role: priority; original member name unknown.
    u32 unknown14;                    // Role and original member name unknown.
  };

  // Inferred role: a waiting talk; original type name unknown.
  struct unknown001 {
    u8 _00[0x2 - 0x0];
    s8 unknown02; // Inferred role: rest count; original member name unknown.
    u8 _03[0x4 - 0x3];
  };

  // Inferred role: a queued voice; original type name unknown.
  struct unknown002 {
    u32 unknown00; // Role and original member name unknown.
    u32 unknown04; // Role and original member name unknown.
  };

  TalkManager();
  ~TalkManager();
  void ResetVoiceGroupID();
  static void Create();
  void Initialize();
  void NotifyMapChange();
  static void Destroy();
  void Finalize();
  void InitializeGroupTopData();
  bool IsTalk(int id) const;
  bool IsEnableFieldBladeChange() const;
  bool IsPlayingEnemyVoice() const;
  bool IsPlayingEnemyWinVoice() const;
  static void PreUpdate(const fw::UpdateInfo &updateInfo);
  void PreUpdateProc(const fw::UpdateInfo &updateInfo);
  static void Update(const fw::UpdateInfo &updateInfo);
  void UpdateProc(const fw::UpdateInfo &updateInfo);
  bool CheckPriority(gf::GF_OBJ_HANDLE *handle, int priority, bool isExcludeSame) const;
  int GetBdatDef(int type) const;
  bool CheckPriority(int id, int priority, bool isExcludeSame) const;
  const CHR_VOICE_DATA *GetRegisterDataConst(int id) const;
  const CHR_VOICE_DATA *GetRegisterDataConst(gf::GF_OBJ_HANDLE *handle) const;
  int GetPlayVoiceID(int id) const;
  bool CheckPriority(const CHR_VOICE_DATA *data, int priority, bool isExcludeSame) const;
  int GetGroupTop(int group) const;
  bool NotifyTrigger(int id, TRIGGER trigger, int, int);
  gf::GAME_VOICE_HANDLE *PlayVoice(int id, int voice);
  gf::GAME_VOICE_HANDLE *PlayVoice(int id, const char *name);

  // Inferred role: non-const GetRegisterDataConst; original name unknown.
  CHR_VOICE_DATA *unknown003(int id) {
    for (CHR_VOICE_DATA &data : unknown08) {
      if (data.unknown11_5 == id) {
        return &data;
      }
    }

    return nullptr;
  }

  bool RegisterTalk(int id, int voice, int type, int group, int, int, bool);

  mm::mtl::FixedVector<CHR_VOICE_DATA, CHARACTER_COUNT> unknown08; // Inferred role: registered voices; original member name unknown.
  mm::mtl::FixedVector<unknown001, 4> unknown880;                  // Inferred role: waiting talks; original member name unknown.
  mm::mtl::FixedList<unknown002, 200> unknown898;                  // Inferred role: queued voices; original member name unknown.
  u8 unknown12d8[0x14dc - 0x12d8];                                 // Role and original member name unknown.
  u16 unknown14dc[77];                                             // Inferred role: group tops; original member name unknown.
  u8 unknown1576[0x157a - 0x1576];                                 // Role and original member name unknown.
};

static_assert(offsetof(TalkManager::CHR_VOICE_DATA, unknown08) == 0x8, "");
static_assert(offsetof(TalkManager::CHR_VOICE_DATA, unknown14) == 0x14, "");
static_assert(sizeof(TalkManager::CHR_VOICE_DATA) == 0x18, "");
static_assert(offsetof(TalkManager, unknown08) == 0x8, "");
static_assert(offsetof(TalkManager, unknown880) == 0x880, "");
static_assert(offsetof(TalkManager, unknown898) == 0x898, "");
static_assert(offsetof(TalkManager, unknown14dc) == 0x14dc, "");

} // namespace btl
