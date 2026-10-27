#pragma once
#include <stddef.h>

#include "battle/arts_data.h"
#include "gf/data/gf_data_weapon.h"
#include "mm_mtl/fixed_vector.h"
#include "types.h"

namespace mm {
struct Vec3;
} // namespace mm

namespace fw {
struct UpdateInfo;
}

namespace gf {
struct GF_OBJ_HANDLE;
class GfObj;
struct GfObjPropertyCharacter;
class GfStatusProperty;
struct SDataEnemy;
} // namespace gf

namespace btl {

class GROUP_DATA;

constexpr int SPECIAL_ENHANCE_COUNT = 14;
constexpr int ADDITIONAL_ENHANCE_COUNT = 6;
constexpr int HATE_COUNT = 3;

struct FIGHT_COMBO_DATA {
  // Inferred role: resets the combo to its empty state; original name unknown.
  void unknown001() {
    unknown00 = 0;
    unknown01 = 0x5a;
    unknown02 = 0;
    unknown04 = 0;
    unknown08 = 0.0f;
    unknown0c = 0;
    unknown10 = 0;
    unknown14 = 0.0f;
  }

  u8 unknown00;  // Inferred role: combo id; original member name unknown.
  u8 unknown01;  // Inferred role: character id; original member name unknown.
  u16 unknown02; // Inferred role: base value; original member name unknown.
  u32 unknown04; // Role and original member name unknown.
  f32 unknown08; // Inferred role: rest time; original member name unknown.
  u32 unknown0c; // Role and original member name unknown.
  u32 unknown10; // Role and original member name unknown.
  f32 unknown14; // Role and original member name unknown.
};

static_assert(sizeof(FIGHT_COMBO_DATA) == 0x18, "");

struct ENHANCE_EFFECT_DATA {
  u16 unknown00; // Inferred role: enhance id; original member name unknown.
  u8 _02[0x8 - 0x2];
  f32 unknown08; // Inferred role: value; original member name unknown.
};

struct BUFF_DATA {
  u16 unknown00; // Inferred role: buff id; original member name unknown.
  u8 _02[0x4 - 0x2];
  f32 unknown04; // Inferred role: rest frame; original member name unknown.
  f32 unknown08; // Inferred role: effect; original member name unknown.
  u8 _0c[0x10 - 0xc];
};

class CharacterParameter {
public:
  enum ADD_ENHANCE_TYPE {
    ADD_ENHANCE_TYPE_HP_RATE,
    ADD_ENHANCE_TYPE_STRENGTH_RATE,
    ADD_ENHANCE_TYPE_ETHER_POWER_RATE,
    ADD_ENHANCE_TYPE_DEX_RATE,
    ADD_ENHANCE_TYPE_AGILITY_RATE,
    ADD_ENHANCE_TYPE_LUCK_RATE,
    ADD_ENHANCE_TYPE_CRITICAL_RATE,
    ADD_ENHANCE_TYPE_PHYSICAL_ARMOR_RATE,
    ADD_ENHANCE_TYPE_ETHER_ARMOR_RATE,
    ADD_ENHANCE_TYPE_GUARD_RATE,
    ADD_ENHANCE_TYPE_HP,
    ADD_ENHANCE_TYPE_STRENGTH,
    ADD_ENHANCE_TYPE_ETHER_POWER,
    ADD_ENHANCE_TYPE_DEX,
    ADD_ENHANCE_TYPE_AGILITY,
    ADD_ENHANCE_TYPE_LUCK,
    ADD_ENHANCE_TYPE_CRITICAL,
    ADD_ENHANCE_TYPE_PHYSICAL_ARMOR,
    ADD_ENHANCE_TYPE_ETHER_ARMOR,
    ADD_ENHANCE_TYPE_GUARD,
  };

  enum SPECIAL_ENHANCE_TYPE {};

  struct ADDITIONAL_ENHANCE_DATA {
    ENHANCE_EFFECT_DATA unknown00; // Inferred role: effect; original member name unknown.
    int unknown0c;                 // Inferred role: enhance; original member name unknown.
  };

  struct ENHANCE_DATA {
    f32 unknown00; // Inferred role: value; original member name unknown.
    u8 _04[0x6 - 0x4];
    u16 unknown06; // Inferred role: display name; original member name unknown.
  };

  CharacterParameter();
  virtual void Reset();
  virtual void Initialize(gf::GF_OBJ_HANDLE *handle);
  virtual void InitializeArtsPalette(int);
  virtual void CheckChangeArtsPalette() {}
  virtual void BattleStart(int);
  virtual void BattleEnd();
  virtual void BattleEndInitialize();
  virtual void PreUpdate(const fw::UpdateInfo &updateInfo);
  void ResetSpecialEnhanceRate(bool isAll);
  void ResetEnhance(bool isAll);
  virtual void Update(const fw::UpdateInfo &updateInfo, bool);
  virtual void PostUpdate(const fw::UpdateInfo &updateInfo);
  virtual int GetAttribute() const;
  virtual int GetBladeIndex() const { return -1; }
  virtual int GetWeaponID(int slot) const = 0;
  virtual int GetEquipAccessory() const { return 0; }
  virtual int GetIdeaLevel(int) const { return 0; }
  virtual const ARTS_PALETTE_DATA *GetArtsPaletteDataConst(int index) const = 0;
  virtual int GetArtsPaletteNum() const { return 1; }
  virtual void ResetRecast() { const_cast<ARTS_PALETTE_DATA *>(GetArtsPaletteDataConst(-1))->ResetAllRecast(); }
  virtual void WritebackRecast(GROUP_DATA *) {}
  virtual u32 GetWeakAttributeFlag() const;
  virtual bool InitializeEnhance() const;
  virtual bool IsPlayerParameter() const { return false; }
  virtual bool IsEnemyParameter() const { return false; }
  virtual bool IsInvalidTarget() const { return m_invalidTarget; }
  virtual bool IsInvalidWarp() const { return false; }
  virtual bool IsLevelDiffDamageCorrect() const { return false; }
  virtual bool IsFallDeadDrop() const { return true; }
  virtual bool SetAngry(bool, f32) { return false; }
  virtual int GetAngryAuraID() const { return 0; }
  virtual int GetAngryAttr() const { return 0; }
  virtual bool IsAngry() const { return false; }
  virtual int GetBGMID() const { return 0; }
  virtual void SetupBGM() {}
  virtual int GetDeadSEID() const { return 0; }
  virtual void SetOverwriteAttr(int) {}
  virtual void AddUseWeapon(int) {}
  virtual f32 GetUseWeaponRate(int) const { return 0.0f; }
  virtual int GetEatNum() const { return 0; }
  virtual void IncEatNum() {}
  virtual bool UsePerfectAvoid() const { return false; }
  virtual int GetBladeChangeType() const { return 0; }
  virtual bool IsBoss() const { return false; }
  virtual bool IsNamed() const { return false; }
  virtual bool IsBossOrNamed() const { return false; }
  virtual bool IsEatTarget() const { return false; }
  virtual bool IsChild() const { return false; }
  virtual bool IsInvalidHikariSp() const { return false; }
  virtual bool IsAlwaysKakusei() const { return false; }
  virtual void SetBuddy(gf::GF_OBJ_HANDLE *handle, bool isIgnoreBuddy);
  virtual void InitializeAttackParam();
  virtual u32 CalcDamageArmorEx(u32 damage) { return damage; }

  gf::GfObj *GetUserObject() const;
  gf::GfObj *GetBuddyObject() const;
  int GetClass() const;
  f32 GetHPRate() const;
  gf::GfStatusProperty *GetStatusProperty() const;
  void SetHP(u32 hp);
  u32 GetHP() const;
  u32 GetMaxHP() const;
  int ApplyStatusEnhance(int value, int rateType, int addType) const;
  bool IsBuff(int buff) const;
  void CheckDebuff();
  void ClearBuff(int buff, bool isEnd);
  void ClearAllBuff();
  void SetArtsEffect(int effect);
  void SetAdditionalEnhance(ADD_ENHANCE_TYPE type, int value);
  bool CheckUniteCombo(int id, bool);
  bool SetElementalComboID(int combo, int id);
  void AddEnhance(int enhance) const;
  u32 CalcDamageArmor(u32 damage);
  void AddHP(int value);
  const FIGHT_COMBO_DATA *GetFightComboDataConst() const;
  u32 GetLevel() const;
  f32 GetBuffEffect(int buff) const;
  bool IsBuffInfinite(int buff) const;
  const BUFF_DATA *GetBuffDataConst(int buff, int *index) const;
  f32 GetBuffRestFrame(int buff) const;
  f32 GetBlowRotSpeed() const;
  bool IsBlowRot() const;
  bool GetBlowRotAxis(mm::Vec3 &axis) const;
  bool IsProgressCoolTime() const;
  void SetupLinkDistanceBonus() const;
  bool GetEnhanceEffect(ENHANCE_DATA &data, int enhance) const;
  const ENHANCE_EFFECT_DATA *GetEnhanceEffectDataConst(int enhance) const;
  bool GetAdditionalEnhanceEffect(ENHANCE_DATA &data, int type, int *) const;
  gf::GfObjPropertyCharacter *GetCharacterProperty() const;
  void SetSpecialEnhanceRate(SPECIAL_ENHANCE_TYPE type, f32 rate, u16 value = 0);
  void AddSpecialEnhanceRate(SPECIAL_ENHANCE_TYPE type, f32 rate, u16 value = 0);
  void MinSpecialEnhanceRate(SPECIAL_ENHANCE_TYPE type, f32 rate, u16 value = 0);
  void MaxSpecialEnhanceRate(SPECIAL_ENHANCE_TYPE type, f32 rate, u16 value = 0);
  f32 GetSpecialEnhanceRate(SPECIAL_ENHANCE_TYPE type, int *value) const;
  int GetGender() const;
  int GetBaseSTR() const;
  int GetBaseDEX() const;
  int GetBaseAGI() const;
  int GetBaseLUK() const;
  int GetBaseEtherPower() const;
  int GetBasePArmor() const;
  int GetBaseEArmor() const;
  int GetBaseCriticalPercent() const;
  int GetBaseGuardPercent() const;
  int GetBaseResistPowerAttack() const;
  int GetBaseResistEtherAttack() const;
  void GetBaseDamage(u32 &minimum, u32 &maximum) const;
  int GetSTR() const;
  int GetDEX() const;
  int GetAGI() const;
  int GetLUK() const;
  int GetEtherPower() const;
  int GetPArmor() const;
  int GetEArmor() const;
  int GetCriticalPercent() const;
  int GetGuardPercent() const;
  int GetResistPowerAttack() const;
  int GetResistEtherAttack() const;

  gf::GF_OBJ_HANDLE *unknown08; // Inferred role: user handle; original member name unknown.
  gf::GF_OBJ_HANDLE *unknown10; // Inferred role: buddy handle; original member name unknown.
  u32 unknown18;                // Inferred role: game object id; original member name unknown.
  int unknown1c;                // Inferred role: party id; original member name unknown.
  int unknown20;                // Inferred role: battle index; original member name unknown.
  u32 unknown24;                // Inferred role: blade id; original member name unknown.
  f32 unknown28;                // Inferred role: launch effect scale factor; original member name unknown.
  f32 unknown2c;                // Inferred role: radius; original member name unknown.
  f32 unknown30;                // Inferred role: ball height; original member name unknown.
  f32 unknown34;                // Inferred role: height; original member name unknown.
  f32 unknown38;                // Role and original member name unknown.
  f32 unknown3c;                // Inferred role: ball radius; original member name unknown.
  u8 _40[0x4c - 0x40];
  f32 unknown4c; // Inferred role: attack angle; original member name unknown.
  u8 _50[0x5c - 0x50];
  f32 unknown5c[SPECIAL_ENHANCE_COUNT]; // Inferred role: special enhance rates; original member name unknown.
  u16 unknown94[SPECIAL_ENHANCE_COUNT]; // Inferred role: special enhance values; original member name unknown.
  u8 _b0[0xbc - 0xb0];
  u8 unknownbc_0 : 7; // Inferred role: attack weapon type; original member name unknown.
  u8 : 1;
  u8 _bd[0xc0 - 0xbd];
  FIGHT_COMBO_DATA unknownc0;                                      // Inferred role: fight combo; original member name unknown.
  FIGHT_COMBO_DATA unknownd8;                                      // Inferred role: overwrite fight combo; original member name unknown.
  mutable mm::mtl::FixedVector<ENHANCE_EFFECT_DATA, 64> unknownf0; // Inferred role: enhance effects; original member name unknown.
  ADDITIONAL_ENHANCE_DATA unknown3f8[ADDITIONAL_ENHANCE_COUNT];    // Inferred role: additional enhances; original member name unknown.
  BUFF_DATA unknown458[20];                                        // Inferred role: buffs; original member name unknown.
  u8 unknown598;                                                   // Inferred role: buff count; original member name unknown.
  u8 unknown599[5];                                                // Inferred role: buff flags; original member name unknown.
  u16 unknown59e;                                                  // Inferred role: resistant attribute flags; original member name unknown.
  u8 _5a0[0x5a2 - 0x5a0];
  mutable s16 unknown5a2; // Inferred role: link distance bonus; original member name unknown.
  u8 unknown5a4;          // Role and original member name unknown.
  u8 unknown5a5;          // Inferred role: elemental combo id; original member name unknown.
  u8 _5a6[0x5a7 - 0x5a6];
  u8 unknown5a7_0 : 6; // Inferred role: object type; original member name unknown.
  u8 : 2;
  u16 unknown5a8_0 : 4; // Inferred role: size class; original member name unknown.
  u16 : 4;
  u8 m_perfectAvoid : 5;
  u8 unknown5a9_5 : 3;         // Inferred role: super armor level; original member name unknown.
  s8 unknown5aa;               // Inferred role: rotate X; original member name unknown.
  s8 unknown5ab;               // Inferred role: rotate Y; original member name unknown.
  s8 unknown5ac;               // Inferred role: rotate Z; original member name unknown.
  s8 unknown5ad;               // Inferred role: rotate degrees; original member name unknown.
  u8 unknown5ae;               // Inferred role: character id; original member name unknown.
  s8 unknown5af;               // Inferred role: class id; original member name unknown.
  mutable u8 unknown5b0[0x2f]; // Inferred role: enhance flags; original member name unknown.
  u8 unknown5df_0 : 1;         // Inferred role: initialized; original member name unknown.
  u8 unknown5df_1 : 1;         // Inferred role: battle; original member name unknown.
  s16 m_invalidTarget : 1;     // Signed: BattleCharacter::SetUpperCollisionPriority adds it as -1.
  u8 unknown5df_3 : 1;         // Inferred role: cool time enabled; original member name unknown.
  u8 : 2;
  u8 unknown5df_6 : 1; // Inferred role: ignore buddy; original member name unknown.
  u8 unknown5df_7 : 1; // Inferred role: debuff flag; original member name unknown.
  u8 : 1;
  u8 unknown5e0_1 : 1;         // Inferred role: overwrite fight combo; original member name unknown.
  mutable u8 unknown5e0_2 : 1; // Inferred role: initialized enhance; original member name unknown.
};

static_assert(sizeof(BUFF_DATA) == 0x10, "");
static_assert(offsetof(CharacterParameter, unknown08) == 0x8, "");
static_assert(offsetof(CharacterParameter, unknown10) == 0x10, "");
static_assert(offsetof(CharacterParameter, unknown18) == 0x18, "");
static_assert(offsetof(CharacterParameter, unknown1c) == 0x1c, "");
static_assert(offsetof(CharacterParameter, unknown20) == 0x20, "");
static_assert(offsetof(CharacterParameter, unknown24) == 0x24, "");
static_assert(offsetof(CharacterParameter, unknown28) == 0x28, "");
static_assert(offsetof(CharacterParameter, unknown2c) == 0x2c, "");
static_assert(offsetof(CharacterParameter, unknown4c) == 0x4c, "");
static_assert(offsetof(CharacterParameter, unknownc0) == 0xc0, "");
static_assert(offsetof(CharacterParameter, unknownf0) == 0xf0, "");
static_assert(offsetof(CharacterParameter, unknown458) == 0x458, "");
static_assert(offsetof(CharacterParameter, unknown598) == 0x598, "");
static_assert(offsetof(CharacterParameter, unknown599) == 0x599, "");
static_assert(offsetof(CharacterParameter, unknown59e) == 0x59e, "");
static_assert(offsetof(CharacterParameter, unknown5a4) == 0x5a4, "");
static_assert(offsetof(CharacterParameter, unknown5a5) == 0x5a5, "");
static_assert(offsetof(CharacterParameter, unknown5aa) == 0x5aa, "");
static_assert(offsetof(CharacterParameter, unknown5ad) == 0x5ad, "");
static_assert(offsetof(CharacterParameter, unknown5ae) == 0x5ae, "");
static_assert(offsetof(CharacterParameter, unknown5b0) == 0x5b0, "");
static_assert(sizeof(ENHANCE_EFFECT_DATA) == 0xc, "");
static_assert(offsetof(CharacterParameter, unknown5af) == 0x5af, "");
static_assert(sizeof(CharacterParameter) == 0x5e8, "");

class PlayerParameter : public CharacterParameter {
public:
  PlayerParameter();
  virtual ~PlayerParameter();
  void Initialize(gf::GF_OBJ_HANDLE *handle) override;
  void ResetUseWeapon();
  void InitializeArtsPalette(int) override;
  void CheckChangeArtsPalette() override;
  void InitializeAttackParam() override;
  bool InitializeEnhance() const override;
  void BattleStart(int) override;
  void SetupPouchDamageArmor();
  void BattleEnd() override;
  void BattleEndInitialize() override;
  void Update(const fw::UpdateInfo &updateInfo, bool) override;
  void WritebackRecast(GROUP_DATA *groupData) override;
  void AddUseWeapon(int weapon) override;
  f32 GetUseWeaponRate(int weapon) const override;
  const ARTS_PALETTE_DATA *GetArtsPaletteDataConst(int index) const override;
  u32 CalcDamageArmorEx(u32 damage) override;
  void ResetRecast() override;
  int GetBladeIndex() const override;
  int GetWeaponID(int slot) const override;
  int GetEquipAccessory() const override;
  int GetIdeaLevel(int idea) const override;
  int GetArtsPaletteNum() const override { return m_artsPaletteNum; }
  bool IsPlayerParameter() const override { return true; }
  int GetBladeChangeType() const override { return m_bladeChangeType; }

  ARTS_PALETTE_DATA *unknown5e8;             // Inferred role: arts palettes; original member name unknown.
  u32 unknown5f0[gf::WEAPON_TYPE_COUNT + 1]; // Inferred role: use weapon counts; original member name unknown.
  u32 unknown65c;                            // Inferred role: total weapon use; original member name unknown.
  int unknown660;                            // Inferred role: pouch damage armor; original member name unknown.
  u8 m_artsPaletteNum;
  u8 m_bladeChangeType;
};

static_assert(offsetof(PlayerParameter, unknown5e8) == 0x5e8, "");
static_assert(offsetof(PlayerParameter, unknown5f0) == 0x5f0, "");
static_assert(offsetof(PlayerParameter, unknown65c) == 0x65c, "");
static_assert(offsetof(PlayerParameter, unknown660) == 0x660, "");
static_assert(offsetof(PlayerParameter, m_artsPaletteNum) == 0x664, "");
static_assert(sizeof(PlayerParameter) == 0x668, "");

class EnemyParameter : public CharacterParameter {
public:
  struct HATE_DATA {
    void Set(int type, f32 hate);

    f32 unknown00[2]; // Inferred role: hates; original member name unknown.
    f32 unknown08;    // Inferred role: rate; original member name unknown.
    bool unknown0c;   // Inferred role: empty flag; original member name unknown.
    u8 _0d[0x10 - 0x0d];
  };

  void AddHate(int index, int type, f32 hate);
  EnemyParameter();
  virtual ~EnemyParameter();
  void Initialize(gf::GF_OBJ_HANDLE *handle) override;
  const gf::SDataEnemy *GetEnemyData() const;
  void SetBuddy(gf::GF_OBJ_HANDLE *handle, bool isIgnoreBuddy) override;
  void InitializeArtsPalette(int) override;
  void InitializeAttackParam() override;
  bool InitializeEnhance() const override;
  void BattleStart(int) override;
  void BattleEnd() override;
  void BattleEndInitialize() override;
  void CheckChangeAttr();
  void AngryInfection(f32 range);
  void Update(const fw::UpdateInfo &updateInfo, bool) override;
  void MulHate(int index, int type, f32 rate);
  void ResetHate(int index, bool isResetTarget);
  void PostUpdate(const fw::UpdateInfo &updateInfo) override;
  int GetBGMID() const override;
  void SetupBGM() override;
  int GetAttribute() const override;
  bool SetAngry(bool isAngry, f32 time) override;
  int GetWeaponID(int slot) const override;
  bool IsBoss() const override;
  bool IsNamed() const override;
  bool IsBossOrNamed() const override;
  bool IsEatTarget() const override;
  bool IsChild() const override;
  bool IsInvalidHikariSp() const override;
  bool IsAlwaysKakusei() const override;
  bool UsePerfectAvoid() const override;
  const HATE_DATA *GetHateDataConst(int index) const;
  int GetHateTarget() const;
  const ARTS_PALETTE_DATA *GetArtsPaletteDataConst(int) const override { return &m_artsPaletteData; }
  bool IsEnemyParameter() const override { return true; }
  bool IsInvalidTarget() const override { return m_invalidTarget; }
  bool IsInvalidWarp() const override { return m_invalidWarp; }
  bool IsLevelDiffDamageCorrect() const override { return m_levelDiffDamageCorrect; }
  bool IsFallDeadDrop() const override { return m_fallDeadDrop; }
  int GetAngryAuraID() const override { return m_angryAuraID; }
  int GetAngryAttr() const override { return m_angryAttr; }
  bool IsAngry() const override { return m_angry; }
  int GetDeadSEID() const override { return m_deadSEID; }
  void SetOverwriteAttr(int attribute) override { m_overwriteAttr = attribute; }
  int GetEatNum() const override { return m_eatNum; }
  void IncEatNum() override {
    if (m_eatNum != 0xff) {
      m_eatNum++;
    }
  }

  ARTS_PALETTE_DATA m_artsPaletteData;
  HATE_DATA unknown820[HATE_COUNT]; // Inferred role: hates; original member name unknown.
  int unknown850;                   // Inferred role: hate target; original member name unknown.
  u8 _854[0x864 - 0x854];
  u16 m_angryAuraID;
  u8 m_angryAttr;
  u8 m_deadSEID;
  u8 m_overwriteAttr;
  u8 unknown869; // Inferred role: attribute cache; original member name unknown.
  u8 m_eatNum;
  mutable u8 unknown86b; // Inferred role: perfect avoid count; original member name unknown.
  u8 m_angry : 1;
  u8 : 2;
  u8 m_eatTarget : 1;
  u8 m_child : 1;
  u8 m_invalidHikariSp : 1;
  u8 m_alwaysKakusei : 1;
  u8 m_invalidTarget : 1;
  u8 m_invalidWarp : 1;
  u8 m_levelDiffDamageCorrect : 1;
  u8 m_fallDeadDrop : 1;
};

static_assert(offsetof(EnemyParameter, m_artsPaletteData) == 0x5e8, "");
static_assert(offsetof(EnemyParameter, unknown820) == 0x820, "");
static_assert(offsetof(EnemyParameter, unknown850) == 0x850, "");
static_assert(offsetof(EnemyParameter, m_angryAuraID) == 0x864, "");
static_assert(offsetof(EnemyParameter, m_overwriteAttr) == 0x868, "");
static_assert(offsetof(EnemyParameter, m_eatNum) == 0x86a, "");
static_assert(offsetof(EnemyParameter, unknown86b) == 0x86b, "");
static_assert(sizeof(EnemyParameter) == 0x870, "");

} // namespace btl
