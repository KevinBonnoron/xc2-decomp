#pragma once
#include "mm_math/mm_quat.h"
#include "mm_math/mm_vec3.h"

namespace fw {

struct Transform {
  mm::Vec3 position;
  mm::Quat rotation;
};

static_assert(sizeof(Transform) == 0x20, "");

} // namespace fw
