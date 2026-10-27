#pragma once
#include <stddef.h>

#include "gf/object/component/enemy/gf_enemy_battle_property.h"
#include "gf/object/component/property/gf_com_property.h"
#include "mm_math/mm_quat.h"
#include "mm_math/mm_vec3.h"
#include "types.h"

namespace mm {
namespace mtl {
class RTTI;
} // namespace mtl
} // namespace mm

namespace gf {

class GfComPropertyEnemy : public GfComProperty {
public:
  static mm::mtl::RTTI m_rtti;

  bool isFieldDeadCondMatched() const;
  void flush();
  void writeBack();

  u8 _38[0x40 - 0x38];
  enemy::GfEnemyBattleProperty unknown40; // Inferred role: battle property; original member name unknown.
  mm::Vec3 unknown60;                     // Inferred role: position; original member name unknown.
  mm::Quat unknown70;                     // Inferred role: rotation; original member name unknown.
  mm::Vec3 unknown80;                     // Inferred role: position of the previous flush; original member name unknown.
  mm::Quat unknown90;                     // Inferred role: rotation of the previous flush; original member name unknown.
};

static_assert(offsetof(GfComPropertyEnemy, unknown40) == 0x40, "");
static_assert(offsetof(GfComPropertyEnemy, unknown60) == 0x60, "");
static_assert(offsetof(GfComPropertyEnemy, unknown70) == 0x70, "");
static_assert(offsetof(GfComPropertyEnemy, unknown80) == 0x80, "");
static_assert(offsetof(GfComPropertyEnemy, unknown90) == 0x90, "");
static_assert(sizeof(GfComPropertyEnemy) == 0xa0, "");

} // namespace gf
