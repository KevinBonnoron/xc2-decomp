#pragma once
#include "battle/character/character_manager_battle.h"
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

class TalkManager : public mm::mtl::PtrSingleton<TalkManager> {
public:
  enum TRIGGER {
    TRIGGER_ENEMY_WIN = 26,
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
    gf::GF_OBJ_HANDLE *handle;
    u8 _08[0x10 - 0x08];
    u32 type : 3;
    u32 voiceId : 10;
    u32 id : 7;
    u32 priority : 8;
  };

  void ResetVoiceGroupID();
  void Initialize();
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
  void PlayVoice(int id, int voice);

  mm::mtl::FixedVector<CHR_VOICE_DATA, CHARACTER_COUNT> registeredVoices;
  u8 _880[0x14dc - 0x880];
  u16 groupTops[77];
};

static_assert(sizeof(TalkManager::CHR_VOICE_DATA) == 0x18, "");
static_assert(offsetof(TalkManager, registeredVoices) == 0x8, "");
static_assert(offsetof(TalkManager, groupTops) == 0x14dc, "");

} // namespace btl
