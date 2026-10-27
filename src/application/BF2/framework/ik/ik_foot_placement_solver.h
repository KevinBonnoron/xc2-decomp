#pragma once
#include <stddef.h>

#include "anm/anm_foot_placement_ik_solver.h"
#include "framework/ik/ik_solver.h"
#include "mm_math/mm_quat.h"
#include "mm_math/mm_vec3.h"
#include "types.h"

namespace mm {
namespace mtl {
class RTTI;
} // namespace mtl
} // namespace mm

namespace fw {
class ParamAdapter;

class FootPlacementIKSolver : public IkSolver {
public:
  struct Param {
    f32 unknown00; // Inferred role: unknown; original member name unknown.
    f32 unknown04; // Inferred role: raycast distance offset; original member name unknown.
    f32 unknown08; // Inferred role: raycast distance offset; original member name unknown.
  };

  static mm::mtl::RTTI m_rtti;

  ~FootPlacementIKSolver() override;
  void solve(const UpdateInfo &info) override;
  // Inferred helper: forces the raycast up distance; original name unknown.
  void unknown001(f32 distance) {
    unknowna0 |= 4;
    unknowna4 = distance;
  }

  // Inferred helper: forces the raycast down distance; original name unknown.
  void unknown002(f32 distance) {
    unknowna0 |= 8;
    unknowna8 = distance;
  }

  // Inferred helper: sets or clears the placement enable flag; original name unknown.
  void unknown003(bool enable) {
    if (enable) {
      unknowna0 |= 1;
    } else {
      unknowna0 &= ~1;
    }
  }

  f32 getRaycastDown() const;
  void drawDebug();
  const mm::mtl::RTTI *getRTTI() const override;

  anm::FootPlacementIKSolver *unknown20; // Inferred role: anim foot placement solver; original member name unknown.
  const char *unknown28;                 // Inferred role: name; original member name unknown.
  const char *unknown30;                 // Inferred role: name; original member name unknown.
  const char *unknown38;                 // Inferred role: name; original member name unknown.
  f32 unknown40;                         // Inferred role: unknown; original member name unknown.
  f32 unknown44;                         // Inferred role: unknown; original member name unknown.
  f32 unknown48;                         // Inferred role: unknown; original member name unknown.
  u16 unknown4c;                         // Inferred role: unknown; original member name unknown.
  u8 _4e[0x50 - 0x4e];
  u64 unknown50; // Inferred role: unknown; original member name unknown.
  u16 unknown58; // Inferred role: unknown; original member name unknown.
  u8 _5a[0x60 - 0x5a];
  mm::Vec3 unknown60; // Inferred role: foot position; original member name unknown.
  u8 _70[0xa0 - 0x70];
  u32 unknowna0; // Inferred role: flags; original member name unknown.
  f32 unknowna4; // Inferred role: raycast up distance; original member name unknown.
  f32 unknowna8; // Inferred role: raycast down distance; original member name unknown.
  u8 _ac[0xb0 - 0xac];
  mm::Quat unknownb0; // Inferred role: ground angle; original member name unknown.
  mm::Quat unknownc0; // Inferred role: unknown; original member name unknown.
  u64 unknownd0;      // Inferred role: unknown; original member name unknown.
  u8 _d8[0xe0 - 0xd8];
};

static_assert(offsetof(FootPlacementIKSolver, unknown20) == 0x20, "");
static_assert(offsetof(FootPlacementIKSolver, unknown28) == 0x28, "");
static_assert(offsetof(FootPlacementIKSolver, unknown40) == 0x40, "");
static_assert(offsetof(FootPlacementIKSolver, unknown4c) == 0x4c, "");
static_assert(offsetof(FootPlacementIKSolver, unknown50) == 0x50, "");
static_assert(offsetof(FootPlacementIKSolver, unknown58) == 0x58, "");
static_assert(offsetof(FootPlacementIKSolver, unknown60) == 0x60, "");
static_assert(offsetof(FootPlacementIKSolver, unknowna4) == 0xa4, "");
static_assert(offsetof(FootPlacementIKSolver, unknowna8) == 0xa8, "");
static_assert(offsetof(FootPlacementIKSolver, unknownb0) == 0xb0, "");
static_assert(offsetof(FootPlacementIKSolver, unknownc0) == 0xc0, "");
static_assert(offsetof(FootPlacementIKSolver, unknownd0) == 0xd0, "");
static_assert(sizeof(FootPlacementIKSolver) == 0xe0, "");

void buildDescFromParam(ParamAdapter &param, anm::FootPlacementIKSolver::Description *description);

} // namespace fw
