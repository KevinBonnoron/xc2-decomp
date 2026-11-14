#pragma once
#include "types.h"

namespace mm {

struct Col3 {
  static const Col3 gray;   // Name from the game symbol _ZN2mm4Col34grayE; also in torna and xc1de.
  static const Col3 black;  // Name from the game symbol _ZN2mm4Col35blackE; also in torna and xc1de.
  static const Col3 red;    // Name from the game symbol _ZN2mm4Col33redE; also in torna and xc1de.
  static const Col3 green;  // Name from the game symbol _ZN2mm4Col35greenE; also in torna and xc1de.
  static const Col3 blue;   // Name from the game symbol _ZN2mm4Col34blueE; also in torna and xc1de.
  static const Col3 cyan;   // Name from the game symbol _ZN2mm4Col34cyanE; also in torna and xc1de.
  static const Col3 yellow; // Name from the game symbol _ZN2mm4Col36yellowE; also in torna and xc1de.

  Col3() {}
  Col3(f32 r, f32 g, f32 b) : r(r), g(g), b(b) {}

  Col3 operator+(const Col3 &color) const { return Col3(r + color.r, g + color.g, b + color.b); }

  friend Col3 operator*(f32 scale, const Col3 &color) { return Col3(scale * color.r, scale * color.g, scale * color.b); }

  f32 r;
  f32 g;
  f32 b;
};

} // namespace mm
