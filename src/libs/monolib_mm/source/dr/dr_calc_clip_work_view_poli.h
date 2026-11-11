#pragma once
#include <stddef.h>

#include "dr/dr_calc_clip_work.h"
#include "mm_math/mm_vec3.h"
#include "types.h"

namespace ml {

class DrCalcClipWorkViewPoli : public DrCalcClipWork {
public:
  DrCalcClipWorkViewPoli();
  ~DrCalcClipWorkViewPoli();
  // The second argument is a direction, not an end point: the game's clipLineTest (0x71008a9db0) intersects start + direction * t with the
  // planes and scales it by 2000 for checkLineNeraPointGet.
  bool clipLineTest(const mm::Vec3 &start, const mm::Vec3 &direction, f32 radius) const override;

  // Game symbol _ZN2ml22DrCalcClipWorkViewPoli21checkLineNeraPointGetERN2mm4Vec3ES3_RKS2_S5_S5_S5_ (0x71008a99d4, not decompiled yet).
  // clipLineTest calls it with six register arguments and no `this`, so it is static. The parameter roles are inferred from that call: the
  // closest points of the line (position, corner direction) and of the line (start, scaled direction); original parameter names unknown.
  static void checkLineNeraPointGet(mm::Vec3 &closest1, mm::Vec3 &closest2, const mm::Vec3 &line1Point, const mm::Vec3 &line1Direction, const mm::Vec3 &line2Point, const mm::Vec3 &line2Direction);

  // Layout evidence: setMatrix (0x71008a8cec) writes these members and clipLineTest (0x71008a9db0) reads them.
  mm::Vec3 unknown10;     // Inferred role: view position, the Vec3 argument of setMatrix; original member name unknown.
  mm::Vec3 unknown20[4];  // Inferred role: view volume corners computed by setMatrix; original member name unknown.
  mm::Vec3 unknown60[4];  // Inferred role: side plane normals (cross products of neighbouring corner directions); original member name unknown.
  mm::Vec3 unknownA0[4];  // Inferred role: directions from the view position to the corners; original member name unknown.
  mm::Vec3 unknownE0[4];  // Inferred role: first edge test normals, filled by createLineNormal; original member name unknown.
  mm::Vec3 unknown120[4]; // Inferred role: second edge test normals, filled by createLineNormal; original member name unknown.
  f32 unknown160[4];      // Inferred role: side plane distances (view position dotted with the normals); original member name unknown.
};

static_assert(offsetof(DrCalcClipWorkViewPoli, unknown10) == 0x10, "");
static_assert(offsetof(DrCalcClipWorkViewPoli, unknown20) == 0x20, "");
static_assert(offsetof(DrCalcClipWorkViewPoli, unknown60) == 0x60, "");
static_assert(offsetof(DrCalcClipWorkViewPoli, unknownA0) == 0xa0, "");
static_assert(offsetof(DrCalcClipWorkViewPoli, unknownE0) == 0xe0, "");
static_assert(offsetof(DrCalcClipWorkViewPoli, unknown120) == 0x120, "");
static_assert(offsetof(DrCalcClipWorkViewPoli, unknown160) == 0x160, "");

} // namespace ml
