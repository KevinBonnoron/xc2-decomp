#pragma once
#include "battle/utility_battle.h"
#include "mm_math/mm_vec3.h"
#include "types.h"
#include <stddef.h>

namespace gf {
struct GF_OBJ_HANDLE;
}

namespace btl {

constexpr int ELEMENTAL_COMBO_COUNT = 3;
constexpr int ELEMENTAL_ATTACK_COUNT = 20;

class ElementalComboManager {
public:
  enum ELEMENTAL_STATE {
    ELEMENTAL_STATE_BURST = 2,
    ELEMENTAL_STATE_DIRECTING = 3,
  };

  struct ELEMENTAL_DATA {
    f32 unknown00;                         // Inferred role: value; original member name unknown.
    f32 unknown04;                         // Inferred role: ratio; original member name unknown.
    f32 unknown08;                         // Inferred role: timer; original member name unknown.
    int unknown0c;                         // Inferred role: state; original member name unknown.
    u32 unknown10;                         // Inferred role: effect handle; original member name unknown.
    u32 unknown14[ELEMENTAL_ATTACK_COUNT]; // Inferred role: attack ids; original member name unknown.
    u32 unknown64[ELEMENTAL_ATTACK_COUNT]; // Inferred role: damages; original member name unknown.
    u32 unknownb4;                         // Inferred role: total damage; original member name unknown.
    s8 unknownb8;                          // Inferred role: burst character; original member name unknown.
    u8 unknownb9;                          // Inferred role: combo id; original member name unknown.
    u8 unknownba;                          // Inferred role: stage; original member name unknown.
    u8 unknownbb;                          // Inferred role: attribute; original member name unknown.
  };

  struct ELEMENTAL_COMBO_DATA {
    u8 _00[0xc - 0x0];
    f32 unknown0c; // Inferred role: rest time max; original member name unknown.
    f32 unknown10; // Inferred role: rest time; original member name unknown.
    f32 unknown14; // Inferred role: suspend ratio; original member name unknown.
    u8 _18[0x74 - 0x18];
    u16 unknown74; // Inferred role: rest time speed; original member name unknown.
    u8 unknown76;  // Inferred role: combo id; original member name unknown.
    u8 _77[0x88 - 0x77];
    u8 unknown88_0 : 1; // Inferred role: suspend; original member name unknown.
    u8 : 7;
    u8 _89[0x8c - 0x89];
  };

  struct BALL_DATA {
    mm::Vec3 unknown00; // Inferred role: position; original member name unknown.
    u8 _10[0x34 - 0x10];
    u32 unknown34; // Inferred role: effect handle; original member name unknown.
    u8 _38[0x40 - 0x38];
  };

  virtual ~ElementalComboManager();
  void DeleteBallEffect(int attribute);
  void CreateBreakEffect(int attribute);
  void Burst(int character, int attribute, u32 attack, bool isAnyAttribute);
  void Initialize(gf::GF_OBJ_HANDLE *handle);
  void CheckCharacterID();
  void ResetElement(int attribute);
  int GetResistantAttrBreakDamage(int attribute) const;
  int GetResistantAttrBreakTotalDamage(int attribute) const;
  bool IsEnableElementalCombo(int attribute, int stage, bool isIncludeBurst, bool isAnyAttribute) const;
  int GetNextElementalComboID(int attribute, bool isIncludeBurst, bool isAnyAttribute) const;
  bool IsFullElementalValue(int attribute) const;
  bool IsDirecting(int attribute) const;
  bool IsEnableStartElementalCombo() const;
  int GetElementalComboID(bool isIncludeBurst) const;
  f32 CalcRestTimeRatio(const ELEMENTAL_COMBO_DATA &combo) const;
  void SetElementalValue(int attribute, f32 value);
  f32 GetElementalValue(int attribute) const;
  f32 GetRestTimeRatio(bool &isSuspend) const;

  gf::GF_OBJ_HANDLE *unknown08;                           // Inferred role: handle; original member name unknown.
  int unknown10;                                          // Inferred role: character id; original member name unknown.
  f32 unknown14;                                          // Inferred role: ball scale; original member name unknown.
  f32 unknown18;                                          // Inferred role: start wait time; original member name unknown.
  ELEMENTAL_DATA unknown1c[ATTRIBUTE_COUNT + 1];          // Inferred role: elements; original member name unknown.
  ELEMENTAL_COMBO_DATA unknown6b8[ELEMENTAL_COMBO_COUNT]; // Inferred role: combos; original member name unknown.
  u8 _85c[0x860 - 0x85c];
  BALL_DATA unknown860[ATTRIBUTE_COUNT + 1]; // Inferred role: balls; original member name unknown.
  u8 _aa0[0xaa4 - 0xaa0];
  u8 unknownaa4_0 : 4; // Inferred role: combo index; original member name unknown.
  u8 : 4;
  u8 unknownaa5;                  // Inferred role: elemental value max; original member name unknown.
  u8 unknownaa6;                  // Inferred role: burst combo id; original member name unknown.
  u8 unknownaa7[ATTRIBUTE_COUNT]; // Inferred role: resistant attribute break total damages; original member name unknown.
  u8 unknownaaf_0 : 1;            // Inferred role: player flag; original member name unknown.
  u8 : 7;
};

static_assert(sizeof(ElementalComboManager::ELEMENTAL_DATA) == 0xbc, "");
static_assert(sizeof(ElementalComboManager::ELEMENTAL_COMBO_DATA) == 0x8c, "");
static_assert(sizeof(ElementalComboManager::BALL_DATA) == 0x40, "");
static_assert(offsetof(ElementalComboManager, unknown08) == 0x8, "");
static_assert(offsetof(ElementalComboManager, unknown1c) == 0x1c, "");
static_assert(offsetof(ElementalComboManager, unknown6b8) == 0x6b8, "");
static_assert(offsetof(ElementalComboManager, unknown860) == 0x860, "");
static_assert(offsetof(ElementalComboManager, unknownaa5) == 0xaa5, "");
static_assert(offsetof(ElementalComboManager, unknownaa7) == 0xaa7, "");
static_assert(sizeof(ElementalComboManager) == 0xab0, "");

} // namespace btl
