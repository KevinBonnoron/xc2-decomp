#pragma once
#include "types.h"

namespace anm {

struct QsTransform;

class Locomotion {
public:
  void getReference(f32 time, QsTransform *transform) const;
  void getDeltaReference(f32 previousTime, f32 time, f32 start, f32 end, bool looped, QsTransform *transform) const;
};

} // namespace anm
