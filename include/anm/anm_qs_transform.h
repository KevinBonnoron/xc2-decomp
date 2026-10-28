#pragma once
#include <stddef.h>

#include "mm_math/mm_quat.h"
#include "mm_math/mm_vec4.h"

namespace mm {
struct Vec3;
} // namespace mm

namespace anm {

struct alignas(16) QsTransform {
  // Defaulted: value-initialization in Vector zero-fills the elements, as in the game.
  QsTransform() = default;
  QsTransform(const mm::Vec3 &translation, const mm::Quat &rotation, const mm::Vec3 &scale) : unknown00(translation, 1.0f), unknown10(rotation), unknown20(scale, 1.0f) {}

  mm::Vec4 unknown00; // Inferred role: translation; original member name unknown.
  mm::Quat unknown10; // Inferred role: rotation; original member name unknown.
  mm::Vec4 unknown20; // Inferred role: scale; original member name unknown.
};

static_assert(offsetof(QsTransform, unknown10) == 0x10, "");
static_assert(offsetof(QsTransform, unknown20) == 0x20, "");
static_assert(sizeof(QsTransform) == 0x30, "");

} // namespace anm
