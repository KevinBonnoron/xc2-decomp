#pragma once
#include "battle/arts_data.h"
#include "gf/data/gf_data_weapon.h"
#include "mm_mtl/fixed_vector.h"
#include "types.h"
#include <stddef.h>

namespace fw {
struct UpdateInfo;
}

namespace gf {
struct GF_OBJ_HANDLE;
class GfObj;
class GfStatusProperty;
struct SDataEnemy;
} // namespace gf

namespace btl {

class GROUP_DATA;

constexpr int SPECIAL_ENHANCE_COUNT = 14;
constexpr int ADDITIONAL_ENHANCE_COUNT = 6;
constexpr int HATE_COUNT = 3;

struct FIGHT_COMBO_DATA {
  u8 id;
  u8 _01[0x18 - 0x01];
};

struct ENHANCE_EFFECT_DATA {
  u16 id;
  u8 _02[0xc - 0x2];
};

struct BUFF_DATA {
  u16 id;
  u8 _02[0x4 - 0x2];
  f32 restFrame;
  f32 effect;
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
    ENHANCE_EFFECT_DATA effect;
    int enhance;
  };

  struct ENHANCE_DATA {
    f32 value;
    u8 _04[0x8 - 0x4];
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
  virtual bool IsInvalidTarget() const { return isBlade; }
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
  const FIGHT_COMBO_DATA *GetFightComboDataConst() const;
  u32 GetLevel() const;
  f32 GetBuffEffect(int buff) const;
  bool IsBuffInfinite(int buff) const;
  const BUFF_DATA *GetBuffDataConst(int buff, int *index) const;
  f32 GetBuffRestFrame(int buff) const;
  f32 GetBlowRotSpeed() const;
  bool IsBlowRot() const;
  bool IsProgressCoolTime() const;
  void SetupLinkDistanceBonus() const;
  bool GetEnhanceEffect(ENHANCE_DATA &data, int enhance) const;
  const ENHANCE_EFFECT_DATA *GetEnhanceEffectDataConst(int enhance) const;
  bool GetAdditionalEnhanceEffect(ENHANCE_DATA &data, int type, int *) const;
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

  gf::GF_OBJ_HANDLE *user;
  gf::GF_OBJ_HANDLE *buddy;
  u32 gameObjectId;
  int partyId;
  u8 _20[0x2c - 0x20];
  f32 radius;
  f32 ballHeight;
  u8 _34[0x3c - 0x34];
  f32 ballRadius;
  u8 _40[0x5c - 0x40];
  f32 specialEnhanceRates[SPECIAL_ENHANCE_COUNT];
  u16 specialEnhanceValues[SPECIAL_ENHANCE_COUNT];
  u8 _b0[0xbc - 0xb0];
  u8 attackWeaponType : 7;
  u8 : 1;
  u8 _bd[0xc0 - 0xbd];
  FIGHT_COMBO_DATA fightCombo;
  FIGHT_COMBO_DATA overwriteFightCombo;
  mm::mtl::FixedVector<ENHANCE_EFFECT_DATA, 64> enhanceEffects;
  ADDITIONAL_ENHANCE_DATA additionalEnhances[ADDITIONAL_ENHANCE_COUNT];
  BUFF_DATA buffs[20];
  u8 buffNum;
  u8 buffFlags[5];
  u16 resistantAttributeFlags;
  u8 _5a0[0x5a2 - 0x5a0];
  mutable s16 linkDistanceBonus;
  u8 _5a4[0x5a5 - 0x5a4];
  u8 elementalComboId;
  u8 _5a6[0x5a7 - 0x5a6];
  u8 objectType : 6;
  u8 : 2;
  u8 : 8;
  u8 : 8;
  s8 rotateX;
  s8 rotateY;
  s8 rotateZ;
  s8 rotateDeg;
  u8 characterId;
  s8 classId;
  u8 _5b0[0x5df - 0x5b0];
  u8 isInitialized : 1;
  u8 isBattle : 1;
  u8 isBlade : 1;
  u8 isEnableCoolTime : 1;
  u8 : 2;
  u8 isIgnoreBuddy : 1;
  u8 : 1;
  u8 : 1;
  u8 isOverwriteFightCombo : 1;
  mutable u8 isInitializedEnhance : 1;
};

static_assert(sizeof(BUFF_DATA) == 0x10, "");
static_assert(offsetof(CharacterParameter, user) == 0x8, "");
static_assert(offsetof(CharacterParameter, buddy) == 0x10, "");
static_assert(offsetof(CharacterParameter, gameObjectId) == 0x18, "");
static_assert(offsetof(CharacterParameter, partyId) == 0x1c, "");
static_assert(offsetof(CharacterParameter, radius) == 0x2c, "");
static_assert(offsetof(CharacterParameter, fightCombo) == 0xc0, "");
static_assert(offsetof(CharacterParameter, enhanceEffects) == 0xf0, "");
static_assert(offsetof(CharacterParameter, buffs) == 0x458, "");
static_assert(offsetof(CharacterParameter, buffNum) == 0x598, "");
static_assert(offsetof(CharacterParameter, buffFlags) == 0x599, "");
static_assert(offsetof(CharacterParameter, resistantAttributeFlags) == 0x59e, "");
static_assert(offsetof(CharacterParameter, elementalComboId) == 0x5a5, "");
static_assert(offsetof(CharacterParameter, rotateX) == 0x5aa, "");
static_assert(offsetof(CharacterParameter, rotateDeg) == 0x5ad, "");
static_assert(offsetof(CharacterParameter, characterId) == 0x5ae, "");
static_assert(offsetof(CharacterParameter, classId) == 0x5af, "");
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
  int GetArtsPaletteNum() const override { return artsPaletteNum; }
  bool IsPlayerParameter() const override { return true; }
  int GetBladeChangeType() const override { return bladeChangeType; }

  ARTS_PALETTE_DATA *artsPalettes;
  u32 useWeaponCounts[gf::WEAPON_TYPE_COUNT + 1];
  u32 useWeaponTotal;
  int pouchDamageArmor;
  u8 artsPaletteNum;
  u8 bladeChangeType;
};

static_assert(offsetof(PlayerParameter, artsPalettes) == 0x5e8, "");
static_assert(offsetof(PlayerParameter, useWeaponCounts) == 0x5f0, "");
static_assert(offsetof(PlayerParameter, useWeaponTotal) == 0x65c, "");
static_assert(offsetof(PlayerParameter, pouchDamageArmor) == 0x660, "");
static_assert(offsetof(PlayerParameter, artsPaletteNum) == 0x664, "");
static_assert(sizeof(PlayerParameter) == 0x668, "");

class EnemyParameter : public CharacterParameter {
public:
  struct HATE_DATA {
    void Set(int type, f32 hate);

    f32 hates[2];
    f32 rate;
    bool isEmpty;
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
  void Update(const fw::UpdateInfo &updateInfo, bool) override;
  void MulHate(int index, int type, f32 rate);
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
  const ARTS_PALETTE_DATA *GetArtsPaletteDataConst(int) const override { return &artsPalette; }
  bool IsEnemyParameter() const override { return true; }
  bool IsInvalidTarget() const override { return isInvalidTarget; }
  bool IsInvalidWarp() const override { return isInvalidWarp; }
  bool IsLevelDiffDamageCorrect() const override { return isLevelDiffDamageCorrect; }
  bool IsFallDeadDrop() const override { return isFallDeadDrop; }
  int GetAngryAuraID() const override { return angryAuraId; }
  int GetAngryAttr() const override { return angryAttr; }
  bool IsAngry() const override { return isAngry; }
  int GetDeadSEID() const override { return deadSeId; }
  void SetOverwriteAttr(int attribute) override { overwriteAttr = attribute; }
  int GetEatNum() const override { return eatNum; }
  void IncEatNum() override {
    if (eatNum != 0xff) {
      eatNum++;
    }
  }

  ARTS_PALETTE_DATA artsPalette;
  HATE_DATA hates[HATE_COUNT];
  int hateTarget;
  u8 _854[0x864 - 0x854];
  u16 angryAuraId;
  u8 angryAttr;
  u8 deadSeId;
  u8 overwriteAttr;
  u8 _869[0x86a - 0x869];
  u8 eatNum;
  mutable u8 perfectAvoidNum;
  u8 isAngry : 1;
  u8 : 2;
  u8 isEatTarget : 1;
  u8 isChild : 1;
  u8 isInvalidHikariSp : 1;
  u8 isAlwaysKakusei : 1;
  u8 isInvalidTarget : 1;
  u8 isInvalidWarp : 1;
  u8 isLevelDiffDamageCorrect : 1;
  u8 isFallDeadDrop : 1;
};

static_assert(offsetof(EnemyParameter, artsPalette) == 0x5e8, "");
static_assert(offsetof(EnemyParameter, hates) == 0x820, "");
static_assert(offsetof(EnemyParameter, hateTarget) == 0x850, "");
static_assert(offsetof(EnemyParameter, angryAuraId) == 0x864, "");
static_assert(offsetof(EnemyParameter, overwriteAttr) == 0x868, "");
static_assert(offsetof(EnemyParameter, eatNum) == 0x86a, "");
static_assert(offsetof(EnemyParameter, perfectAvoidNum) == 0x86b, "");
static_assert(sizeof(EnemyParameter) == 0x870, "");

} // namespace btl
