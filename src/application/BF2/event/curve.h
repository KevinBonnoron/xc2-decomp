#pragma once
#include "types.h"

namespace event {

enum CV_TYPE {
  CV_TYPE_STEP,
  CV_TYPE_LINEAR,
  CV_TYPE_EASE_IN_OUT,
  CV_TYPE_EASE_IN,
  CV_TYPE_EASE_OUT,
  CV_TYPE_EASE_IN_WEAK,
  CV_TYPE_EASE_OUT_WEAK,
};

class Curve {
public:
  static f32 getValue(CV_TYPE type, f32 rate);
};

} // namespace event
