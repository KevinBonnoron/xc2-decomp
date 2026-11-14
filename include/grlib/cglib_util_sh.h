#pragma once
#include "types.h"

namespace mm {
struct Vec3;
} // namespace mm

namespace grlib {

class CGLibUtilSH {
public:
  static void TexelCoordToVect(mm::Vec3 &vector, int face, f32 u, f32 v, int size);
  static f32 TexelCoordSolidAngle(int face, f32 u, f32 v, int size);
};

} // namespace grlib
