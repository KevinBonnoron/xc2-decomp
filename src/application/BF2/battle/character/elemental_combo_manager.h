#pragma once
#include "battle/utility_battle.h"
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
    f32 value;
    f32 ratio;
    f32 timer;
    int state;
    u32 effectHandle;
    u32 attackIds[ELEMENTAL_ATTACK_COUNT];
    u32 damages[ELEMENTAL_ATTACK_COUNT];
    u32 totalDamage;
    s8 burstCharacter;
    u8 comboId;
    u8 stage;
    u8 attribute;
  };

  struct ELEMENTAL_COMBO_DATA {
    u8 _00[0xc - 0x0];
    f32 restTimeMax;
    f32 restTime;
    f32 suspendRatio;
    u8 _18[0x74 - 0x18];
    u16 restTimeSpeed;
    u8 comboId;
    u8 _77[0x88 - 0x77];
    u8 isSuspend : 1;
    u8 : 7;
    u8 _89[0x8c - 0x89];
  };

  struct BALL_DATA {
    u8 _00[0x34 - 0x00];
    u32 effectHandle;
    u8 _38[0x40 - 0x38];
  };

  virtual ~ElementalComboManager();
  void DeleteBallEffect(int attribute);
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

  gf::GF_OBJ_HANDLE *handle;
  int characterId;
  f32 ballScale;
  f32 startWaitTime;
  ELEMENTAL_DATA elements[ATTRIBUTE_COUNT + 1];
  ELEMENTAL_COMBO_DATA combos[ELEMENTAL_COMBO_COUNT];
  u8 _85c[0x860 - 0x85c];
  BALL_DATA balls[ATTRIBUTE_COUNT + 1];
  u8 _aa0[0xaa4 - 0xaa0];
  u8 comboIndex : 4;
  u8 : 4;
  u8 elementalValueMax;
  u8 burstComboId;
  u8 resistantAttrBreakTotalDamages[ATTRIBUTE_COUNT];
  u8 isPlayer : 1;
  u8 : 7;
};

static_assert(sizeof(ElementalComboManager::ELEMENTAL_DATA) == 0xbc, "");
static_assert(sizeof(ElementalComboManager::ELEMENTAL_COMBO_DATA) == 0x8c, "");
static_assert(sizeof(ElementalComboManager::BALL_DATA) == 0x40, "");
static_assert(offsetof(ElementalComboManager, handle) == 0x8, "");
static_assert(offsetof(ElementalComboManager, elements) == 0x1c, "");
static_assert(offsetof(ElementalComboManager, combos) == 0x6b8, "");
static_assert(offsetof(ElementalComboManager, balls) == 0x860, "");
static_assert(offsetof(ElementalComboManager, elementalValueMax) == 0xaa5, "");
static_assert(offsetof(ElementalComboManager, resistantAttrBreakTotalDamages) == 0xaa7, "");
static_assert(sizeof(ElementalComboManager) == 0xab0, "");

} // namespace btl
