#pragma once
#include <stddef.h>

#include "anm/anm_array-inl.h"
#include "anm/anm_extra_truck.h"
#include "types.h"

namespace anm {

struct SerialiseArg;

// Cubic polynomial piece of an extra truck: the start time, then the cubic, quadratic, linear and constant terms.
struct CubicCurve {
  f32 unknown00;
  f32 unknown04[4];
};

static_assert(sizeof(CubicCurve) == 0x14, "");

class CubicExtraTruck : public unknown002 {
public:
  explicit CubicExtraTruck(const SerialiseArg &arg) : unknown18(arg) {}
  void sampleTrucks(f32 time, const Binding &binding, const ExtraBinding &extraBinding, u32 count, f32 *values) const override;

  Array<Array<CubicCurve>> unknown18; // Inferred role: curves of each truck; original member name unknown.
};

static_assert(offsetof(CubicExtraTruck, unknown18) == 0x18, "");

void calcValue(const Array<CubicCurve> &curves, f32 time, f32 *pOut);

} // namespace anm
