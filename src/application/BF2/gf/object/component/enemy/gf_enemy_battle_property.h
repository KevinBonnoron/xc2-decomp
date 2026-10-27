#pragma once
#include <stddef.h>

#include "mm_math/mm_vec3.h"
#include "types.h"

namespace btl {
class CharacterParameter;
class EnemyParameter;
} // namespace btl

namespace gf {

class GfComPropertyEnemy;
struct MsgObjectNotifyDamage;

namespace enemy {

class GfEnemyBattleProperty {
public:
  GfEnemyBattleProperty();
  void Initialize(const GfComPropertyEnemy &property);
  void Finalize(const GfComPropertyEnemy &property);
  const btl::CharacterParameter *GetCharacterParameterConst() const;
  const btl::EnemyParameter *GetEnemyParameterConst() const;
  f32 GetReturnHomeDistance() const;
  f32 GetReturnHomeCharacterDistance() const;
  void NotifyDamage(const MsgObjectNotifyDamage &message);

  mm::Vec3 unknown00; // Inferred role: home position; original member name unknown.
  int _10;
  f32 unknown14; // Inferred role: return home distance; original member name unknown.
  f32 unknown18; // Inferred role: return home character distance; original member name unknown.
  u8 unknown1c;  // Inferred role: BatAreaType of the enemy arrange; original member name unknown.
  u8 unknown1d;  // Inferred role: act type of the enemy resource; original member name unknown.
  u16 _1e;
};

static_assert(offsetof(GfEnemyBattleProperty, _10) == 0x10, "");
static_assert(offsetof(GfEnemyBattleProperty, unknown14) == 0x14, "");
static_assert(offsetof(GfEnemyBattleProperty, unknown18) == 0x18, "");
static_assert(offsetof(GfEnemyBattleProperty, _1e) == 0x1e, "");
static_assert(sizeof(GfEnemyBattleProperty) == 0x20, "");

} // namespace enemy
} // namespace gf
