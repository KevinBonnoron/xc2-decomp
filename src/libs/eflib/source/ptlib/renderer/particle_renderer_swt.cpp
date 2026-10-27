#include "ptlib/renderer/particle_renderer_swt.h"

#include <stddef.h>

#include "mm_math/mm_vec3.h"

namespace ptlib {
namespace renderer {

namespace {

// Inferred role: header of a locus point followed by its frames of four s16 values; original name unknown.
struct unknown001 {
  u8 _00[0x26 - 0x00];
  s16 unknown26[]; // Inferred role: x, y, z (in thousandths) and padding of each frame; original member name unknown.
};

static_assert(offsetof(unknown001, unknown26) == 0x26, "");

} // namespace

bool getSwtPos(const u32 *data, f32 frame, mm::Vec3 &position, bool &isFound) {
  const unknown001 *locus = reinterpret_cast<const unknown001 *>(data);
  u32 index = static_cast<u32>(frame) << 2;
  const s16 *values = &locus->unknown26[index];
  s16 y = values[1];
  s16 z = values[2];
  position.x = values[0] / 1000.0f;
  position.y = y / 1000.0f;
  position.z = z / 1000.0f;
  return true;
}

} // namespace renderer
} // namespace ptlib
