#pragma once
#include "types.h"

namespace ptlib {
namespace forcefield {

struct alignas(16) AddForceParam {
  u8 _00[0x40 - 0x00];
};

static_assert(sizeof(AddForceParam) == 0x40, "");

} // namespace forcefield
} // namespace ptlib
