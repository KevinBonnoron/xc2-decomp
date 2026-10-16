#pragma once
#include "types.h"
#include <stddef.h>

namespace fw {
struct UpdateInfo;
}

namespace gf {
struct GF_OBJ_HANDLE;
}

namespace btl {

class GROUP_DATA;
struct ARTS_PALETTE_DATA;

struct FIGHT_COMBO_DATA {
  u8 id;
};

class CharacterParameter {
public:
  virtual void Reset();
  virtual void Initialize(gf::GF_OBJ_HANDLE *handle);
  virtual void InitializeArtsPalette(int);
  virtual void CheckChangeArtsPalette();
  virtual void BattleStart(int);
  virtual void BattleEnd();
  virtual void BattleEndInitialize();
  virtual void PreUpdate(const fw::UpdateInfo &updateInfo);
  virtual void Update(const fw::UpdateInfo &updateInfo, bool);
  virtual void PostUpdate(const fw::UpdateInfo &updateInfo);
  virtual int GetAttribute() const;
  virtual int GetBladeIndex() const;
  virtual int GetWeaponID(int) const = 0;
  virtual int GetEquipAccessory() const;
  virtual int GetIdeaLevel(int) const;
  virtual const ARTS_PALETTE_DATA *GetArtsPaletteDataConst(int) const = 0;
  virtual int GetArtsPaletteNum() const;
  virtual void ResetRecast();
  virtual void WritebackRecast(GROUP_DATA *groupData);
  virtual u32 GetWeakAttributeFlag() const;
  virtual bool InitializeEnhance() const;
  virtual bool IsPlayerParameter() const;
  virtual bool IsEnemyParameter() const;
  virtual bool IsInvalidTarget() const;
  virtual bool IsInvalidWarp() const;
  virtual bool IsLevelDiffDamageCorrect() const;
  virtual bool IsFallDeadDrop() const;
  virtual void SetAngry(bool isAngry, f32 time);
  virtual int GetAngryAuraID() const;
  virtual int GetAngryAttr() const;
  virtual bool IsAngry() const;
  virtual int GetBGMID() const;
  virtual void SetupBGM();
  virtual int GetDeadSEID() const;
  virtual void SetOverwriteAttr(int attribute);
  virtual void AddUseWeapon(int weapon);
  virtual f32 GetUseWeaponRate(int weapon) const;
  virtual int GetEatNum() const;
  virtual void IncEatNum();
  virtual bool UsePerfectAvoid() const;
  virtual int GetBladeChangeType() const;
  virtual bool IsBoss() const;
  virtual bool IsNamed() const;
  virtual bool IsBossOrNamed() const;
  virtual bool IsEatTarget() const;
  virtual bool IsChild() const;
  virtual bool IsInvalidHikariSp() const;
  virtual bool IsAlwaysKakusei() const;
  virtual void SetBuddy(gf::GF_OBJ_HANDLE *handle, bool);
  virtual void InitializeAttackParam();
  virtual void CalcDamageArmorEx(u32);

  int GetClass() const;
  f32 GetHPRate() const;
  u32 GetHP() const;
  u32 GetMaxHP() const;
  bool IsBuff(int buff) const;
  const FIGHT_COMBO_DATA *GetFightComboDataConst() const;
  u32 GetLevel() const;

  u8 _08[0x10 - 0x08];
  gf::GF_OBJ_HANDLE *buddy;
  u8 _18[0x1c - 0x18];
  int partyId;
  u8 _20[0x2c - 0x20];
  f32 radius;
  u8 _30[0x59e - 0x30];
  u16 resistantAttributeFlags;
  u8 _5a0[0x5a5 - 0x5a0];
  u8 elementalComboId;
  u8 _5a6[0x5df - 0x5a6];
  u8 : 1;
  u8 isBattle : 1;
  u8 isBlade : 1;
  u8 : 5;
  u8 : 3;
};

static_assert(offsetof(CharacterParameter, buddy) == 0x10, "");
static_assert(offsetof(CharacterParameter, partyId) == 0x1c, "");
static_assert(offsetof(CharacterParameter, radius) == 0x2c, "");
static_assert(offsetof(CharacterParameter, resistantAttributeFlags) == 0x59e, "");
static_assert(offsetof(CharacterParameter, elementalComboId) == 0x5a5, "");

} // namespace btl
