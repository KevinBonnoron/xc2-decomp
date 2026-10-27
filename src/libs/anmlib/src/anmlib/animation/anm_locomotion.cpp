#include "anm/anm_locomotion.h"

#include "anm/anm_qs_transform.h"
#include "anm/anm_transform_util.h"
#include "mm_math/mm_math.h"
#include "mm_math/mm_vec4.h"

namespace anm {

void Locomotion::getDeltaReference(f32 previousTime, f32 time, f32 start, f32 end, bool looped, QsTransform *transform) const {
  f32 from = mm::clamp(previousTime, start, end);
  f32 to = from + time;
  u32 loopCount;
  if (looped) {
    loopCount = static_cast<u32>(to / (end - start));
    to = to - (end - start) * loopCount;
  } else {
    to = to < end ? to : end;
    loopCount = 0;
  }
  QsTransform inverse;
  QsTransform fromReference;
  QsTransform toReference;
  QsTransform endReference;
  QsTransform accumulated;
  QsTransform tail;
  getReference(from, &fromReference);
  getReference(to, &toReference);
  if (loopCount == 0) {
    TransformUtil::invert(fromReference, &inverse);
    TransformUtil::mul(inverse, toReference, transform);
  } else {
    getReference(end, &endReference);
    TransformUtil::invert(fromReference, &inverse);
    TransformUtil::mul(inverse, endReference, &accumulated);
    for (u32 i = 1; i < loopCount; i++) {
      TransformUtil::mul(accumulated, endReference, &accumulated);
    }
    getReference(start, &fromReference);
    TransformUtil::invert(fromReference, &inverse);
    TransformUtil::mul(inverse, toReference, &tail);
    TransformUtil::mul(accumulated, tail, transform);
  }
  transform->unknown20 = mm::Vec4::unit;
}

} // namespace anm
