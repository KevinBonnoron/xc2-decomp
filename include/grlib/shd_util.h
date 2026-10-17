#pragma once
#include "types.h"

namespace mm {
struct Col3;
struct Col4;
struct Mat44;
struct Vec3;
struct Vec4;
} // namespace mm

namespace grlib {

void ShdInstancePosMatrix3x4Set(f32 *destination, const mm::Mat44 &source, f32 value);
void ShdF32SetMat44(f32 *destination, const f32 *source);
void ShdF32TransposeMat34(f32 *destination, const f32 *source);
void ShdF32TransposeMat44(f32 *destination, const f32 *source);
void ShdMat44SetMat44(f32 *destination, const mm::Mat44 &source);
void ShdMat44SetMat34(f32 *destination, const mm::Mat44 &source);
void ShdMat44TransposeMat34(f32 *destination, const mm::Mat44 &source);
void ShdMat44TransposeMat44(f32 *destination, const mm::Mat44 &source);
void ShdMat44SetMat44Array(f32 *destination, const mm::Mat44 *source, int count);
void ShdMat44TransposeMat34Array(f32 *destination, const mm::Mat44 *source, int count);
void ShdMat44TransposeMat44Array(f32 *destination, const mm::Mat44 *source, int count);
void ShdF32SetF32Array(f32 *destination, const f32 *source, int count);
void ShdF32SetVec2(f32 *destination, const f32 *source);
void ShdF32SetVec3(f32 *destination, const f32 *source);
void ShdF32SetVec4(f32 *destination, const f32 *source);
void ShdVec3SetVec3(f32 *destination, const mm::Vec3 &source);
void ShdVec4SetVec4(f32 *destination, const mm::Vec4 &source);
void ShdCol3SetVec3(f32 *destination, const mm::Col3 &source);
void ShdCol4SetVec4(f32 *destination, const mm::Col4 &source);
void ShdUniformS32SetS32Array(int *destination, const int *source, int count);
void ShdS32SetIVec4(int *destination, const int *source);
void ShdU32SetUVec4(u32 *destination, const u32 *source);

} // namespace grlib
