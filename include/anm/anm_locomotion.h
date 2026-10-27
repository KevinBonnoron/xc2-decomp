#pragma once
#include <stddef.h>

#include "anm/anm_array-inl.h"
#include "mm_math/mm_vec3.h"
#include "types.h"

namespace mm {
struct Vec4;
} // namespace mm

namespace anm {

struct QsTransform;

class Locomotion {
public:
  void getReference(f32 time, QsTransform *transform) const;
  void getDeltaReference(f32 previousTime, f32 time, f32 start, f32 end, bool looped, QsTransform *transform) const;

  mm::Vec3 unknown00;        // Inferred role: rotation axis; original member name unknown.
  f32 unknown10;             // Inferred role: key interval; original member name unknown.
  Array<mm::Vec4> unknown18; // Inferred role: keys (position, rotation angle); original member name unknown.
};

static_assert(offsetof(Locomotion, unknown10) == 0x10, "");
static_assert(offsetof(Locomotion, unknown18) == 0x18, "");

} // namespace anm
