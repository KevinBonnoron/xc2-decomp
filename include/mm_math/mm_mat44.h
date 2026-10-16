#pragma once
#include "types.h"

namespace mm {

struct alignas(16) Mat44 {
  static const Mat44 identity;

  f32 rows[4][4];
};

static_assert(sizeof(Mat44) == 0x40, "");

} // namespace mm
