#pragma once
#include "anm/anm_array-inl.h"
#include "types.h"

namespace anm {

// Cubic polynomial piece of an extra truck: the start time, then the cubic, quadratic, linear and constant terms.
struct CubicCurve {
  f32 unknown00;
  f32 unknown04[4];
};

static_assert(sizeof(CubicCurve) == 0x14, "");

void calcValue(const Array<CubicCurve> &curves, f32 time, f32 *pOut);

} // namespace anm
