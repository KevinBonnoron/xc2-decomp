#pragma once
#include "types.h"

namespace mm {
struct Mat44;
} // namespace mm

namespace grlib {

void ShdF32TransposeMat34(f32 *destination, const f32 *source);
void ShdMat44TransposeMat34(f32 *destination, const mm::Mat44 &source);
void ShdMat44TransposeMat44(f32 *destination, const mm::Mat44 &source);
void ShdF32SetF32Array(f32 *destination, const f32 *source, int count);
void ShdF32SetVec4(f32 *destination, const f32 *source);

} // namespace grlib
