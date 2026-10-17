#pragma once
#include <stddef.h>

#include "mm_math/mm_quat.h"
#include "mm_math/mm_vec3.h"
#include "types.h"

namespace anm {

struct alignas(16) QsTransform {
  QsTransform() {}
  QsTransform(const mm::Vec3 &translation, const mm::Quat &rotation, const mm::Vec3 &scale)
      : translation{translation.x, translation.y, translation.z, 1.0f}, rotation(rotation), scale{scale.x, scale.y, scale.z, 1.0f} {}

  f32 translation[4];
  mm::Quat rotation;
  f32 scale[4];
};

static_assert(offsetof(QsTransform, rotation) == 0x10, "");
static_assert(offsetof(QsTransform, scale) == 0x20, "");
static_assert(sizeof(QsTransform) == 0x30, "");

} // namespace anm
