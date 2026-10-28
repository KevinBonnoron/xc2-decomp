#include "anm/anm_cubic_animation.h"

#include <algorithm>

#include "anm/anm_array.h"
#include "mm/mm_std_base.h"

namespace anm {
struct SerialiseArg;

CubicAnimation::CubicAnimation(mm::mtl::IAllocator *pAllocator) : Animation(pAllocator) {}

CubicAnimation::CubicAnimation(const SerialiseArg &arg) : Animation(arg), unknown48(arg) {}

void calcVec3(const Array<Cubic3Curve> &curves, f32 time, f32 *pOut) {
  ArrayIterartor<const Cubic3Curve> it = std::upper_bound(curves.begin(), curves.end(), time, CmpCubic());
  u32 index;
  if (it == curves.end()) {
    index = curves.size() - 1;
  } else if (it == curves.begin()) {
    index = 0;
  } else {
    index = (it - 1) - curves.begin();
  }
  const Cubic3Curve &curve = curves[index];
  f32 frame = time - curve.unknown00;
  MM_ASSERT(frame >= 0.0f);
  f32 frame2 = frame * frame;
  f32 frame3 = frame * frame2;
  pOut[0] = (frame3 * curve.unknown04[0] + frame2 * curve.unknown04[1] + frame * curve.unknown04[2]) + curve.unknown04[3];
  pOut[1] = (frame3 * curve.unknown04[4] + frame2 * curve.unknown04[5] + frame * curve.unknown04[6]) + curve.unknown04[7];
  pOut[2] = (frame3 * curve.unknown04[8] + frame2 * curve.unknown04[9] + frame * curve.unknown04[10]) + curve.unknown04[11];
}

s32 CubicAnimation::getImplType() const { return 1; }

} // namespace anm
