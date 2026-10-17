#pragma once
#include <stddef.h>

#include "mm_math/mm_quat.h"
#include "mm_math/mm_vec4.h"

namespace mm {
struct Vec3;
} // namespace mm

namespace anm {

struct alignas(16) QsTransform {
  QsTransform() {}
  QsTransform(const mm::Vec3 &translation, const mm::Quat &rotation, const mm::Vec3 &scale)
      : translation(translation, 1.0f), rotation(rotation), scale(scale, 1.0f) {}

  mm::Vec4 translation;
  mm::Quat rotation;
  mm::Vec4 scale;
};

static_assert(offsetof(QsTransform, rotation) == 0x10, "");
static_assert(offsetof(QsTransform, scale) == 0x20, "");
static_assert(sizeof(QsTransform) == 0x30, "");

} // namespace anm
