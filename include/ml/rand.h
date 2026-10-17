#pragma once
#include "types.h"

namespace ml {

void mtInit(u32 seed);
int mtRand();
int mtRand(int max);
int mtRand(int min, int max);
f32 mtRandf1();
f32 mtRandf1(f32 max);
f32 mtRandf1(f32 min, f32 max);
f32 mtRandf2();
f32 mtRandf2(f32 max);
f32 mtRandf2(f32 min, f32 max);
f32 mtRandf3();
f32 mtRandf3(f32 max);
f32 mtRandf3(f32 min, f32 max);

} // namespace ml
