#pragma once
#include <math.h>

#include "mm_math/mm_math.h"
#include "types.h"

namespace ui {

enum CURVE_TYPE {
  CURVE_TYPE_LINEAR = 0,
  CURVE_TYPE_SIN90 = 1,
  CURVE_TYPE_SIN90_REV = 2,
  CURVE_TYPE_LINEAR_LOOP = 3,
  CURVE_TYPE_SIN180 = 4,
  CURVE_TYPE_SIN180_REV = 5,
};

class UICtrlCurve {
public:
  virtual f32 calc(f32 time, f32 start, f32 end, f32 duration) const = 0;
};

class UICtrlCurveLinear : public UICtrlCurve {
public:
  virtual f32 calc(f32 time, f32, f32, f32 duration) const { return time / duration; }
};

class UICtrlCurveLinearLoop : public UICtrlCurve {
public:
  virtual f32 calc(f32 time, f32, f32, f32 duration) const {
    f32 rate = time / (duration * 0.5f);
    return rate < 1.0f ? rate : 2.0f - rate;
  }
};

class UICtrlCurveSin90 : public UICtrlCurve {
public:
  virtual f32 calc(f32 time, f32 start, f32 end, f32 duration) const {
    return (end - start) * sinf(time / duration * 90.0f * mm::DEG_TO_RAD) + start;
  }
};

class UICtrlCurveSin180 : public UICtrlCurve {
public:
  virtual f32 calc(f32 time, f32 start, f32 end, f32 duration) const {
    return (end - start) * sinf(time / duration * 180.0f * mm::DEG_TO_RAD) + start;
  }
};

class UICtrlCurveSin90Rev : public UICtrlCurve {
public:
  virtual f32 calc(f32 time, f32 start, f32 end, f32 duration) const {
    return (end - start) * (1.0f - sinf((time / duration * 90.0f + 90.0f) * mm::DEG_TO_RAD)) + start;
  }
};

class UICtrlCurveSin180Rev : public UICtrlCurve {
public:
  virtual f32 calc(f32 time, f32 start, f32 end, f32 duration) const {
    return (end - start) * (1.0f - fabsf(sinf((time / duration * 180.0f + 90.0f) * mm::DEG_TO_RAD))) + start;
  }
};

} // namespace ui
