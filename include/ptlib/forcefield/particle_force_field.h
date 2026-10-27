#pragma once
#include <stddef.h>

#include "mm_math/mm_vec3.h"
#include "types.h"

namespace ptlib {
namespace forcefield {

struct alignas(16) AddForceParam {
  u64 unknown00;      // Role and original member name unknown.
  mm::Vec3 unknown10; // Role and original member name unknown.
  mm::Vec3 unknown20; // Role and original member name unknown.
  f32 unknown30;      // Role and original member name unknown.
};

static_assert(offsetof(AddForceParam, unknown10) == 0x10, "");
static_assert(offsetof(AddForceParam, unknown20) == 0x20, "");
static_assert(offsetof(AddForceParam, unknown30) == 0x30, "");
static_assert(sizeof(AddForceParam) == 0x40, "");

} // namespace forcefield
} // namespace ptlib
