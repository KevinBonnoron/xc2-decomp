#pragma once
#include "mm_math/mm_quat.h"
#include "mm_math/mm_vec3.h"

namespace fw {

struct Transform {
  static void mul(const Transform &transform, const Transform &other, Transform *result);
  static void invert(const Transform &transform, Transform *result);

  mm::Vec3 position;
  mm::Quat rotation;
};

static_assert(sizeof(Transform) == 0x20, "");

} // namespace fw
