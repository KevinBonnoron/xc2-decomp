#pragma once
#include <stddef.h>

#include "mm_math/mm_vec3.h"

namespace mm {

// Name from the game symbol _ZNK2mm3Obb8getCrossERNS_4Vec3ES2_RKNS_4LineE.
// Layout evidence: mm::Obb::getCross(Vec3 &, Vec3 &, const Line &) (1.0.0: 0x71009b6f28) reads two vectors,
// and the Line2 overload (0x71009b7258) fills them with the normalized direction and the end point of the segment.
struct Line {
  Vec3 unknown00; // Inferred role: direction of the line; original member name unknown.
  Vec3 unknown10; // Inferred role: a point of the line; original member name unknown.
};

static_assert(offsetof(Line, unknown10) == 0x10, "");
static_assert(sizeof(Line) == 0x20, "");

} // namespace mm
