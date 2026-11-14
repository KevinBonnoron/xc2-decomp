#pragma once
#include "types.h"

namespace mm {

struct Col4 {
  static const Col4 zero;   // Name from the game symbol _ZN2mm4Col44zeroE; also in torna and xc1de.
  static const Col4 black;  // Name from the game symbol _ZN2mm4Col45blackE; also in torna and xc1de.
  static const Col4 white;  // Name from the game symbol _ZN2mm4Col45whiteE; also in torna and xc1de.
  static const Col4 red;    // Name from the game symbol _ZN2mm4Col43redE; also in torna and xc1de.
  static const Col4 green;  // Name from the game symbol _ZN2mm4Col45greenE; also in torna and xc1de.
  static const Col4 blue;   // Name from the game symbol _ZN2mm4Col44blueE; also in torna and xc1de.
  static const Col4 cyan;   // Name from the game symbol _ZN2mm4Col44cyanE; also in torna and xc1de.
  static const Col4 yellow; // Name from the game symbol _ZN2mm4Col46yellowE; also in torna and xc1de.
  static const Col4 gray;   // Name from the game symbol _ZN2mm4Col44grayE; also in torna and xc1de.

  Col4() {}
  Col4(f32 r, f32 g, f32 b, f32 a) : r(r), g(g), b(b), a(a) {}

  f32 r;
  f32 g;
  f32 b;
  f32 a;
};

} // namespace mm
