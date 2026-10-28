#include "anm/anm_cubic_extra_truck.h"

#include <algorithm>

#include "anm/anm_array-inl.h"
#include "anm/anm_array.h"
#include "anm/anm_cubic_animation.h"
#include "mm/mm_std_base.h"

namespace anm {

void calcValue(const Array<CubicCurve> &curves, f32 time, f32 *pOut) {
  ArrayIterartor<const CubicCurve> it = std::upper_bound(curves.begin(), curves.end(), time, CmpCubic());
  u32 index;
  if (it == curves.end()) {
    index = curves.size() - 1;
  } else if (it == curves.begin()) {
    index = 0;
  } else {
    index = (it - 1) - curves.begin();
  }
  const CubicCurve &curve = curves[index];
  f32 frame = time - curve.unknown00;
  MM_ASSERT(frame >= 0.0f);
  *pOut = (frame * frame * frame * curve.unknown04[0] + frame * frame * curve.unknown04[1] + frame * curve.unknown04[2]) + curve.unknown04[3];
}

} // namespace anm
