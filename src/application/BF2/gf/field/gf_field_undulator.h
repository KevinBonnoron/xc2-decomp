#pragma once
#include <stddef.h>

#include "mm_math/mm_vec3.h"
#include "types.h"

namespace gf {

// Layout evidence: GfFieldUndulator::GfFieldUndulator at 0x71003400e4 initializes the members below, GfFieldUndulator::create at
// 0x71003401bc fills the CreateInfo and BdatInfo, and the sub object occupies 0x5460 to 0x54a0 of GfComBehaviorEnemy (initialized
// in its constructor at 0x7100514074). The vectors are the unit vector Y until castRay finds a ground.
class GfFieldUndulator {
public:
  struct CreateInfo {
    int unknown00; // Inferred role: row of BDAT_CHR_EN_ARRANGE; original member name unknown.
    f32 unknown04; // Inferred role: width of the enemy; original member name unknown.
  };

  struct BdatInfo {
    void create(int id);

    bool unknown00; // Inferred role: UndX flag of BDAT_RSC_EN_UND; original member name unknown.
    bool unknown01; // Inferred role: UndZ flag of BDAT_RSC_EN_UND; original member name unknown.
    f32 unknown04;  // Inferred role: UndMinX in radians; original member name unknown.
    f32 unknown08;  // Inferred role: UndMaxX in radians; original member name unknown.
    f32 unknown0c;  // Inferred role: UndMinZ in radians; original member name unknown.
    f32 unknown10;  // Inferred role: UndMaxZ in radians; original member name unknown.
    f32 unknown14;  // Inferred role: UndDeg scaled to radians; original member name unknown.
  };

  void create(const CreateInfo &info);
  void dispose();

  CreateInfo unknown00; // Inferred role: create info; original member name unknown.
  BdatInfo unknown08;   // Inferred role: bdat info; original member name unknown.
  mm::Vec3 unknown20;   // Inferred role: ground normal for the pitch; original member name unknown.
  mm::Vec3 unknown30;   // Inferred role: ground normal for the roll; original member name unknown.
};

static_assert(sizeof(GfFieldUndulator::CreateInfo) == 0x8, "");
static_assert(offsetof(GfFieldUndulator::BdatInfo, unknown04) == 0x04, "");
static_assert(offsetof(GfFieldUndulator::BdatInfo, unknown14) == 0x14, "");
static_assert(sizeof(GfFieldUndulator::BdatInfo) == 0x18, "");
static_assert(offsetof(GfFieldUndulator, unknown08) == 0x08, "");
static_assert(offsetof(GfFieldUndulator, unknown20) == 0x20, "");
static_assert(offsetof(GfFieldUndulator, unknown30) == 0x30, "");
static_assert(sizeof(GfFieldUndulator) == 0x40, "");

} // namespace gf
