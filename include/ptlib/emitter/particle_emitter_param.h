#pragma once
#include <stddef.h>

#include "mm_math/mm_col3.h"
#include "mm_math/mm_col4.h"
#include "mm_math/mm_pnt.h"
#include "mm_math/mm_vec3.h"
#include "types.h"

namespace ptlib {
namespace emitter {

// Inferred role: transform block copied between an EmitterParam and an EmitterObj; original name unknown.
struct unknown001 {
  u8 _00[0x30 - 0x00];
  mm::Vec3 unknown30; // Inferred role: position; original member name unknown.
};

static_assert(offsetof(unknown001, unknown30) == 0x30, "");
static_assert(sizeof(unknown001) == 0x40, "");

struct EmitterParam {
  unknown001 unknown00; // Inferred role: transform; original member name unknown.
  mm::Col4 unknown40;   // Inferred role: color, the alpha of an emitter's is read by the draw sort; original member name unknown.
  mm::Col3 unknown50;   // Inferred role: copied to the emitter; original member name unknown.
  u8 _5c[0x60 - 0x5c];
  mm::Pnt<f32> unknown60; // Inferred role: copied to the emitter; original member name unknown.
  f32 unknown68;          // Inferred role: gpu check radius, 0 to disable; original member name unknown.
  f32 unknown6c;          // Inferred role: scale; original member name unknown.
  s8 unknown70;           // Inferred role: priority offset; original member name unknown.
  u8 unknown71;           // Inferred role: disp; original member name unknown.
  u8 unknown72;           // Inferred role: no wait; original member name unknown.
  u8 unknown73;           // Original member name unknown.
  u16 unknown74;          // Inferred role: copied to the emitter; original member name unknown.
  u8 unknown76;           // Inferred role: copied to the emitter; original member name unknown.
  u8 unknown77;           // Inferred role: copied to the emitter; original member name unknown.
  f32 speed;              // Inferred role: negative to keep. Evidence: name from the assertion string "math::isFinite(m_param.speed)" in EmitterObj::update.
  f32 unknown7c;          // Inferred role: skip frame; original member name unknown.
  f32 unknown80;          // Inferred role: copied to the emitter; original member name unknown.
  f32 unknown84;          // Inferred role: copied to the emitter; original member name unknown.
  f32 unknown88;          // Inferred role: copied to the emitter; original member name unknown.
  f32 unknown8c;          // Inferred role: copied to the emitter; original member name unknown.
  u32 unknown90;          // Inferred role: category, -1 to keep; original member name unknown.
  u8 unknown94;           // Inferred role: copied to the emitter; original member name unknown.
};

static_assert(offsetof(EmitterParam, unknown40) == 0x40, "");
static_assert(offsetof(EmitterParam, unknown50) == 0x50, "");
static_assert(offsetof(EmitterParam, unknown60) == 0x60, "");
static_assert(offsetof(EmitterParam, unknown68) == 0x68, "");
static_assert(offsetof(EmitterParam, unknown70) == 0x70, "");
static_assert(offsetof(EmitterParam, unknown74) == 0x74, "");
static_assert(offsetof(EmitterParam, speed) == 0x78, "");
static_assert(offsetof(EmitterParam, unknown80) == 0x80, "");
static_assert(offsetof(EmitterParam, unknown90) == 0x90, "");
static_assert(offsetof(EmitterParam, unknown94) == 0x94, "");

static_assert(offsetof(EmitterParam, unknown7c) == 0x7c, "");
static_assert(sizeof(EmitterParam) == 0xa0, "");

} // namespace emitter
} // namespace ptlib
