#include "event/curve.h"

namespace event {

static inline f32 bezier(f32 rate, f32 point0, f32 point1, f32 point2, f32 point3) {
  f32 rate2 = rate * rate;
  f32 rate3 = rate2 * rate;
  f32 weight0 = -rate3 + 3.0f * rate2 - 3.0f * rate + 1.0f;
  f32 weight1 = 3.0f * rate3 - 6.0f * rate2 + 3.0f * rate;
  f32 weight2 = 3.0f * rate2 - 3.0f * rate3;
  f32 weight3 = rate3;
  return weight0 * point0 + weight1 * point1 + weight2 * point2 + weight3 * point3;
}

f32 Curve::getValue(CV_TYPE type, f32 rate) {
  switch (type) {
  case CV_TYPE_STEP:
    return rate < 1.0f ? 0.0f : 1.0f;
  case CV_TYPE_LINEAR:
    return rate;
  case CV_TYPE_EASE_IN_OUT:
    return bezier(rate, 0.0f, 0.0f, 1.0f, 1.0f);
  case CV_TYPE_EASE_IN:
    return bezier(rate, 0.0f, 0.0f, 0.1f, 1.0f);
  case CV_TYPE_EASE_OUT:
    return bezier(rate, 0.0f, 0.9f, 1.0f, 1.0f);
  case CV_TYPE_EASE_IN_WEAK:
    return bezier(rate, 0.0f, 0.0f, 0.66f, 1.0f);
  case CV_TYPE_EASE_OUT_WEAK:
    return bezier(rate, 0.0f, 0.33f, 1.0f, 1.0f);
  }
  return rate;
}

} // namespace event
