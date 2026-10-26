#pragma once
#include "battle/arts_data.h"
#include "battle/character/character_manager_battle.h"
#include "battle/character/character_parameter_battle.h"
#include "battle/group_data.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/singleton.h"
#include "types.h"
#include <stddef.h>

namespace fw {
struct UpdateInfo;
}

namespace gf {
struct GF_OBJ_HANDLE;
class GfMenuCallContext;
} // namespace gf

namespace btl {

constexpr int PLAYER_PARAMETER_COUNT = 18;

class DataManager : public mm::mtl::PtrSingleton<DataManager> {
public:
  struct ENEMY_GROUP_DATA {
    gf::GF_OBJ_HANDLE *unknown00; // Inferred role: leader handle; original member name unknown.
    gf::GF_OBJ_HANDLE *unknown08; // Inferred role: member handle; original member name unknown.
    u8 _10[0x18 - 0x10];
  };

  enum POUCH_BUFF_TYPE {
    POUCH_BUFF_TYPE_DAMAGE_ARMOR,
    POUCH_BUFF_TYPE_UNKNOWN_4 = 4, // Inferred role: first value checked by the timing update; original name unknown.
    POUCH_BUFF_TYPE_KIZUNA = 6,
    POUCH_BUFF_TYPE_UNKNOWN_9 = 9,   // Inferred role: second value checked by the timing update; original name unknown.
    POUCH_BUFF_TYPE_UNKNOWN_12 = 12, // Inferred role: timing counter; original name unknown.
  };

  struct POUCH_BUFF_DATA {
    f32 unknown00[14]; // Inferred role: pouch buff params; original member name unknown.
    u8 _38[0x3b - 0x38];
    bool unknown3b; // Inferred role: timing flag; original member name unknown.
  };

  DataManager();
  ~DataManager();
  static void Create();
  static void Destroy();
  void Finalize();
  void Initialize();
  void AddPartyGauge(f32 value, int partyId, bool isNotify);
  void FluctuatePartyGauge(int value, int partyId);
  void InitializeComboRequestUI();
  const CharacterParameter *GetCharacterParameterConst(int id) const;
  const CharacterParameter *SearchCharacterParameterConst(gf::GF_OBJ_HANDLE *handle, bool) const;
  void GetArtsData(ARTS_DATA::DATA_TYPE type, int id, ARTS_DATA &data) const;
  ARTS_DATA *GetCacheArtsDataConst(ARTS_DATA::DATA_TYPE type, int id) const;
  ARTS_DATA *CacheArtsData(ARTS_DATA::DATA_TYPE type, int id, ARTS_DATA *cache) const;
  void UpdateCacheID(const ARTS_DATA *cache) const;
  f32 GetPouchBuffParam(int type, int pouch) const;
  int GetPartyGauge() const;
  void SetPartyGauge(int partyGauge, bool isNotify);
  bool IsPouchBuffTiming(int pouch) const;
  int RegisterEnemyGroup(gf::GF_OBJ_HANDLE *leader, gf::GF_OBJ_HANDLE *member);
  void ReleaseEnemyGroup(gf::GF_OBJ_HANDLE *handle);
  int GetEnemyGroupIndex(gf::GF_OBJ_HANDLE *handle);
  void DeleteElementalEffect();
  void RequestPermit(int party, gf::GF_OBJ_HANDLE *target);
  void UpdatePouchBuff(f32 time);
  static void PreUpdate(const fw::UpdateInfo &updateInfo);
  void PreUpdateProc(const fw::UpdateInfo &updateInfo);
  static void Update(const fw::UpdateInfo &updateInfo);
  void UpdateProc(const fw::UpdateInfo &updateInfo);
  void UpdateElementalEffect(f32 time);
  static void PostUpdate(const fw::UpdateInfo &updateInfo);
  void PostUpdateProc(const fw::UpdateInfo &updateInfo);
  void SetSpecialEffects(int effect, bool isEnable);
  void ResetRequestPermit();
  bool IsExistRequestPermit() const;
  bool IsSpecialEffects(int effect) const;
  static bool IsValidDeadEnhance(int enhance);
  static bool GetEnhanceData(int id, ENHANCE_EFFECT_DATA &data, bool);

  // Inferred role: whether the group of a party has a kizuna gauge; original name unknown.
  bool unknown001(int partyId) const { return partyId >= 0 && unknown10758[partyId].unknown105_5 && !unknown10758[partyId].unknown104_7; }

  PlayerParameter unknown08[PLAYER_PARAMETER_COUNT];                     // Inferred role: player parameters; original member name unknown.
  EnemyParameter *unknown7358[CHARACTER_COUNT - CHARACTER_PLAYER_COUNT]; // Inferred role: enemy parameters; original member name unknown.
  mm::mtl::FixedVector<u8, 65> unknown7588;                              // Inferred role: sorted driver arts cache ids; original member name unknown.
  ARTS_DATA unknown75d8[65];                                             // Inferred role: driver arts cache; original member name unknown.
  mm::mtl::FixedVector<u8, 35> unknownb0c0;                              // Inferred role: sorted blade arts cache ids; original member name unknown.
  ARTS_DATA unknownb0f0[35];                                             // Inferred role: blade arts cache; original member name unknown.
  mm::mtl::FixedVector<u8, 30> unknownd0a8;                              // Inferred role: sorted enemy arts cache ids; original member name unknown.
  ARTS_DATA unknownd0d0[30];                                             // Inferred role: enemy arts cache; original member name unknown.
  mm::mtl::FixedVector<u8, 30> unknownec00;                              // Inferred role: sorted special blade arts cache ids; original member name unknown.
  ARTS_DATA unknownec28[30];                                             // Inferred role: special blade arts cache; original member name unknown.
  GROUP_DATA unknown10758[38];                                           // Inferred role: character groups; original member name unknown.
  ENEMY_GROUP_DATA unknown12e88[35];                                     // Inferred role: enemy groups; original member name unknown.
  POUCH_BUFF_DATA unknown131d0[3];                                       // Inferred role: pouch buffs; original member name unknown.
  u8 _13284[0x13290 - 0x13284];
  gf::GfMenuCallContext *unknown13290; // Inferred role: combo request context; original member name unknown.
  gf::GF_OBJ_HANDLE *unknown13298;     // Inferred role: permit target; original member name unknown.
  s8 unknown132a0;                     // Inferred role: permit party; original member name unknown.
  u8 unknown132a1;                     // Inferred role: permit combo id; original member name unknown.
  u8 unknown132a2;                     // Inferred role: permit combo stage; original member name unknown.
  u8 unknown132a3;                     // Inferred role: elemental effect id; original member name unknown.
  u8 _132a4[0x132a5 - 0x132a4];
  bool unknown132a5[3]; // Inferred role: special effects; original member name unknown.
  bool unknown132a8;    // Inferred role: permit canceled; original member name unknown.
};

static_assert(offsetof(DataManager, unknown08) == 0x8, "");
static_assert(offsetof(DataManager, unknown7358) == 0x7358, "");
static_assert(offsetof(DataManager, unknown7588) == 0x7588, "");
static_assert(offsetof(DataManager, unknown75d8) == 0x75d8, "");
static_assert(offsetof(DataManager, unknownb0c0) == 0xb0c0, "");
static_assert(offsetof(DataManager, unknownb0f0) == 0xb0f0, "");
static_assert(offsetof(DataManager, unknownd0a8) == 0xd0a8, "");
static_assert(offsetof(DataManager, unknownd0d0) == 0xd0d0, "");
static_assert(offsetof(DataManager, unknownec00) == 0xec00, "");
static_assert(offsetof(DataManager, unknownec28) == 0xec28, "");
static_assert(offsetof(DataManager, unknown10758) == 0x10758, "");
static_assert(offsetof(DataManager, unknown12e88) == 0x12e88, "");
static_assert(offsetof(DataManager, unknown131d0) == 0x131d0, "");
static_assert(offsetof(DataManager, unknown13298) == 0x13298, "");
static_assert(offsetof(DataManager, unknown132a3) == 0x132a3, "");
static_assert(offsetof(DataManager, unknown132a5) == 0x132a5, "");

} // namespace btl
