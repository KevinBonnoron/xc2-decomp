#pragma once
#include "types.h"

namespace mm {
struct Vec3;
} // namespace mm

namespace ptlib {
namespace renderer {

bool getSwtPos(const u32 *data, f32 frame, mm::Vec3 &position, bool &isFound);

} // namespace renderer
} // namespace ptlib
