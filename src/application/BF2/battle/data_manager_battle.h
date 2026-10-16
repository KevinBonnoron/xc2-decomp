#pragma once
#include "battle/arts_data.h"
#include "battle/character/character_manager_battle.h"
#include "battle/character/character_parameter_battle.h"
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

class DataManager : public mm::mtl::PtrSingleton<DataManager> {
public:
  struct ENEMY_GROUP_DATA {
    gf::GF_OBJ_HANDLE *leader;
    gf::GF_OBJ_HANDLE *member;
    u8 _10[0x18 - 0x10];
  };

  enum POUCH_BUFF_TYPE {
    POUCH_BUFF_TYPE_KIZUNA = 6,
  };

  struct POUCH_BUFF_DATA {
    f32 params[14];
    u8 _38[0x3b - 0x38];
    bool isTiming;
  };

  const CharacterParameter *GetCharacterParameterConst(int id) const;
  void GetArtsData(ARTS_DATA::DATA_TYPE type, int id, ARTS_DATA &data) const;
  f32 GetPouchBuffParam(int type, int pouch) const;
  int GetPartyGauge() const;
  void SetPartyGauge(int partyGauge, bool isNotify);
  bool IsPouchBuffTiming(int pouch) const;
  int RegisterEnemyGroup(gf::GF_OBJ_HANDLE *leader, gf::GF_OBJ_HANDLE *member);
  void ReleaseEnemyGroup(gf::GF_OBJ_HANDLE *handle);
  int GetEnemyGroupIndex(gf::GF_OBJ_HANDLE *handle);
  void DeleteElementalEffect();
  static void Update(const fw::UpdateInfo &updateInfo);
  void UpdateProc(const fw::UpdateInfo &updateInfo);
  static void PostUpdate(const fw::UpdateInfo &updateInfo);
  void SetSpecialEffects(int effect, bool isEnable);
  bool IsSpecialEffects(int effect) const;
  static bool GetEnhanceData(int id, ENHANCE_EFFECT_DATA &data, bool);

  PlayerParameter playerParameters[18];
  EnemyParameter *enemyParameters[CHARACTER_COUNT - CHARACTER_PLAYER_COUNT];
  u8 _7588[0x12e88 - 0x7588];
  ENEMY_GROUP_DATA enemyGroups[35];
  POUCH_BUFF_DATA pouchBuffs[3];
  u8 _13284[0x132a3 - 0x13284];
  u8 elementalEffectId;
  u8 _132a4[0x132a5 - 0x132a4];
  bool specialEffects[3];
};

static_assert(offsetof(DataManager, playerParameters) == 0x8, "");
static_assert(offsetof(DataManager, enemyParameters) == 0x7358, "");
static_assert(offsetof(DataManager, enemyGroups) == 0x12e88, "");
static_assert(offsetof(DataManager, pouchBuffs) == 0x131d0, "");
static_assert(offsetof(DataManager, elementalEffectId) == 0x132a3, "");
static_assert(offsetof(DataManager, specialEffects) == 0x132a5, "");

} // namespace btl
