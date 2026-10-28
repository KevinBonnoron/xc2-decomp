#pragma once
#include <stddef.h>

#include "anm/anm_array-inl.h"
#include "anm/anm_extra_truck.h"
#include "types.h"

namespace anm {

struct SerialiseArg;

class UncompressExtraTruck : public unknown002 {
public:
  explicit UncompressExtraTruck(const SerialiseArg &arg) : unknown18(arg) {}
  void sampleTrucks(f32 time, const Binding &binding, const ExtraBinding &extraBinding, u32 count, f32 *values) const override;

  Array<f32> unknown18; // Inferred role: values of each truck for each frame; original member name unknown.
};

static_assert(offsetof(UncompressExtraTruck, unknown18) == 0x18, "");

} // namespace anm
