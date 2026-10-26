#pragma once
#include <stddef.h>

#include "grlib/cglib_texture_buffer.h"
#include "mm_math/mm_aabb.h"
#include "mm_math/mm_vec3.h"
#include "types.h"

namespace ml {
namespace irrvol {

class DrIrrVolCascade {
public:
  u8 _000[0x560];
  mm::Aabb unknown560[2]; // Inferred role: volume area per buffer; original member name unknown.
  u8 _5a0[0x5b0 - 0x5a0];
  mm::Vec3 unknown5b0; // Inferred role: uv per pixel; original member name unknown.
  u8 _5c0[0x5d0 - 0x5c0];
  mm::Vec3 unknown5d0; // Inferred role: uv scale; original member name unknown.
  u32 unknown5e0;      // Inferred role: current buffer index; original member name unknown.
  u8 _5e4[0x5e8 - 0x5e4];
  grlib::CGLibTextureBuffer unknown5e8[2][3]; // Inferred role: irradiance volume textures per buffer; original member name unknown.
  u8 _888[0x8e0 - 0x888];
  mm::Vec3 unknown8e0; // Inferred role: eye offset; original member name unknown.
  mm::Vec3 unknown8f0; // Inferred role: uv offset; original member name unknown.
};

static_assert(offsetof(DrIrrVolCascade, unknown560) == 0x560, "");
static_assert(offsetof(DrIrrVolCascade, unknown5b0) == 0x5b0, "");
static_assert(offsetof(DrIrrVolCascade, unknown5d0) == 0x5d0, "");
static_assert(offsetof(DrIrrVolCascade, unknown5e0) == 0x5e0, "");
static_assert(offsetof(DrIrrVolCascade, unknown5e8) == 0x5e8, "");
static_assert(offsetof(DrIrrVolCascade, unknown8e0) == 0x8e0, "");
static_assert(offsetof(DrIrrVolCascade, unknown8f0) == 0x8f0, "");

} // namespace irrvol
} // namespace ml
