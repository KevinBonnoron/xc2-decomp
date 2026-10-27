#pragma once
#include "types.h"

namespace mm {

struct Col4 {
  static const Col4 zero;
  static const Col4 black;
  static const Col4 white;
  static const Col4 red;
  static const Col4 green;
  static const Col4 blue;
  static const Col4 cyan;
  static const Col4 yellow;
  static const Col4 gray;

  Col4() {}
  Col4(f32 r, f32 g, f32 b, f32 a) : r(r), g(g), b(b), a(a) {}

  f32 r;
  f32 g;
  f32 b;
  f32 a;
};

} // namespace mm
