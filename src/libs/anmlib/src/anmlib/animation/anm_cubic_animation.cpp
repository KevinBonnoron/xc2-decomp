#include "anm/anm_cubic_animation.h"

#include <algorithm>
#include <math.h>

#include "anm/anm_array.h"
#include "anm/anm_binding.h"
#include "anm/anm_qs_transform.h"
#include "mm/mm_std_base.h"
#include "mm_math/mm_quat.h"
#include "mm_math/mm_vec4.h"

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

void calcQuat(const Array<Cubic4Curve> &curves, f32 time, mm::Quat *pOut) {
  ArrayIterartor<const Cubic4Curve> it = std::upper_bound(curves.begin(), curves.end(), time, CmpCubic());
  u32 index;
  if (it == curves.end()) {
    index = curves.size() - 1;
  } else if (it == curves.begin()) {
    index = 0;
  } else {
    index = (it - 1) - curves.begin();
  }
  const Cubic4Curve &curve = curves[index];
  f32 frame = time - curve.unknown00;
  MM_ASSERT(frame >= 0.0f);
  f32 frame2 = frame * frame;
  f32 frame3 = frame * frame2;
  pOut->x = (frame3 * curve.unknown04[0] + frame2 * curve.unknown04[1] + frame * curve.unknown04[2]) + curve.unknown04[3];
  pOut->y = (frame3 * curve.unknown04[4] + frame2 * curve.unknown04[5] + frame * curve.unknown04[6]) + curve.unknown04[7];
  pOut->z = (frame3 * curve.unknown04[8] + frame2 * curve.unknown04[9] + frame * curve.unknown04[10]) + curve.unknown04[11];
  pOut->w = (frame3 * curve.unknown04[12] + frame2 * curve.unknown04[13] + frame * curve.unknown04[14]) + curve.unknown04[15];
  f32 scale = 1.0f / sqrtf(pOut->x * pOut->x + pOut->y * pOut->y + pOut->z * pOut->z + pOut->w * pOut->w);
  pOut->x = pOut->x * scale;
  pOut->y = scale * pOut->y;
  pOut->z = scale * pOut->z;
  pOut->w = scale * pOut->w;
}

void CubicAnimation::sampleTrucks(f32 time, const Binding &binding, QsTransform *transforms) const {
  f32 frame = unknown010(time);
  u32 count = binding.m_indexTable.size();
  for (u32 i = 0; i < count; i++) {
    s16 index = binding.m_indexTable[i];
    if (index >= 0) {
      const unknown004 &curves = unknown48[index];
      calcVec3(curves.unknown00, frame, &transforms[i].unknown00.x);
      transforms[i].unknown00.w = 1.0f;
      calcQuat(curves.unknown10, frame, &transforms[i].unknown10);
      calcVec3(curves.unknown20, frame, &transforms[i].unknown20.x);
      transforms[i].unknown20.w = 1.0f;
    }
  }
}

s32 CubicAnimation::getImplType() const { return 1; }

} // namespace anm
