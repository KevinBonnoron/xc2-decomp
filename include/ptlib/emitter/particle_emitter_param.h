#pragma once
#include <stddef.h>

#include "mm_math/mm_vec3_na.h"
#include "types.h"

namespace ptlib {
namespace emitter {

// Inferred role: transform block copied between an EmitterParam and an EmitterObj; original name unknown.
struct unknown001 {
  u8 _00[0x30 - 0x00];
  mm::Vec3NA unknown30; // Inferred role: position; original member name unknown.
  u8 _3c[0x40 - 0x3c];
};

static_assert(offsetof(unknown001, unknown30) == 0x30, "");
static_assert(sizeof(unknown001) == 0x40, "");

struct EmitterParam {
  unknown001 unknown00; // Inferred role: transform; original member name unknown.
  u8 _40[0x7c - 0x40];
  f32 unknown7c; // Inferred role: skip frame; original member name unknown.
};

static_assert(offsetof(EmitterParam, unknown7c) == 0x7c, "");

} // namespace emitter
} // namespace ptlib
