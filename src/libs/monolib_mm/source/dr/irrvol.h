#pragma once
#include "types.h"

namespace mm {
struct Mat44;
} // namespace mm

namespace ml {
namespace irrvol {

void convertSHMatrix(mm::Mat44 &matrix, const f32 *coefficients);
void lerpSH(const f32 *from, const f32 *to, f32 ratio, f32 *result);

} // namespace irrvol
} // namespace ml
