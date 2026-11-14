#pragma once
#include "types.h"

namespace mm {
struct Mat44;
struct Vec4;
} // namespace mm

namespace ml {
namespace irrvol {

// Layout evidence: DrIrrVolMan keeps two of them 0x6c bytes apart (0xb8 and 0x124), and
// DrIrrVolCascade::updateIrrVolByGlobalProbe (1.0.0: 0x71007eaacc) indexes 0x24 byte entries of 9 floats.
struct SHTerms {
  f32 unknown00[3][9]; // Inferred role: spherical harmonics coefficients per colour channel; original member name unknown.
};

static_assert(sizeof(SHTerms) == 0x6c, "");

void convertSHMatrix(mm::Mat44 &matrix, const f32 *coefficients);
f32 calcIrradiance(const mm::Mat44 &matrix, const mm::Vec4 &normal);
void lerpSH(const f32 *from, const f32 *to, f32 ratio, f32 *result);

} // namespace irrvol
} // namespace ml
