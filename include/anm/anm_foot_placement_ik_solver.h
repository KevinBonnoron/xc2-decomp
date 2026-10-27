#pragma once
#include <stddef.h>

#include "anm/anm_reference_object.h"
#include "types.h"

namespace anm {

class FootPlacementIKSolver : public ReferenceObject {
public:
  struct Description {
    u8 _00[0x48];
    f32 unknown48; // Inferred role: raycast distance; original member name unknown.
    f32 unknown4c; // Inferred role: raycast distance; original member name unknown.
    f32 unknown50; // Inferred role: unknown; original member name unknown.
    f32 unknown54; // Inferred role: base distance; original member name unknown.
  };

  u8 _18[0x2c - 0x18];
  u16 unknown2c; // Inferred role: foot bone index; original member name unknown.
  u8 _2e[0x70 - 0x2e];
  f32 unknown70; // Inferred role: raycast up distance; original member name unknown.
  f32 unknown74; // Inferred role: raycast down distance; original member name unknown.
};

static_assert(offsetof(FootPlacementIKSolver::Description, unknown48) == 0x48, "");
static_assert(offsetof(FootPlacementIKSolver::Description, unknown54) == 0x54, "");
static_assert(offsetof(FootPlacementIKSolver, unknown2c) == 0x2c, "");
static_assert(offsetof(FootPlacementIKSolver, unknown70) == 0x70, "");
static_assert(offsetof(FootPlacementIKSolver, unknown74) == 0x74, "");

} // namespace anm
