#pragma once
#include "types.h"

namespace mm {

struct Col3 {
  static const Col3 black;
  static const Col3 yellow;

  Col3() {}
  Col3(f32 r, f32 g, f32 b) : r(r), g(g), b(b) {}

  f32 r;
  f32 g;
  f32 b;
};

} // namespace mm
