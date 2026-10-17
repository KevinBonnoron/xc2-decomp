#pragma once
#include "types.h"

namespace grlib {

void ShdF32TransposeMat34(f32 *destination, const f32 *source);
void ShdF32SetF32Array(f32 *destination, const f32 *source, int count);

} // namespace grlib
